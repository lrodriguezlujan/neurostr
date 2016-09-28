#ifndef NEUROSTR_BASE_NEURITE_H_
#define NEUROSTR_BASE_NEURITE_H_

#include <vector>
#include <list>
#include <cstdint>
#include <limits>
#include <iterator>
#include <map>
#include <iostream>

#include <boost/iterator.hpp>
#include <boost/any.hpp>
#include <boost/geometry.hpp>
#include <boost/utility/enable_if.hpp>

#include "core/definitions.h"
#include "core/property.h"
#include "core/tree.hh"
#include "core/branch.h"
#include "core/neurite_type.h"

namespace neurostr {

class Neurite : public WithProperties  {
 public:
  
  // New iterators (fwd)
  class stem_iterator;
  
  template <typename iter> 
    class node_iterator;
  
  template <typename iter> 
    class const_node_iterator;

  // Traits
  using tree_type     = tree<Branch>;
  using tree_node     = tree_node_<Branch>;
  using id_type       = int;

  // Iterators renamed  
  using branch_iterator           = tree_type::pre_order_iterator;
  using const_branch_iterator     = tree_type::pre_order_iterator; //FIXME
  
  using base_node_iterator        = node_iterator<branch_iterator>;
  using const_base_node_iterator  = const_node_iterator<branch_iterator>;

  using fixed_order_iterator      = tree_type::fixed_depth_iterator;
  using terminal_branch_iterator  = tree_type::leaf_iterator;
  using branch_bfs_iterator       = tree_type::breadth_first_iterator;
  using sibling_iterator          = tree_type::sibling_iterator;

  /**
   * @brief Empty neurite constructor. Id -1 and type undefined
   * @return Neurite
   */
  Neurite();

  /**
   * @brief Create a neurite with given id and type undefined
   * @param id Neurite id
   * @return Neurite
   */
  Neurite(int id);

  /**
   * @brief Create a neurite with given id and type
   * @param id Neurite id
   * @param t Neurite type
   * @return  Neurite
   */
  Neurite(int id, const NeuriteType& t);

  // Copy and assign (Default)
  Neurite(const Neurite& n) = default;
  Neurite(Neurite&& n) = default;
  Neurite& operator=(const Neurite& n) = default;
  Neurite& operator=(Neurite&& n) = default;

  // Empty destructor
  ~Neurite() {};

  // Data members
 private:
  
  // Container
  tree_type tree_;

  // Neurite info
  int id_;
  NeuriteType type_;
  
  bool root_is_soma_;
  
  // Belongs to...
  Neuron* neuron_;

  public:
 
  
  /**
   * @brief Compares two neurites by ID
   * @param n Other neurite
   * @return  True if ids match
   */
  bool operator==(const Neurite& n) const { return (id_ == n.id_); }
  
  /**
   * @brief Compares two neurites by ID
   * @param n Other neurite
   * @return  True if ids dont match
   */
  bool operator!=(const Neurite& n) const { return (id_ != n.id_); }
  
  /**
   * @brief Return neurite type
   * @return  NeuriteType
   */
  const NeuriteType& type() const { return type_; }
  
  /**
   * @brief Returns neurite id
   * @return Neurite ID
   */
  const int id() const { return id_; }
  
  /**
   * @brief Checks if root is soma
   * @return True if neurite root is soma
   */
  bool root_is_soma() const{return root_is_soma_; }
  
  /**
   * @brief Return neurite parent neuron reference
   * @return  Neuron reference
   */
  Neuron&  neuron() const { return *neuron_; }
  
  //
  // SET
  // 
  
  /**
   * @brief Set neurite type
   * @param t New neurite type
   */
  void type(const NeuriteType& t) { type_ = t; }
  
  /**
   * @brief Set neurite ID
   * @param id New neurite ID
   */
  void id(int id) { id_ = id; }
  
  /**
   * @brief Set neurite parent neuron pointer
   * @param n Nueron pointer
   */
  void neuron(Neuron* const n) { neuron_ = n; }

  
  /**
   * @brief Checks if the root branch of the neurite has root
   * @return True if the neurite is rooted (i.e. attached to soma)
   */
  bool has_root() const { return begin_branch()->has_root(); }
  
  /**
   * @brief Get root reference
   * @return Root reference
   */
  const Node& root() const { return begin_branch()->root(); }
  
  // ROOT BRANCH SET
  
  /**
   * @brief Sets an empt branch as the root branch without root node
   */
  void set_root();
  
