#include <neurostr/core/branch.h>
#include <iostream>
#include <ios>

namespace neurostr{
 
/******
 * 
 * BRANCH METHODS
 * 
 */
 
 // Constructors
 
 
  /**
   * @brief Default constructor. creates a branch with order -1 and empty id
   * @return Branch
   */
  Branch::Branch() 
    : WithProperties()
    , id_()
    , neurite_(nullptr)
    , order_(-1)
    , root_(nullptr)
    , nodes_() {};

  /**
   * @brief Creates a branch with given id and order
   * @param id Branch id
   * @param order Branch order
   * @return Branch
   */
  Branch::Branch(const Branch::id_type& id, int order) 
    : WithProperties()
    , id_(id)
    , neurite_(nullptr)
    , order_(order)
    , root_(nullptr)
    , nodes_() {
  };

  /**
   * @brief Creates a branch with given id,order and root
   * @param id Branch id
   * @param order Centrifugal order
   * @param root Branch root node
   * @return Branch
   */
  Branch::Branch(const Branch::id_type& id, int order, const Node& root)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(new Node(root) ) {
        root_->branch(this);
  };
  
  /**
   * @brief Creates a branch with given id,order, root and nodes
   * @param id Branch id
   * @param order Centrifugal order
   * @param root Branch root node
   * @param nodes Branch nodes
   * @return Branch
   */
  Branch::Branch(const Branch::id_type& id, int order, 
         const Node& root, const std::vector<Node>& nodes)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(new Node(root))
      , nodes_() {
        root_->branch(this);
        for(auto it = std::begin(nodes); it != std::end(nodes); ++it ){
          Node* tmp = new Node(*it);
          tmp->branch(this);
          nodes_.emplace_back(tmp);
        }
  };
  
  const Neurite& Branch::neurite() const { 
    _check_neurite();
    return *neurite_;
  }
  
  Neurite& Branch::neurite() { 
    _check_neurite();
    return *neurite_;
  }
  
    /**
   * @brief Set branch id
   * @param id new id
   * @return Update branch reference
   */
  Branch& Branch::id(const Branch::id_type& id) {
    id_ = id;
    return *this;
  }
  
  
  /**
   * @brief Set branch centrifugal order
   * @param o new centrifugal order
   * @return Update branch reference
   */
  Branch& Branch::order(int o) {
    order_ = o;
    return *this;
  }
  
  /**
   * @brief Set branch parent neurite
   * @param n Neurite pointer
   * @return Update branch reference
   */
  Branch& Branch::neurite(Neurite* n) {
    neurite_ = n;
    return *this;
  }
  
  
  /**
   * @brief Get root node reference
   * @throws runtime_error Attempt to access nullptr
   * @return Root node reference
   */
  const Node& Branch::root() const {
    _check_root();
    return *root_;
  };
  
  /**
   * @brief Get root node reference
   * @throws runtime_error Attempt to access nullptr
   * @return Root node reference
   */
  Node& Branch::root() {
    _check_root();
    return *root_;
  };
  
  /**
   * @brief Returns branch first node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  const Node& Branch::first() const {
    _check_size();
    return *(nodes_.front());
  };
  
  /**
   * @brief Returns branch last node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  const Node& Branch::last() const {
    _check_size();
    return *(nodes_.back());
  };
  
  /**
   * @brief Returns branch first node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  Node& Branch::first() {
    _check_size();
    return *(nodes_.front());
  };
  
  /**
   * @brief Returns branch last node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  Node& Branch::last() {
    _check_size();
    return *(nodes_.back());
  };
  
  point_type Branch::director_vector() const{
    if( size() > 0){
      if(has_root()){
          return root().vectorTo(last());
      } else {
        if( size() == 1 ){
          return last().position();
        } else {
          return first().vectorTo(last());
        }
      }
    } else {
      return point_type(0,0,0);
    }
  }
  
  /**
   * @brief Copy a node to the end of the branch
   * @param n Node to copy
   */
  void Branch::push_back(const Node& n) { 
    Node* ncopy = new Node(n);
    ncopy->branch(this);
    nodes_.emplace_back(ncopy); 
  }
  
