#ifndef NEUROSTR_CORE_BRANCH_H_
#define NEUROSTR_CORE_BRANCH_H_

#include <iostream>
#include <vector>
#include <type_traits>  // For aserts and stuff
#include <iterator>
#include <algorithm>

#include <memory>
#include <boost/iterator/indirect_iterator.hpp>

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
  using storage_type = std::vector< std::unique_ptr<Node> >;
  using size_type = typename storage_type::size_type;
  
  // Define iterators
  using iterator = boost::indirect_iterator<typename storage_type::iterator>;
  using reverse_iterator = boost::indirect_iterator<typename storage_type::reverse_iterator>;
  using const_iterator = boost::indirect_iterator<typename storage_type::const_iterator>;
  using const_reverse_iterator = boost::indirect_iterator<typename storage_type::const_reverse_iterator>;

  // Constructors
  Branch() : WithProperties(), id_(), order_(-1), root_(), nodes_() {};

  Branch(const id_type& id, int order) 
    : WithProperties()
    , id_(id)
    , neurite_(nullptr)
    , order_(order)
    , root_(nullptr)
    , nodes_() {
  };

  // Copy root (small type...)
  Branch(const id_type& id, int order, const Node& root)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(new Node(root) ) {
        root_->branch(this);
  };
  
  // Move nodes
  Branch(const id_type& id, int order, 
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

  // Now with iterators
  template <typename Iter>
  Branch(const id_type& id, int order, 
         const Node& root, const Iter& b, const Iter& e)
      : WithProperties()
      , id_(id)
      , neurite_(nullptr)
      , order_(order)
      , root_(new Node(root))
      , nodes_() {
    // assert that iter actually defers to Node
    static_assert(std::is_same<Node, 
                  std::remove_reference_t<
                    typename std::iterator_traits<Iter>::value_type>
                  >(),
                  "Iterator must defers to node type");
    root_->branch(this);
    for(auto it = b; it != e ; ++it){
      Node* tmp = new Node(*it);
      tmp->branch(this);
      nodes_.emplace_back(tmp);
    }
  };

  // Nothing to do here
  ~Branch() {};

  // Copy (not allowd)
  Branch(const Branch& b)  = delete;
  Branch& operator=(const Branch& b) = delete;

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
           std::equal(begin(), end(), b.begin());
  }
  bool operator!=(const Branch& b) const { return !(b == (*this)); }

  // Size (number of nodes)
  size_type size() const { return nodes_.size(); }
  bool has_root() const { return root_.get() != nullptr; }

  // These funcs may throw exceptions
  // Get root node
  const Node& root() const {
    return *root_;
  };
  
  Node& root() {
    return *root_;
  };
  
  void root(const Node& n) {
    root_.reset(new Node(n));
  }
  
  void root(Node&& n) {
    root_.reset(new Node(n));
  }
  
  // Get first non root node
  const Node& first() const {
    return *(nodes_.front());
  };
  // Get last node (non root)
  const Node& last() const {
    return *(nodes_.back());
  };
  
  // Get first non root node
  Node& first() {
    return *(nodes_.front());
  };
  // Get last node (non root)
  Node& last() {
    return *(nodes_.back());
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
  iterator begin() { return std::begin(nodes_); }
  iterator end() { return std::end(nodes_); }
  
  reverse_iterator rbegin() { return std::rbegin(nodes_); }
  reverse_iterator rend() { return std::rend(nodes_); }
  
  const_iterator begin() const { return std::begin(nodes_); }
  const_iterator end() const { return std::end(nodes_); }
  
  const_reverse_iterator rbegin() const { return std::rbegin(nodes_); }
  const_reverse_iterator rend() const { return std::rend(nodes_); }
  
  const_iterator cbegin() const { return std::begin(nodes_); }
  const_iterator cend() const { return std::end(nodes_); }
  
  // END Iterator definition

  // Push back (cp and mv)
  void push_back(const Node& n) { 
    Node* ncopy = new Node(n);
    ncopy->branch(this);
    nodes_.emplace_back(ncopy); 
  }
  
  void push_back(Node&& n) { 
    n.branch(this);
    nodes_.emplace_back(new Node(n));
  }

  // Insert at position
  iterator insert(iterator pos, const Node& n) { 
    if( pos != end() ){
      pos->invalidate_basis();
      pos->invalidate_length();
    }
    Node* ncopy = new Node(n);
    ncopy->branch(this);
    return (nodes_.emplace(pos.base(), ncopy));
  }

  template <typename Iter> 
  void insert(iterator pos, Iter b, Iter e) {
    if( pos != end() ){
      pos->invalidate_basis();
      pos->invalidate_length();
    }
    // Change node branch
    Node * tmp;
    for(auto it = b ; it != e ; ++it){
      tmp = new Node(*it);
      tmp->branch(this);
      pos = nodes_.emplace(pos.base(),tmp);
    }
  };
  
  // Erase
  iterator erase(const iterator& pos);
  iterator erase(const iterator& first,const iterator& last);
  
  void clear() { nodes_.clear(); }

  // Split
  // FIXME (move instead of copy elements!)
  Branch split(const iterator& pos) {
    
    Branch splitbranch{id_, order_+1};
    splitbranch.neurite(neurite_); // Set neurite
    
    if (pos == end() ){
        return splitbranch;
    } else{
        iterator b = pos;
        
        // Create branch 
        splitbranch.root(*pos); // Copy root
        
        // move
        std::move(std::next(b,1).base(),nodes_.end(), std::back_inserter(splitbranch.nodes_));
        
        // Remove nodes
        erase(std::next(b,1), end());
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
    for(auto it = begin(); it != end(); ++it)
      it->branch(this);
    if(root_.get()!=nullptr)
      root_->branch(this);
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
  std::unique_ptr<Node> root_;
  std::vector<std::unique_ptr<Node>> nodes_;

};  // class template Branch

std::ostream& operator<<(std::ostream& os, const Branch& b);

}  // namespace neurostr

#endif