  /**
   * @brief Creates an empty branch with node as root as root branch
   * @param node Root node
   */
  void set_root(const Node& node);

  /**
   * @brief Get neurite max c.order
   * @return Centrifugal order
   */
  int max_centrifugal_order() const;

  /**
   * @brief Neurite size (branch count)
   * @return Number of branches in the neurite
   */
  int size() const { return tree_.size(); }

  /**
   * @brief Neurite node count
   * @return Number of distinct node ins the neurite (roots excluded)
   */
  int node_count() const ;
  
  /**
   * @brief Adds a property to the neurite and optionally to its branches
   * @param key Property key
   * @param v Property value
   * @param recursive If true, property is also added to braches and nodes
   */
  template <typename T> 
  auto add_property(const std::string& key, T v, bool recursive = true) {
    if (recursive) {
      for( auto it = begin_branch(); it != end_branch(); ++it)
        it->add_property(key,v, recursive);
    }
    return properties.set(key,v);
  };

   /**
   * @brief Adds an empty  property to the neurite and optionally to its branches
   * @param key Property key
   * @param recursive If true, property is also added to braches and nodes
   */
  auto add_property(const std::string& key, bool recursive = true) {
    if (recursive) {
      for( auto it = begin_branch(); it != end_branch(); ++it)
        it->add_property(key, recursive);
    }
    return properties.set(key);
  }

  
  /**
   * @class stem_iterator
   * @author Luis
   * @date 28/06/16
   * @file neurite.h
   * @brief Tree iterator (fwd) that ascends from the given tree node till the root.
   */
  class stem_iterator : public tree_type::iterator_base {
    public:
    
    /**
     * @brief Empty constructor
     * @return Default iterator (actually, useless)
     */
    stem_iterator() ;
      
    /**
     * @brief Creates an stem iterator that points to tn
     * @param tn Tree node pointer
     * @return Stem iterator
     */
    stem_iterator(tree_node* tn) ;
      
    /**
     * @brief Copies the given iterator as stem iterator
     * @param other Iterator
     * @return  Copied stem iterator
     */
    stem_iterator(const typename tree_type::iterator_base& other) ;


    bool operator==(const stem_iterator& other) const ;
    
    bool operator!=(const stem_iterator& other) const ;

    /**
     * @brief Stem iterator single step - ascend one branch
     * @return Updated iterator
     */
    stem_iterator& operator++() ;
      

    /**
     * @brief Stem iterator single step - ascend one branch
     * @return new updated iterator
     */
    stem_iterator operator++(int) ;
      

    /**
     * @brief Stem iterator multi step - ascend num branches
     * @return Updated iterator
     */
    stem_iterator& operator+=(unsigned int num) ;
      
  };
  /**********************************************************************/

