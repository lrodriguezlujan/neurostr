#ifndef NEUROSTR_MEASURE_NEURITE_MEASURE_H_
#define NEUROSTR_MEASURE_NEURITE_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include <neurostr/core/node.h>
#include <neurostr/core/neurite.h>

#include <neurostr/measure/measure_operations.h>
#include <neurostr/measure/node_measure.h>

#include <neurostr/selector/selector.h>
#include <neurostr/selector/node_selector.h>
#include <neurostr/selector/neurite_selector.h>

namespace neurostr {

namespace measure {
  
const auto root_is_soma = [](const Neurite& n) -> bool {
  return n.root_is_soma();
};


} // measure
} // neurostr

#endif
