#ifndef NEUROSTR_MEASURES_COMBINE_TUPLE_DETAIL_H_
#define NEUROSTR_MEASURES_COMBINE_TUPLE_DETAIL_H_

#include <iterator>
#include <vector>

#include <boost/type_traits.hpp>
#include "core/traits.h"
#include "selector/selector.h"
#include "measure/measure_traits.h"

namespace neurostr {
namespace measure {
namespace detail {

// Check in types for every measure and arity

// Recursive
template <typename M1, typename M2, typename... Rest>
struct check_same_input {
  const static bool in_set = measure_func_traits<M1>::in_set;
  using in_type = typename measure_func_traits<M1>::in_type;
  
  const static bool value =  check_same_input<M1,M2>::value &&
                       check_same_input<M1,Rest...>::value ;
};

// Base case
template <typename M1, typename M2>
struct check_same_input<M1,M2> {
  const static bool in_set = measure_func_traits<M1>::in_set;
  using in_type = typename measure_func_traits<M1>::in_type;
  
  const static bool value =  std::is_same< typename measure_func_traits<M1>::in_type,
                                     typename measure_func_traits<M2>::in_type >::value &&
                                     measure_func_traits<M1>::in_set == 
                                     measure_func_traits<M2>::in_set;
};

// Auxiliar types
template <typename T1, typename... Rest>
struct combine_tuple;

template <typename T1, typename... Rest>
struct combine_tuple< T1, std::tuple<Rest...>> {
  using type = std::tuple<T1,Rest...>;
};

// Recursive
template <typename M, typename... Rest>
struct measure_tuple_ret_type {
  using type = typename combine_tuple< typename measure_func_traits<M>::out_type,
                              typename measure_tuple_ret_type<Rest...>::type>::type;
};

// Base case
template <typename M>
struct measure_tuple_ret_type<M> {
  using type = std::tuple<typename measure_func_traits<M>::out_type>;
};

template <typename T, typename M, typename... Rest, 
          std::enable_if_t<sizeof...(Rest)!=0>* = nullptr>
auto apply_measures(T& v, const M& measure, const Rest&... rest){
    return std::tuple_cat( std::make_tuple(measure(v)), 
                           apply_measures(v,rest...));
};

template <typename T, typename M, typename... Rest,  
          std::enable_if_t<sizeof...(Rest)==0>* = nullptr>
auto apply_measures(T& v, const M& measure){
    return std::make_tuple(measure(v));
};

template <typename T, typename M, typename... Rest,
          std::enable_if_t<sizeof...(Rest)!=0>* = nullptr>
auto apply_measures(const selector::selector_iterator<T>& b, 
                    const selector::selector_iterator<T>& e, 
                    const M& measure, 
                    const Rest&... rest){
    return std::tuple_cat( std::make_tuple(measure(b,e)), 
                           apply_measures(b,e,rest...));
};

template <typename T, typename M, typename... Rest,
          std::enable_if_t<sizeof...(Rest)==0>* = nullptr>
auto apply_measures(const selector::selector_iterator<T>& b, 
                    const selector::selector_iterator<T>& e, 
                    const M& measure){
    return std::make_tuple(measure(b,e));
};



// False . not set
template <bool set, typename T, typename...Measures,
          std::enable_if_t<!set>* = nullptr>
auto createMeasureTupleImpl(const Measures&... measures ){
  
  using out_type = typename measure_tuple_ret_type<Measures...>::type;
  
  return [=]( T& v ) -> out_type {
    return apply_measures(v,measures...);
  };
};

template <bool set, typename T, typename...Measures,
          std::enable_if_t<set>* = nullptr>
auto createMeasureTupleImpl(const Measures&... measures ){
  
  using out_type = typename measure_tuple_ret_type<Measures...>::type;
  
  return [=]( const selector::selector_iterator<T>& b, 
              const selector::selector_iterator<T>& e) 
                               -> out_type {
    return apply_measures(b,e,measures...);
  };
};

} // detail
} // Measure} // Neurostr


#endif
