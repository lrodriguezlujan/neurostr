#ifndef NEUROSTR_SELECTOR_NEURITE_SELECTOR_H_
#define NEUROSTR_SELECTOR_NEURITE_SELECTOR_H_

#include <functional>

#include "selector/selector.h"
#include "selector/branch_selector.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite_type.h"
#include "core/neurite.h"
#include "core/neuron.h"


namespace neurostr {
namespace selector {
/**
* Neurite selector
*/

// IN: Neurite - Out: Neuron
const auto neurite_neuron_selector = [](Neurite& n) -> Neuron& { 
    return n.neuron();
};

// IN: Neurite - Out: Node set
const auto neurite_node_selector = [](Neurite& n)
    -> std::vector<node_reference> {
  std::vector<node_reference> selection;
    for (auto it = n.begin_node();it != n.end_node() ; ++it)
        selection.emplace_back(*it);
  return selection;
};

// IN: Neurite - Out: Branch set
const auto neurite_branch_selector = [](Neurite& n)
    -> std::vector<branch_reference> {
  std::vector<branch_reference> selection;
    for (auto it = n.begin_branch();it != n.end_branch() ; ++it)
        selection.emplace_back(*it);
  return selection;
};


// IN: Neurite - Out: Branch set
const auto neurite_first_branch_selector = [](Neurite& n)
    -> Branch& {
  std::vector<branch_reference> selection;

  return *(n.begin_branch());
};

// This could be done by composition (neurite node selector + bif selector)
// But this is several times faster

// IN: Neurite - Out: Node set
const auto neurite_bifurcation_selector = [](Neurite& n)
    -> std::vector<node_reference> {
  std::vector<node_reference> selection;
    for (auto br_it = n.begin_branch(); br_it != n.end_branch(); ++br_it)
      if (br_it.number_of_children() >= 2 && br_it->size() > 0)
        selection.emplace_back(br_it->last());
  return selection;
};

// IN: Neurite(set) , OUT: NodeSet
const auto neurite_terminal_selector = [](Neurite& n)
    -> std::vector<node_reference> {
  std::vector<node_reference> selection;
    for (auto br_it = n.begin_leaf(); br_it != n.end_leaf(); ++br_it)
      if(br_it->size() > 0)
        selection.emplace_back(br_it->last());
  return selection;
};

/** STATIC Factory: Neurite type */
template<NeuriteType T>
struct neurite_type_selector{
  std::vector<neurite_reference> operator() (
      const std::vector<neurite_reference>::iterator & b,
      const std::vector<neurite_reference>::iterator & e){
        std::vector<neurite_reference> selection;
      for (auto it = b; it != e; ++it)
        if ( it->get().type() == T) selection.emplace_back(*it);
        
      return selection;
  };
};

// Aliases
using dendrite_selector = neurite_type_selector<NeuriteType::kDendrite>;
using axon_selector = neurite_type_selector<NeuriteType::kAxon>;
using apical_selector = neurite_type_selector<NeuriteType::kApical>;


/** Dynamic factory */
static inline auto neurite_type_factory(NeuriteType type){
  return [t_ = type](const std::vector<neurite_reference>::iterator & b,
                     const std::vector<neurite_reference>::iterator & e)
                               -> std::vector<neurite_reference> {
        std::vector<neurite_reference> selection;
      for (auto it = b; it != e; ++it)
        if ( it->get().type() == t_) selection.emplace_back(*it);
        
      return selection;
  };
};

const auto neurite_terminal_branches = [](Neurite &n) ->
  std::vector<branch_reference> {
    
  std::vector<branch_reference> selection;
  for (auto br_it = n.begin_leaf(); br_it != n.end_leaf(); ++br_it){
    selection.emplace_back(*br_it);
  }
  return selection;
  
};

const auto neurite_non_terminal_branches =
  selector::diff_selector_factory(
    neurite_branch_selector,
    neurite_terminal_branches
  );
  
const auto neurite_pre_terminal_branches = [](Neurite &n) ->
  std::vector<branch_reference> {
  
    std::vector<branch_reference> pre_selection;
  for (auto br_it = n.begin_leaf(); br_it != n.end_leaf(); ++br_it){
    if(br_it.node->parent != nullptr){
      pre_selection.emplace_back(br_it.node->parent->data);
    }
  }
  
  return selector::unique_selector<Branch>()(pre_selection.begin(), pre_selection.end());
  
};

const auto neurite_terminal_bifurcations = 
  compose_selector(selector_in_single_to_set(branch_last_node_selector), 
          neurite_pre_terminal_branches);


} // End selector
} // End neurostr

#endif
