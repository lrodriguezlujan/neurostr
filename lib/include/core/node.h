#ifndef NEUROSTR_CORE_NODEDATA_H_
#define NEUROSTR_CORE_NODEDATA_H_

#include <cstdint>
#include <vector>
#include <array>
#include <iostream>
#include <boost/geometry.hpp>
#include <Eigen/Geometry>
#include "core/definitions.h"
#include "core/property.h"
#include "core/geometry.h"

namespace neurostr {

class Node : public WithProperties{

  public:
 
  using id_type = int;

  // Default empty constructor
  Node()
      : WithProperties()
      , id_(-1)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(0, 0, 0))
      , radius_(0.)
      , valid_length_(false)
      , valid_local_basis_(false) {}  
      
  Node(int id)
      : WithProperties()
      , id_(id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(0, 0, 0))
      , radius_(0.)
      , valid_length_(false)
      , valid_local_basis_(false) {}  
      
  Node( int id, const point_type& p, double r)
      : WithProperties()
      , id_(id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(p)
      , radius_(r)
      , valid_length_(false)
      , valid_local_basis_(false) {}  
  
  Node(int node_id, double x, double y, double z, double r)
      : WithProperties()
      , id_(node_id)
      , branch_(nullptr)
      , parent_(nullptr)
      , position_(point_type(x, y, z))
      , radius_(r)
      , valid_length_(false)
      , valid_local_basis_(false) {}  

  // Default copy/assign
  Node(const Node& n) = default;
  Node(Node&& n) = default;
  Node& operator=(const Node& n) = default;
  Node& operator=(Node&& n) = default;

  // Destructor
  ~Node() {}

  // Equality Operators
  bool operator==(const Node& n) const { return n.id_ == id_; }
  bool operator!=(const Node& n) const { return n.id_ != id_; }

  // Accesors
  float radius() const { return radius_; }
  const id_type id() const { return id_; }
  const point_type& position() const { return position_; }
  float x() const { return geometry::get<0>(position_); }
  float y() const { return geometry::get<1>(position_); }
  float z() const { return geometry::get<2>(position_); }
  
  // Access branch
  Branch& branch(){ return *branch_; }
  const Branch& branch() const { return *branch_;} 
  
  // Setters
  Node& position(const point_type& p) {
    position_ = p;
    return (*this);
  }
  
  Node& position(float x, float y, float z) {
    position_ = point_type(x,y,z);
    return (*this);
  }

  Node& radius(float r) {
    radius_ = r;
    return (*this);
  }
  
  Node& branch(Branch* b ){
    branch_ = b;
    return (*this);
  }
  
  Node& parent(Node* n ){
    parent_ = n;
    return (*this);
  }
  
  // Vector to other node point
  point_type vectorTo(const point_type& p) const;
  point_type vectorTo(const Node& n) const;
  
  // Distance to other node / point
  float distance(const point_type& p) const;
  float distance(const Node& n) const;

  // Parent node finder
  bool valid_parent() { return parent_ != nullptr; }
  Node& parent() const { return *parent_; }
  
  
  // Length to our parent
  float length(const Node& parent) const;
  
  // Invalidate parent length cache
  void invalidate_length() const {
    valid_length_ = false;
  };

  // Compute local basis (Uses neuron up vector)
  const std::array<point_type, 3>& local_basis(const Node& parent ,
                                               const point_type& up) const;
                            
  // Invalidate precomputed basis
  void invalidate_basis() const { valid_local_basis_ = false; }
  
  // Node point transformations
  void traslate(const point_type& traslation_v );
  void rotate(const Eigen::Quaternionf& q);
  void scale(float r, const point_type& p );
  void scale(float rx, float ry, float rz);

  // To string
  friend std::ostream& operator<<(std::ostream&, const Node&);

 private:
  
  // Node identifier
  id_type id_;
  
  // Parent branch
  Branch* branch_;
  Node* parent_; // Parent node

  // Node properties
  point_type position_;
  float radius_;

  // Cached values
  mutable bool valid_length_;
  mutable float length_;

  // More cached values
  mutable bool valid_local_basis_;
  mutable std::array<point_type, 3> local_basis_;


};  // Class node

}  // Namespace neurostr

#endif  // NEUROSTR_BASE_NODEDATA_H_
