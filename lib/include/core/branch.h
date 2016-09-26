#ifndef NEUROSTR_CORE_BRANCH_H_
#define NEUROSTR_CORE_BRANCH_H_

#include <iostream>
#include <vector>
#include <type_traits>  // For aserts and stuff
#include <iterator>
#include <algorithm>
#include <Eigen/Geometry>
#include "core/property.h"
#include "core/definitions.h"
#include "core/node.h"

namespace neurostr {

// Branch node template

class Branch : public WithProperties{
  
 public:

  // In class definitions
  using id_type = std::vector<int>;
  using node_type = Node;
  using storage_type = std::vector<Node>;
  using size_type = typename storage_type::size_type;
  
  // Define iterators
  using iterator = typename storage_type::iterator;
  using reverse_iterator = typename storage_type::reverse_iterator;
  using const_iterator = typename storage_type::const_iterator;
  using const_reverse_iterator = typename storage_type::const_reverse_iterator;

  // Constructors
  Branch() : WithProperties(), id_(), order_(-1), root_(), nodes_() {};

  Branch(const id_type& id, int order) 
    : WithProperties()
    , id_(id)
    , neurite_(nullptr)
    , order_(order)
    , root_()
    , nodes_() {
      set_nodes_branch();
  };

  // Copy root (small type...)
  Branch(const id_type& id, int order, const node_type& root)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(root) {
        set_nodes_branch();
        
  };

  // Copy both root and nodes
  Branch(const id_type& id, int order, 
         const node_type& root, const storage_type& nodes)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(root)
      , nodes_(nodes) {
        set_nodes_branch();
  };

  // Move nodes
  Branch(const id_type& id, int order, 
         const node_type& root, storage_type&& nodes)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(root)
      , nodes_(nodes) {
      set_nodes_branch();
  };

  // Now with iterators
  template <typename Iter>
  Branch(const id_type& id, int order, 
         const node_type& root, const Iter& b, const Iter& e)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(root)
      , nodes_() {
    // assert that iter actually defers to node_type
    static_assert(std::is_same<node_type, 
                  std::remove_reference_t<
                    typename std::iterator_traits<Iter>::value_type>
                  >(),
                  "Iterator must defers to node type");
                  
    nodes_.insert(nodes_.begin(), b, e);
    set_nodes_branch();
  };

  // Nothing to do here
  ~Branch() {};

  // Copy
  Branch(const Branch& b)  = default;
  
  Branch& operator=(const Branch& b) = default;

  // Move
  Branch(Branch&& b) = default;
  Branch& operator=(Branch&& b) = default;

  /** Accessor **/
  int order() const { return order_; }
  const id_type& id() const { return id_; }
  
  std::string idString() const;
  
  const Neurite& neurite() const { return *neurite_;}
  Neurite& neurite() { return *neurite_;}

  
  /** SETTERS **/
  Branch& id(const id_type& id) {
    id_ = id;
    return *this;
  }
  
  Branch& order(int o) {
    order_ = o;
    return *this;
  }
  
  Branch& neurite(Neurite* n) {
    neurite_ = n;
    return *this;
  }

  // Operators
  bool operator==(const Branch& b) const {
    return (id_.size() == b.id_.size()) && (nodes_.size() == b.nodes_.size()) &&
           std::equal(id_.cbegin(), id_.cend(), b.id_.cbegin()) && (root_ == b.root_) && 
           std::equal(nodes_.cbegin(), nodes_.cend(), b.nodes_.cbegin());
  }
  bool operator!=(const Branch& b) const { return !(b == (*this)); }

  // Size (number of nodes)
  size_type size() const { return nodes_.size(); }
  bool has_root() const { return root_.id() != -1; }

  // These funcs may throw exceptions
  // Get root node
  node_type root() const {
    return root_;
  };
  
  node_type& root() {
    return root_;
  };
  
  void root(const node_type& n) {
    root_ = n;
  }
  
  // Get first non root node
  const node_type& first() const {
    return nodes_.front();
  };
  // Get last node (non root)
  const node_type& last() const {
    return nodes_.back();
  };
  
