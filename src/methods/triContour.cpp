#include <neurostr/methods/triContour.h>
#include <algorithm>
namespace neurostr{
namespace methods{
  
    /**
   * @brief Given two contours, reorients them in counter clockwise order. 
   * Also applies a rotation to ensure that the two first nodes are the closest ones.
   * @param a First contour
   * @param b Second contour
   */
  void align_contours( Contour& a, Contour& b, int component){
    
    // Fix orientation
    if( a.clockwise_oriented(component)) a.reverse();
    if( b.clockwise_oriented(component)) b.reverse();
    
    // Really unefficient
    float min_dist = std::numeric_limits<float>::max();
    Contour::iterator min_a,min_b;
    float d;
    
    // Search the closest points
    for(auto it_a = a.begin(); it_a != a.end(); ++it_a){
      for(auto it_b = b.begin(); it_b != b.end(); ++it_b){
          d = geometry::distance(*it_a,*it_b);
          if(d < min_dist){
            min_dist = d;
            min_a = it_a;
            min_b = it_b;
          }
      }
    }
    
    // Align them
    a.rotate(min_a);
    b.rotate(min_b);
    
    return ;
  }
  
  /**
   * @brief Closes the contour 
   * @param a Contour
   * @return Set of triangules to close the contour
   */
  std::vector<triangle_type> close_contour(const Contour& a){
    std::vector<triangle_type> trs;
    trs.reserve(a.size());
    
    point_type b = a.barycenter(); // Same number of triangles, less prone to errors
    for (auto it = std::next(a.begin(),1); it != a.end(); ++it) {
        trs.push_back( {*std::prev(it,1), *it, b} );
    }

    return trs;
  }
  
  /**
   * @brief 
   * @param r
   * @param name
   * @param component
   */
  void reconstructionContourProcess( Reconstruction& r, const std::string& name, int component){
    
    std::vector<Contour> selected;
    
    // First: Extract contours with given name
    for(auto it = r.contour_begin(); it != r.contour_end(); ++it){
      if(it->name() == name){
        selected.push_back(*it);
      }
    }
    
    // Order by depth
    // This is the comp function
    auto c_func = [comp_=component](const Contour& c1, const Contour& c2) -> bool {
      if(&c1 == &c2 ) return false;
      std::pair<float,float> r_1 = c1.range(comp_);
      std::pair<float,float> r_2 = c2.range(comp_);
      return r_1.second < r_2.second; // Compare max values
    };
    
    std::sort(selected.begin(),selected.end(),c_func);
    
    // Check that they are closed (and close them)
    for(auto it = selected.begin(); it != selected.end(); ++it){
      if(!it->is_closed()){
        NSTR_LOG_(warn, " Open contour - Please check that given contours are closed");
        it->close();
      }
    }
    
    // Join and create triangular contour
    triMesh_type tricontour = create_triangular_contour(selected.begin(),selected.end(),component);
    
    // Apply to each neuron in the rec
    for(auto it = r.begin(); it != r.end(); ++it){
      neuronContourProcess(*it,name,tricontour);
    }
    
    // Done.
    
  }
  
  /**
   * @brief 
   * @param n
   * @param name
   * @param contour
   */
  void neuronContourProcess( Neuron& n, const std::string& name, const triMesh_type& contour){
    
    // Cut each neurite
    for(auto it = n.begin_neurite() ; it != n.end_neurite(); ++it ){
      neuriteContourProcess(*it, name, contour);
    }
    
    // Cut soma
    for( auto it = n.begin_soma() ; it != n.end_soma() ; ++it ){
        it->properties.set(name,contour.point_inside(it->position()));
    }
  }
  
  /**
   * @brief 
   * @param n
   * @param name
   * @param contour
   */
  void neuriteContourProcess( Neurite& n, const std::string& name, const triMesh_type& contour){
     
     // ITerate over the neurite
    for( auto it = n.begin_branch() ; it != n.end_branch(); ++it ){
      branchContourProcess( *it, name, contour );
    }
  }
  
