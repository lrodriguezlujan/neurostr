#include "core/node.h"

namespace neurostr{

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
  
}// namespace neurostr
