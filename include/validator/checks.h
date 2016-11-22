#ifndef NEUROSTR_VALIDATOR_CHECKS_H_
#define NEUROSTR_VALIDATOR_CHECKS_H_

#include "core/traits.h"
namespace neurostr{

/**
* Validator namespace contains the validator template class and the predefined validators and check functions.
***/
namespace validator{ 


/**
 * @class check_func_traits
 * @file checks.h
 * @brief Check function traits. Gets input and output type
 */
template <typename F> struct check_func_traits {  
  
  using base_traits = neurostr::traits::function_traits<F>;

  using out_type = typename base_traits::result_type;
  using in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
};

/**
 * @brief Range check factory. Checks that a given value is in the range [min, max)
 * @param min Range minimum
 * @param max Range maximum
 */
template <typename T>
auto range_check_factory( T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::infinity() ){
  return [min_ = min, max_ = max](const T& v) -> bool {
    return v >= min_ &&  v < max_;
  }; 
};

/**
* @brief Dummy. Checks that a given boolean is true
**/
const auto is_true = []( const bool& i ) -> bool { return i; };

/**
* @brief Dummy. Checks that a given booelan is false
**/
const auto is_false = []( const bool& i ) -> bool { return !i; };

/**
* @brief Dummy. Checks that a given string is empty
**/
const auto empty_string = []( const std::string& s ) -> bool { return s.size() == 0; };

}//validation
}//neurostr

#endif
