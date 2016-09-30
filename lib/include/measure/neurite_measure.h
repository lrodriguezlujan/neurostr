#ifndef NEUROSTR_MEASURE_NEURITE_MEASURE_H_
#define NEUROSTR_MEASURE_NEURITE_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include "core/node.h"
#include "core/neurite.h"

#include "measure/measure_operations.h"
#include "measure/node_measure.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/neurite_selector.h"

namespace neurostr {

namespace measure {
  
const auto root_is_soma = [](Neurite& n) -> bool {
  return n.root_is_soma();
};


} // measure
} // neurostr

#endif
