#ifndef NEUROSTR_MEASURE_NEURON_MEASURE_H_
#define NEUROSTR_MEASURE_NEURON_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include <neurostr/core/node.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neurite_type.h>
#include <neurostr/core/neuron.h>

#include <neurostr/measure/measure_operations.h>
#include <neurostr/measure/node_measure.h>

#include <neurostr/selector/selector.h>
#include <neurostr/selector/node_selector.h>
#include <neurostr/selector/neurite_selector.h>

namespace neurostr {
  
namespace measure {
  

const auto has_soma = [](const Neuron& i) -> bool {
  return i.has_soma();
};

auto neuron_neurite_count = [](const Neuron &n){
  return n.size();
};

// Aliases
const auto neuron_dendrite_counter = [](const Neuron& n){
    return n.dendrite_count();
};

const auto neuron_axon_counter = [](const Neuron& n){
    return n.axon_count();
};

const auto neuron_apical_counter = [](const Neuron& n){
    return n.apical_count();
};

const auto soma_section_area = [](const Neuron& n ) -> float {
  return n.somaArea();
};

const auto soma_surface = [](const Neuron& n ) -> float {
  auto soma_size = std::distance(n.begin_soma(),n.end_soma());
  
  if(soma_size == 1){
      return M_PI*4*std::pow(n.begin_soma()->radius(),2);
  } else {
    
    point_type c = n.soma_barycenter();
    
    // Avg rad
    float dist = 0.;
    for(auto it = n.begin_soma(); it != n.end_soma(); ++it){
      dist+= it->radius() + it->distance(c);
    }
    
    return M_PI*4*std::pow(dist/soma_size,2);
  }
};

} // measure
} // neurostr

#endif