  /**
   * @brief Move a node to the end of the branch
   * @param n Node to move
   */
  void Branch::push_back(Node&& n) { 
    n.branch(this);
    nodes_.emplace_back(new Node(n));
  }

  /**
   * @brief Copies the given node at the position
   * @param pos Position to insert
   * @param n Node
   * @return Updated iterator
   */
  Branch::iterator Branch::insert(Branch::iterator pos, const Node& n) { 
    if( pos != end() ){
      pos->invalidate_basis();
      pos->invalidate_length();
    }
    Node* ncopy = new Node(n);
    ncopy->branch(this);
    return (nodes_.emplace(pos.base(), ncopy));
  }
  
  Branch Branch::split(const Branch::iterator& pos) {
    
    Branch splitbranch{id_, order_+1};
    splitbranch.neurite(neurite_); // Set neurite
    
    if (pos == end() ){
        return splitbranch;
    } else{
        iterator b = pos;
        
        // Create branch 
        splitbranch.root(*pos); // Copy root
        
        // move
        std::move(std::next(b,1).base(),nodes_.end(), 
                  std::back_inserter(splitbranch.nodes_));
        
        // Remove nodes
        erase(std::next(b,1), end());
        return splitbranch;
      }
  }
 
 std::string Branch::idString() const {
   if(id_.size() == 0){
     return std::string();
   } else {
    std::string ret = std::to_string(*(id_.begin()));
    for( auto it = ++id_.begin(); it != id_.end() ; it++ ){
     ret += std::string("-") + std::to_string(*it);
    }
    return ret;
   }
 }
 
 void Branch::set_nodes_branch(){
    for(auto it = begin(); it != end(); ++it)
      it->branch(this);
    if(root_.get()!=nullptr)
      root_->branch(this);
  };
  
  /**
   * @brief Throw an exception if root is null
   */
  void Branch::_check_root() const{
    if(root_.get() == nullptr ){
      throw std::logic_error("Empty root access attempt");
    }
  }
  
  /**
   * @brief Throw an exception if neurite is null
   */
  void Branch::_check_neurite() const{
    if(neurite_ == nullptr ){
      throw std::logic_error("Invalid neurite reference access");
    }
  }
  
  /**
   * @brief Throw an exception if size is 0
   */
  void Branch::_check_size() const {
    if(nodes_.size() == 0 ){
      throw std::length_error("Empty branch access attempt");
    }
  }
  
  float Branch::distance(const Branch& other, 
                         bool ignore_radius) const{
      NSTR_LOG_(trace, "branch distance function call");
      if(other == *this){
        NSTR_LOG_(trace, "branch distance return on equal branches");
        return 0.0;
      }
      else {
        
        // Distance
        float mindist =  std::numeric_limits<float>::max();
        float d;
        
        if(size() == 0 || other.size() == 0){
          NSTR_LOG_(trace, "branch distance return on empty branches");
          return mindist;
        }
        
        // Against the other root if they are not equal
        if(other.has_root() 
           && (!has_root() || other.size()>1 || other.first() != root() ) ){
          // Ignore root condition - we are brothers
          bool ignore_root = (!has_root() || root() == other.root());
            
          // Ignore last condition - Im others father
          bool ignore_last = (last() == other.root());
            
          // Distance to the other root
          d = _distance_segment(other.root().position(), other.first().position(),
                                ignore_radius,
                                ignore_root,
                                ignore_last);
            
          // Substract other segment radius
          if( !ignore_radius ){
            d-= std::min(other.root().radius(),other.first().radius());
          }
            
          if(d <= 0.0 ){
            return 0.0;
          } else {
            mindist = d;  
          }
            
        } // End other root
        
        if (other.size() == 1) {
          return mindist;
        }
        
        // Rest of the other branch segments
        const_iterator last;
          
        // Do not compare the last segment of the other branch if its my parent
        if(!has_root() || other.last() != root() ){
          last = other.end();
        } else{
          last = std::prev(other.end(),1);
        }
          
        for(auto it = std::next(other.begin(),1); it != last; ++it){
          d = _distance_segment(std::prev(it,1)->position(), it->position(),
                                  ignore_radius);
              
          // radius
          if( !ignore_radius ){
            d-= std::min(std::prev(it,1)->radius(), it->radius());
          }
            
          if( d < 0){
            return 0.0;
          } else if(d<mindist){
            mindist = d;
          }
        } // End for other nodes
        
        return mindist;
      }
  } // End distance method

  
  box_type Branch::boundingBox() const {
    
    std::vector<point_type> tmp;
    tmp.reserve(size()+1);
    
    if(has_root())
      tmp.push_back(root().position());
    
    for(auto it = begin(); it != end() ; ++it){
      tmp.push_back(it->position());
    }
    return geometry::bounding_box(tmp);
  }
 
// Friend output method
std::ostream& operator<<(std::ostream& os, const Branch& b){
  std::string padding(b.order()+1, os.fill() );
  
  os << padding << "Branch ";
  
  // Print id
  os << *b.id().begin();
  for( auto it = ++b.id().cbegin(); it != b.id().cend() ; it++ )
    os << "-" << *it;
  os << std::endl;
  // Print order
  os << padding << "\t order: " << b.order() << std::endl;
  
    // Print root
  if(b.has_root())
    os << padding  << "\t root: " << b.root() << std::endl;
  else
    os << padding  << "\t NO ROOT DEFINED" << std::endl;
  
  // Print number of nodes
  os << padding << "\t# nodes: " << b.size() << std::endl;
  
  // Print content
  for( auto it = b.cbegin(); it != b.cend() ; it++ )
    os << padding  << "\t" << *it << std::endl;
    
  return os;
};

