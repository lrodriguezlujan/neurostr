#include "core/node.h"

namespace neurostr{
  
  // Constr.
  Node::Node()
      : WithProperties()
      , id_(-1)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(0, 0, 0))
      , radius_(0.)
      , valid_length_(false)
      , valid_local_basis_(false) {}  
      
  Node::Node(int id)
      : WithProperties()
      , id_(id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(0, 0, 0))
      , radius_(0.)
      , valid_length_(false)
      , valid_local_basis_(false) {} 
      
  Node::Node( int id, const point_type& p, double r)
      : WithProperties()
      , id_(id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(p)
      , radius_(r)
      , valid_length_(false)
      , valid_local_basis_(false) {}  
      
  Node::Node(int id, double x, double y, double z, double r)
      : WithProperties()
      , id_(id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(x, y, z))
      , radius_(r)
      , valid_length_(false)
      , valid_local_basis_(false) {} 
      
  // Access
  Branch& Node::branch(){ 
    _check_null_branch();
    return *branch_; 
  }
  
  const Branch& Node::branch() const { 
    _check_null_branch();
    return *branch_;
  } 
  
  // Set
  Node& Node::position(const point_type& p){
    position_ = p;
    invalidate_basis();
    invalidate_length();
    return (*this);
  }
  
  Node& Node::position(float x, float y, float z) {
    position_ = point_type(x,y,z);
    invalidate_basis();
    invalidate_length();
    return (*this);
  }
  
  Node& Node::radius(float r) {
    radius_ = r;
    return (*this);
  }
  
  Node& Node::branch(Branch* b ){
    branch_ = b;
    return (*this);
  }
  
  void Node::parent(Node* n ) const{
    parent_ = n;
    invalidate_basis();
    invalidate_length();
  }
  
  const Node& Node::parent() const { 
    _check_null_parent();
    return *parent_;
  }
  
  Node& Node::parent() { 
    _check_null_parent();
    return *parent_;
  }

  // NODE MEHTHODS
  
    float Node::distance(const point_type& p) const{
      if( id_ == -1) return -1;
      else return geometry::distance(position_, p);
    }
    
    float Node::distance(const Node& n) const{
      if( id_ == -1 ||n.id_ == -1) return -1;
      else return geometry::distance(position_, n.position_);
    }
    
    point_type Node::vectorTo(const point_type& p) const{
      if( id_ == -1 ) return point_type(0,0,0);
      else{
        return geometry::vectorFromTo(position_, p);
      }
    }
    
    point_type Node::vectorTo(const Node& n) const{
      if( id_ == -1 || n.id_ == -1) return point_type(0,0,0);
      else{
       return geometry::vectorFromTo(position_, n.position_);
      }
    }
    
    std::ostream& operator<<(std::ostream& os, const Node& n){
      return os << boost::format("%i:(%.2f, %.2f, %.2f, %.2f)") % n.id() % 
        geometry::get<0>(n.position()) % 
        geometry::get<1>(n.position()) % 
        geometry::get<2>(n.position()) % 
        n.radius();
    }
    
    float Node::length(const Node& parent) const {
        if( !valid_length_ ){
            length_ = distance(parent);
            valid_length_ = true ;
        }
        return length_;
    }
    
    float Node::length() const {
      if(valid_parent()){
          return length(parent());
      }else{
          return -1;
      }
    }
    
    void Node::traslate(const point_type& v ) {
      geometry::traslate(position_, v);
      invalidate_basis();
      invalidate_length();
    };
    
    void Node::scale(float r, const point_type& ref ){
      geometry::scale(position_,r,ref);
      invalidate_basis();
      invalidate_length();
    }
    
    void Node::scale(float rx, float ry, float rz){
      geometry::scale(position_,rx,ry,rz);
      invalidate_basis();
      invalidate_length();
    }
    
    void Node::rotate(const Eigen::Quaternionf& q){
      // Boost geometry to Eigen Vector3f
      Eigen::Vector3f tmp( x(),y(),z());
      
      // Apply quaternion
      tmp = q * tmp;
      position_ = point_type(tmp[0],tmp[1],tmp[2]);
      invalidate_basis();
      invalidate_length();
    }
    
    const std::array<point_type, 3>& 
    Node::local_basis(const Node& parent, 
                      const point_type& up) const {
                        
        if( !valid_local_basis_){
        if( geometry::norm(parent.vectorTo(position_)) == 0) {
          local_basis_ = geometry::get_basis(position_, up);
        } else { 
          local_basis_ = geometry::get_basis(parent.vectorTo(position_), up);
        }
        valid_local_basis_ = true;
      }
      return local_basis_;
    }
  
  const std::array<point_type, 3>& Node::local_basis(const point_type& up) const{
    if(valid_parent()){
      return local_basis(parent(),up);
    } else {
      return local_basis(Node(),up);
    }
  }
  
  void Node::_check_null_branch() const{
    if( branch_ == nullptr ){
      throw std::logic_error("Null parent branch access attempt");
    }
  }
  
  void Node::_check_null_parent() const{
    if( parent_ == nullptr ){
      throw std::logic_error("Null parent node access attempt");
    }
  }
  
}// namespace neurostr
