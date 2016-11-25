#ifndef NEUROSTR_MEASURE_UNIVERSAL_MEASURE_H_
#define NEUROSTR_MEASURE_UNIVERSAL_MEASURE_H_

#include <functional>

#include <neurostr/measure/measure.h>
#include <neurostr/core/node.h>
#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>

#include <neurostr/selector/selector_traits.h>


namespace neurostr {
namespace measure {
  
/** STATIC count*/
template <typename T, typename C_type = int>
std::function<C_type(const T&)>  count_factory(const C_type c){
  return [c_ = c](const T& item) -> C_type {return c_;};
};

/* template <typename T>
const std::function<unsigned int(const selector::const_selector_iterator<T>&, 
                                 const selector::const_selector_iterator<T>&)> 
set_size = [](const selector::const_selector_iterator<T>& b, 
              const selector::const_selector_iterator<T>& e) -> unsigned int {return std::distance(b,e);};
*/

} // measure namespace
} // neurostr namespace

#endif
