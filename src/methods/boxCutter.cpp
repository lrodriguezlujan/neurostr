#include <neurostr/methods/boxCutter.h>
#include <deque>

namespace neurostr{
namespace methods{
  
  void neuronBoxCutter( Neuron& n,const point_type& min_corner, const point_type& max_corner ){
    
    
    // Create box geometry
    box_type cutbox(min_corner,max_corner);
    
    // Cut each neurite
    for(auto it = n.begin_neurite() ; it != n.end_neurite(); ++it ){
      neuriteBoxCutter(*it, cutbox);
    }
    
    // Cut soma
    for( auto it = n.begin_soma() ; it != n.end_soma() ; ++it ){
      if( !geometry::covered_by(it->position(),cutbox) ){
        it->properties.set("cut");
      }
    }
    
    //Add cutbox definition to neuron poperties
    n.properties.set("cutbox_min", min_corner);
    n.properties.set("cutbox_max", max_corner);
  }
  
  void neuriteBoxCutter( Neurite& n, const box_type& box){
    if( (n.has_root() && !geometry::covered_by(n.root().position(),box)) || 
        (!n.has_root() && !geometry::covered_by(n.begin_branch()->first().position(),box) ) ){
        for( auto it = n.begin_branch() ; it != n.end_branch(); ++it ){
            it->add_property("cut", true);
        }
    } else {
        // ITerate over the neurite in Depth First mode
        for( auto it = n.begin_branch() ; it != n.end_branch(); ++it ){
          if(branchBoxCutter( *it, box )){
            // If true. Branch have been cut
            auto sbit = n.begin_branch_subtree(it);
            for( ++sbit; sbit != n.end_branch_subtree(it); ++sbit ){
              sbit->add_property("cut", true); // Mark branch and its nodes as "cut"
            }
            // Skip children
            it.skip_children();
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
            
              // Parent node is the intersection point
              if(geometry::equal(cutpoint, parent.position())){
                it->properties.set("cut");
              }
              
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
  
  void BoxCutterRestore( Neuron& n ){
    // Remove "cut" from soma
    for( auto it = n.begin_soma() ; it != n.end_soma() ; ++it ){
        it->properties.remove("cut") ;
    }
    
    // Remove cut from branches and nodes
    for(auto neurite = n.begin_neurite(); neurite != n.end_neurite(); ++neurite){
        for( auto branch = neurite->begin_branch(); branch != neurite->end_branch(); ++branch ){
            branch->properties.remove("cut");
            for( auto node = branch->begin(); node != branch->end() ; ++node ){
                if(node->id() == -2 ){
                    node = --(branch->erase(node));
                } else {
                    node->properties.remove("cut");    
                }
            }
        }
    }
    
    n.properties.remove("cutbox_min");
    n.properties.remove("cutbox_max");
  }
    
} // Methods namespace
} // Neurostr namespace
