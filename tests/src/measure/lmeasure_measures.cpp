#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "aux/load_data_funcs.h"

#include "measure/lmeasure_decl.h"

#include "core/neuron.h"


namespace nlm = neurostr::measure::lmeasure;
namespace ns = neurostr::selector;

TEST(lmeasures_test) {

  
  // Open reconstruction
  auto r = neurostr_test::load_full_reconstruction();
  
  neurostr::Neuron& n = *(r->begin());
  
  // To get accurate measures
  n.remove_null_segments();

  ///////////////
  // NODE MEASURE
  ///////////////

  // Single measures
  float soma_surface = nlm::soma_surface(n);
  int stems = nlm::n_stems(n);
  int bifs = nlm::n_bifs(n);
  int branches = nlm::n_branch(n);
  int tips = nlm::n_tips(n);
  float width = nlm::width(n);
  float height = nlm::height(n);
  float  depth = nlm::depth(n);
  
  // Aggregated
  auto diameter = nlm::diameter(n);
  auto diameter_pow = nlm::diameter_pow(n);
  auto length = nlm::length(n);
  auto surface = nlm::surface(n);
  auto section_area = nlm::section_area(n);
  auto volume = nlm::volume(n);
  auto euc_distance = nlm::euc_distance(n);
  auto path_distance = nlm::path_distance(n);
  auto branch_order = nlm::branch_order(n);
  auto terminal_degree = nlm::terminal_degree(n);
  auto taper_1 = nlm::taper_1(n);
  auto taper_2 = nlm::taper_2(n);
  auto branch_pathlength = nlm::branch_pathlength(n);
  auto contraction = nlm::contraction(n);
  auto fragmentation = nlm::fragmentation(n);
  auto daughter_ratio = nlm::daughter_ratio(n);
  //aggr_pack parent_daughter_ratio = nlm::parent_daughter_ratio(n);
  auto partition_asymmetry = nlm::partition_asymmetry(n); // Looop
  auto rall_power = nlm::rall_power(n);
  auto pk = nlm::pk(n);
  auto pk_classic = nlm::pk_classic(n);
  auto pk_2 = nlm::pk_2(n);
  auto bif_ampl_local = nlm::bif_ampl_local(n);
  auto bif_ampl_remote = nlm::bif_ampl_remote(n);
  auto bif_tilt_local = nlm::bif_tilt_local(n);
  auto bif_tilt_remote = nlm::bif_tilt_remote(n);
  auto bif_torque_local = nlm::bif_torque_local(n);
  auto bif_torque_remote = nlm::bif_torque_remote(n);
  auto last_parent_diam = nlm::last_parent_diam(n);
  auto hillman_threshold = nlm::hillman_threshold(n);
  auto fractal_dim = nlm::fractal_dim(n);
  
  #ifdef PRINT_OUTPUT
  
  // Single measures
  std::cout << soma_surface << std::endl;
  std::cout << stems << std::endl;
  std::cout << bifs << std::endl;
  std::cout << branches << std::endl;
  std::cout << tips << std::endl;
  std::cout << width << std::endl;
  std::cout << height << std::endl;
  std::cout <<  depth << std::endl;
  
  // Aggregated
  std::cout << diameter << std::endl;
  std::cout << diameter_pow << std::endl;
  std::cout << length << std::endl;
  std::cout << surface << std::endl;
  std::cout << section_area << std::endl;
  std::cout << volume << std::endl;
  std::cout << euc_distance << std::endl;
  std::cout << path_distance<< std::endl;
  std::cout << branch_order << std::endl;
  std::cout << terminal_degree << std::endl;
  std::cout << taper_1 << std::endl;
  std::cout << taper_2 << std::endl;
  std::cout << branch_pathlength << std::endl;
  std::cout << contraction << std::endl;
  std::cout << fragmentation << std::endl;
  std::cout << daughter_ratio << std::endl;
  //std::cout << parent_daughter_ratio = nlm::parent_daughter_ratio(n);
  std::cout << partition_asymmetry << std::endl; // Looop
  std::cout << rall_power << std::endl;
  std::cout << pk << std::endl;
  std::cout << pk_classic << std::endl;
  std::cout << pk_2 << std::endl;
  std::cout << bif_ampl_local << std::endl;
  std::cout << bif_ampl_remote << std::endl;
  std::cout << bif_tilt_local << std::endl;
  std::cout << bif_tilt_remote << std::endl;
  std::cout << bif_torque_local << std::endl;
  std::cout << bif_torque_remote << std::endl;
  std::cout << last_parent_diam << std::endl;
  std::cout << hillman_threshold << std::endl;
  std::cout << fractal_dim << std::endl;
  
  
  #endif
  
} // End node count test