  /**
   * @class node_iterator
   * @author Luis
   * @date 28/06/16
   * @file neurite.h
   * @brief Templated iterator. Iter parameter determines 
   *        tree-visitor strategy. References to Node.
   */
  template <typename iter>
  class node_iterator : public boost::iterator_facade<
                          node_iterator<iter>,
                          Node,
                          typename std::iterator_traits<iter>::iterator_category> {

    public:
    
    /**
     * @brief Empty constructor. Nonsense
     * @return Node iterator
     */
    node_iterator();
    
    /**
     * @brief Creates a node iterator that starts at the first node of b and ends
     * at the first node of e.
     * @param b First branch
     * @param e Last branch
     * @return Node iterator
     */
    node_iterator(const iter& b, const iter& e);

     /**
     * @brief Creates a node iterator that starts at the first node of b and ends
     * at the first node of e. Current node is the first node of c.
     * @param b First branch
     * @param e Last branch
     * @param c Current branch
     * @return Node iterator
     */
    node_iterator(const iter& b, const iter& e, const iter& c);
    
     /**
     * @brief Creates a node iterator that starts at the first node of b and ends
     * at the first node of e. Current node is the nodeit node of c.
     * @param b First branch
     * @param e Last branch
     * @param c Current branch
     * @param nodeit Current node
     * @return Node iterator
     */
    node_iterator(const iter& b,
                  const iter& e,
                  const iter& c,
                  const typename Branch::iterator& nodeit);

    // Copy and move
    node_iterator(const node_iterator<iter>&) = default;
    node_iterator& operator=(const node_iterator<iter>&) = default;

    node_iterator(node_iterator<iter>&&) = default;
    node_iterator& operator=(node_iterator<iter>&&) = default;

    // DATA
   private:
    iter begin_;
    iter current_;
    iter end_;
    Branch::iterator node_current_;

    public:
    
    /**
     * @brief Get iterator first branch
     * @return First branch
     */
    iter begin() const;
    
    /**
     * @brief Get iterator last branch
     * @return Last branch
     */
    iter end() const;
    
    /**
     * @brief Get iterator current branch
     * @return Current branch
     */
    iter current() const;
    
    /**
     * @brief Get iterator current branch
     * @return Current branch
     */
    iter branch() const ;
    
    /**
     * @brief Get iterator current noe
     * @return Current node
     */
    Branch::iterator node() const ;

    /**
     * @brief Get current branch neurite
     * @return Neurite reference
     */
    Neurite& neurite() const ;
    
    /**
     * @brief Get current branch neuron
     * @return Neuron reference
     */
    Neuron& neuron() const ;
    
    /**
     * @brief Get an iterator to the end node
     * @return End node iterator
     */
    node_iterator<iter> last() const ;

    /**
     * @brief Get an iterator to the first node
     * @return First node iterator
     */
    node_iterator<iter> first() const ;

    // FACADE METHODS
    private:
   
    friend class boost::iterator_core_access;
    template <typename OtherIter> friend class node_iterator;

    /**
     * @brief Dereference facade method
     * @return Node reference
     */
    Node& dereference() ;
    
    /**
     * @brief Dereference facade method
     * @return Node reference
     */
    Node& dereference() const ;

    /**
     * @brief Compares two iterators by current branch and node
     * @param other Other node iterator
     * @return Ture if both current branch and node matches
     */
    template< typename OtherIter>
    bool equal(const node_iterator<OtherIter>& other) const ;

    /**
     * @brief Increments the node iterator by 1
     */
    void increment() ;
    
    /**
     * @brief Decrements the node iterator by 1
     */
    void decrement() ;
    
  };  // End node iterator

  /**********************
   *  END ITERATORS     *
   **********************/

 public:
  
  /**** Branch iterators ***/
  
  /**
   * @brief Begin DFS branch iterator
   * @return branch_iterator
   */
  branch_iterator begin_branch() const { return tree_.begin(); }
  
  /**
   * @brief End DFS branch iterator
   * @return branch_iterator
   */
  branch_iterator end_branch() const { return tree_.end(); }
  
  // Starts with the given branch and iterates only over its subtree
  
  /**
   * @brief Creates a branch DFS iterator over the subtree of the branch pointed by \cod€{other}
   * @param other Branch iterator
   * @return DFS branch iterator
   */
  branch_iterator begin_branch_subtree(const typename tree_type::iterator_base& other) const {
    return Neurite::branch_iterator(other);
  }
  
  /**
   * @brief Creates a branch DFS iterator over the subtree of the branch pointed by \cod€{other}
   * @param other Branch iterator
   * @return DFS branch iterator
   */
  branch_iterator end_branch_subtree(const typename tree_type::iterator_base& other) const ;

  // Fixed centrifugal order (from the root)
  
  /**
   * @brief Creates an iterator over the branches with centrifugal order \code{order}
   * @param order Centrifugal order
   * @return Begin iterator
   */
  fixed_order_iterator begin_fixed_order(std::uint32_t order) const { return tree_.begin_fixed(tree_.begin(), order); }
  
  /**
   * @brief Creates an iterator over the branches with centrifugal order \code{order}
   * @param order Centrifugal order
   * @return End iterator
   */
  fixed_order_iterator end_fixed_order(std::uint32_t order) const { return tree_.end_fixed(tree_.begin(), order); }
  
  /**
   * @brief Creates an iterator over the branches in the subtree of \code{it} 
   * with centrifugal order \code{order}
   * @param it Branch iterator
   * @param order Centrifugal order
   * @return begin iterator
   */
  fixed_order_iterator begin_fixed_order(const typename tree_type::iterator_base& it, std::uint32_t order) const {
    return tree_.begin_fixed(it, order - tree_type::depth(it));
  }
  
  /**
   * @brief Creates an iterator over the branches in the subtree of \code{it} 
   * with centrifugal order \code{order}
   * @param it Branch iterator
   * @param order Centrifugal order
   * @return end iterator
   */
  fixed_order_iterator end_fixed_order(const typename tree_type::iterator_base& it, std::uint32_t order) const {
    return tree_.end_fixed(it, order - tree_type::depth(it));
  }

