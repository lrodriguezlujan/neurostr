#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "io/SWCParser.h"

TEST(SWC_Parser_simple)
{
  // Open file
  std::ifstream is("../data/simple_tree.swc");
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::SWCParser parser(is);
    auto r = parser.read("simple_tree");
    //std::cout << *r;
    is.close();
    
  }
}


TEST(SWC_Parser_real)
{
  // Open file
  std::ifstream is("../data/g0435P1.CNG.swc");
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::SWCParser parser(is);
    auto r = parser.read("g0435P1");
    //std::cout << *r;
    is.close();
  }
}
