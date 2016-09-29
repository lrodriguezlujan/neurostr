#ifndef NEUROSTR_SELECTOR_SELECTOR_SETOPS_H_
#define NEUROSTR_SELECTOR_SELECTOR_SETOPS_H_

#include <functional>
#include <boost/iterator.hpp>

#include "core/traits.h"
#include "selector/selector_traits.h"
#include "selector/selector_operations.h"
#include "selector/detail/selector_set_detail.h"

#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace selector {

// Union

/**
 * @brief Recursive template for selector union
 * @param f1 First function
 * @param f2 Second function
 * @param fns.. Rest..
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) != 0>* = nullptr>
constexpr auto union_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return union_selector(detail::union_selector_pair(f1, f2), fns...);
};


/**
 * @brief Recursive template for selector union. Base case.
 * @param f1 First function
 * @param f2 Second function
 * @return f1of2
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) == 0>* = nullptr>
constexpr auto union_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return detail::union_selector_pair(f1, f2);
};

// Intersection

/**
 * @brief Recursive template for selector intersection
 * @param f1 First function
 * @param f2 Second function
 * @param fns.. Rest..
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) != 0>* = nullptr>
constexpr auto intersection_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return intersection_selector(detail::intersection_selector_pair(f1, f2), fns...);
};


/**
 * @brief Recursive template for selector intersection. Base case.
 * @param f1 First function
 * @param f2 Second function
 * @return f1of2
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) == 0>* = nullptr>
constexpr auto intersection_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return detail::intersection_selector_pair(f1, f2);
};

// Aymmetric difference

/**
 * @brief Assymetric difference 
 * @param f_1 Base set
 * @param f_2 Difference set
 * @note F1 inputs a set, F2 inputs a set
 */
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

/**
 * @brief Assymetric difference 
 * @param f_1 Base set
 * @param f_2 Difference set
 * @note F1 inputs single, F2 inputs single
 */
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

  
} // end selector ns
} // end neurostr ns

#endif
