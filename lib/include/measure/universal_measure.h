#ifndef NEUROSTR_MEASURE_UNIVERSAL_MEASURE_H_
#define NEUROSTR_MEASURE_UNIVERSAL_MEASURE_H_

#include <functional>

#include "measure/measure.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"


namespace neurostr {
namespace measure {
  
/** STATIC count*/
template <typename T, typename C_type = int>
auto count_factory(const C_type c){
  return [c_ = c](T& item) -> C_type {return c_;};
};


} // measure namespace
} // neurostr namespace

#endif
