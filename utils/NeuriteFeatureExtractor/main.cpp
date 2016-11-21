#include <stdio.h>

#include <stdio.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/format.hpp>

//#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include "core/log.h"
#include "core/neuron.h"

#include "measure/universal_measure.h"
#include "measure/branch_measure.h"
#include "measure/neurite_measure.h"
#include "measure/node_measure.h"
#include "measure/aggregate.h"
#include "measure/measure_operations.h"

#include "selector/neurite_selector.h"

#include "io/parser_dispatcher.h"

namespace po = boost::program_options;
namespace ns = neurostr::selector;
namespace nm = neurostr::measure;

 std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }
 
 std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }
 
 
 
 std::map<std::string, std::vector<float>> get_neurite_measures(const neurostr::Neurite& n){
   
   std::map<std::string, std::vector<float>> m; // measures
   
   // Aux vector for single values
   std::vector<float> aux;
   
   // Number of bifurcations
   float nbifs = ns::neurite_bifurcation_selector(n).size();
   aux.push_back(nbifs);
   m.emplace( "N_bifurcations", aux );
   
   // Number of branches
   aux.clear();
   aux.push_back(n.size());
   m.emplace( "N_branches", aux );
   
   // Number of nodes
   float nnodes = ns::neurite_node_selector(n).size();
   aux.clear();
   aux.push_back(nnodes);
   m.emplace( "N_nodes", aux );
   
   // Node (compartment) length
   m.emplace( "node_length" , nm::selectorMeasureCompose(ns::neurite_node_selector,
                              nm::measureEach(nm::node_length_to_parent))(n));
  
  // Neurite box volume
  aux.clear();
  aux.push_back(nm::selectorMeasureCompose(ns::neurite_node_selector,
                                                      nm::box_volume)(n));
  m.emplace( "box_volume", aux);
                                                      
  // Node euclidean distance to root
  m.emplace( "node_root_dist", nm::selectorMeasureCompose(ns::neurite_node_selector,
                               nm::measureEach(nm::node_distance_to_root))(n)); 

  // Node path distance to root
  m.emplace( "node_root_path", nm::selectorMeasureCompose(ns::neurite_node_selector,
                               nm::measureEach(nm::node_path_to_root))(n)); 
                               
  // Branch length
  m.emplace( "branch_length", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                               nm::measureEach(nm::branch_length))(n)); 
                               
  // Branch volume
  m.emplace( "branch_volume", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                               nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                    nm::measureEachAggregate( nm::node_volume,
                                                              nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n)); 
                               
  // Branch surface
  m.emplace( "branch_surface", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                                 nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                    nm::measureEachAggregate( nm::node_compartment_surface,
                                                              nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n)); 
                               
  // Terminal branch length
  m.emplace( "terminal_branch_length", nm::selectorMeasureCompose(ns::neurite_terminal_branch_selector,
                                       nm::measureEach(nm::branch_length)) (n)); 
                                       
  // Terminal branch order
  
  // Auxiliar - branch order outputs integers
  auto orders = nm::selectorMeasureCompose(ns::neurite_terminal_branch_selector,
                                       nm::measureEach(nm::branch_order))(n);
  aux.clear();
  aux.insert(aux.end(),orders.begin(),orders.end());
  
  m.emplace( "terminal_branch_order", aux); 

  // Terminal nodes distance to root
  m.emplace( "terminal_nodes_root_dist", nm::selectorMeasureCompose(ns::neurite_terminal_selector,
                                       nm::measureEach(nm::node_distance_to_root)) (n)); 

  // Terminal nodes path to root
  m.emplace( "terminal_nodes_root_path", nm::selectorMeasureCompose(ns::neurite_terminal_selector,
                                       nm::measureEach(nm::node_path_to_root)) (n)); 
                                       
  // Branch tortuosity
  m.emplace( "branch_tortuosity", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                               nm::measureEach(nm::tortuosity))(n)); 

  // Hillman taper rate
  m.emplace( "hill_taper_rate", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                               nm::measureEach(nm::taper_rate_hillman))(n)); 
  // Burker taper rate
  m.emplace( "burker_taper_rate", nm::selectorMeasureCompose(ns::neurite_branch_selector,
                               nm::measureEach(nm::taper_rate_burker))(n)); 

  // Branch fractal dimension
  m.emplace( "branch_fractal_dimension", nm::selectorMeasureCompose( ns::neurite_branch_selector,
                                          nm::measureEach(
                                            nm::selectorMeasureCompose(
                                              ns::branch_node_selector,
                                              nm::node_set_fractal_dim)))(n)); 


  /** Bifurcation measures **/
  if(n.size() > 1){
    
    // Local bifurcation angle
    m.emplace( "local_bifurcation_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::local_bifurcation_angle)) (n)); 
                                          
    // Local tilt angle
    m.emplace( "local_tilt_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::local_tilt_angle)) (n)); 

    // Local torque angle
    m.emplace( "local_torque_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::local_torque_angle)) (n)); 
                                          
    // Remote bifurcation angle
    m.emplace( "remote_bifurcation_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::remote_bifurcation_angle)) (n)); 
                                          
    // Remote tilt angle
    m.emplace( "remote_tilt_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::remote_tilt_angle)) (n)); 

    // Remote torque angle
    m.emplace( "remote_torque_angle", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::remote_torque_angle)) (n)); 
                                          
    // Child diameter ratio
    m.emplace( "child_diam_ratio", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach(nm::child_diam_ratio)) (n)); 
    // Partition asymmetry
    m.emplace( "partition_asymmetry", nm::selectorMeasureCompose(ns::neurite_non_terminal_branches,
                                          nm::measureEach( nm::partition_asymmetry )) (n)); 
  } else {
    NSTR_LOG_(info, std::string("Neurite ") + std::to_string(n.id()) + " doesn't have any bifuractions. Bifurcations measures are skipped.." );
  }
  
  return m;
  
}
 
void print_neurite_id(const neurostr::Neurite& n, std::ostream& os){
  os << escape_string("neuron") << " : " << escape_string(n.neuron().id()) << ", ";
  os << escape_string("neurite") << " : " << n.id() << ", ";
  os << escape_string("neurite_type") << " : ";
  if(n.type() == neurostr::NeuriteType::kAxon){ 
    os << escape_string("Axon");
  } else if(n.type() == neurostr::NeuriteType::kApical){ 
    os << escape_string("Apical");
  } else if(n.type() == neurostr::NeuriteType::kDendrite){ 
    os << escape_string("Dendrite");
  } else {
    os << escape_string("Unknown");
  }
}

// Note: This should be done with rapidjson
void print_vector_measures(std::map<std::string, std::vector<float>>& m , 
                            std::ostream& os ){
  bool first = true;
  // Measures json element
  os << escape_string("measures") << " : { ";   

  // Print each measure
  for(auto it = m.begin(); it!=m.end();++it ){
    
    // Values vector reference
    std::vector<float>& v = it->second;
    
    // Remove nans (FIX! nans shouldnt appear here)
    for(auto val = v.begin(); val != v.end(); ++val){
      if( std::isnan(*val) ){
        val = v.erase(val)-1;
        NSTR_LOG_(warn, std::string("Nan value removed in measure ") + it->first );
      }
    }
    
    // If values vector is not empty
    if(v.size() > 0){
      if(first){
        first = false;
      } else {
        os << ", ";
      }      
    
      // Print key
      os << escape_string(it->first) << " : " ;
      
      // Print value vector
      os << "[ " ;
      os << v.front();
      
      // Print rest
      for( auto val = std::next(v.begin(),1); val != v.end(); ++val){
        os << ", " << *val;
      }
      
      // Close array
      os << "]";
    
    } // End if vector is empty 
  } // End for loop
  os << " }"; // Close measures
}

void print_neurite_measures(const neurostr::Neurite& n, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_neurite_id(n,os);
  os << ", ";
  
  // Get measures
  auto m = get_neurite_measures(n);
  
  // Print them
  print_vector_measures(m,os);
  
  // End obj
  os << "}";
}

/**
 * @brief 
 * @param ac
 * @param av
 * @return 
 */
int main(int ac, char **av)
{
  // Log errors in std::cerr
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();
  
  std::string ifile;
  
  // omits
  bool omitapical = false;
  bool omitaxon = false;
  bool omitdend = false;
  bool correct = false;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("correct,c", "Try to correct the errors in the reconstruction")
    ("omitapical", "Ignore the apical dendrite")
    ("omitaxon", "Ignore the axon")
    ("omitdend", "Ignore the non-apical dendrites");
  
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: NeuriteFeatureExtractor -i test.swc " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: NeuriteFeatureExtractor -i test.swc " << std::endl << std::endl ;
    return 2;
  }
  
  
  omitapical = (vm.count("omitapical") > 0);
  omitaxon = (vm.count("omitaxon") > 0);
  omitdend = (vm.count("omitdend") > 0);
  correct = (vm.count("correct") > 0);
  
  /*** END PARAMETER PARSING */
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Measure each neurite and output report
  bool first = true;
  std::cout << "[" << std::endl;
  
  // For each neuron
  for(auto n_it = r->begin(); n_it != r->end(); ++n_it){
    neurostr::Neuron& n = *n_it;
    
    /** Remove **/
    if(omitapical) n.erase_apical();
    if(omitaxon) n.erase_axon();
    if(omitdend) n.erase_dendrites();
    if(correct) n.correct();
  
    // For each neurite
    for(auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
      if(!first){
        std::cout << " , ";
      }
      first = false;
      print_neurite_measures(*it, std::cout);
    }  
  }
  
  std::cout << "]" << std::endl;
  
}

