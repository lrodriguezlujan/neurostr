#ifndef NEUROSTR_BASE_REFERENCES_H_
#define NEUROSTR_BASE_REFERENCES_H_

#include <boost/tti/has_member_function.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include "utils/traits.h"
#include "base/node.h"
#include "base/branch.h"
#include "base/tree.hh"

namespace neurostr {
  
// Forward definitions
template <typename Value> class reference_base;
class Neurite;
class Neuron;

// Generate metafunctions
namespace detail {
  
  
  //BOOST_TTI_HAS_MEMBER_FUNCTION(node);
  //BOOST_TTI_HAS_MEMBER_FUNCTION(branch);
  //BOOST_TTI_HAS_MEMBER_FUNCTION(neurite);
  
  //boost::function_types::const_qualified
  //boost::mpl::vector<>
  template<typename T>
  struct has_neurite_method {
  private:
    typedef std::true_type yes;
    typedef std::false_type no;
   
    template<typename U> static auto test(int) -> decltype(std::declval<U>().neurite() == nullptr, yes());
    template<typename> static no test(...);
   
  public:
   
    static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
  };
  
  template<typename T>
  struct has_node_method {
  private:
    typedef std::true_type yes;
    typedef std::false_type no;
   
    template<typename U> static auto test(int) -> decltype(std::declval<U>().node() == Branch::iterator(), yes());
    template<typename> static no test(...);
   
  public:
   
    static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
  };
  
    template<typename T>
  struct has_branch_method {
  private:
    typedef std::true_type yes;
    typedef std::false_type no;
   
    template<typename U> static auto test(int) -> decltype(std::declval<U>().branch() , yes());
    template<typename> static no test(...);
   
  public:
   
    static constexpr bool value = std::is_same<decltype(test<T>(0)),yes>::value;
  };
  
  template <typename Iter>
  /*constexpr bool is_filter_iterator = traits::is_base_of_template<Iter, boost::indirect_iterator>::value || 
                                    traits::is_base_of_template<Iter, boost::filter_iterator>::value;*/
  
  constexpr bool is_filter_iterator = traits::is_base_of_template<Iter, boost::filter_iterator>::value;
                                    
