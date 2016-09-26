#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "core/neuron.h"
#include "io/DATParser.h"

TEST(DAT_Parser_single)
{
  // Open file
  std::ifstream is("../data/P14_rata1_capaII_cel1.DAT", std::ifstream::binary);
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::DATParser parser(is);
    auto r = parser.read("P14_rata1_capaII_cel1");
    is.close();
    //std::cout << (*r);
    // delete r;
  }
}

TEST(DAT_Parser_map)
{
  // Open file
  std::ifstream is("../data/mapita_rata_1_capa_II.DAT", std::ifstream::binary);
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::DATParser parser(is);
    auto  r = parser.read("mapita_rata_1_capa_II");
    is.close();
    //std::cout << (*r);
    // delete r;
  }
}
