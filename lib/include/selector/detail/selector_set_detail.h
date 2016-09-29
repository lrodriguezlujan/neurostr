#ifndef NEUROSTR_SELECTOR_SELECTOR_SETOPS_DETAIL_H_
#define NEUROSTR_SELECTOR_SELECTOR_SETOPS_DETAIL_H_

#include <functional>
#include <algorithm>

#include "core/traits.h"
#include "selector/selector_traits.h"

#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace selector {
namespace detail {

  
// SELECTOR UNION  

template <typename F1, typename F2>
constexpr bool unionable =
    std::is_convertible<typename selector_func_traits<F2>::out_type,
                        typename selector_func_traits<F1>::out_type>::value &&
    std::is_convertible<typename selector_func_traits<F2>::in_type,
                        typename selector_func_traits<F1>::in_type>::value && 
                        selector_func_traits<F2>::out_set && 
                        selector_func_traits<F1>::out_set && 
                        selector_func_traits<F1>::in_set == selector_func_traits<F2>::in_set
                        ;
                        
// Union (Input: Set )
template <typename F1,
          typename F2,
          std::enable_if_t<selector_func_traits<F1>::in_set && selector_func_traits<F2>::in_set>* = nullptr>
constexpr auto f_union(const F1& f1, const F2& f2) {

  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using in_type = typename f1_traits::base_in_type;
  using out_type = std::vector<std::reference_wrapper<typename f1_traits::out_type>>;

  return[f1_ = f1, f2_ = f2](in_type & b, in_type& e)->out_type {
    auto sel1 = f1_(b, e);
    auto sel2 = f2_(b, e);
    // join
    sel1.insert(sel1.end(),sel2.begin(),sel2.end());
    return sel1;
  };
};

// Union (Input: single )
template <typename F1,
          typename F2,
          std::enable_if_t<!selector_func_traits<F1>::in_set && !selector_func_traits<F2>::in_set>* = nullptr>
constexpr auto f_union(const F1& f1, const F2& f2) {
  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using in_type = typename f1_traits::base_in_type;
  using out_type = std::vector<std::reference_wrapper<typename f1_traits::out_type>>;

  return[f1_ = f1, f2_ = f2](in_type & r)->out_type {
    auto sel1 = f1_(r);
    auto sel2 = f2_(r);
    // join
    sel1.insert(sel1.end(),sel2.begin(),sel2.end());
    return sel1;
  };
};
  
template <typename F1, typename F2> 
constexpr auto union_selector_pair(const F1& f1, const F2& f2) {

    // Static check that types match
    static_assert(unionable<F1, F2>, "Selector output not compatible");

    return f_union(f1, f2);
};


// SELECTOR INTERSECTION

template <typename F1, typename F2>
constexpr bool intersectable =
    std::is_convertible<typename selector_func_traits<F2>::out_type,
                        typename selector_func_traits<F1>::out_type>::value &&
    std::is_convertible<typename selector_func_traits<F2>::in_type,
                        typename selector_func_traits<F1>::in_type>::value && 
                        selector_func_traits<F2>::out_set &&
                        selector_func_traits<F1>::out_set && 
                        selector_func_traits<F1>::in_set == selector_func_traits<F2>::in_set;

// Intersection (Input: Set )
template <typename F1,
          typename F2,
          std::enable_if_t<selector_func_traits<F1>::in_set && selector_func_traits<F2>::in_set>* = nullptr>
constexpr auto f_intersection(const F1& f1, const F2& f2) {

  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using in_type = typename f1_traits::base_in_type;
  using out_type = std::vector<std::reference_wrapper<typename f1_traits::out_type>>;

  return[f1_ = f1, f2_ = f2](in_type & beg, in_type& end)->out_type {
    auto a = f1_(beg, end);
    auto b = f2_(beg, end);
    out_type ret;
    // NOT EFFICIENT
    for(auto it = a.begin(); it != a.end(); ++it){
        // Arhg we need to compare reference wrappers
        auto it2 = b.begin();
        for(; it2 != b.end() && it2->get()!=it->get(); ++it2);
        // Not found : add
        if(it2 != b.end()){
          ret.emplace_back(*it);
        }
    }
    return ret;
  };
};

// Intersection (Input: single )
template <typename F1,
          typename F2,
          std::enable_if_t<!selector_func_traits<F1>::in_set && !selector_func_traits<F2>::in_set>* = nullptr>
constexpr auto f_intersection(const F1& f1, const F2& f2) {
  // Function traits
  using f1_traits = selector_func_traits<F1>;
  using in_type = typename f1_traits::base_in_type;
  using out_type = std::vector<std::reference_wrapper<typename f1_traits::out_type>>;

  return[f1_ = f1, f2_ = f2](in_type & r)->out_type {
    auto a = f1_(r);
    auto b = f2_(r);
    out_type ret;
    // NOT EFFICIENT
    for(auto it = a.begin(); it != a.end(); ++it){
        // Arhg we need to compare reference wrappers
        auto it2 = b.begin();
        for(; it2 != b.end() && it2->get()!=it->get(); ++it2);
        // Not found : add
        if(it2 != b.end()){
          ret.emplace_back(*it);
        }
    }
    return ret;
  };
};
  
template <typename F1, typename F2> 
constexpr auto intersection_selector_pair(const F1& f1, const F2& f2) {

    // Static check that types match (SAME CRITERIA)
    static_assert(intersectable<F1, F2>, "Selector output not compatible");

    return f_intersection(f1, f2);
};  
  

/**
 * @brief Asymmetric difference bw vectors a,b
 * @return A \ B
 */
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
  
} // Detail namespace
} // end selector ns
} // End neurostr ns 

  
#endif
