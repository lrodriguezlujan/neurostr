#include <unittest++/UnitTest++.h>
#include "aux/load_data_funcs.h"
#include "validator/checks.h"
#include "validator/validator.h"
#include "validator/predefined_validators.h"

namespace nm = neurostr::measure;
namespace ns = neurostr::selector;
namespace nv = neurostr::validator;

TEST(test_simple_validator_attached) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::neurites_attached_to_soma;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
  
}

TEST(test_full_validator_attached) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::neurites_attached_to_soma;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
  
}


TEST(test_simple_validator_hassoma) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::neuron_has_soma;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
  
}

TEST(test_full_validator_hassoma) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::neuron_has_soma;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
  
}


TEST(test_simple_validator_planar) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::planar_reconstruction_validator_factory(0.1);
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it dont pass
  CHECK(!validator.pass());
  
}

TEST(test_full_validator_planar) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::planar_reconstruction_validator_factory(0.1);
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
}


TEST(test_simple_validator_angles) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::extreme_angles_validator;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it dont pass
  CHECK(validator.pass());
  
  //auto fail = validator.get_failures();
}


TEST(test_full_validator_angles) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::extreme_angles_validator;
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it pass
  CHECK(validator.pass());
  
  //auto fail = validator.get_failures();
    
}

TEST(test_simple_validator_linear) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::linear_branches_validator_factory(1.01);
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Check that it dont pass
  CHECK(!validator.pass());
  
}


TEST(test_full_validator_linear) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::linear_branches_validator_factory(1.01);
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  // Chekc that it dont pass
  CHECK(!validator.pass());
  
}


TEST(test_simple_validator_collision) {

  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::segment_collision_validator;
  
  std::clock_t begin = clock();
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  std::clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  
  #ifdef PRINT_OUTPUT
    std::cout << "Elapsed time (s): " << elapsed_secs << std::endl;
  #endif
    
  
  CHECK(validator.pass());
  
}

TEST(test_full_validator_collision) {

  // Open reconstruction
  auto r = neurostr_test::load_full_SWC_reconstruction();

  ///////////////
  // CREATE VALIDATOR
  ///////////////
  auto validator = nv::segment_collision_validator;
  
  std::clock_t begin = clock();
  
  // Execute validator
  validator.validate(*(r->begin()));
  
  std::clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  
  #ifdef PRINT_OUTPUT
    std::cout << "Elapsed time (s): " << elapsed_secs << std::endl;
  #endif
  
  CHECK(!validator.pass());
}

/*
TEST(test_validate_real){
   // Open reconstruction
  auto r = neurostr_test::load_full_real_reconstruction();
  
  // Create all needed validators
  auto attached_validator = nv::neurites_attached_to_soma;
  auto soma_validator = nv::neuron_has_soma;
  auto angles_validator = nv::extreme_angles;
  auto planar_validator = nv::planar_reconstruction_validator(0.1);
  auto linear_validator = nv::linear_branches_validator(1.01);
  auto collision_validator = nv::segment_collision_validatior(1E-6);
  
  auto neuron = r->begin();
  
  //std::cout << *r ;
  
  // Validation time
  std::clock_t begin = clock();
  
  attached_validator.execute(neuron);
  soma_validator.execute(neuron);
  angles_validator.execute(neuron);
  planar_validator.execute(neuron);
  linear_validator.execute(neuron);
  collision_validator.execute(neuron);
  
  std::clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  
  
  
  // Output validation report
  std::cout << "Neuron: " << neuron->id() << std::endl;
  std::cout << "Time elapsed (seg): " << elapsed_secs << std::endl;
  std::cout << "Tests: "  << std::endl
            << "\t Attached neurites to soma:\t\t" << attached_validator.pass() << std::endl 
            << "\t Has soma:\t\t" << soma_validator.pass() << std::endl 
            << "\t Extreme angles:\t\t" << angles_validator.pass() << std::endl 
            << "\t Planar reconstruction:\t\t" << planar_validator.pass() << std::endl 
            << "\t Linear reconstruction:\t\t" << linear_validator.pass() << std::endl 
            << "\t Collision:\t\t" << collision_validator.pass() << std::endl;
}*/
