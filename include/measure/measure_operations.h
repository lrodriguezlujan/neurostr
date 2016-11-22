#ifndef NEUROSTR_MEASURES_MEASURE_OPS_H_
#define NEUROSTR_MEASURES_MEASURE_OPS_H_

#include "measure/measure_traits.h"
#include "measure/aggregator_traits.h"

#include "measure/detail/compose_selector_measure_detail.h"
#include "measure/detail/measure_combine_tuple_detail.h"

namespace neurostr {
namespace measure {
  
/**
 * @brief Convert a single-input measure into a set measure that applies the
 * original measure to each element of the input set
 * 
 * @param f Original single-input measure
 * 
**/
template <typename Fn>
auto measureEach(const Fn& f){
  // Check that f isnt a set function
  static_assert(!measure_func_traits<Fn>::in_set, "Fn is a set function");
  
  // Types
  using iterator_type = typename std::vector< detail::measure_fn_reference<Fn> >::iterator;
  using ret_type = std::vector<typename measure_func_traits<Fn>::out_type>;
                          
  // Return (create) function
  return [f_ = f](const iterator_type& b, const iterator_type& e ) ->  ret_type{
    ret_type ret;
    for (auto it = b ; it != e ; ++it) {
      ret.emplace_back( f_(it->get()) );
    }
    return ret;
  };
};

/**
 * @brief Convert a single-input measure into a set measure that applies the
 * original measure to each element of the input set and then aggregates the 
 * output.
 * 
 * @param f Original single-input measure
 * @param aggr Aggregator function
**/
template <typename Fn, typename Aggr>
auto measureEachAggregate(const Fn& f, const Aggr& aggr){
  using measure_traits = measure_func_traits<Fn>;
  using aggr_traits = aggregate::aggr_func_traits<Aggr>;
  
  // Check that f isnt a set function
  static_assert(!measure_traits::in_set, "Fn is a set function");
  // Check that types match
  static_assert(
    std::is_convertible<typename measure_traits::out_type, typename aggr_traits::in_type>::value, 
    "Incompatible types" );
  
  // Types
  using iterator_type = typename std::vector< detail::measure_fn_reference<Fn> >::iterator;
                          
  // Return (create) function
  return [f_ = f, a_ = aggr](const iterator_type& b, const iterator_type& e ) 
                            ->  typename aggr_traits::out_type {
    
    std::vector<typename measure_traits::out_type> ret;
    
    for (auto it = b ; it != e ; ++it) {
      ret.emplace_back( f_(it->get()) );
    }
    return a_(ret.begin(), ret.end());
  };
};

/**
 * @brief Creates a new measure as result of the composition of the selector
 * and the measure (M o S). Types and arity must match
 * @param selector Selector 
 * @param measure Measure
 */
template <typename S, typename M>
auto selectorMeasureCompose(const S& selector, const M& measure){
  
  using selector_traits = selector::selector_func_traits<S>;
  using measure_traits = measure_func_traits<M>;
  
  // Check that they are compatible
  static_assert( selector_traits::out_set == measure_traits::in_set, 
                 "Arity doesnt match");
  static_assert( std::is_convertible<typename selector_traits::out_type,
                                     typename measure_traits::in_type>::value, 
                                     "Types doesnt match");
  
  // Call detail
  return detail::composeSelectorMeasure_(selector,measure);
}

/**
 * @brief Creates a measure that applies several measures to the same
 * input and returns their result in a tuple
 * 
 * @param measures Measures to combine in the tuple
 */
template <typename... Measures>
auto createMeasureTuple(const Measures&... measures ) {
  
  
  static_assert(sizeof...(Measures) > 0, "Attempt to create empty tuple");
  
  using input_check = detail::check_same_input<Measures...>;
  static_assert(input_check::value, "Not matching measures");
  
  return detail::createMeasureTupleImpl<input_check::in_set, 
                                typename input_check::in_type>(measures...);
}

} // measure NS
} // Neurostr NS

#endif
