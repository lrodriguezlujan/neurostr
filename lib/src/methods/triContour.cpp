#include "methods/triContour.h"

namespace neurostr{
namespace methods{
  
    /**
   * @brief Given two contours, reorients them in counter clockwise order. 
   * Also applies a rotation to ensure that the two first nodes are the closest ones.
   * @param a First contour
   * @param b Second contour
   */
  void align_contours( Contour& a, Contour& b, int component){
    
    // Fix orientation
    if( a.clockwise_oriented(component)) a.reverse();
    if( b.clockwise_oriented(component)) b.reverse();
    
    // Really unefficient
    float min_dist = std::numeric_limits<float>::max();
    Contour::iterator min_a,min_b;
    float d;
    
    // Search the closest points
    for(auto it_a = a.begin(); it_a != a.end(); ++it_a){
      for(auto it_b = b.begin(); it_b != b.end(); ++it_b){
          d = geometry::distance(*it_a,*it_b);
          if(d < min_dist){
            min_dist = d;
            min_a = it_a;
            min_b = it_b;
          }
      }
    }
    
    // Align them
    a.rotate(min_a);
    b.rotate(min_b);
    
    return ;
  }
  
  /**
   * @brief Closes the contour 
   * @param a Contour
   * @return Set of triangules to close the contour
   */
  std::vector<triangle_type> close_contour(const Contour& a){
    std::vector<triangle_type> trs;
    trs.reserve(a.size());
    
    point_type b = a.barycenter(); // Same number of triangles, less prone to errors
    for (auto it = std::next(a.begin(),1); it != a.end(); ++it) {
        trs.push_back( {*std::prev(it,1), *it, b} );
    }

    return trs;
  }
  
} // End namespace methods  
} // End namespace neurostr

