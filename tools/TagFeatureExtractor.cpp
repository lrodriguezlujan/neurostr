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
 
 void add_tag_neurite_node_measures(const neurostr::Neurite& n , const std::string& tag, std::map<std::string, std::vector<float>>& m){
   
   // Aux vector for single values
   std::vector<float> aux;
   
   // Node presel
   auto tag_nodes_selector = ns::compose_selector(ns::property_exists_factory<neurostr::Node>(tag),
                                      ns::neurite_node_selector);
                                      
    // Early return
   if(tag_nodes_selector(n).size() == 0 ) return ;

   // Number of bifurcations
   float nbifs = (ns::compose_selector(ns::property_exists_factory<neurostr::Node>(tag),
                                      ns::neurite_bifurcation_selector)(n)) .size();
                                           
   aux.push_back(nbifs);
   m.emplace( "N_bifurcations", aux );
   
   // Number of nodes
   aux.clear();
   aux.push_back(tag_nodes_selector(n).size());
   m.emplace( "N_nodes", aux );
   
   // Box volume
   
   // Node (compartment) length
   m.emplace( "node_length" , nm::selectorMeasureCompose(tag_nodes_selector,
                              nm::measureEach(nm::node_length_to_parent))(n));
  
  // Selected nodes box volume
  aux.clear();
  aux.push_back(nm::selectorMeasureCompose(tag_nodes_selector,
                                           nm::box_volume)(n));
  m.emplace( "box_volume", aux);
                                                      
  // Node euclidean distance to root
  m.emplace( "node_root_dist", nm::selectorMeasureCompose(tag_nodes_selector,
                               nm::measureEach(nm::node_distance_to_root))(n)); 

  // Node path distance to root
  m.emplace( "node_root_path", nm::selectorMeasureCompose(tag_nodes_selector,
                               nm::measureEach(nm::node_path_to_root))(n)); 

  // Compartment surface
  m.emplace( "compartment_surface", nm::selectorMeasureCompose(tag_nodes_selector,
                               nm::measureEach(nm::node_compartment_surface))(n)); 
                               
  // Compartment volume
  m.emplace( "compartment_volume", nm::selectorMeasureCompose(tag_nodes_selector,
                               nm::measureEach(nm::node_volume))(n)); 
                               
  // End plain node measures
  
  // This selects the terminal tips in the neurite
  auto tag_terminal_selector = ns::compose_selector(ns::property_exists_factory<neurostr::Node>(tag),
                                      ns::neurite_terminal_selector);
  if(tag_terminal_selector(n).size() > 0 ){
    // Number of terminal tips
    aux.clear();
    aux.push_back(tag_terminal_selector(n).size());
    m.emplace( "N_terminal", aux );
    
    // Order
    auto orders =nm::selectorMeasureCompose(tag_terminal_selector,
                                 nm::measureEach(nm::node_order))(n);
    aux.clear();
    aux.insert(aux.end(),orders.begin(),orders.end());
    m.emplace( "terminal_order", aux); 

    // Node euclidean distance to root
    m.emplace( "terminal_root_dist", nm::selectorMeasureCompose(tag_nodes_selector,
                                 nm::measureEach(nm::node_distance_to_root))(n)); 

    // Node path distance to root
    m.emplace( "terminal_root_path", nm::selectorMeasureCompose(tag_nodes_selector,
                                 nm::measureEach(nm::node_path_to_root))(n)); 
  }
}
  
 void add_tag_neurite_branch_measures(const neurostr::Neurite& n , const std::string& tag, std::map<std::string, std::vector<float>>& m){
   
   // Aux vector for single values
   std::vector<float> aux;
   
   // Branch sel
   auto tag_branch_selector = ns::compose_selector(ns::property_exists_factory<neurostr::Branch>(tag),
                                      ns::neurite_branch_selector);

    // Early return
   if(tag_branch_selector(n).size() == 0 )
     return ;

   // Number of nodes
   aux.clear();
   aux.push_back(tag_branch_selector(n).size());
   m.emplace( "N_branches", aux );
   
   // Box volume
   
   // Branch length
   m.emplace( "branch_length" , nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::branch_length))(n));

  // Branch order
  auto orders = nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::branch_order))(n);
  aux.clear();
  aux.insert(aux.end(),orders.begin(),orders.end());
  
  m.emplace( "branch_order" , aux);
  
  // Tortuosity
  m.emplace( "branch_tortuosity" , nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::tortuosity))(n));
                              
  // Taper rates
  m.emplace( "branch_burker_taper_rate" , nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::taper_rate_burker))(n));

  m.emplace( "branch_hillman_taper_rate" , nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::taper_rate_hillman))(n));
                              
  // Fractal dim
  m.emplace( "branch_fractal_dimension" , nm::selectorMeasureCompose(tag_branch_selector,
                              nm::measureEach(nm::branch_fractal_dim))(n));
                              
  m.emplace( "branch_surface" , nm::selectorMeasureCompose(tag_branch_selector,
                                nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                                                           nm::measureEachAggregate( nm::node_compartment_surface,
                                                                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n));
                              
  m.emplace( "branch_volume" , nm::selectorMeasureCompose(tag_branch_selector,
                                nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                                                           nm::measureEachAggregate( nm::node_volume,
                                                                                                    nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n));
  // Terminal branches
  auto tag_terminal_branch_selector = ns::compose_selector(ns::property_exists_factory<neurostr::Branch>(tag),
                                      ns::neurite_terminal_branch_selector);

  if(tag_terminal_branch_selector(n).size() > 0){

     // Branch length
     m.emplace( "terminal_branch_length" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::branch_length))(n));

    // Branch order
    orders = nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::branch_order))(n);
    aux.clear();
    aux.insert(aux.end(),orders.begin(),orders.end());
    
    m.emplace( "terminal_branch_length" , aux);
    
    // Tortuosity
    m.emplace( "terminal_branch_tortuosity" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::tortuosity))(n));
                                
    // Taper rates
    m.emplace( "terminal_branch_burker_taper_rate" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::taper_rate_burker))(n));

    m.emplace( "terminal_branch_hillman_taper_rate" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::taper_rate_hillman))(n));
                                
    // Fractal dim
    m.emplace( "terminal_branch_fractal_dimension" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                nm::measureEach(nm::branch_fractal_dim))(n));
                                
    m.emplace( "terminal_branch_surface" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                  nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                                                             nm::measureEachAggregate( nm::node_compartment_surface,
                                                                                                      nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n));
                                
    m.emplace( "terminal_branch_volume" , nm::selectorMeasureCompose(tag_terminal_branch_selector,
                                  nm::measureEach(nm::selectorMeasureCompose(ns::branch_node_selector,
                                                                             nm::measureEachAggregate( nm::node_volume,
                                                                                                      nm::aggregate::sum_aggr_factory<float,float>(0.0)))))(n));
  }
  
  // Non-Terminal branches - Bifurcation measures
  auto tag_bif_branch_selector = ns::compose_selector(ns::property_exists_factory<neurostr::Branch>(tag),
                                      ns::neurite_non_terminal_branches);

  if(tag_bif_branch_selector(n).size() > 0 ){
    // Local bifurcation angle
    m.emplace( "local_bifurcation_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::local_bifurcation_angle)) (n)); 
                                            
    // Local tilt angle
    m.emplace( "local_tilt_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::local_tilt_angle)) (n)); 

    // Local torque angle
    m.emplace( "local_torque_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::local_torque_angle)) (n)); 
                                            
    // Remote bifurcation angle
    m.emplace( "remote_bifurcation_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::remote_bifurcation_angle)) (n)); 
                                            
    // Remote tilt angle
    m.emplace( "remote_tilt_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::remote_tilt_angle)) (n)); 

    // Remote torque angle
    m.emplace( "remote_torque_angle", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::remote_torque_angle)) (n)); 
                                            
    // Child diameter ratio
    m.emplace( "child_diam_ratio", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach(nm::child_diam_ratio)) (n)); 
    // Partition asymmetry
    m.emplace( "partition_asymmetry", nm::selectorMeasureCompose(tag_bif_branch_selector,
                                            nm::measureEach( nm::partition_asymmetry )) (n));
  }
}

void add_tag_neurite_markers(const neurostr::Neurite& n , 
                                     const std::string& tag, 
                                     const std::vector<std::string>& markers,
                                     std::map<std::string, std::vector<float>>& m){

  std::vector<float> aux(1);
  
  for(auto mark_name = markers.begin(); mark_name != markers.end(); ++mark_name){
    
    aux[0] = ns::compose_selector(ns::property_exists_factory<neurostr::Node>(tag),
                                  ns::neurite_marker_selector(*mark_name))(n).size();
    m.emplace(std::string("marker_count_")+*mark_name, aux);
  }
}
 
std::map<std::string, std::vector<float>> get_tag_measures(const neurostr::Neurite& n, const std::string& tag, const std::vector<std::string>& markers){
   
   std::map<std::string, std::vector<float>> m; // measures
   
  add_tag_neurite_node_measures(n,tag,m);
  add_tag_neurite_branch_measures(n,tag,m);
  add_tag_neurite_markers(n,tag,markers,m);
  
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
void print_vector_measures(std::map<std::string, std::vector<float>>& m,
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
        NSTR_LOG_(info, std::string("Nan value removed in measure ") + it->first );
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

void print_tag_measures(const neurostr::Neurite& n, const std::string& tag, const std::vector<std::string>& markers, std::ostream& os){
  os << "{" ;
  // Print neurite ID
  print_neurite_id(n,os);
  os << ", ";
  
  // print tag
  os << " \"tag\" : " << escape_string(tag) << ", ";
  
  // Get measures
  auto m = get_tag_measures(n,tag, markers);
  
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
  std::string tag;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("tag,t", po::value< std::string >(&tag), "Tag (property key")
    ("marker,m", po::value< std::vector<std::string>>(), "Marker names")
    ("omitapical", "Ignore the apical dendrite")
    ("omitaxon", "Ignore the axon")
    ("omitdend", "Ignore the non-apical dendrites");
  
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_tagfeature -i test.swc " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("tag")){
    std::cout << "ERROR: input file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_tagfeature -i test.swc " << std::endl << std::endl ;
    return 2;
  }
  
  // Process contour
   std::vector<std::string> markers;
   
   if(vm.count("marker") > 0){
     markers=vm["marker"].as<std::vector<std::string>>();
   }
   
  omitapical = (vm.count("omitapical") > 0);
  omitaxon = (vm.count("omitaxon") > 0);
  omitdend = (vm.count("omitdend") > 0);
  
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
  
    // For each neurite
    for(auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
      if(!first){
        std::cout << " , ";
      }
      first = false;
      print_tag_measures(*it, tag, markers, std::cout);
    }  
  }
  
  std::cout << "]" << std::endl;
  
}