  // Erase
  Branch::iterator Branch::erase(const Branch::iterator& pos) { 
    
    if(pos == end()) return pos;
    
    auto next = std::next(pos,1);
    if( next != end() ){
      next->invalidate_basis();
      next->invalidate_length();
      if(pos->valid_parent()){
        next->parent(&(pos->parent()));
      } else {
        next->parent(nullptr);
      }
    }
    return nodes_.erase(pos.base());
  }
  Branch::iterator Branch::erase(const Branch::iterator& first,
                                 const Branch::iterator& last) { 
    if( last != end() ){
      last->invalidate_basis();
      last->invalidate_length();
    }
    
    return nodes_.erase(first.base(), last.base());
  }
  
  // Transformations
  void Branch::simplify(float eps){
    
    if(size() <= 1) {
      return;
      
    } else if(eps < 0) {
      eps = (-eps) * (root_->radius() + last().radius() ) / 2.0 ;
    }
    
    std::vector<Node> tmp;
    
    // Add root
    tmp.push_back(*root_);
    
    // Add nodes
    tmp.insert(tmp.end(), begin(), end() );
    
    // RDP Simplification
    geometry::RDPSimplifier<Node>(eps,tmp).simplify();
    
    // Remove nodes
    auto ref = begin();
    for(auto it = std::next(tmp.begin(),1); it != tmp.end(); ++it){
      while(*ref != *it){
        ref = erase(ref);
      }
      
      if (ref != end()){
        ++ref;
      }
    }
    
  }
  
  void Branch::scale(float r){
    
    // Base case
    if(size() == 0 || r == 1) return ;
    
    // Scaled vectors
    std::vector<point_type> vecs;
    point_type v;
    
    // First node scales wrt to root...if it exists
    if ( has_root() ){
      v=root().vectorTo(*begin());
      geometry::scale(v,r);
      
    } else {
      v = first().position();
    }
    vecs.push_back(v);
    
    for(auto it = std::next(begin(),1); it != end() ; ++it){
      v = std::prev(it,1)->vectorTo(*it);
      geometry::scale(v,r);  
      vecs.push_back(v);
    }
    
    // Reconstruct. Root stays put
    point_type curr_pos;
    if ( has_root() ){
      curr_pos = root().position();
    } else {
      curr_pos = point_type(0,0,0);
    }
    
    for(unsigned int i = 0 ; i < vecs.size() ; ++i){
      geometry::traslate(curr_pos,vecs[i]);
      nodes_[i]->position(curr_pos);
    }
  }
  
