#ifndef NEUROSTR_MEASURE_LMEASURE_H_
#define NEUROSTR_MEASURE_LMEASURE_H_

#include "measure/universal_measure.h"
#include "measure/branch_measure.h"
#include "measure/neurite_measure.h"
#include "measure/neuron_measure.h"

#include "measure/aggregate.h"

namespace neurostr{
namespace measure{
namespace lmeasure{
  
  namespace ns = neurostr::selector;
  
  namespace detail {
    
    const auto all_branch_selector = ns::compose_selector(
      ns::selector_in_single_to_set(ns::neurite_branch_selector),
      ns::neuron_neurites);
      
    const auto terminal_branch_selector = ns::compose_selector(
      ns::selector_in_single_to_set(ns::neurite_terminal_branches),
      ns::neuron_neurites);
      
    const auto preterminal_branch_selector = ns::compose_selector(
      ns::selector_in_single_to_set(ns::neurite_pre_terminal_branches),
      ns::neuron_neurites);
      
    const auto terminal_bif_selector = ns::compose_selector(
      ns::selector_in_single_to_set(ns::neurite_terminal_bifurcations),
      ns::neuron_neurites);
      
    // This selects all non terminal branches in the neuron
    const auto non_terminal_selector = ns::compose_selector(
      ns::selector_in_single_to_set(ns::neurite_non_terminal_branches),
      ns::neuron_neurites);
    
    const auto intermediate_branch_selector = 
      ns::diff_selector_factory(non_terminal_selector,
        ns::compose_selector(
          ns::selector_in_single_to_set(ns::neurite_first_branch_selector),
          ns::neuron_neurites
        )
      );
      
    // This counts number of branches
    const auto branch_counter = measureEachAggregate(
                            count_factory<Branch, unsigned int>(1), 
                            aggregate::sum_aggr_factory<unsigned int>(0));
                            
    // This counts number of nodes
    const auto node_counter = measureEachAggregate(
                            count_factory<Node, unsigned int>(1), 
                            aggregate::sum_aggr_factory<unsigned int>(0));
    
  } // Detail namespace

  // Redeclare soma surface in this NS
  const auto soma_surface = neurostr::measure::soma_surface;
  
  // N_Stems (Tree count)
  const auto n_stems = neuron_neurite_count;
  
  // N_bifs  
  const auto n_bifs = selectorMeasureCompose(detail::non_terminal_selector,
                                             detail::branch_counter);
  // N_branches                                 
  const auto n_branch = selectorMeasureCompose(detail::all_branch_selector ,
                                               detail::branch_counter);
  // N tips
  const auto n_tips = selectorMeasureCompose(detail::terminal_branch_selector,
                                               detail::branch_counter);


  // Width
  const auto width = selectorMeasureCompose(ns::neuron_node_selector,
                                            measureEachAggregate(
                                              node_x, 
                                              aggregate::range_length<float>
                                            ));
            
  // Height
  const auto height = selectorMeasureCompose( ns::neuron_node_selector,
                                              measureEachAggregate(
                                                node_y, 
                                                aggregate::range_length<float>
                                              ));
                                            
  // Depth
  const auto depth = selectorMeasureCompose( ns::neuron_node_selector,
                                              measureEachAggregate(
                                                node_z, 
                                                aggregate::range_length<float>
                                              ));

  // Type "measure" dont make any sense - we do not include it
  
  const auto diameter = selectorMeasureCompose(ns::neuron_node_selector,
                                              measureEachAggregate(
                                                node_diameter, 
                                                aggregate::all_aggr_factory<float,float>(0.)
                                              ));
  
  const auto diameter_pow = selectorMeasureCompose(ns::neuron_node_selector,
                                                  measureEachAggregate(
                                                    node_diameter_pow, 
                                                    aggregate::all_aggr_factory<float,float>(0.)
                                                  ));
  
  const auto length = selectorMeasureCompose(ns::neuron_node_selector,
                                             measureEachAggregate(
                                              node_length_to_parent, 
                                              aggregate::all_aggr_factory<float,float>(0.)
                                            ));
                                            
  const auto surface = selectorMeasureCompose( ns::neuron_node_selector,
                                                measureEachAggregate(
                                                    node_compartment_surface, 
                                                    aggregate::all_aggr_factory<float,float>(0.)
                                                )
                                              );
                                              
  
  const auto branch_surface = selectorMeasureCompose( ns::neuron_branch_selector,
                                                measureEachAggregate(
                                                    selectorMeasureCompose(
                                                      ns::branch_node_selector,
                                                      measureEachAggregate(
                                                        node_compartment_surface,
                                                        aggregate::sum_aggr_factory<float,float>(0.)
                                                    )),
                                                    aggregate::all_aggr_factory<float,float>(0.)
                                                )
                                              );                                            
                                            
