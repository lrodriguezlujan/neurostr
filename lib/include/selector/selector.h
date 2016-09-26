#ifndef NEUROSTR_SELECTOR_SELECTOR_H_
#define NEUROSTR_SELECTOR_SELECTOR_H_

#include <functional>

#include <boost/iterator.hpp>

#include "core/traits.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace selector {

// Selector tags -> scales upwards (from a node we can get its branch, neurite and neuron)
struct selector_neuron_tag {
  using value_type = Neuron;
};
using neuron_reference  = std::reference_wrapper<Neuron>;

struct selector_neurite_tag : public selector_neuron_tag {
  using value_type = Neurite;
};
using neurite_reference  = std::reference_wrapper<Neurite>;

struct selector_branch_tag : public selector_neurite_tag {
  using value_type = Branch;
};
using branch_reference  = std::reference_wrapper<Branch>;

struct selector_node_tag : public selector_branch_tag {
  using value_type = Node;
};
using node_reference  = std::reference_wrapper<Node>;

template <typename T>
using selector_reference = std::reference_wrapper<T>;

template <typename T>
using selector_iterator = typename std::vector<selector_reference<T>>::iterator;

template <typename T> struct selector_tag {
  using base_T = std::remove_const_t<std::remove_reference_t<T>>;
  using type = std::conditional_t<
      std::is_same<base_T, selector_neuron_tag::value_type>::value,
      selector_neuron_tag,
      std::conditional_t<std::is_same<base_T, selector_neurite_tag::value_type>::value,
                         selector_neurite_tag,
                         std::conditional_t<std::is_same<base_T, selector_branch_tag::value_type>::value,
                                            selector_branch_tag,
                                            selector_node_tag>>>;
};

template <bool, typename T>
struct type_chooser {
  using type = std::remove_reference_t<std::remove_const_t<T>>; // False, is a reference
};

template <typename T>
struct type_chooser<true,T> {
  using type = typename T::value_type::type; // True: Is an iterator to a wrapped reference
};



// Selector func traits
template <typename F> struct selector_func_traits {
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  constexpr static bool out_set = (traits::is_vector<typename base_traits::result_type>::value);

  using out_type = typename type_chooser<out_set, typename base_traits::result_type>::type;

  // In "set" selector funcs accept iterators!
  using base_in_type = typename std::remove_reference_t<std::remove_const_t<typename base_traits::template arg<0>>>;
  using in_type = typename type_chooser<in_set, base_in_type>::type;
};

// Is composable checker
template <typename F1, typename F2>
constexpr bool is_composable =
    std::is_convertible<typename selector_func_traits<F2>::out_type,
                        typename selector_func_traits<F1>::in_type>::value &&
                        (!selector_func_traits<F2>::out_set ||
                         selector_func_traits<F1>::in_set);

namespace detail {
  
  template <typename Fn,
            std::enable_if_t<selector_func_traits<Fn>::in_set>* = nullptr >
  using selector_fn_in_reference = std::reference_wrapper<
                                    typename selector_func_traits<Fn>::in_type>;


// Compose (Input: single)
template <typename F1,
          typename F2,
          std::enable_if_t<!selector_func_traits<F2>::in_set && selector_func_traits<F2>::out_set>* = nullptr>
constexpr auto f_comp(const F1& f1, const F2& f2) {

  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using f2_traits = selector_func_traits<F2>;
  using in_type = typename f2_traits::base_in_type;
  using out_type =
      std::conditional_t<f1_traits::out_set, 
                        std::vector<std::reference_wrapper<typename f1_traits::out_type>>,
                        typename f1_traits::out_type>;

  return[=](in_type& r)->out_type {
    auto sel = f2(r);
    return f1(sel.begin(), sel.end());
  };
};

// Compose (Input: single)
template <typename F1,
          typename F2,
          std::enable_if_t<!selector_func_traits<F2>::in_set && !selector_func_traits<F2>::out_set>* = nullptr>
constexpr auto f_comp(const F1& f1, const F2& f2) {
  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using f2_traits = selector_func_traits<F2>;
  using in_type = typename f2_traits::base_in_type;
  using out_type =
      std::conditional_t<f1_traits::out_set, 
            std::vector<std::reference_wrapper<typename f1_traits::out_type>>, 
            typename f1_traits::out_type>;

  return[=](in_type& r)->out_type {
    return f1(f2(r));
  };
};

// Compose (Input: Set )
template <typename F1,
          typename F2,
          std::enable_if_t<selector_func_traits<F2>::in_set&& selector_func_traits<F2>::out_set>* = nullptr>
constexpr auto f_comp(const F1& f1, const F2& f2) {

  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using f2_traits = selector_func_traits<F2>;
  using in_type = typename f2_traits::base_in_type;
  using out_type =
      std::conditional_t<f1_traits::out_set, 
        std::vector<std::reference_wrapper<typename f1_traits::out_type>>, 
        typename f1_traits::out_type>;

  return[=](in_type & b, in_type& e)->out_type {
    auto sel = f2(b, e);
    return f1(sel.begin(), sel.end());
  };
};

// Compose (Input: Set )
template <typename F1,
          typename F2,
          std::enable_if_t<selector_func_traits<F2>::in_set && !selector_func_traits<F2>::out_set>* = nullptr>
constexpr auto f_comp(const F1& f1, const F2& f2) {
  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using f2_traits = selector_func_traits<F2>;
  using in_type = typename f2_traits::base_in_type;
  using out_type =
      std::conditional_t<f1_traits::out_set, 
        std::vector<std::reference_wrapper<typename f1_traits::out_type>>, 
        typename f1_traits::out_type>;

  return[=](in_type & b, in_type & e)->out_type {
    return f1(f2(b, e));
  };
};

} // Detail namespace