  template <typename T>
  using plain_type = std::remove_reference_t<std::remove_const_t<T>>;
}



template <typename Value> class reference_base {

 public:
  // Node ref
  using node_ref = std::conditional_t<std::is_const<Value>::value, Branch::const_iterator, Branch::iterator>;
  // Branch ref
  using branch_ref = tree<Branch>::iterator_base;
  // Neurite ref
  using neurite_ref = std::conditional_t<std::is_const<Value>::value, const Neurite*, Neurite*>;
  // Neuron ref
  using neuron_ref = std::conditional_t<std::is_const<Value>::value, const Neuron*, Neuron*>;

  using base_value_type = std::remove_const_t<Value>;
  using value_type = detail::plain_type<Value>;

  reference_base() : node_(), branch_(), neurite_(nullptr), neuron_(nullptr) {};
  reference_base(const neuron_ref& neuron,
                 const neurite_ref& neurite = nullptr,
                 const branch_ref& branch = branch_ref(),
                 const node_ref& node = node_ref())
      : node_(node), branch_(branch), neurite_(neurite), neuron_(neuron) {};

  reference_base(const neurite_ref& neurite, const branch_ref& branch = branch_ref(), const node_ref& node = node_ref())
      : node_(node), branch_(branch), neurite_(neurite), neuron_(neurite->neuron()) {};

  // Copy from other value
  template <typename OtherValue>
  reference_base(const reference_base<OtherValue>& other,
                 std::enable_if_t<std::is_const<OtherValue>::value || !std::is_const<Value>::value, Value>* = nullptr)
      : node_(other.node_), branch_(other.branch_), neurite_(other.neurite_), neuron_(other.neuron_) {};

  // Move from other value
  template <typename OtherValue>
  reference_base(reference_base<OtherValue>&& other,
                 std::enable_if_t<std::is_const<OtherValue>::value || !std::is_const<Value>::value, Value>* = nullptr)
      : node_(other.node_), branch_(other.branch_), neurite_(other.neurite_), neuron_(other.neuron_) {};
  
  // Create from any iterator that points to either neurite or Neuron (Not filter or indirect)
  template <typename Iter,
            typename std::enable_if_t<
            !traits::is_base_of_template<Iter, reference_base>::value &&
            !detail::is_filter_iterator<Iter> &&
            (std::is_same<value_type, Neuron>::value ||  std::is_same<value_type, Neurite>::value) &&
            std::is_same< detail::plain_type<typename Iter::value_type>, Neurite>::value>* = nullptr>
  reference_base(const Iter& it)
      : node_(), branch_(), neurite_( &(*it)), neuron_(it->neuron()) {};

  template <typename Iter,
            typename std::enable_if_t<
            !traits::is_base_of_template<Iter, reference_base>::value && // This lines avoids to collide with copy/move operators from other refs
            !detail::is_filter_iterator<Iter> &&
            std::is_same<value_type, Neuron>::value &&
            std::is_same< detail::plain_type<typename Iter::value_type>, Neuron>::value>* = nullptr>
  reference_base(const Iter& it)
      : node_(), branch_(), neurite_(), neuron_(&(*it)) {};

  // Any object that has branch and neurite methods
  // has_member_function_neurite<T,neurite_ref>
  // has_member_function_branch<T,branch_ref>
  // has_member_function_node<T,node_ref>
  
  template <typename T,
            typename std::enable_if_t<
            !traits::is_base_of_template<T, reference_base>::value && // This lines avoids to collide with copy/move operators from other refs
            std::is_same<value_type, Branch>::value && // We are creating a Branch reference
            detail::has_neurite_method<T>::value &&
            detail::has_branch_method<T>::value >* = nullptr>
  reference_base(const T& obj)
      : node_(), branch_(obj.branch()), neurite_(obj.neurite()), neuron_(obj.neurite()->neuron()) {};
  
  // Same for node
  template <typename T,
            typename std::enable_if_t<
            !traits::is_base_of_template<T, reference_base>::value && // This line avoids to collide with copy/move operators from other refs
            std::is_same<value_type, Node>::value && // We are creating a Node reference
            detail::has_node_method<T>::value &&
            detail::has_branch_method<T>::value && 
            detail::has_neurite_method<T>::value >* = nullptr>
  reference_base(const T& obj)
      : node_(obj.node()), branch_(obj.branch()), neurite_(obj.neurite()), neuron_(obj.neurite()->neuron()) {};
  
  // Create from indirect/¿filter? iterators
  template <typename Iter,
            typename std::enable_if_t<detail::is_filter_iterator<Iter>>* = nullptr>
  reference_base(const Iter& it)
      : reference_base(it.base()) {};
  
  // Assignation
  template <typename OtherValue> reference_base& operator=(const reference_base<OtherValue>& other) {
    static_assert(std::is_const<OtherValue>::value || !std::is_const<Value>::value);
    this->branch_ = other.branch_;
    this->node_ = other.node_;
    this->neurite_ = other.neurite_;
    this->neuron_ = other.neuron_;
    return *this;
  }

  template <typename OtherValue> reference_base& operator=(reference_base<OtherValue>&& other) {
    static_assert(std::is_const<OtherValue>::value || !std::is_const<Value>::value);
    this->branch_ = other.branch_;
    this->node_ = other.node_;
    this->neurite_ = other.neurite_;
    this->neuron_ = other.neuron_;
    return *this;
  }

  // Acces members
  branch_ref branch() const { return branch_; }
  node_ref node() const { return node_; }
  neurite_ref neurite() const { return neurite_; }
  neuron_ref neuron() const { return neuron_; }

  void node( const node_ref& node) {node_ = node;}
  void branch( const branch_ref& branch) {branch_ = branch;}
  void neurite(const neurite_ref& neurite) { neurite_ = neurite; }
  void neuron(const neuron_ref& neuron) { neuron_ = neuron; }

  bool valid() const { return branch_.node != nullptr && branch_->end() != node_; }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Node>::value, U&> operator*() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return *node_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Branch>::value, U&> operator*() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return *branch_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neurite>::value, U&> operator*() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return *neurite_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neuron>::value, U&> operator*() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return *neuron_;
  }

  // ->

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Branch>::value, U*> operator->() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return branch_.operator->();
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neurite>::value, U*> operator->() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return neurite_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neuron>::value, U*> operator->() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return neuron_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Node>::value, U*> operator->() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return node_.operator->();
  }
  
  // GET
  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neurite>::value, U*> get() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return neurite_;
  }

  template <typename... Dummy, typename U = Value>
  std::enable_if_t<std::is_same<std::remove_const_t<U>, Neuron>::value, U*> get() const {
    static_assert(sizeof...(Dummy) == 0, "Do not specify template arguments");
    return neuron_;
  }

  reference_base parent_node() const {

    reference_base parent(*this);  // Copy ourselves

    if (branch_.node != nullptr) {

      // We are at the begining
      if (branch_->begin() == node_) {
        // Check if we can go up
        parent.branch_ = branch_ref(branch_.node->parent);
        if (branch_.node->parent != nullptr) {
          parent.node_ = --parent.branch_->end();
        }
      } else {
        --parent.node_;
      }
    }
    return parent;
  }

  bool operator==(const reference_base& other) const { return **this == *other; }

  bool operator!=(const reference_base& other) const { return **this != *other; }

 private:
  node_ref node_;
  branch_ref branch_;
  neurite_ref neurite_;
  neuron_ref neuron_;

  template <typename OtherValue> friend class reference_base;
};  // Referece base

// Sugar
using node_reference = reference_base<Node>;
using const_node_reference = reference_base<const Node>;

using branch_reference = reference_base<Branch>;
using const_branch_reference = reference_base<const Branch>;

using neurite_reference = reference_base<Neurite>;
using const_neurite_reference = reference_base<const Neurite>;

using neuron_reference = reference_base<Neuron>;
using const_neuron_reference = reference_base<const Neuron>;

// Create reference from indirect iterator to reference

// Indirect iterators
template<  typename T, typename Iter>
std::enable_if_t< !traits::is_base_of_template<typename Iter::value_type, reference_base>::value,
                  typename Iter::value_type > reference_from_iterator(const Iter& i){
                    return reference_base<T>(*i);
}

                  

} // Neurostr namespace

#endif