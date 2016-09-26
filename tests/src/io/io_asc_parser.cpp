#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "io/nl_structure.h"
#include "io/ASCParser.h"

TEST(ASC_Parser_simple)
{
  // Open file
  std::ifstream is("../data/simple_tree.ASC");
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::ASCParser parser(is);
    auto r = parser.read("simple_tree");
    //std::cout << (*r);
    is.close();
    // delete r;
  }
}

TEST(ASC_Parser_single)
{
  // Open file
  std::ifstream is("../data/P14_rata1_capaIII_cel4.ASC");
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::ASCParser parser(is);
    auto r = parser.read("P14_rata1_capaIII_cel4");
    //std::cout << (*r);
    is.close();
    //delete r;
  }
}

TEST(ASC_Parser_map)
{
  // Open file
  std::ifstream is("../data/map_rat_1_layer_II.ASC");
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::ASCParser parser(is);
    auto r = parser.read("map_rat_1_layer_II");
    is.close();
    //std::cout << (*r);
    //delete r;
  }
}