  const auto section_area = selectorMeasureCompose( ns::neuron_node_selector,
                                                  measureEachAggregate(
                                                    node_compartment_section_area, 
                                                    aggregate::all_aggr_factory<float,float>(0.)
                                                  ));

  const auto volume = selectorMeasureCompose( ns::neuron_node_selector,
                                                measureEachAggregate(
                                              node_volume, 
                                              aggregate::all_aggr_factory<float,float>(0.)
                                            ));
  
  const auto branch_volume = selectorMeasureCompose( ns::neuron_branch_selector,
                                                measureEachAggregate(
                                                  selectorMeasureCompose(
                                                    ns::branch_node_selector,
                                                      measureEachAggregate(
                                                        node_volume, 
                                                        aggregate::sum_aggr_factory<float,float>(0.)
                                                      )
                                                  ),
                                              aggregate::all_aggr_factory<float,float>(0.)
                                            ));
                                          
  const auto euc_distance = selectorMeasureCompose( ns::neuron_node_selector,
                                                  measureEachAggregate(
                                                    node_distance_to_root, 
                                                    aggregate::all_aggr_factory<float,float>(0.)
                                                  ));
                                            
  const auto path_distance = selectorMeasureCompose( ns::neuron_node_selector,
                                                     measureEachAggregate(
                                                      node_path_to_root, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
  
  const auto branch_order = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      neurostr::measure::branch_order, 
                                                      aggregate::all_aggr_factory<int,float>(0.)
                                                    ));                            
              
  const auto terminal_degree = selectorMeasureCompose( ns::neuron_node_selector,
                                                      measureEachAggregate(
                                                      selectorMeasureCompose( 
                                                        ns::node_subtree_terminals,
                                                        detail::node_counter
                                                      ), 
                                                      aggregate::all_aggr_factory<int,float>(0.)
                                                    )); 
                                                    
  const auto branch_terminal_degree = selectorMeasureCompose( ns::neuron_branch_selector,
                                                      measureEachAggregate(
                                                      selectorMeasureCompose(
                                                        ns::intersection_selector(
                                                          ns::compose_selector( ns::neurite_terminal_branch_selector,
                                                                                ns::branch_neurite_selector),
                                                          ns::branch_subtree_selector
                                                        ),
                                                        set_size
                                                      ), 
                                                      aggregate::all_aggr_factory<int,float>(0.)
                                                    )); 
  
  // Terminal segment.... nope
  
  
  const auto taper_1 = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      taper_rate_burker, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));                            
                                                    
  const auto taper_2 = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      taper_rate_hillman, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));

  const auto branch_pathlength = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      branch_length, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto contraction = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      tortuosity, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto fragmentation = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      branch_size, 
                                                      aggregate::all_aggr_factory<int,float>(0.)
                                                    ));

  const auto daughter_ratio = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      child_diam_ratio, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
  
  /*const auto parent_daughter_ratio = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      parent_child_diam_ratio, 
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));*/
                                                    
  const auto partition_asymmetry = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      neurostr::measure::partition_asymmetry,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto rall_power = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      rall_power_fit_factory(0,5),
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto pk = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      pk_fit_factory(0,5),
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto pk_classic = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      pk_factory(1.5),
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto pk_2 = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      pk_factory(2),
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto bif_ampl_local = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      local_bifurcation_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));

  const auto bif_ampl_remote = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      remote_bifurcation_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto bif_tilt_local = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      local_tilt_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));

  const auto bif_tilt_remote = selectorMeasureCompose( detail::non_terminal_selector,
                                                    measureEachAggregate(
                                                      remote_tilt_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto bif_torque_local = selectorMeasureCompose( detail::intermediate_branch_selector,
                                                    measureEachAggregate(
                                                      local_torque_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));

  const auto bif_torque_remote = selectorMeasureCompose( detail::intermediate_branch_selector,
                                                    measureEachAggregate(
                                                      remote_torque_angle,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
  
  const auto last_parent_diam = selectorMeasureCompose( detail::terminal_bif_selector,
                                                    measureEachAggregate(
                                                      node_diameter,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));
                                                    
  const auto hillman_threshold = selectorMeasureCompose( detail::preterminal_branch_selector,
                                                    measureEachAggregate(
                                                      neurostr::measure::hillman_threshold,
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));                                                      

  const auto fractal_dim = selectorMeasureCompose( detail::all_branch_selector,
                                                    measureEachAggregate(
                                                      selectorMeasureCompose(
                                                        ns::branch_node_selector,
                                                        node_set_fractal_dim
                                                      ),
                                                      aggregate::all_aggr_factory<float,float>(0.)
                                                    ));        

} // lmeasure
} // measure
} // neurostr

#endif
