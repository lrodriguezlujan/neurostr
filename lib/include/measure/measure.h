#ifndef NEUROSTR_MEASURES_MEASURE_H_
#define NEUROSTR_MEASURES_MEASURE_H_

// Useful type traits from boost library
#include <iterator>
#include <tuple>

#include <boost/type_traits.hpp>

#include "core/traits.h"

#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

#include "selector/selector.h"

namespace neurostr {
namespace measure {

namespace detail{
  template <bool, typename T>
  struct type_chooser {
    using type = T; // False, is a reference
  };

  template <typename T>
  struct type_chooser<true,T> {
    using type = typename T::value_type::type; // True: Is an iterator to a wrapped reference
  };    
} // Namepsace detail

  
template <typename F> struct measure_func_traits {  
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  using out_type = typename base_traits::result_type;
  
  using base_in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
  using in_type = typename detail::type_chooser<in_set, base_in_type>::type;
};

template <typename F> struct aggr_func_traits {
  
  using base_traits = neurostr::traits::function_traits<F>;
  
  using out_type = typename base_traits::result_type;
  using base_in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
  using in_type = typename base_in_type::value_type;
};

namespace detail {
  template <typename Fn,
            std::enable_if_t<!measure_func_traits<Fn>::in_set>* = nullptr >
  using measure_fn_reference = std::reference_wrapper<
                                    typename measure_func_traits<Fn>::in_type>;
}

// ForEach - only for non set function - This does not return a measure!
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

// ForEach with aggregation - Returns a new measure
template <typename Fn, typename Aggr>
auto measureEachAggregate(const Fn& f, const Aggr& aggr){
  using measure_traits = measure_func_traits<Fn>;
  using aggr_traits = aggr_func_traits<Aggr>;
  
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

namespace detail {
  
  // Case 1: S input single output single
  template <typename S, typename M,
            std::enable_if_t< (!selector::selector_func_traits<S>::in_set) &&
                              (!selector::selector_func_traits<S>::out_set)>* = nullptr >
  auto composeSelectorMeasure_(const S& selector, const M& measure){
    
    using selector_traits = selector::selector_func_traits<S>;
    using measure_traits = measure_func_traits<M>;
    
    // Single-single
    return [s_ = selector, m_ = measure]( typename selector_traits::in_type& v ) 
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
    return [s_ = selector, m_ = measure](typename selector_traits::in_type& v ) 
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

// Selector - measure composition : Returns a measure
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

} // detail namespace

// Create measure tuple
template <typename... Measures>
auto createMeasureTuple(const Measures&... measures ) {
  
  
  static_assert(sizeof...(Measures) > 0, "Attempt to create empty tuple");
  
  using input_check = detail::check_same_input<Measures...>;
  static_assert(input_check::value, "Not matching measures");
  
  return detail::createMeasureTupleImpl<input_check::in_set, 
                                typename input_check::in_type>(measures...);
}



}  // measures namespace
}  // meurostr namespace

#endif
