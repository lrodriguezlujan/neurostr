#ifndef NEUROSTR_TEST_AUX__H_
#define NEUROSTR_TEST_AUX__H_


#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>

#include "core/neuron.h"
#include "io/DATParser.h"
#include "io/SWCParser.h"

namespace neurostr_test{
  
// Common function to load data
// Common function to load data
std::unique_ptr<neurostr::Reconstruction> load_full_reconstruction() ;
std::unique_ptr<neurostr::Reconstruction> load_simple_reconstruction();
std::unique_ptr<neurostr::Reconstruction> load_full_SWC_reconstruction();
std::unique_ptr<neurostr::Reconstruction> load_full_real_reconstruction();

}

#endif