// Variadic template (base case)
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) != 0>* = nullptr>
constexpr auto compose_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return compose_selector(compose(f1, f2), fns...);
};

// Variadic template (stop)
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) == 0>* = nullptr>
constexpr auto compose_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return compose(f1, f2);
};


template <typename F1, typename F2> 
constexpr auto compose(const F1& f1, const F2& f2) {

  // Static check that types match
  static_assert(is_composable<F1, F2>, "Functions are not composable");

  return detail::f_comp(f1, f2);
};

// Unique selector
// IN: SET OUT: SET
template <typename T>
struct unique_selector{
  using reference = std::reference_wrapper<T>;
  std::vector<reference> operator() (const typename std::vector<reference>::iterator & b,
                                     const typename std::vector<reference>::iterator & e){
    // Copy vector
    std::vector<reference> ret(b,e);
    
    // unique
    std::unique(ret.begin(),ret.end(), [](const reference& a, 
                                          const reference &b){
      return a.get() == b.get();
    });
    
    return ret;
  }
};

// Join factory ( This creates a selector  - out single)
template <typename F,
          std::enable_if_t<!selector_func_traits<F>::out_set>* = nullptr>
constexpr auto join_selector_factory(const F& f){
   
   using f_traits      = selector_func_traits<F>;
   static_assert(!f_traits::in_set, "Join is only implemented for single funcs");
   
   using reference_out = std::reference_wrapper<typename f_traits::out_type>;
   using reference_in  = std::reference_wrapper<typename f_traits::in_type>;
   
   // Create join function
   return [f_ = f](const typename std::vector<reference_in>::iterator& b, 
                   const typename std::vector<reference_in>::iterator& e)
                    -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      for (auto it = b; it != e; ++it) {
        ret.emplace_back(f_(it->get()));
      }
      return ret;
   };
            
};

// Join factory ( This creates a selector  - out set)
template <typename F,
          std::enable_if_t<selector_func_traits<F>::out_set>* = nullptr>
constexpr auto join_selector_factory(const F& f){
   
   using f_traits      = selector_func_traits<F>;
   static_assert(!f_traits::in_set, "Join is only implemented for single funcs");
   
   using reference_out = std::reference_wrapper<typename f_traits::out_type>;
   using reference_in  = std::reference_wrapper<typename f_traits::in_type>;
   
   // Create join function
   return [f_ = f](const typename std::vector<reference_in>::iterator& b, 
                   const typename std::vector<reference_in>::iterator& e)
                    -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      for (auto it = b; it != e; ++it) {
        auto sel = f_(it->get());
        for(auto el = sel.begin() ; el != sel.end() ; ++el){
          ret.emplace_back(el->get());
        }
      }
      return ret;
   };            
};

namespace detail {
  
  template<typename T>
  std::vector<std::reference_wrapper<T>> reference_vector_diff(
    const std::vector<std::reference_wrapper<T>>& a,
    const std::vector<std::reference_wrapper<T>>& b){
      std::vector<std::reference_wrapper<T>> ret;
      
      for(auto it = a.begin(); it != a.end(); ++it){
        // Arhg we need to compare reference wrappers
        auto it2 = b.begin();
        for(; it2 != b.end() && it2->get()!=it->get(); ++it2);
        // Not found : add
        if(it2 == b.end()){
          ret.emplace_back(*it);
        }
      }
      return ret;
  };
}

// Diff selector factory for in_set functions
template <typename F1, typename F2, 
          std::enable_if_t<selector_func_traits<F1>::in_set>* = nullptr>
constexpr auto diff_selector_factory(const F1& f_1, const F2& f_2){
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;
  using reference_out = std::reference_wrapper<typename f1_traits::out_type>;
  using iterator_in = typename std::vector<
                                std::reference_wrapper<
                                  typename f1_traits::in_type>>::iterator;
  
  // Check that both selectors return a set
  static_assert(f1_traits::out_set, "First argument doesnt select a set");
  static_assert(f2_traits::out_set, "Second argument doesnt select a set");
  
  // Check that both input to the same type
  static_assert(f1_traits::in_set == f2_traits::in_set, "Input arity doesnt match");
  // Check that type match
  static_assert(std::is_convertible<typename f1_traits::in_type,
                                    typename f2_traits::in_type>::value, "Input type doesnt match");
  
  // Create function
  return [f1_ = f_1, f2_ = f_2](
                   const iterator_in& b, 
                   const iterator_in& e)
                   -> std::vector<reference_out> {
      return detail::reference_vector_diff(f1_(b,e),f2_(b,e));
   };            
};

// Diff selector factory for NOT in_set functions
template <typename F1, typename F2, 
          std::enable_if_t<!selector_func_traits<F1>::in_set>* = nullptr>
constexpr auto diff_selector_factory(const F1& f_1, const F2& f_2){
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;
  using reference_out = std::reference_wrapper<typename f1_traits::out_type>;
  
  // Check that both selectors return a set
  static_assert(f1_traits::out_set, "First argument doesnt select a set");
  static_assert(f2_traits::out_set, "Second argument doesnt select a set");
  
  // Check that both input to the same type
  static_assert(f1_traits::in_set == f2_traits::in_set, "Input arity doesnt match");
  // Check that type match
  static_assert(std::is_convertible<typename f1_traits::in_type,
                                    typename f2_traits::in_type>::value, "Input type doesnt match");
  
  // Create function
  return [f1_ = f_1, f2_ = f_2](typename f1_traits::in_type& r)
                   -> std::vector<reference_out> {
      return detail::reference_vector_diff(f1_(r),f2_(r));
   };            
};


}
}

#endif
