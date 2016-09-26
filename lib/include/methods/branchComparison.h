#ifndef NEUROSTR_METHOD_BRANCHCOMPARISON_H_
#define NEUROSTR_METHOD_BRANCHCOMPARISON_H_

#include <vector>

#include "core/branch.h"
#include "core/neuron.h"

namespace neurostr {
namespace method {
  
  // align branches and computes theri f. dist
  float oriented_frechet_branch_distance( Branch &a,  Branch &b);
  
  std::vector<float> inter_pair_distance( Neuron& n , bool restrict_order = false, bool sided = false  );
  std::vector<std::vector<float>> inter_pair_distance_byorder( Neuron& n, bool sided = false);
  
} // Selector
} // Neurostr

#endif