  /**
   * @brief Creates an iterator over the terminal branches of the neurite
   * @return begin terminal_branch_iterator
   */
  terminal_branch_iterator begin_leaf() const { return tree_.begin_leaf(); }
  
  /**
   * @brief Creates an iterator over the terminal branches of the neurite
   * @return end terminal_branch_iterator
   */
  terminal_branch_iterator end_leaf() const { return tree_.end_leaf(); }
  
  /**
   * @brief Creates an iterator over the terminal branches of the subtree of \code{top}
   * @param top Branch iterator
   * @return begin terminal_branch_iterator
   */
  terminal_branch_iterator begin_leaf(const typename tree_type::iterator_base& top) const {
    return tree_.begin_leaf(top);
  }
  
  /**
   * @brief Creates an iterator over the terminal branches of the subtree of \code{top}
   * @param top Branch iterator
   * @return end terminal_branch_iterator
   */
  terminal_branch_iterator end_leaf(const typename tree_type::iterator_base& top) const { return tree_.end_leaf(top); }

  /**
   * @brief Stem iterator form it to the root branch
   * @param it Branch iterator
   * @return begin stem_iterator
   */
  stem_iterator begin_stem(const typename tree_type::iterator_base& it) const { return stem_iterator(it); }
  
  /**
   * @brief Stem iterator form it to the root branch
   * @param it Branch iterator
   * @return end stem_iterator
   */
  stem_iterator end_stem(const typename tree_type::iterator_base& it) const { return stem_iterator(tree_.head); }
  
  /**
   * @brief Iterator over the child branches of it
   * @param it Branch iterator
   * @return begin sibling_iterator
   */
  tree_type::sibling_iterator begin_children(const tree_type::iterator_base& it ) const {
    return tree_.begin(it);
  };
  
  /**
   * @brief Iterator over the child branches of it
   * @param it Branch iterator
   * @return end sibling_iterator
   */
  tree_type::sibling_iterator end_children(const tree_type::iterator_base& it ) const {
    return tree_.end(it);
  };

  /**
   * @brief Node iterator that starts at it and ends at the end of the neurite
   * @param it Branch iterator
   * @return Node iterator begin
   */
  template <typename iter> node_iterator<iter> begin_node(iter& it) {
    return (node_iterator<iter>(it, end_branch()));
  }

  /**
   * @brief Node iterator that starts at it and ends at the end of the neurite
   * @param it Branch iterator
   * @return Node iterator end
   */
  template <typename iter> node_iterator<iter> end_node(iter& it) {
    return (node_iterator<iter>(it, end_branch()).last());
  }

  /**
   * @brief Creates a node iterator that starts at i and ends at e
   * @param i begin branch
   * @param e end branch
   * @return Node iterator begin
   */
  template <typename iter> node_iterator<iter> begin_node(iter& i, iter& e) {
    return (node_iterator<iter>(i, e));
  }
  
  /**
   * @brief Creates a node iterator that starts at i and ends at e
   * @param i begin branch
   * @param e end branch
   * @return Node iterator end
   */
  template <typename iter> node_iterator<iter> end_node(iter& i, iter& e) {
    return (node_iterator<iter>(i, e).last());
  }

  /**
   * @brief Neurite node iterator with DFS strategy
   * @return Node iterator begin
   */
  base_node_iterator begin_node() {
    return node_iterator<branch_iterator>(begin_branch(), end_branch());
  }

   /**
   * @brief Neurite node iterator with DFS strategy
   * @return Node iterator end
   */
  base_node_iterator end_node() {
    return node_iterator<branch_iterator>(begin_branch(), end_branch()).last();
  }
  
  /*** Find methods ****/
  
  /**
   * @brief Looks for a branch in the tree that matches \code{b}
   * @param b Branch to find
   * @return Iterator to the branch in the tree. returns end_branch() otherwise
   */
  branch_iterator find(const Branch& b);
  
  /**
   * @brief Looks for a node in the tree that matches \code{n}
   * @param n node to finde
   * @return Iterator to the branch in the tree. returns end_node() otherwise
   */
  base_node_iterator find(const Node& n) { 
    return std::find(begin_node(), end_node(), n); 
  }

  /**
   * @brief Looks for a node with id \code{id} in the tree
   * @param id ID of the node to find
   * @return Iterator to the branch in the tree. returns end_node() otherwise
   */
  base_node_iterator find(Node::id_type id) { return find(Node(id));}
  
  /*** Branch-related methods **/
  
