#include "methods/scholl.h"

#include "measure/node_measure.h"
#include "measure/neurite_measure.h"

namespace neurostr{
namespace methods{
  
std::vector<std::pair<float, int>> schollAnalysis(Neuron& n){
  
  std::vector<float> branch_begin; // Array with position where a branch is added
  std::vector<float> branch_end; // Array with position where a branch is terminated
  
  // For each neurite...
  for (auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
    // Dendrite begin node iterator
    auto tmp = it->begin_node();
    
  // Fill branch begin with roots
    if ( it->has_root())
      branch_begin.push_back(0); // Starts at 0
    else
      branch_begin.push_back(measure::node_distance_to_soma(*tmp));
      
    // Add bifurcations
    auto sel = selector::neurite_bifurcation_selector(*it);
    
    for (auto node_it = sel.begin(); node_it != sel.end(); ++node_it)
      branch_begin.push_back(
        measure::node_distance_to_soma(node_it->get()));

    // Terminals
    sel = selector::neurite_terminal_selector(*it);
    for (auto node_it = sel.begin(); node_it != sel.end(); ++node_it)
      branch_end.push_back(measure::node_distance_to_soma(node_it->get()));
  };

  // First sort
  std::sort(branch_begin.begin(), branch_begin.end());
  std::sort(branch_end.begin(), branch_end.end());

  float currdist = 0;
  int currcount = 0;
  auto begin_it = branch_begin.begin();
  auto end_it = branch_end.begin();
  std::vector<std::pair<float, int>> scholl;

  while (begin_it != branch_begin.end() || end_it != branch_end.end()) {
    // First adds
    while (begin_it != branch_begin.end() && currdist >= *begin_it) {
      ++currcount;
      ++begin_it;
    }

    // Then remove
    while (end_it != branch_end.end() && currdist >= *end_it) {
      --currcount;
      ++end_it;
    }

    // Addup and advance
    scholl.emplace_back(currdist, currcount);
    if (end_it != branch_end.end()) currdist = *end_it;
    if (begin_it != branch_begin.end() && *begin_it < currdist) currdist = *begin_it;
  };

  return scholl;
}
  
} // methods
} // neurostr
