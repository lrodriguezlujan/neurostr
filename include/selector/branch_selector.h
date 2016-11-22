#ifndef NEUROSTR_SELECTOR_BRANCH_SELECTOR_H_
#define NEUROSTR_SELECTOR_BRANCH_SELECTOR_H_

#include <functional>

#include "selector/selector.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace selector {
 
/******
 *  Branch selectors
 */

// IN: Branch - Out: Neurite
auto branch_neurite_selector = [](const Branch& b) -> const Neurite& {
  return b.neurite();
};

// IN: Branch - Out: Branch
auto branch_parent_selector = [](const Branch& b) -> const Branch& {
  auto branch_it = b.neurite().find(b);
  if(branch_it.node->parent == nullptr){
    return b;
  } else {
    return branch_it.node->parent->data;
  }
};

// IN: Branch - Out: Branch
auto branch_sibling_selector = [](const Branch& b) -> const Branch& {
  auto branch_it = b.neurite().find(b);
  if (branch_it.node->next_sibling != nullptr){
    return branch_it.node->next_sibling->data;
  } else if (branch_it.node->prev_sibling != nullptr){
    return branch_it.node->prev_sibling->data;
  } else {
    return b;
  }
};

// IN: Branch - Out: Node
auto branch_last_node_selector = [](const Branch& b) -> const Node& {
  if (b.size() == 0)
    return b.root();
  else
    return b.last();
};

// IN: Branch - Out: Node
auto branch_first_node_selector = [](const Branch& b) -> const Node& {
  if (b.size() == 0)
    return  b.root();
  else
    return b.first();
};

// IN: Branch - Out: Node set
auto branch_node_selector = [](const Branch& b) -> std::vector<const_node_reference> {
  std::vector<const_node_reference> selection;
  for (auto it = b.begin(); it != b.end(); ++it) 
    selection.emplace_back(*it);
  return selection;
};

// IN: Branch - Out: Branch SET
auto branch_subtree_selector = [](const Branch &b) -> std::vector<const_branch_reference> {
  auto branch_it = b.neurite().find(b);
  std::vector<const_branch_reference> st;
  for (auto it =  b.neurite().begin_branch_subtree(branch_it); 
            it != b.neurite().end_branch_subtree(branch_it); 
            ++it) {
    st.emplace_back(*it);
  }
  return st;
};

// IN: Branch - Out: Branch SET
auto branch_stem_selector = [](const Branch &b) -> std::vector<const_branch_reference> {
  std::vector<const_branch_reference> st;
  auto branch_it = b.neurite().find(b);
  for (auto it =  b.neurite().begin_stem(branch_it);
            it != b.neurite().end_stem(branch_it); 
            ++it) {
    st.emplace_back(*it);
  }
  return st;
};

/** Branch - specific factories **/
// IN: Branch set - Out: Branch set
static inline auto branch_order_filter_factory(int order){
  return [o_ = order](const std::vector<const_branch_reference>::iterator & b,
                      const std::vector<const_branch_reference>::iterator & e ) 
                      -> std::vector<const_branch_reference> {
        std::vector<const_branch_reference> st;
        for (auto it = b; it != e; ++it) {
          if( it->get().order() == o_)
            st.emplace_back(*it);
        }
        return st;
  };
};

 
} // End selector space
} // End neurostr space

#endif
