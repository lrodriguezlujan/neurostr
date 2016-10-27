#ifndef NEUROSTR_SELECTOR_NEURON_SELECTOR_H_
#define NEUROSTR_SELECTOR_NEURON_SELECTOR_H_

#include <functional>

#include "selector/selector.h"
#include "selector/universal_selector.h"
#include "selector/neurite_selector.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"


namespace neurostr {
namespace selector {
  
  /**
* Neuron selector
*/
const auto neuron_neurites = [](const Neuron &n) -> std::vector<const_neurite_reference> {
  std::vector<const_neurite_reference> sel;
  for(auto it = n.begin_neurite(); it!=n.end_neurite(); ++it)
    sel.emplace_back(*it);
  return sel;
};

// Im using this all the time
const auto neuron_node_selector =  compose_selector(selector_in_single_to_set(neurite_node_selector),
                                            neuron_neurites);

const auto neuron_branch_selector =  compose_selector(selector_in_single_to_set(neurite_branch_selector),
                                            neuron_neurites);
                                            
/*
const auto neuron_branches = [](const neuron_reference& n)
    -> std::vector<branch_reference> {
  std::vector<branch_reference> selection;
  for(auto i = n->begin_neurite(); i!=n->end_neurite(); ++i)
    for (auto it = i->begin_branch();it != i->end_branch() ; ++it)
        selection.emplace_back(n.neuron(),n.neurite(),it);
  return selection;
};
*/


  
} // Namespace neurostr
} // Namespace selector
#endif
