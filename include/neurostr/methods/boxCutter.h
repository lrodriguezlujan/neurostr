#ifndef NEUROSTR_METHODS_BOX_CUTTER_H_
#define NEUROSTR_METHODS_BOX_CUTTER_H_

#include <neurostr/core/geometry.h>
#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>

namespace neurostr{
namespace methods{
  
  void neuronBoxCutter( Neuron& n,const point_type& min_corner, const point_type& max_corner );
  
  void neuriteBoxCutter( Neurite& n, const box_type& box);
  
  bool branchBoxCutter( Branch& b, const box_type& box);
  
  void BoxCutterRestore( Neuron& n );
     
} // methods
} // neurostr


#endif
