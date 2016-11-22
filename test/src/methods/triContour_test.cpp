#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>


#include "core/geometry.h"
#include "core/contour.h"
#include "methods/triContour.h"


namespace ng = neurostr::geometry;
namespace nm = neurostr::methods;

using namespace neurostr;

TEST(triangulate_contours){
  
  std::vector<point_type> z0({
    point_type(0,0,0),
    point_type(10,0,0),
    point_type(10,5,0),
    point_type(0,5,0)
  });
  
  std::vector<point_type> z1({
    point_type(1,1,1),
    point_type(9,1,1),
    point_type(9,4,1),
    point_type(1,4,1)
  });
  
    // Create contours
  Contour c0(z0);
  Contour c1(z1);
  
  // Close them
  c0.close();
  c1.close();
  
  
  auto tris = methods::triangulate_contours( c0.begin(), c0.end(),
                        c1.begin(), c1.end());
  
  for(auto it = tris.begin(); it != tris.end(); ++it){
    
    std::cout << "\t\tFace: " << std::endl ;  
    std::cout << "\t\t\t (" << geometry::getx( (*it)[0] ) << ", " << geometry::gety((*it)[0]) << ", " << geometry::getz((*it)[0]) << ")" << std::endl;
    std::cout << "\t\t\t (" << geometry::getx( (*it)[1] ) << ", " << geometry::gety((*it)[1]) << ", " << geometry::getz((*it)[1]) << ")" << std::endl;
    std::cout << "\t\t\t (" << geometry::getx( (*it)[2] ) << ", " << geometry::gety((*it)[2]) << ", " << geometry::getz((*it)[2]) << ")" << std::endl;
    
  }
  
}

TEST(join_contours) {
  
  // Three contours 
  // 1. (Z = 0) (0,0) (10,0) (10,5) (0,5)
  // 2. (Z = 1) (1,1) (9,1) (9,4) (1,4)
  // 3. (Z = 2) (0,0) (10,0) (10,5) (0,5)
  std::vector<point_type> z0({
    point_type(0,0,0),
    point_type(10,0,0),
    point_type(10,5,0),
    point_type(0,5,0)
  });
  
  std::vector<point_type> z1({
    point_type(1,1,1),
    point_type(9,1,1),
    point_type(9,4,1),
    point_type(1,4,1)
  });
  
  std::vector<point_type> z2({
    point_type(0,0,2),
    point_type(10,0,2),
    point_type(10,5,2),
    point_type(0,5,2)
  });
  
  // Create contours
  Contour c0(z0);
  Contour c1(z1);
  Contour c2(z2);
  
  // Close them
  c0.close();
  c1.close();
  c2.close();
  
  // Store in a vector
  std::vector<Contour> cs({c0,c1,c2});
  
  // Call.... triangulation
  auto mesh = nm::create_triangular_contour(cs.begin(),cs.end(),2);
  std::cout << mesh;
  
} // End contour join


TEST(in_contour) {
  
  // Three contours 
  // 1. (Z = 0) (0,0) (10,0) (10,5) (0,5)
  // 2. (Z = 1) (1,1) (9,1) (9,4) (1,4)
  // 3. (Z = 2) (0,0) (10,0) (10,5) (0,5)
  std::vector<point_type> z0({
    point_type(0,0,0),
    point_type(10,0,0),
    point_type(10,5,0),
    point_type(0,5,0)
  });
  
  std::vector<point_type> z1({
    point_type(1,1,1),
    point_type(9,1,1),
    point_type(9,4,1),
    point_type(1,4,1)
  });
  
  std::vector<point_type> z2({
    point_type(0,0,2),
    point_type(10,0,2),
    point_type(10,5,2),
    point_type(0,5,2)
  });
  
  // Create contours
  Contour c0(z0);
  Contour c1(z1);
  Contour c2(z2);
  
  // Close them
  c0.close();
  c1.close();
  c2.close();
  
  // Store in a vector
  std::vector<Contour> cs({c0,c1,c2});
  
  // Call.... triangulation
  auto mesh = nm::create_triangular_contour(cs.begin(),cs.end(),2);
  bool res = mesh.point_inside(point_type(5,2.5,1.1));
  
  CHECK(res);
  
} // End contour join
