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
  using branch_type   = Branch;
  using tree_type     = tree<branch_type>;
  using tree_node     = tree_node_<branch_type>;
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

  // Constructors
  Neurite()
      : WithProperties()
      , tree_()  // Call constructor
      , id_(-1)
      , type_(NeuriteType::kUndefined)
      , root_is_soma_(false)
      , neuron_(){
        //set_root();
  };

  Neurite(int id)
      : WithProperties()
      , tree_()  // Call constructor
      , id_(id)
      , type_(NeuriteType::kUndefined)
      , root_is_soma_(false)
      , neuron_(){
        //set_root();
  };

  Neurite(int id, const NeuriteType& t)
      : WithProperties()
      , tree_()  // Call constructor
      , id_(id)
      , type_(t)
      , root_is_soma_(false)
      , neuron_(){
        //set_root();
  };

  // Copy and assign (Default)
  Neurite(const Neurite& n) = default;
  Neurite(Neurite&& n) = default;
  Neurite& operator=(const Neurite& n) = default;
  Neurite& operator=(Neurite&& n) = default;

  // Destructors
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
 
  // Compare TODO: Deep-comparison (tree)
  bool operator==(const Neurite& n) const { return (id_ == n.id_); }
  bool operator!=(const Neurite& n) const { return (id_ != n.id_); }
  
  // Getters
  const NeuriteType& type() const { return type_; }
  const int id() const { return id_; }
  bool root_is_soma() const{return root_is_soma_; }
  Neuron&  neuron() const { return *neuron_; }

  // Setters
  void type(const NeuriteType& t) { type_ = t; }
  void id(int id) { id_ = id; }
  void neuron(Neuron* const n) { neuron_ = n; }
  
  // Returns neurite max centrifugal order
  int max_centrifugal_order() const;
  
  // Root checker
  bool has_root() const { return begin_branch()->has_root(); }
  const Node& root() const { return begin_branch()->root(); }
  
  // ROOT SET
  // Empty root
  void set_root();
  void set_root(const Node& node);


  // Size and counter
  int size() const { return tree_.size(); }

  int node_count() const {
    int count = 0;
    for (auto it = begin_branch(); it != end_branch(); it++) count += it->size();
    return count;
  }
  
  /*** Property management ***/
  template <typename T> 
  auto add_property(const std::string& key, T v, bool recursive = true) {
    if (recursive) {
      for( auto it = begin_branch(); it != end_branch(); ++it)
        it->add_property(key,v, recursive);
    }
    return properties.set(key,v);
  };

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
   * @brief Tree iterator that ascends from the given tree node till the root.
   */
  class stem_iterator : public tree_type::iterator_base {
   public:
    // Constructors
    stem_iterator() 
      : tree_type::iterator_base() {};
      
    stem_iterator(tree_node* tn) 
      : tree_type::iterator_base(tn) {};
      
    stem_iterator(const typename tree_type::iterator_base& other) 
      : tree_type::iterator_base(other.node) {};

    // Operators
    bool operator==(const stem_iterator& other) const {
      return (this->node == other.node);
    };
    bool operator!=(const stem_iterator& other) const {
      return (this->node != other.node);
    };

    stem_iterator& operator++() {
      assert(this->node != nullptr);
      if(this->node->parent == nullptr){
        assert(this->node->prev_sibling != nullptr);
        this->node = this->node->prev_sibling;
      } else
        this->node = this->node->parent;
      return *this;
    };

    stem_iterator operator++(int) {
      stem_iterator copy = *this;
      ++(*this);
      return copy;
    };

    stem_iterator& operator+=(unsigned int num) {
      while (num > 0) {
        ++(*this);
        num--;
      }
      return *this;
    };
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
    // Constructor
    node_iterator() 
      : begin_()
      , current_()
      , end_()
      , node_current_(){};

    node_iterator(const iter& b, const iter& e)
        : begin_(b)
        , current_(b)
        , end_(e)
        , node_current_(b->begin()){};

    node_iterator(const iter& b, const iter& e, const iter& c)
        : begin_(b)
        , current_(c)
        , end_(e)
        , node_current_(c->begin()){};

    node_iterator(const iter& b,
                  const iter& e,
                  const iter& c,
                  const typename branch_type::iterator& nodeit)
        : begin_(b), current_(c), end_(e), node_current_(nodeit){};
        

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
    branch_type::iterator node_current_;

   public:
    iter begin() const { return begin_; }
    iter end() const { return end_; }
    
    iter current() const { return current_; }
    iter branch() const { return current_; }
    branch_type::iterator node() const { return node_current_; }
    // Neurite&  neurite() const { return neurite_; }
    // Neuron& neuron() const { return neurite_->neuron(); }
    
    bool empty() const { return tree_.empty(); }
    Neurite& neurite() const { return current_->neurite(); } 
    Neuron& neuron() const { return current_->neurite().neuron(); }
    

    node_iterator<iter> last() const {
      node_iterator n(*this);  // Copy ourselves
      n.current_ = end_;
      n.node_current_ = end_->begin();
      return n;
    }

    node_iterator<iter> first() const {
      node_iterator n(*this);  // Copy ourselves
      n.current_ = begin_;
      n.node_current_ = begin_->begin();
      return n;
    }

    // FACADE METHODS
   private:
    friend class boost::iterator_core_access;
    template <typename OtherIter> friend class node_iterator;

    Node& dereference() { return *node_current_; }
    Node& dereference() const { return *node_current_; }

    template< typename OtherIter>
    bool equal(const node_iterator<OtherIter>& other) const {
      return current_ == other.current_ && node_current_ == other.node_current_;
    }

    void increment() {
      if (current_ != end_) {
        ++node_current_;
        if (node_current_ == current_->end()) {
          ++current_;
          node_current_ = current_->begin();
        }
      }
    }

    void decrement() {
      if (node_current_ != begin_->begin()) {

        if (node_current_ == current_->begin()) {
          --current_;
          node_current_ = --(current_->end());
        } else {
          --node_current_;
        }
      }
    }
  };  // End node iterator

  /**********************
   *  END ITERATORS     *
   **********************/

 public:
  
  /**** Branch iterators ***/
  branch_iterator begin_branch() const { return tree_.begin(); }
  branch_iterator end_branch() const { return tree_.end(); }
  
  // Starts with the given branch and iterates only over its subtree
  branch_iterator begin_branch_subtree(const typename tree_type::iterator_base& other) const {
    return Neurite::branch_iterator(other);
  }
  branch_iterator end_branch_subtree(const typename tree_type::iterator_base& other) const {
    tree_node* tn = other.node;

    if (tn == nullptr)
      return Neurite::branch_iterator(other);
    else {
      while (tn->next_sibling == nullptr) {
        tn = tn->parent;
        if (tn == nullptr) return Neurite::branch_iterator(tn);
      }
      // The next "node"
      return Neurite::branch_iterator(tn->next_sibling);
    }
  }

  // Fixed centrifugal order (from the root)
  fixed_order_iterator begin_fixed_order(std::uint32_t order) const { return tree_.begin_fixed(tree_.begin(), order); }
  fixed_order_iterator end_fixed_order(std::uint32_t order) const { return tree_.end_fixed(tree_.begin(), order); }
  
  // Fixed order (only in the subtree from it
  fixed_order_iterator begin_fixed_order(const typename tree_type::iterator_base& it, std::uint32_t order) const {
    return tree_.begin_fixed(it, order - tree_type::depth(it));
  }
  fixed_order_iterator end_fixed_order(const typename tree_type::iterator_base& it, std::uint32_t order) const {
    return tree_.end_fixed(it, order - tree_type::depth(it));
  }

  // Terminal branch iterator
  terminal_branch_iterator begin_leaf() const { return tree_.begin_leaf(); }
  terminal_branch_iterator end_leaf() const { return tree_.end_leaf(); }
  
  // Terminal branch in the subtree of a node
  terminal_branch_iterator begin_leaf(const typename tree_type::iterator_base& top) const {
    return tree_.begin_leaf(top);
  }
  terminal_branch_iterator end_leaf(const typename tree_type::iterator_base& top) const { return tree_.end_leaf(top); }

  // Stem iterator
  stem_iterator begin_stem(const typename tree_type::iterator_base& it) const { return stem_iterator(it); }
  stem_iterator end_stem(const typename tree_type::iterator_base& it) const { return stem_iterator(tree_.head); }
  
  // Iterates over branch children
  tree_type::sibling_iterator begin_children(const tree_type::iterator_base& it ) const {
    return tree_.begin(it);
  };
  
  tree_type::sibling_iterator end_children(const tree_type::iterator_base& it ) const {
    return tree_.end(it);
  };

  // NODE iterators given a branch iterator
  template <typename iter> node_iterator<iter> begin_node(iter& it) {
    return (node_iterator<iter>(it, end_branch()));
  }

  template <typename iter> node_iterator<iter> end_node(iter& it) {
    return (node_iterator<iter>(it, end_branch()).last());
  }

  /** This unfold any branch iterator into a node iterator seamlessly*/
  template <typename iter> node_iterator<iter> begin_node(iter& i, iter& e) {
    return (node_iterator<iter>(i, e));
  }
  template <typename iter> node_iterator<iter> end_node(iter& i, iter& e) {
    return (node_iterator<iter>(i, e).last());
  }

  // Begin node iterators
  base_node_iterator begin_node() {
    return node_iterator<branch_iterator>(begin_branch(), end_branch());
  }

  base_node_iterator end_node() {
    return node_iterator<branch_iterator>(begin_branch(), end_branch()).last();
  }
  
  /*** Find methods ****/
  branch_iterator find(const Branch& b);
  
  base_node_iterator find(const Node& n) { 
    return std::find(begin_node(), end_node(), n); 
  }

  // Diferent name different return...find should work like select
  base_node_iterator find(Node::id_type id) { return find(Node(id));}

  template<typename iter>
  std::vector<base_node_iterator> find(iter b, iter e) {
    // Check iter type
    static_assert(
      std::is_convertible<typename std::iterator_traits<iter>::value_type, 
                          typename Node::id_type>::value);

    std::vector<base_node_iterator> tmp;
    for (iter it = b; it != e; ++it) 
      tmp.emplace_back(find(*it));
      
    return tmp;
  };
  
  /*** Branch-related methods **/
  
  // Get given branch sibiling branch
  template <typename iter> 
  iter sibling(iter position) {
    assert(position.node != nullptr);
    iter ret(position);  // Copy
    if (position.node->prev_sibling == nullptr)
      ret.node = position.node->next_sibling;
    else
      ret.node = position.node->prev_sibling;
    return ret;
  };
  

