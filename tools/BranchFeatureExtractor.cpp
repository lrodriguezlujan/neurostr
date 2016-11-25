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

#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include <neurostr/core/log.h>
#include <neurostr/core/neuron.h>

#include <neurostr/measure/universal_measure.h>
#include <neurostr/measure/branch_measure.h>
#include <neurostr/measure/neurite_measure.h>
#include <neurostr/measure/node_measure.h>
#include <neurostr/measure/aggregate.h>
#include <neurostr/measure/measure_operations.h>

#include <neurostr/selector/neurite_selector.h>

#include <neurostr/io/parser_dispatcher.h>

namespace po = boost::program_options;
namespace ns = neurostr::selector;
namespace nm = neurostr::measure;

 std::string escape_string(const std::string& s){
   return "\""+s+"\"";
 }
 
 std::string escape_string(const char *c){
   return escape_string(std::string(c));
 }
 
 
 std::map<std::string, float> get_branch_measures(const neurostr::Branch& b){
   
   std::map<std::string, float> m; // measures
   bool is_bifurcation = false;
   
   
  // Number of nodes
  m.emplace( "N_nodes", b.size());
   
  // Tortuosity
  m.emplace( "tortuosity", nm::tortuosity(b));
   
  // Hillman taper rate
  m.emplace( "hill_taper_rate", nm::taper_rate_hillman(b)); 
  
  // Burker taper rate
  m.emplace( "burker_taper_rate", nm::taper_rate_burker(b)); 
  
  // Centrifugal order
  m.emplace( "centrifugal_order", b.order()); 
  
  // Length
  m.emplace("length", b.length());
  
  // Number of descs
  int ndescs = b.neurite().find(b).number_of_children();
  is_bifurcation = ndescs > 1;
  m.emplace("N_descs", ndescs);
  
  // Volume
  m.emplace("volume",   nm::selectorMeasureCompose(ns::branch_node_selector,
                          nm::measureEachAggregate( nm::node_volume,
                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))(b));
                                                    
  // Surface
  m.emplace("surface",   nm::selectorMeasureCompose(ns::branch_node_selector,
                          nm::measureEachAggregate( nm::node_compartment_surface,
                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))(b));
  
  // Box volume
  m.emplace("box_volume",   nm::selectorMeasureCompose(ns::branch_node_selector,
                                                       nm::box_volume)(b));
                                                       
  // Fractal dim
  m.emplace("fractal_dimension",   nm::branch_fractal_dim(b));


  /** Bifurcation measures **/
  if(is_bifurcation){
    
    // Local bifurcation angle
    m.emplace( "local_bifurcation_angle", nm::local_bifurcation_angle(b)); 
                                          
    // Local tilt angle
    m.emplace( "local_tilt_angle", nm::local_tilt_angle(b)); 

    // Local torque angle
    m.emplace( "local_torque_angle", nm::local_torque_angle(b)); 
                                          
    // Remote bifurcation angle
    m.emplace( "remote_bifurcation_angle", nm::remote_bifurcation_angle(b)); 
                                          
    // Remote tilt angle
    m.emplace( "remote_tilt_angle", nm::remote_tilt_angle(b)); 

    // Remote torque angle
    m.emplace( "remote_torque_angle", nm::remote_torque_angle(b)); 
                                          
    // Child diameter ratio
    m.emplace( "child_diam_ratio", nm::child_diam_ratio(b)); 
    // Partition asymmetry
    m.emplace( "partition_asymmetry", nm::selectorMeasureCompose(ns::branch_node_selector,
                                                                 nm::node_set_fractal_dim)(b)); 
  } else {
    NSTR_LOG_(info, std::string("Branch ") + b.idString() + " is not a bifurcation branch. Bif. measures are skipped" );
  }
  
  return m;
  
}
 
void print_branch_id(const neurostr::Branch& b, std::ostream& os){
  os << escape_string("neuron") << " : " << escape_string(b.neurite().neuron().id()) << ", ";
  os << escape_string("neurite") << " : " << b.neurite().id() << ", ";
  os << escape_string("neurite_type") << " : ";
  if(b.neurite().type() == neurostr::NeuriteType::kAxon){ 
    os << escape_string("Axon");
  } else if(b.neurite().type() == neurostr::NeuriteType::kApical){ 
    os << escape_string("Apical");
  } else if(b.neurite().type() == neurostr::NeuriteType::kDendrite){ 
    os << escape_string("Dendrite");
  } else {
    os << escape_string("Unknown");
  }
  
  os << ", " << escape_string("branch") << " : " << escape_string(b.idString()) ;
}

// Note: This should be done with rapidjson
void print_measures(std::map<std::string, float>& m , 
                            std::ostream& os ){
  bool first = true;
  // Measures json element
  os << escape_string("measures") << " : { ";   

  // Print each measure
  for(auto it = m.begin(); it!=m.end();++it ){
    
    // If values vector is not empty
    if(!std::isnan(it->second)){
      if(first){
        first = false;
      } else {
        os << ", ";
      }      
    
     // Print key and value
      os << escape_string(it->first) << " : " << std::to_string(it->second) ;
    
    } // End if value is nan
    
  } // End for loop
  os << " }"; // Close measures
}

void print_branch_measures(const neurostr::Branch& b, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_branch_id(b,os);
  os << ", ";
  
  // Get measures
  auto m = get_branch_measures(b);
  
  // Print them
  print_measures(m,os);
  
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
  
  std::string selection;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("correct,c", "Try to correct the errors in the reconstruction")
    ("selection,s", po::value< std::string >(&selection) -> default_value("all"), "Branch subset: all, terminal, nonterminal, preterminal or root")
    ("omitapical", "Ignore the apical dendrite")
    ("omitaxon", "Ignore the axon")
    ("omitdend", "Ignore the non-apical dendrites");
  
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_branchfeature -i test.swc " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_branchfeature -i test.swc " << std::endl << std::endl ;
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
    
    // Select branch subset
    std::vector<ns::const_branch_reference> branches;
    
    if(selection == "all"){
      branches = ns::neuron_branch_selector(n);
    } else if (selection == "terminal"){
      branches = ns::selector_foreach(ns::neuron_neurites,ns::neurite_terminal_branches)(n);
    } else if (selection == "nonterminal"){
      branches = ns::selector_foreach(ns::neuron_neurites,ns::neurite_non_terminal_branches)(n);
    } else if (selection == "preterminal"){
      branches = ns::selector_foreach(ns::neuron_neurites,ns::neurite_pre_terminal_branches)(n);
    } else if (selection == "root"){
      branches = ns::compose_selector(ns::branch_order_filter_factory(0),ns::neuron_branch_selector)(n);
    } else {
      NSTR_LOG_(error, "Unrecognized selection type. Selecting all branches.")
      branches = ns::neuron_branch_selector(n);
    }

 
  
    // Select branches
    for(auto it = branches.begin(); it != branches.end(); ++it){
      if(!first){
        std::cout << " , ";
      }
      first = false;
      
      print_branch_measures(*it, std::cout);
    }  
  }
  
  std::cout << "]" << std::endl;
  
}

