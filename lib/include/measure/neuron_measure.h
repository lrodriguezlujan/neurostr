#ifndef NEUROSTR_MEASURE_NEURON_MEASURE_H_
#define NEUROSTR_MEASURE_NEURON_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include "core/node.h"
#include "core/neurite.h"
#include "core/neuron.h"

#include "measure/measure_operations.h"
#include "measure/node_measure.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/neurite_selector.h"

namespace neurostr {
  
namespace measure {
  

const auto has_soma = [](Neuron& i) -> bool {
  return i.has_soma();
};

auto neuron_neurite_count = [](Neuron &n){
  return n.size();
};

/** Count specific neurite types **/
template <NeuriteType T>
auto neurite_type_counter  = [](Neuron& n){
  int count = 0;
    for (auto it = n.begin_neurite(); it != n.end_neurite(); ++it)
      if (it->type() == T) ++count;
    return count;
};

// Aliases
const auto neuron_dendrite_counter = neurite_type_counter<NeuriteType::kDendrite>;
const auto neuron_axon_counter = neurite_type_counter<NeuriteType::kAxon>;
const auto neuron_apical_counter = neurite_type_counter<NeuriteType::kApical>;

const auto soma_section_area = [](Neuron& n ) -> float {
  return n.somaArea();
};

const auto soma_surface = [](Neuron& n ) -> float {
  auto soma_size = std::distance(n.begin_soma(),n.end_soma());
  
  if(soma_size == 1){
      return M_PI*4*std::pow(n.begin_soma()->radius(),2);
  } else {
    
    point_type c = n.soma_barycenter();
    
    // Avg rad
    float dist;
    for(auto it = n.begin_soma(); it != n.end_soma(); ++it){
      dist+= it->radius() + it->distance(c);
    }
    
    return M_PI*4*std::pow(dist/soma_size,2);
  }
};

} // measure
} // neurostr

#endif