  /**
   * @brief Branch sibling iterator
   * sibling returns an iterator to itself
   * @param position Branch iterator
   * @return Iterator to the sibling of the given branch. If branch has no
   * sibling returns an iterator to itself 
   */
  template <typename iter> 
  iter sibling(iter position) {
    assert(position.node != nullptr);
    iter ret(position);  // Copy
    if (position.node->next_sibling != nullptr)
      ret.node = position.node->next_sibling;
    else if (position.node->prev_sibling != nullptr)
      ret.node = position.node->prev_sibling;
    return ret;
  };
  
  /** INSERT / DELETE NODES **/

  /**
   * @brief Inserts a node at the given position
   * @param pos Node iterator - insert position
   * @param node Node to copy
   * @return Insert position iterator
   */
  template <typename iter>
  node_iterator<iter> insert_node(const node_iterator<iter>& pos, const Node& node){
      if( pos.branch().node == tree_.feet){
        set_root();  // Empty root
        tree_.begin()->push_back(node);
        
        // Return an iterator
        return node_iterator<iter>( tree_.begin(), tree_.end(), tree_.begin(), tree_.begin()->begin());
        
      } else if (pos.branch()->size() == 0) {
        // Empty branch
        pos.branch()->push_back(node);
        return node_iterator<iter>(pos.begin(),pos.end(),pos.branch(), pos.branch()->begin() );
      }
      // Check if pos is the last one
      else if (pos.node() < (pos.branch()->end() - 1)) {
        // Split if we are not inserting in the last position split - pos is
        // still valid in this case
        split(pos);  
      }

      // At this point: We are always inserting in the last pos
      // If theres no more nodes just append
      if (pos.branch().number_of_children() == 0) {
        pos.branch()->push_back(node);
        return node_iterator<iter>(pos.begin(),pos.end(),pos.branch(), --(pos.branch()->end()) );
      } else {
        // Create new branch id
        std::vector<int> id{pos.branch()->id()};
        id.push_back(pos.branch().number_of_children() + 1);

        // Create branch - pos node will be the root        
        auto aux = tree_.append_child(pos.branch(), Branch(id, pos.branch()->order() + 1, *pos) );
        aux->neurite(this);
        aux->push_back(node);
        
        // POST INSERT
        return node_iterator<iter>(pos.begin(),pos.end(), aux, aux->begin());
      }      
  }
  
  // Node - based function
  
  /**
   * @brief Inserts a node as child of the node with id \code{parent_id}
   * @param parent_id Parent node id
   * @param node Node to add
   * @return  Insert iterator
   */
  base_node_iterator insert_node(Node::id_type parent_id, const Node& node);

  /**
   * @brief Moves a branch into the tree
   * @param pos Target position (branch iterator)
   * @return Updated iterator
   */
  template <typename iter> 
  iter append_branch(iter pos, Branch&& b) { 
    b.neurite(this);
    return tree_.append_child(pos, std::move(b)); 
  }
  
  /**
   * @brief Splits the branch at given position
   * @param pos Branch position
   */
  template <typename iter> 
  void split(const node_iterator<iter>& pos){
      // Verify that iterator is valid
      if (pos.branch().node == tree_.feet || pos.branch().node == tree_.head) 
          return ;

      // Create new branch id
      int id_len = pos.branch()->id().size();
      std::vector<int> id{pos.branch()->id()};
      id.push_back(1);  // This new branch is the first

      // Split branch - this modifies the it.current branch

      // Preppend child
      branch_iterator new_pos = tree_.prepend_child(pos.branch(), pos.branch()->split(pos.node()) );
      new_pos->neurite(this);
      new_pos->id(id);
      new_pos->order(pos.branch()->order()+1);
      new_pos->set_nodes_branch();

      // Reparent
      tree_.reparent(new_pos, ++pos.branch().begin(), pos.branch().end());  // Reparent the rest of nodes

      // Update id and order
      for (branch_iterator desc_it = new_pos.begin(); desc_it != new_pos.end(); ++desc_it) {
        id = desc_it->id();  // Get id
        id.insert(id.begin() + id_len, 1);
        desc_it->id(id);                       // Set id
        desc_it->order(desc_it->order() + 1);  // Update order
      }
      return ;
  }

  /**
   * @brief Fixes errors in the Neurite TODO: Which ones?
   */
  void correct();
  
  /**
   * @brief Removes zero-length segments in the neurite
   */
  void remove_null_segments();


  /**
   * @brief Scales all branches in the neurite wrt root or 0,0,0
   * @param r Scale rate
   */
  void scale(float r);
  