  /**
   * @brief 
   * @param b
   * @param name
   * @param contour
   * @return 
   */
  void branchContourProcess( Branch& b, const std::string& name, const triMesh_type& contour){
    
     if(b.has_root()){
       b.root().properties.set(name, contour.point_inside(b.root().position()));
     }
    
     for(auto it = b.begin(); it != b.end() ; ++it){
      // Check if the node is inside the contour
      if( !contour.point_inside(it->position()) ){
        it->properties.set(name,false);
        // If node is not in the contour (and the parent is) add a virtual node
        Node parent;
        
        // Find parent
        if(it == b.begin()){
          if(b.has_root()){
            parent = b.root();
          } else {
            parent = *it;
          }
        } else {
          parent = *(it-1);
        }
        
        // Already set
        if(parent != *it && parent.properties.get<bool>(name)){
          // Find cutpoint - ray direction
          point_type ray_direction = parent.vectorTo(*it);
          geometry::normalize(ray_direction);
          
          point_type intersection = contour.ray_intersection(parent.position(), ray_direction);
          // Check that the intersection is not at some of the already existing nodes
          if( geometry::distance(intersection, parent.position()) > 1E-3 
              && geometry::distance(intersection, it->position()) > 1E-3 ){
                // Insert a node with id -3
              auto insert_it = b.insert(it, Node(-3,intersection, (parent.radius() + it->radius())/2 ) );
              it = insert_it;
              it->properties.set(name,false); // The point is NOT in the contour (well...actually it is... nevermind
          }
        }
      } else {
        // End IF inside by
        it->properties.set(name,true);
      }
    } // End for loop
  }
  
  /**
   * @brief 
   * @param r
   */
  void removeContourVirtualNodes( Reconstruction& r ){
    // Remove cut from branches and nodes
    for(auto n = r.begin(); n != r.end(); ++n){
      for(auto neurite = n->begin_neurite(); neurite != n->end_neurite(); ++neurite){
        for( auto branch = neurite->begin_branch(); branch != neurite->end_branch(); ++branch ){
          for( auto node = branch->begin(); node != branch->end() ; ++node ){
            if(node->id() == -3 ){
              node = --(branch->erase(node));
            }
          }
        }
      }
    }
  }
  
  bool branchBoxCutter( Branch& b, const box_type& box){
    
    for(auto it = b.begin(); it != b.end() ; ++it){
      // Check if the node is inside the box
      if( !geometry::covered_by(it->position(),box) ){
        // If node is not in the box, we need to find its cutpoint
        Node parent;
        
        // Find parent
        if(it == b.begin()){
          if(b.has_root()){
            parent = b.root();
          } else {
            parent = *it;
          }
        } else {
          parent = *(it-1);
        }
        
        // Find cutpoint
        segment_type seg(parent.position(), it->position());
        point_type cutpoint;  
        if( geometry::segment_box_intersection(box, seg, cutpoint) ){
          
          // Intersects -> add a node at the intersection point. ID -1 since it is a virtual node
          // Iterator changes
          // Note: id -1 is a special id for invalid node.
          if( !geometry::equal(cutpoint, parent.position()) && !geometry::equal(cutpoint, it->position()) ){
                auto insert_it = b.insert(it, Node(-2,cutpoint, (parent.radius() + it->radius())/2 ) );
          
                // Mark the following nodes as "CUT"
                for(++insert_it ; insert_it != b.end(); ++insert_it){
                    insert_it->properties.set("cut");
                }
          } else {
              // Node is the intersection point
              for(++it ; it != b.end(); ++it){
                    it->properties.set("cut");
                }
          }
          
          return true;
        }
      } // End IF covered by
    } // End for loop
    return false;
  }

  
} // End namespace methods  
} // End namespace neurostr

