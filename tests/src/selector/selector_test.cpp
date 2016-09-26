#include <unittest++/UnitTest++.h>

#include "aux/load_data_funcs.h"
#include "selector/selector.h"
#include "selector/universal_selector.h"
#include "selector/node_selector.h"
#include "selector/branch_selector.h"
#include "selector/neurite_selector.h"
#include "selector/neuron_selector.h"

namespace ns = neurostr::selector;

TEST(self_selector_test) {

  // Open reconstruction
  auto r = neurostr_test::load_full_reconstruction();

  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite());

  auto sel = ns::self_selector_factory<neurostr::Node>();
  CHECK_EQUAL(sel(*(first_neurite.begin_node())),*(first_neurite.begin_node()));



  // some stupid stuff 
  auto sel_compo_auto = ns::compose_selector(sel, sel, sel);
  
  CHECK_EQUAL(sel_compo_auto(*(first_neurite.begin_node())),*(first_neurite.begin_node()));
}


TEST(bifurcation_selector) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite());

  // Set by step
  auto sel_nodes = ns::neurite_node_selector(first_neurite);
  auto sel_bifs = ns::node_bifurcation_selector(sel_nodes.begin(),sel_nodes.end());
  CHECK_EQUAL(1, sel_bifs.size());
  
  // As composition
  auto sel_compo = ns::compose_selector(ns::node_bifurcation_selector, 
                                        ns::neurite_node_selector);
  
  CHECK_EQUAL(1, sel_compo(first_neurite).size());

  // Optimized
  auto sel_bifs_opt = ns::neurite_bifurcation_selector(first_neurite);
  CHECK_EQUAL(1, sel_bifs_opt.size());
}


TEST(terminal_nodeset_selector) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite());

  // Set by step
  auto sel_nodes = ns::neurite_node_selector(first_neurite);
  auto sel_bifs = ns::node_terminal_selector(sel_nodes.begin(),sel_nodes.end());
  CHECK_EQUAL(2, sel_bifs.size());
  
  // As composition
  auto sel_compo = ns::compose_selector(ns::node_terminal_selector, 
                                        ns::neurite_node_selector);
  
  CHECK_EQUAL(2, sel_compo(first_neurite).size());

  // Optimized
  auto sel_bifs_opt = ns::neurite_terminal_selector(first_neurite);
  CHECK_EQUAL(2, sel_bifs_opt.size());
}
