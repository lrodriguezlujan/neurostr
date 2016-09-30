#ifndef NEUROSTR_MEASURES_MEASURE_TRAITS_H_
#define NEUROSTR_MEASURES_MEASURE_TRAITS_H_

// Useful type traits from boost library
#include "core/traits.h"

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

namespace detail{
  
   template <typename Fn,
            std::enable_if_t<!measure_func_traits<Fn>::in_set>* = nullptr >
  using measure_fn_reference = std::reference_wrapper<
                                    typename measure_func_traits<Fn>::in_type>;
                                    
} // Namespace detail

} // Measure
} // Neurostr


#endif
