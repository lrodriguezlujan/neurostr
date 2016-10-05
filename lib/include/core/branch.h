#ifndef NEUROSTR_CORE_BRANCH_H_
#define NEUROSTR_CORE_BRANCH_H_

#include <iostream>
#include <vector>
#include <type_traits>  // For aserts and stuff
#include <iterator>
#include <algorithm>
#include <stdexcept>
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

  /**
   * @brief Default constructor. creates a branch with order -1 and empty id
   * @return Branch
   */
  Branch();

  /**
   * @brief Creates a branch with given id and order
   * @param id Branch id
   * @param order Branch order
   * @return Branch
   */
  Branch(const id_type& id, int order);

  /**
   * @brief Creates a branch with given id,order and root
   * @param id Branch id
   * @param order Centrifugal order
   * @param root Branch root node
   * @return Branch
   */
  Branch(const id_type& id, int order, const Node& root);
  
  /**
   * @brief Creates a branch with given id,order, root and nodes
   * @param id Branch id
   * @param order Centrifugal order
   * @param root Branch root node
   * @param nodes Branch nodes
   * @return Branch
   */
  Branch(const id_type& id, int order, 
         const Node& root, const std::vector<Node>& nodes);

    /**
   * @brief Creates a branch with given id,order, root and nodes
   * @param id Branch id
   * @param order Centrifugal order
   * @param root Branch root node
   * @param b Node begin iterator
   * @param e Node end iterator
   * @return Branch
   */
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

  /**
   * @brief Empty destructor
   */
  ~Branch() {};

  // Delete copy
  Branch(const Branch& b)  = delete;
  Branch& operator=(const Branch& b) = delete;

  // Default 
  Branch(Branch&& b) = default;
  Branch& operator=(Branch&& b) = default;

  /**
   * @brief Centrifugal order accessor
   * @return Centrifugal order
   */
  int order() const { return order_; }
  
  /**
   * @brief ID accessor
   * @return Branch Id
   */
  const id_type& id() const { return id_; }
  
  /**
   * @brief Returns Branch ID as a string
   * @return ID as string
   */
  std::string idString() const;
  
  /**
   * @brief Branch neurite reference validity check
   * @return True if Neurite reference is valid
   */
   bool valid_neurite() const { return neurite_ != nullptr; }
  
  /**
   * @brief Branch parent neurite
   * @return Parent neurite reference
   */
  const Neurite& neurite() const;
  
  /**
   * @brief Branch parent neurite
   * @return Parent neurite reference
   */
  Neurite& neurite();

  /**
   * @brief Set branch id
   * @param id new id
   * @return Update branch reference
   */
  Branch& id(const id_type& id);
  
  
  /**
   * @brief Set branch centrifugal order
   * @param o new centrifugal order
   * @return Update branch reference
   */
  Branch& order(int o);
  
  /**
   * @brief Set branch parent neurite
   * @param n Neurite pointer
   * @return Update branch reference
   */
  Branch& neurite(Neurite* n);
  
  /**
   * @brief Copy a node as new root
   * @param n node to copy
   */
  void root(const Node& n) { root_.reset(new Node(n)); }
  
  /**
   * @brief Move a node as new root
   * @param n node to move
   */
  void root(Node&& n) { root_.reset(new Node(n)); }

  /**
   * @brief Compares two branches by ID
   * @param b Branch
   * @return True if two ids are equal
   */
  bool operator==(const Branch& b) const {
    return (id_.size() == b.id_.size()) && (nodes_.size() == b.nodes_.size()) &&
           std::equal(id_.cbegin(), id_.cend(), b.id_.cbegin()) && (root_ == b.root_) && 
           std::equal(begin(), end(), b.begin());
  }
  bool operator!=(const Branch& b) const { return !(b == (*this)); }

  /**
   * @brief Number of nodes in the b
   * @return Branch size 
   */
  size_type size() const { return nodes_.size(); }
  
  /**
   * @brief Branch root validity check
   * @return True/False
   */
  bool has_root() const { return root_.get() != nullptr; }

  /**
   * @brief Get root node reference
   * @throws runtime_error Attempt to access nullptr
   * @return Root node reference
   */
  const Node& root() const;
  
  /**
   * @brief Get root node reference
   * @throws runtime_error Attempt to access nullptr
   * @return Root node reference
   */
  Node& root();
  
  /**
   * @brief Returns branch first node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  const Node& first() const;
  
  /**
   * @brief Returns branch last node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  const Node& last() const;
  
  /**
   * @brief Returns branch first node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  Node& first();
  
  /**
   * @brief Returns branch last node
   * @throws runtime_error Attempt to access empty branch
   * @return Node reference
   */
  Node& last();
  
  /**
   * @brief Adds a property to the branch and optionally to its nodes
   * @param key Property name
   * @param value Property value
   * @param recursive If true, property is also added to branch nodes
   * @return Iterator to added property
   */
  template <typename T>
  auto add_property(const std::string& key, T value, bool recursive = false){
    if(recursive){
      for(auto it = begin(); it != end(); ++it){
        it->properties.set(key,value);
      }
    }
    return properties.set(key,value);
  }
  
  /**
   * @brief Adds an empty property to the branch and optionally to its nodes
   * @param key Property name
   * @param recursive If true, property is also added to branch nodes
   * @return Iterator to added property
   */
  auto add_property(const std::string& key, bool recursive = false){
    if(recursive){
      for(auto it = begin(); it != end(); ++it){
        it->properties.set(key);
      }
    }
    return properties.set(key);
  }

  /*** ITERATORS **/
  
  /**
   * @brief Begin node iterator (indirect iterator)
   * @return Indirect iterator
   */
  iterator begin() { return std::begin(nodes_); }
  
  /**
   * @brief End node iterator (indirect iterator)
   * @return Indirect iterator
   */
  iterator end() { return std::end(nodes_); }
  
  /**
   * @brief Reverse begin node iterator (indirect iterator)
   * @return Indirect iterator
   */
  reverse_iterator rbegin() { return std::rbegin(nodes_); }
  
  /**
   * @brief Reverse end node iterator (indirect iterator)
   * @return Indirect iterator
   */
  reverse_iterator rend() { return std::rend(nodes_); }
  
  /**
   * @brief Begin node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_iterator begin() const { return std::begin(nodes_); }
  
  /**
   * @brief End node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_iterator end() const { return std::end(nodes_); }
  
  /**
   * @brief Reverse begin node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_reverse_iterator rbegin() const { return std::rbegin(nodes_); }
  
  /**
   * @brief Reverse end node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_reverse_iterator rend() const { return std::rend(nodes_); }
  
  /**
   * @brief Begin const node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_iterator cbegin() const { return std::begin(nodes_); }
  
  /**
   * @brief End const node iterator (indirect iterator)
   * @return Indirect iterator
   */
  const_iterator cend() const { return std::end(nodes_); }
  
  // END Iterator definition

  /**
   * @brief Copy a node to the end of the branch
   * @param n Node to copy
   */
  void push_back(const Node& n);
  
  /**
   * @brief Move a node to the end of the branch
   * @param n Node to move
   */
  void push_back(Node&& n);

  /**
   * @brief Copies the given node at the position
   * @param pos Position to insert
   * @param n Node
   * @return Updated iterator
   */
  iterator insert(iterator pos, const Node& n);

  /**
   * @brief Copies a range of nodes into the branch
   * @param pos Insert position
   * @param b Range begin iterator
   * @param e Range end iterator
   */
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
  
  /**
   * @brief Deletes a node in the branch
   * @param pos Position to delete
   * @return Updated iterator
   */
  iterator erase(const iterator& pos);
  
  /**
   * @brief Deletes a range of nodes in the branch
   * @param first first position to delete
   * @param last last position to delete
   * @return Updated iterator
   */
  iterator erase(const iterator& first,const iterator& last);
  
  /**
   * @brief Deletes all nodes in the brnach
   */
  void clear() { nodes_.clear(); }

  /**
   * @brief Divides the branch at given position and creates a new branch
   * @param pos Split position
   * @return Split branch
   */
  Branch split(const iterator& pos);
  
  // Transformations
  
  /**
   * @brief Applies RDF simplification to the branch nodes. Root and last are 
   * always keeped
   * @param eps RDF algorithm epsilon parameter (tolerance). If eps is <0 
   * is used as a relative tolerance to the node radius
   */
  void simplify(float eps = -1.5 );
  
  /**
   * @brief Scales the branch wrt root by r (>1 bigger, <1 smaller)
   * @param r Scale rate
   */
  void scale(float r);
  
  /**
   * @brief Scales branch (including root) 
   * @param rx x-axis scale
   * @param ry y-axis scale
   * @param rz z-axis scale
   */
  void scale(float rx, float ry, float rz);
  
  /**
   * @brief Moves the branch (root included) by the vector p
   * @param p Translation vector
   */
  void traslate(const point_type& p);
  
  /**
   * @brief Rotates the branch (Root included) aplying the quaternion q
   * @param q rotation quaternion
   */
  void rotate(const Eigen::Quaternionf& q);
  
  /**
   * @brief Removes zero-length segments in the branch
   */
  void remove_null_segments();

  /**
   * @brief Computes the frechet distance between two branche s
   * @param other Branch
   * @return Discrete frechet distance
   */
  float discrete_frechet( const Branch& other) const;
  
  /**
   * @brief Computes the distance between both branches.
   * Ignores nodes shared by both branches
   * @param other
   * @return euclidean distance
   */
  float distance(const Branch& other, bool ignore_radius = false) const;
  
  /**
   * @brief Updates branch memeber in all nodes
   */
  void set_nodes_branch();
  
  /**
   * @brief Gets bounding box
   */
   box_type boundingBox() const;
  
  private:
  
  /**
   * @brief Throw an exception if root is null
   */
  void _check_root() const;
  
  /**
   * @brief Throw an exception if neurite is null
   */
  void _check_neurite() const;
  
  /**
   * @brief Throw an exception if size is 0
   */
  void _check_size() const;
  
  /**
   * @brief Computes branch distance to segment p0-p1
   * @param p0 
   * @param p1 
   * @return Euclidean distance
   */
  float _distance_segment(point_type p0, point_type p1, 
                          bool ignore_radius = false,
                          bool ignore_root = false,
                          bool ignore_last = false) const;

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
