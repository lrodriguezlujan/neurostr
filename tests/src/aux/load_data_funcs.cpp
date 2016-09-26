#include "aux/load_data_funcs.h"

namespace neurostr_test{
  

// Common function to load data
std::unique_ptr<neurostr::Reconstruction> load_full_reconstruction() {
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
    return r;
  }
}


// Common function to load data
std::unique_ptr<neurostr::Reconstruction> load_full_SWC_reconstruction() {
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
    is.close();
    //std::cout << (*r);
    // delete r;
    return r;
  }
}

std::unique_ptr<neurostr::Reconstruction> load_simple_reconstruction() {
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
    return r;
  }
}

std::unique_ptr<neurostr::Reconstruction> load_full_real_reconstruction(){
  // Open file
  std::ifstream is("../data/real_data/h213III1.DAT",std::ifstream::binary);
  if(!is){
    std::cerr << "FILE NOT FOUND" << std::endl;
    throw std::runtime_error("FILE NOT FOUND");
  }
  else{
    // Call read
    neurostr::io::DATParser parser(is);
    auto r = parser.read("h213III1");
    //std::cout << *r;
    is.close();
    return r;
  }
}

}
