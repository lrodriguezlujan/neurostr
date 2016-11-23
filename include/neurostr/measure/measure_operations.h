#ifndef NEUROSTR_MEASURES_MEASURE_OPS_H_
#define NEUROSTR_MEASURES_MEASURE_OPS_H_

#include <neurostr/measure/measure_traits.h>
#include <neurostr/measure/aggregator_traits.h>

#include <neurostr/measure/detail/compose_selector_measure_detail.h>
#include <neurostr/measure/detail/measure_combine_tuple_detail.h>

//#include <neurostr/selector/selector_traits.h>

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
 * @brief Removes nan values of the given value range if there is a isnan function
 * for that type
 * @param b Range begin
 * @param e Range end
 */
template <typename T>
std::vector<T> 
  remove_nan_values( typename std::vector<T>::iterator b,  
                     typename std::vector<T>::iterator e){
  return; // Default - do nothing
};

// Internal function to be called by the float double ..instances
template <typename T>
std::vector<T>
  remove_nan_values_detail_( typename  std::vector<T>::iterator b,  
                             typename  std::vector<T>::iterator e){
  // We dont want to modify the original vector so we create a new one and insert
  // only not nan values
  std::vector<T>  ret;
  for(auto it = b; it != e; ++it){
    if(!std::isnan(*it)){
      ret.push_back(*it);
    }
  }
  return ret;
};

template <>
std::vector<float>
  remove_nan_values<float>( typename  std::vector<float>::iterator b,  
                     typename  std::vector<float>::iterator e);

template <>
std::vector<double>
  remove_nan_values<double>( typename  std::vector<double>::iterator b,  
                     typename  std::vector<double>::iterator e);

template <>
std::vector<long double>
  remove_nan_values<long double>( typename  std::vector<long double>::iterator b,  
                     typename  std::vector<long double>::iterator e);

/**
 * @brief Convert a single-input measure into a set measure that applies the
 * original measure to each element of the input set and then aggregates the 
 * output.
 * 
 * @param f Original single-input measure
 * @param aggr Aggregator function
 * @param removeNaN Remove nan values before calling aggregate function
**/
template <typename Fn, typename Aggr>
auto measureEachAggregate(const Fn& f, const Aggr& aggr, bool removeNaN = true){
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
  return [f_ = f, a_ = aggr, nan_ = removeNaN](const iterator_type& b, const iterator_type& e ) 
                            ->  typename aggr_traits::out_type {
    
    std::vector<typename measure_traits::out_type> ret;
    
    for (auto it = b ; it != e ; ++it) {
      ret.emplace_back( f_(it->get()) );
    }
    
    // Remove NAN values before aggregate
    if(nan_){
      ret = remove_nan_values<typename measure_traits::out_type>(ret.begin(),ret.end());
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