  // Get first non root node
  node_type& first() {
    return nodes_.front();
  };
  // Get last node (non root)
  node_type& last() {
    return nodes_.back();
  };
  
  // Set property
  template <typename T>
  auto add_property(const std::string& key, T value, bool recursive = false){
    if(recursive){
      for(auto it = begin(); it != end(); ++it){
        it->properties.set(key,value);
      }
    }
    return properties.set(key,value);
  }
  
  auto add_property(const std::string& key, bool recursive = false){
    if(recursive){
      for(auto it = begin(); it != end(); ++it){
        it->properties.set(key);
      }
    }
    return properties.set(key);
  }

  /*** ITERATORS **/


  // Begin at root - End remains at the same place
  iterator begin() { return nodes_.begin(); }
  iterator end() { return nodes_.end(); }
  
  reverse_iterator rbegin() { return nodes_.rbegin(); }
  reverse_iterator rend() { return nodes_.rend(); }
  
  const_iterator begin() const { return nodes_.begin(); }
  const_iterator end() const { return nodes_.end(); }
  
  const_reverse_iterator rbegin() const { return nodes_.rbegin(); }
  const_reverse_iterator rend() const { return nodes_.rend(); }

  const_iterator cbegin() const { return nodes_.cbegin(); }
  const_iterator cend() const { return nodes_.cend(); }
  
  // END Iterator definition

  // Push back (cp and mv)
  void push_back(const node_type& n) { 
    Node ncopy = n;
    ncopy.branch(this);
    nodes_.push_back(ncopy); 
  }
  void push_back(node_type&& n) { 
    n.branch(this);
    nodes_.push_back(n);
  }

  // Insert at position
  iterator insert(iterator pos, const node_type& n) { 
    if( pos != nodes_.end() ){
      pos->invalidate_basis();
      pos->invalidate_length();
    }
    Node ncopy = n;
    ncopy.branch(this);
    return (nodes_.insert(pos, ncopy));
  }

  template <typename Iter> 
  void insert(iterator pos, Iter b, Iter e) {
    if( pos != nodes_.end() ){
      pos->invalidate_basis();
      pos->invalidate_length();
    }
    // Change node branch
    for(auto it = b ; it != e ; ++it){
      it->branch(this);
    }
    nodes_.insert(pos, b, e);
  };
  
  // Erase
  iterator erase(const iterator& pos);
  iterator erase(const iterator& first,const iterator& last);
  void clear() { nodes_.clear(); }

  // Split
  Branch split(const iterator& pos) {
      if (pos == nodes_.end() )
        return Branch();
      else{
        iterator b = pos;
        
        // Create branch 
        Branch splitbranch{id_, order_+1, *pos, ++b, nodes_.end()};
        splitbranch.neurite(neurite_);
        
        // Remove cp nodes
        erase(b,nodes_.end());
        return splitbranch;
      }
  }
  
  // Transformations
  void simplify(float eps = -1.5 );
  void scale(float r);
  void scale(float rx, float ry, float rz);
  void traslate(const point_type& p);
  void rotate(const Eigen::Quaternionf& q);
  
  void remove_null_segments();

  // Discrete frechet distance
  float discrete_frechet( const Branch& other) const;
  
  void set_nodes_branch(){
    for(auto it = nodes_.begin(); it != nodes_.end(); ++it)
      it->branch(this);
    root_.branch(this);
  };
  
  private:
 
  float _discrete_frechet_recursive(size_t i, size_t j, 
                                    std::vector<float>& tmp,
                                    const Branch& other) const;
  

  
  // DATA MEMBERS

  // Branch identifier
  std::vector<int> id_;
  
  // Parent branch
  Neurite* neurite_;

  // Centrifugal order
  int order_;

  // Node storage
  node_type root_;
  std::vector<node_type> nodes_;

};  // class template Branch

std::ostream& operator<<(std::ostream& os, const Branch& b);

}  // namespace neurostr

#endif
