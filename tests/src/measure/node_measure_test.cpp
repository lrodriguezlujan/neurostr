#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "aux/load_data_funcs.h"

#include "measure/measure.h"
#include "measure/aggregate.h"
#include "measure/universal_measure.h"
#include "measure/node_measure.h"

#include "selector/selector.h"
#include "selector/universal_selector.h"
#include "selector/node_selector.h"
#include "selector/branch_selector.h"
#include "selector/neurite_selector.h"
#include "selector/neuron_selector.h"

#include "core/neuron.h"



namespace nm = neurostr::measure;
namespace ns = neurostr::selector;

TEST(counter_measure) {

  // Open reconstruction
  auto r = neurostr_test::load_full_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite()) ;
  neurostr::Branch& first_branch = *first_neurite.begin_branch();

  ///////////////
  // NODE MEASURE
  ///////////////

  // This measure returns a "1" per node
  auto node_counter = nm::count_factory<neurostr::Node, unsigned int>(1);
  
  // Sum starting at 0
  auto aggr_fn = nm::aggregate::sum_aggr_factory<unsigned int>(static_cast<unsigned int>(0));
  

  // This measure takes a set of nodes and counts them
  auto node_aggr_counter = nm::measureEachAggregate(node_counter, aggr_fn);
  
  
  // This selects all nodes in a neurite set (converts single selector to set selector by join)
  auto neuriteset_nodes = ns::join_selector_factory(ns::neurite_node_selector);
  // Composition magic : In neuron out nodes
  auto neuron_node_selector = ns::compose_selector(neuriteset_nodes,ns::neuron_neurites);
  
  // Branch
  CHECK_EQUAL(nm::selectorMeasureCompose(
                ns::branch_node_selector,
                node_aggr_counter)(first_branch) , 
                first_branch.size());
  
  // Neurite
  CHECK_EQUAL(nm::selectorMeasureCompose(
                ns::neurite_node_selector,
                node_aggr_counter)(first_neurite) , 
                first_neurite.node_count());

  // Neuron
  CHECK_EQUAL(nm::selectorMeasureCompose(
                neuron_node_selector,
                node_aggr_counter)(neuron) , 
                neuron.node_count());
  
  
  /////////////////
  // BRANCH COUNTER (another example)
  /////////////////
  
  // This measure returns a "1" per node
  auto branch_counter = nm::count_factory<neurostr::Branch, unsigned int>(1);
 
  // This measure takes a set of nodes and counts them
  auto branch_aggr_counter = nm::measureEachAggregate(branch_counter, aggr_fn);
  
  // Count branches in the neuron
  int count=0;
  for (auto it = neuron.begin_neurite(); it != neuron.end_neurite(); ++it)
    count+= it->size();
  
  auto neuron_branch_selector = ns::compose_selector(ns::join_selector_factory(ns::neurite_branch_selector),
                                            ns::neuron_neurites);
  
  
  // Neurite
  CHECK_EQUAL(nm::selectorMeasureCompose(
                ns::neurite_branch_selector,
                branch_aggr_counter)(first_neurite) , 
                first_neurite.size());

  // Neuron
  CHECK_EQUAL(nm::selectorMeasureCompose(
                neuron_branch_selector,
                branch_aggr_counter)(neuron) , 
                count);
  
} // End node count test


TEST(node_radius){
  
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  
  // Average starting at 0.
  auto avg_fn = nm::aggregate::avg_aggr_factory<float>(0.);

  auto node_sel = ns::compose_selector(ns::join_selector_factory(ns::neurite_node_selector),
                                            ns::neuron_neurites);
                                            
  CHECK_EQUAL(nm::selectorMeasureCompose(
                node_sel,
                nm::measureEachAggregate(nm::node_radius, avg_fn))
                (neuron) , 
                0.5);  
}


TEST(node_length_to_parent){
  
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  
  //std::cout << neuron ;
  // Average starting at 0.
  auto avg_fn = nm::aggregate::max<float>;
    
  CHECK_CLOSE(  nm::selectorMeasureCompose(
                  ns::neuron_node_selector,
                  nm::measureEachAggregate(nm::node_length_to_parent, avg_fn))
                  (neuron) , 
                std::sqrt(3),
                0.1);  
}


