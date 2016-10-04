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

#include "core/neuron.h"
#include "io/parser_dispatcher.h"
#include "validator/predefined_validators.h"

namespace po = boost::program_options;

int main(int ac, char **av)
{
  std::string ifile;
  bool exhaustive;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("exhaustive,e", "Exhaustive report. Include all validation items, not only failures")
    ;
    
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: validator -i test.swc -e" << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input/output file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: validator -i test.swc -e" << std::endl << std::endl ;
    return 2;
  }
  
  // Get exhaustive flag
  exhaustive = (vm.count("exhaustive") > 0);
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  neurostr::Neuron& n = *(r->begin());
  
  // Run default validations and output report
  std::cout << "[" << std::endl;
  
  auto neurites_attached_to_soma = neurostr::validator::neurites_attached_to_soma;
  neurites_attached_to_soma.validate(n);
  neurites_attached_to_soma.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto neuron_has_soma = neurostr::validator::neuron_has_soma;
  neuron_has_soma.validate(n);
  neuron_has_soma.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto planar_reconstruction = neurostr::validator::planar_reconstruction_validator_factory(1.01);
  planar_reconstruction.validate(n);
  planar_reconstruction.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto dendrite_count_validator = neurostr::validator::dendrite_count_validator_factory(2,13);
  dendrite_count_validator.validate(n);
  dendrite_count_validator.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto apical_count_validator = neurostr::validator::apical_count_validator_factory(true);
  apical_count_validator.validate(n);
  apical_count_validator.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto axon_count_validator = neurostr::validator::axon_count_validator_factory(true);
  axon_count_validator.validate(n);
  axon_count_validator.toJSON(std::cout,!exhaustive);
  
  std::cout << "," << std::endl;

  auto no_trifurcations_validator = neurostr::validator::no_trifurcations_validator;
  no_trifurcations_validator.validate(n);
  no_trifurcations_validator.toJSON(std::cout,!exhaustive);

  std::cout << "," << std::endl;

  auto linear_branches_validator = neurostr::validator::linear_branches_validator_factory(1.01);
  linear_branches_validator.validate(n);
  linear_branches_validator.toJSON(std::cout,!exhaustive);

  std::cout << "," << std::endl;

  auto zero_length_segments_validator = neurostr::validator::zero_length_segments_validator;
  zero_length_segments_validator.validate(n);
  zero_length_segments_validator.toJSON(std::cout,!exhaustive);

  std::cout << "," << std::endl;

  auto increasing_radius_validator = neurostr::validator::increasing_radius_validator;
  increasing_radius_validator.validate(n);
  increasing_radius_validator.toJSON(std::cout,!exhaustive);

  std::cout << "," << std::endl;


  auto branch_collision_validator = neurostr::validator::branch_collision_validator;
  branch_collision_validator.validate(n);
  branch_collision_validator.toJSON(std::cout,!exhaustive);

  std::cout << "," << std::endl;


  auto extreme_angles_validator = neurostr::validator::extreme_angles_validator;
  extreme_angles_validator.validate(n);
  extreme_angles_validator.toJSON(std::cout,!exhaustive);
  
  std::cout << "]" << std::endl;
  
}
