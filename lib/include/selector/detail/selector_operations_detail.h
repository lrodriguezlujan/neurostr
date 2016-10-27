#ifndef NEUROSTR_SELECTOR_SELECTOR_COMPOSITION_DETAIL_H_
#define NEUROSTR_SELECTOR_SELECTOR_COMPOSITION_DETAIL_H_

#include <functional>
#include <boost/iterator.hpp>

#include "core/traits.h"
#include "selector/selector_traits.h"

#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace selector {
namespace detail {
  
/**
* @brief F1 is composable with F2 (F1oF2) if types and arity match
**/
template <typename F1, typename F2>
constexpr bool is_composable =
    std::is_convertible<typename selector_func_traits<F2>::out_type,
                        typename selector_func_traits<F1>::in_type>::value &&
                        (selector_func_traits<F2>::out_set ==
                         selector_func_traits<F1>::in_set);

template <typename Fn,
            std::enable_if_t<selector_func_traits<Fn>::in_set>* = nullptr >
using selector_fn_in_reference = std::reference_wrapper<
                                    const typename selector_func_traits<Fn>::in_type>;


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
                        std::vector<std::reference_wrapper<const typename f1_traits::out_type>>,
                        const typename f1_traits::out_type&>;

  return[=](const in_type& r)->out_type {
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
            std::vector<std::reference_wrapper<const typename f1_traits::out_type>>, 
            const typename f1_traits::out_type&>;

  return[=](const in_type& r)->out_type {
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
        std::vector<std::reference_wrapper<const typename f1_traits::out_type>>, 
        const typename f1_traits::out_type&>;

  return[=](const in_type & b,const in_type& e)->out_type {
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
        std::vector<std::reference_wrapper<const typename f1_traits::out_type>>, 
        const typename f1_traits::out_type &>;

  return[=](const in_type & b,const in_type & e)->out_type {
    return f1(f2(b, e));
  };
};

template <typename F1, typename F2> 
constexpr auto compose_selector_pair(const F1& f1, const F2& f2) {

  // Static check that types match
  static_assert(is_composable<F1, F2>, "Functions are not composable");

  return f_comp(f1, f2);
};

} // Detail namespace
} // end selector ns
} // End neurostr ns 


#endif