  /**
   * @brief  Scales all branches in the neurite 
   * @param rx x-rate
   * @param ry y-rate
   * @param rz z-rate
   */
  void scale(float rx, float ry, float rz);

  /**
   * @brief Traslates all nodes in the neurite by \code{p}
   * @param p Traslation vector
   */
  void traslate(const point_type& p);

  /**
   * @brief Rotates all nodes in the neurite by \code{q}
   * @param q Rotation quaternion
   */
  void rotate(const Eigen::Quaternionf& q);

  /**
   * @brief Applies RDP simplification to all branches in the neurite
   * @param eps Tolerance
   */
  void simplify(float eps = -1.5);

  /**
   * @brief Order child branches by azimuth in ascending order
   */
  void childOrder();

  
  /**
   * @brief Determine the index of a branch in the range of siblings to which it belongs.
   * @param it Branch iterator
   * @return Index
   */
  unsigned int index(sibling_iterator it) const { return tree_.index(it); }

  friend std::ostream& operator<<(std::ostream&, const Neurite&);

  private:

  /**
   * @brief Updates branch ids to match its order in the neurite
   */
  void reassign_branch_ids();
  
};  // Class Neurite

// Print 
std::ostream& operator<<(std::ostream& os, const Neurite& n);


// NODE ITERATOR IMPLEMENTATION

template <typename iter> 
Neurite::node_iterator<iter>::node_iterator() 
      : begin_()
      , current_()
      , end_()
      , node_current_(){};

template <typename iter> 
Neurite::node_iterator<iter>::node_iterator(const iter& b, const iter& e)
        : begin_(b)
        , current_(b)
        , end_(e)
        , node_current_(b->begin()){};

template <typename iter> 
Neurite::node_iterator<iter>::node_iterator(const iter& b, const iter& e, const iter& c)
        : begin_(b)
        , current_(c)
        , end_(e)
        , node_current_(c->begin()){};

template <typename iter> 
Neurite::node_iterator<iter>::node_iterator(const iter& b,
                  const iter& e,
                  const iter& c,
                  const typename Branch::iterator& nodeit)
        : begin_(b), current_(c), end_(e), node_current_(nodeit){};
        
    
template <typename iter>
iter Neurite::node_iterator<iter>::begin() const { return begin_; }
    
template <typename iter>
iter Neurite::node_iterator<iter>::end() const { return end_; }
    
template <typename iter>
iter Neurite::node_iterator<iter>::current() const { return current_; }
    
template <typename iter>
iter Neurite::node_iterator<iter>::branch() const { return current_; }
    
template <typename iter>
Branch::iterator Neurite::node_iterator<iter>::node() const { return node_current_; }

template <typename iter>
Neurite& Neurite::node_iterator<iter>::neurite() const { return current_->neurite(); } 
    
template <typename iter>
Neuron& Neurite::node_iterator<iter>::neuron() const { return current_->neurite().neuron(); }
    
template <typename iter>
Neurite::node_iterator<iter> Neurite::node_iterator<iter>::last() const {
      node_iterator n(*this);  // Copy ourselves
      n.current_ = end_;
      n.node_current_ = end_->begin();
      return n;
    }

template <typename iter>
Neurite::node_iterator<iter> Neurite::node_iterator<iter>::first() const {
      node_iterator n(*this);  // Copy ourselves
      n.current_ = begin_;
      n.node_current_ = begin_->begin();
      return n;
    }

template <typename iter>
Node& Neurite::node_iterator<iter>::dereference() { return *node_current_; }
    
template <typename iter>
Node& Neurite::node_iterator<iter>::dereference() const { return *node_current_; }

template <typename iter>
template< typename OtherIter>
bool Neurite::node_iterator<iter>::equal(const node_iterator<OtherIter>& other) const {
      return current_ == other.current_ && node_current_ == other.node_current_;
    }

template <typename iter>
void Neurite::node_iterator<iter>::increment() {
      if (current_ != end_) {
        ++node_current_;
        if (node_current_ == current_->end()) {
          ++current_;
          node_current_ = current_->begin();
        }
      }
    }
    
template <typename iter>
void Neurite::node_iterator<iter>::decrement() {
      if (node_current_ != begin_->begin()) {

        if (node_current_ == current_->begin()) {
          --current_;
          node_current_ = --(current_->end());
        } else {
          --node_current_;
        }
      }
    }

}  // namespace neurostr

#endif
