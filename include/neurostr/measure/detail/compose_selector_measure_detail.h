#ifndef NEUROSTR_MEASURES_COMPOSE_DETAIL_H_
#define NEUROSTR_MEASURES_COMPOSE_DETAIL_H_

#include <iterator>
#include <vector>

#include <neurostr/core/traits.h>
#include <neurostr/selector/selector.h>
#include <neurostr/measure/measure_traits.h>

namespace neurostr {
namespace measure {
namespace detail {
  
  // Case 1: S input single output single
  template <typename S, typename M,
            std::enable_if_t< (!selector::selector_func_traits<S>::in_set) &&
                              (!selector::selector_func_traits<S>::out_set)>* = nullptr >
  auto composeSelectorMeasure_(const S& selector, const M& measure){
    
    using selector_traits = selector::selector_func_traits<S>;
    using measure_traits = measure_func_traits<M>;
    
    // Single-single
    return [s_ = selector, m_ = measure]( const typename selector_traits::in_type& v ) 
                  -> typename measure_traits::out_type {
                    return m_(s_(v));
    };
  };
  
  // Case 2: S input single output set
  template <typename S, typename M,
            std::enable_if_t< (!selector::selector_func_traits<S>::in_set) &&
                              (selector::selector_func_traits<S>::out_set)>* = nullptr >
  auto composeSelectorMeasure_(const S& selector, const M& measure){
    
    using selector_traits = selector::selector_func_traits<S>;
    using measure_traits = measure_func_traits<M>;
    
    // Single-single
    return [s_ = selector, m_ = measure](const typename selector_traits::in_type& v ) 
                  -> typename measure_traits::out_type {
                    auto aux = s_(v);
                    return m_(aux.begin(),aux.end());
    };
  };
  
  // Case 3: S input set output single
  template <typename S, typename M,
            std::enable_if_t< (selector::selector_func_traits<S>::in_set) &&
                              (!selector::selector_func_traits<S>::out_set)>* = nullptr >
  auto composeSelectorMeasure_(const S& selector, const M& measure){
    
    using measure_traits = measure_func_traits<M>;
    using in_ref_type = selector::detail::selector_fn_in_reference<S>;
    using in_it_type = typename std::vector<in_ref_type>::iterator;
    
    // Single-single
    return [s_ = selector, m_ = measure]( 
                  const in_it_type& b,
                  const in_it_type& e) -> typename measure_traits::out_type {
                    return m_(s_(b,e));
    };
  };
  
  // Case 4: S input set output set
  template <typename S, typename M,
            std::enable_if_t< (selector::selector_func_traits<S>::in_set) &&
                              (selector::selector_func_traits<S>::out_set)>* = nullptr >
  auto composeSelectorMeasure_(const S& selector, const M& measure){
    
    using measure_traits = measure_func_traits<M>;
    using in_ref_type = selector::detail::selector_fn_in_reference<S>;
    using in_it_type = typename std::vector<in_ref_type>::iterator;
    
    // Single-single
    return [s_ = selector, m_ = measure]( 
                  const in_it_type& b,
                  const in_it_type& e) -> typename measure_traits::out_type {
                    auto aux = s_(b,e);
                    return m_(aux.begin(),aux.end());
    };
  };
  
} // End detail
} // measure  
} // neurostr


#endif