/*****
 *  FILTERS
 *
 *  to be used with filter_iterator from boost- Creates lambda expressions
 *  that can be used as arguments of boost::filter_iterator predicate
 *
 ******/

// Node filters

// FILTERS
/*static auto node_filter_inbox(const point_type& min_corner, const point_type& max_corner) {
  auto bounding_box = boost::geometry::model::box<point_type>(min_corner, max_corner);
  // Return lambda expresion that takes node and checks if
  // its position is inside de bbox
  return[bb = bounding_box](const Node & n)->bool {
    return boost::geometry::covered_by(n.position(), bb);
  };
}

static  auto node_filter_distance(const point_type& x, float min_value, float max_value) {
    return[ p = x, min = min_value, max = max_value ](const Node& n)->bool {
                                                     auto dist = boost::geometry::distance(p, n.position());
                                                      return dist >= min && dist < max;
    };
}


static auto branch_filter_inbox(const point_type& min_corner, const point_type& max_corner, bool strict) {
  auto bounding_box = boost::geometry::model::box<point_type>(min_corner, max_corner);
  // Return lambda expresion that takes node and checks if
  // its position is inside de bbox
    return [bb = bounding_box, strict = strict ](const branch_type & b)->bool {
        for(auto it = b.begin(); it != b.end(); ++it)
          if( strict ^ boost::geometry::covered_by(it->position(), bb)) return !strict; // Note: ^ is xor
            return strict;
    };
}

static auto branch_filter_distance(const point_type& x, float min_value, float max_value, bool strict) {

  return[ p = x, min = min_value, max = max_value, strict = strict ](const branch_type & b)->bool {
                                                                      float dist;
    for (auto it = b.begin(); it != b.end(); ++it) {
      dist = boost::geometry::distance(p, it->position());
      if (strict ^ (dist >= max && dist < min)) return !strict;
    }
    return strict;
  };
}

static auto branch_filter_order(const point_type& x, int min_order, int max_order) {
  return[ p = x, min = min_order, max = max_order ](const branch_type & b)->bool {
                                                     return b.order() >= min && b.order() < max;
  };
}*/

