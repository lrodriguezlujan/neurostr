#ifndef NEUROSTR_VALIDATOR_CHECKS_H_
#define NEUROSTR_VALIDATOR_CHECKS_H_

#include "core/traits.h"
namespace neurostr{
namespace validator{ 

  // TODO:: CHECKER traits

template <typename F> struct check_func_traits {  
  
  using base_traits = neurostr::traits::function_traits<F>;

  using out_type = typename base_traits::result_type;
  using in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
};

template <typename T>
auto range_check_factory( T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::infinity() ){
  return [min_ = min, max_ = max](const T& v) -> bool {
    return v >= min_ &&  v < max_;
  }; 
};

const auto is_true = []( const bool& i ) -> bool { return i; };
const auto is_false = []( const bool& i ) -> bool { return !i; };

const auto empty_string = []( const std::string& s ) -> bool { return s.size() == 0; };

}//validation
}//neurostr

#endif
