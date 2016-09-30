#ifndef NEUROSTR_MEASURE_AGGREGATOR_TRAITS_H_
#define NEUROSTR_MEASURE_AGGREGATOR_TRAITS_H_

#include "core/traits.h"

namespace neurostr {
namespace measure {
namespace aggregate {
  
template <typename F> struct aggr_func_traits {
  
  using base_traits = neurostr::traits::function_traits<F>;
  
  using out_type = typename base_traits::result_type;
  using base_in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
  using in_type = typename base_in_type::value_type;
};
  
} // Aggregate 
} // Measure
} // Neurostr

#endif