  void Branch::scale(float rx, float ry, float rz){
    // First node scales wrt to root...if it exists
    if ( has_root() ) root_->scale(rx,ry,rz);
  
    for(auto it  = begin(); it != end() ; ++it){
      it->scale(rx,ry,rz);
    }
  }
  
  void Branch::normalize() {
    float len = length();
    if(len == 0.0 || size() == 0) return;
    else {
      scale(1.0/len);
    }
    
  }
  
  float Branch::length() const{
    float len = 0.0;
    if ( has_root() && size() > 0){
      len+=root().distance(first());
    }
    for(auto it = std::next(begin(),1); it != end() ; ++it){
      len+= std::prev(it,1)->distance(*it);
    }
    return len;
  }
  
  void Branch::traslate(const point_type& p){
      
    for(auto it  = begin(); it != end() ; ++it){
      it->traslate(p);
    }
      
    // Move also the root
    if ( has_root() ) {
      root_->traslate(p);
    }
  }
  
  void Branch::rotate(const Eigen::Quaternionf& q){
    for(auto it  = begin(); it != end() ; ++it){
      it->rotate(q);
    }
      
      // Move also the root
    if ( has_root() ) {
      root_->rotate(q);
    }
  }
  
  void Branch::remove_null_segments(){
    // Check if we should remove the first node
    if( has_root() ){
      // Do it ...
      while(nodes_.size() > 0 && geometry::equal(begin()->position(), root_->position())){
        erase(begin());
      }
    }
    
    if(size() > 0)
      for(auto it = std::next(begin(),1) ; it != end(); ++it){
        if ( geometry::equal( std::prev(it,1)->position(), it->position()) ){
          it = erase(it);
          --it;
        }
      }
  }
  
  float Branch::_distance_segment(point_type p0, point_type p1, 
                                  bool ignore_radius,
                                  bool ignore_root,
                                  bool ignore_last) const{
    NSTR_LOG_(trace, "distance_segment function call");
    
    float mindist =  std::numeric_limits<float>::max();
    float d;
    
    if(size() == 0){
      NSTR_LOG_(trace, "distance_segment return on empty branch");
      return mindist;
    }
    
    // Branch first segment distance (if its possible)
    if(!ignore_root && has_root() && size()>0 && (size()>1 || !ignore_last)  ){
        mindist = geometry::segment_segment_distance(root().position(),
                                               first().position(),
                                               p0,
                                               p1);
        if(!ignore_radius){
          mindist -= std::min(root().radius(),first().radius());
          if(mindist < 0 ) return 0.0;
          
        }
    }
    // No nodes to check 
    if(size() < 2) return mindist;
    
    // Loop
    const_iterator last;
    if(ignore_last) last = std::prev(end(),1);
    else last = end();
    
    for(auto it = std::next(begin(),1); it != last; ++it) {
      d = geometry::segment_segment_distance(  std::prev(it,1)->position(),
                                               it->position(),
                                               p0,
                                               p1);
      if(!ignore_radius){
        d -= std::min(std::prev(it,1)->radius(),it->radius());
        if(mindist <= 0.0 ) return 0.0;
      }
      
      if (d < mindist) mindist = d;    }
    
    return mindist;
  }
  
  float Branch::discrete_frechet(const Branch& other) const {
    
    using iter_type = std::vector<point_type>::const_iterator;
    
    // Create point_type vectors to include root
    std::vector<point_type> a;
    std::vector<point_type> b;
    
    // Add roots
    if(has_root())
      a.push_back(root().position());
    if(other.has_root())
      b.push_back(other.root().position());
    
    // Add nodes
    for(auto it = begin(); it != end() ; ++it ){
      a.push_back(it->position());
    }
    
    for(auto it = other.begin(); it != other.end() ; ++it ){
      b.push_back(it->position());
    }
    
    // Compute discrete frechet
    return geometry::DiscreteFrechet<iter_type,iter_type>(a.begin(),
                                                          a.end(),
                                                          b.begin(),
                                                          b.end()).value();
  }

      
} // Namespace neurostr