TEST(node_distance_to_root){
  
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  
  // Average starting at 0.
  auto avg_fn = nm::aggregate::min<float>;
    
  CHECK_CLOSE(  nm::selectorMeasureCompose(
                  ns::neuron_node_selector,
                  nm::measureEachAggregate(nm::node_distance_to_root, avg_fn))
                  (neuron) , 
                std::sqrt(3),
                0.1);  
}


TEST(node_number_desc){
  
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  
  // Average starting at 0.
  auto avg_fn = nm::aggregate::avg_aggr_factory<unsigned int, float>(0.);
  
  /*std::cout << nm::selectorMeasureCompose(
                  ns::neuron_node_selector,
                  nm::measureEachAggregate(nm::desc_count,avg_fn))
                  (neuron) << std::endl ;
    */
  CHECK_CLOSE(  nm::selectorMeasureCompose(
                  ns::neuron_node_selector,
                  nm::measureEachAggregate(nm::desc_count,avg_fn))
                  (neuron) , 
                5./6,
                1E-3);  
}

/* TODO
TEST(simple_node_box_volume){
  
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite()) ;
  neurostr::Branch& first_branch = *first_neurite.begin_branch();
  
  auto measure = nm::node::box_volume;
  
  nm::Measure<decltype(measure), void > volume(measure);
  CHECK_CLOSE(0, volume.measure( neurostr::neurite_reference(neuron.begin_neurite()) ), 1E-3);
};

TEST(full_node_box_volume){
  
  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite()) ;
  neurostr::Branch& first_branch = *first_neurite.begin_branch();
  
  auto measure = nm::node::box_volume;
  
  nm::Measure<decltype(measure), void > volume(measure);
  CHECK_CLOSE(6E8, volume.measure( neurostr::neurite_reference(&neuron, neuron.begin_axon().base().base()->get() ) ), 1E8);
  
};

////
// BIF angle
////
TEST(bifurcation_angle){
// Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite()) ;
  neurostr::Branch& first_branch = *first_neurite.begin_branch();
  
  auto measure = nm::node::node_bifurcation_angle;
  auto aggr = nm::aggregators::max<float>;
  
  nm::Measure<decltype(measure), decltype(aggr) > bifangle(measure, aggr);
  
  CHECK_CLOSE( std::acos(1.0/3.0), bifangle.measure( neurostr::neurite_reference(neuron.begin_neurite())), 1E-3);
}


TEST(node_orientation){
// Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  neurostr::Neuron& neuron = *(r->begin());
  neurostr::Neurite& first_neurite = *(neuron.begin_neurite()) ;
  neurostr::Branch& first_branch = *first_neurite.begin_branch();
  
  auto measure = nm::node::node_orientation;

  nm::Measure< decltype(measure) ,void > orientation(measure);
  
  std::pair<float,float> o1 = orientation.measure(neuron.find(4));
  std::pair<float,float> o2 = orientation.measure(neuron.find(6));
  
  CHECK_CLOSE( 0, o1.first, 1E-3);
  CHECK_CLOSE( 0, o1.second, 1E-3);
  
  // atan2(-2/sqrt6,1/3)
  CHECK_CLOSE( -1.1832, o2.first, 1E-3);
    
  // atan2(2/sqrt18,1/3)
  CHECK_CLOSE( 0.9553166, o2.second, 1E-3);
}

TEST( neuron_scholl_simple ){
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction(); 
 
  neurostr::Neuron& neuron = *(r->begin());
  
  auto measure = nm::neurite::scholl;
  
  nm::Measure< decltype(measure), void > scholl(measure);
  
  std::vector<std::pair<float,int>> res = scholl.measure( neurostr::neuron_reference(r->begin()) );
  
  CHECK_EQUAL(4,res.size());
  
}*/

/*TEST( neuron_scholl_full ){
  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction(); 
 
  neurostr::Neuron& neuron = *(r->begin());
  
  auto measure = nm::neurite::scholl;
  
  nm::Measure< decltype(measure), void > scholl(measure);
  
  std::vector<std::pair<float,int>> res = scholl.measure(neuron.begin_dendrites(),neuron.end_dendrites());
  
  for(auto it = res.begin(); it != res.end() ; ++it )
    std::cout << it->first << ", " << it->second << std::endl;
}*/