/***** END FILTERS ***/

  /** INSERT / DELETE NODES **/

  // Add nodes
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
        // Split if we are not inserting in the last position
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
        branch_type b{id, pos.branch()->order() + 1, *pos};  // Create branch
        b.neurite(this); // Set ourselves as neurite
        
        // Add node
        b.push_back(node);
        
        // Add new branch
        auto aux = tree_.append_child(pos.branch(), b);
        aux->set_nodes_branch(); // Needed. Append child copies so..
        
        // POST INSERT
        return node_iterator<iter>(pos.begin(),pos.end(), aux, aux->begin());
      }      
  }
  
  // Node - based function
  base_node_iterator insert_node(Node::id_type parent_id, const Node& node);

  // Add branch
  template <typename iter> 
  iter append_branch(iter pos, Branch& b) { 
    Branch b_copy(b);
    b_copy.neurite(this);
    return tree_.append_child(pos, b_copy); 
  }
  
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
      branch_type b = pos.branch()->split(pos.node());
      b.neurite(this); 
      b.id(id);
      b.order(pos.branch()->order()+1);

      // Preppend child
      branch_iterator new_pos = tree_.prepend_child(pos.branch(), b);
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

// What it doeS?
  void correct();
  void remove_null_segments();


  // Scale
  void scale(float r);
  void scale(float rx, float ry, float rz);

  // Traslate
  void traslate(const point_type& p);

  // Rotate
  void rotate(const Eigen::Quaternionf& q);

  // Simplify
  void simplify(float eps = -1.5);

  // Order desc according to azimuth
  void childOrder();

  // Determine the index of a node in the range of siblings to which it belongs.
  unsigned int index(sibling_iterator it) const {
    return tree_.index(it);
  }

  friend std::ostream& operator<<(std::ostream&, const Neurite&);

  private:

  void reassign_branch_ids();
  
};  // Class Neurite

// Auxiliar functions
std::ostream& operator<<(std::ostream& os, const Neurite& n);

}  // namespace neurostr

#endif
