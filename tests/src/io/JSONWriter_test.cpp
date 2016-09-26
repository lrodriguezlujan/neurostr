#include <iostream>
#include <unittest++/UnitTest++.h>
#include "auxiliar_test_funcs.h"
#include "io/JSONWriter.h"

using namespace neurostr;

TEST(simple_writer) {
  // Open reconstruction
  auto r = neurostr_test::load_simple_reconstruction();
  
  // Create Writer
  io::JSONWriter writer(true);
  
  // Write!
  std::string s = writer.write(*r->begin());
  std::cout << s << std::endl;
}

TEST(real_writer) {
  // Open reconstruction
  auto r = neurostr_test::load_full_real_reconstruction();
  
  // Align roots
  r->begin()->up(neurostr::point_type(0,1,0)); // Set Y as UP.
  r->begin()->set_basal_roots_xz(); // Orient
  
  // Create Writer
  io::JSONWriter writer(true);
  
  // Write!
  std::string s = writer.write(*r->begin());
  //std::cout << s << std::endl;
  
  // TEST
  std::ofstream out("output.json");
  out << s;
  out.close();
}