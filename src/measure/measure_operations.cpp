#include <neurostr/measure/measure_operations.h>

namespace neurostr {
namespace measure {

  
  template <>
std::vector<float>
  remove_nan_values<float>( typename  std::vector<float>::iterator b,  
                     typename  std::vector<float>::iterator e){
  return remove_nan_values_detail_<float>(b,e);
}


template <>
std::vector<double>
  remove_nan_values<double>( typename  std::vector<double>::iterator b,  
                     typename  std::vector<double>::iterator e){
  return remove_nan_values_detail_<double>(b,e);
}


template <>
std::vector<long double>
  remove_nan_values<long double>( typename  std::vector<long double>::iterator b,  
                     typename  std::vector<long double>::iterator e){
  return remove_nan_values_detail_<long double>(b,e);
}


  
}
}
