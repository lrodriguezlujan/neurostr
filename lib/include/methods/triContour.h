#ifndef NEUROSTR_METHODS_TRICONTOUR_H_
#define NEUROSTR_METHODS_TRICONTOUR_H_

#include "core/contour.h"
#include "core/geometry.h"


namespace neurostr{
  
  template <typename Iter>
  triMesh_type create_triangular_contour(const Iter& b, const Iter& e){}
  
  std::vector<triangle_type> 
  triangulate_contours( std::vector<point_type>& c1,
                        std::vector<point_type>& c2);
}

#endif
