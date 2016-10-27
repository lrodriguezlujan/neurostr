#include <unittest++/UnitTest++.h>
#include "core/contour.h"

SUITE(contour_tests){

using namespace neurostr;

// Test neurite structure
struct TestContour {
  TestContour() : open(), closed(), empty() {
    
    std::vector<point_type> open_positions = {
      point_type(0,0,0),
      point_type(1,1,1),
      point_type(2,2,2),
      point_type(3,3,3)
    };
    open = Contour(open_positions);
    
    std::vector<point_type> closed_positions = {
      point_type(0,0,1),
      point_type(1,1,1),
      point_type(0,1,1)
    };
    closed = Contour(closed_positions);
    closed.close();
  }
  
  ~TestContour(){};
  
  Contour open;
  Contour closed;
  Contour empty;
};


TEST(empty_constructor){
  Contour c;
  CHECK_EQUAL(c.size(),0);
  
}

TEST(vector_constructor){
  Contour c({
    point_type(0,0,1),
    point_type(1,1,1),
    point_type(0,1,1)
  });
  CHECK_EQUAL(c.size(),3);
  CHECK_EQUAL(3,std::distance(c.begin(),c.end()));
}

TEST(iterator_empty){
  Contour c;
  CHECK(c.begin() == c.end());
}

TEST(length_open){
  TestContour test_data;
  Contour& open = test_data.open;
  
  CHECK_CLOSE(sqrt(27),open.length(),1E-6);
}

TEST(length_closed){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK_CLOSE(2 + sqrt(2) ,closed.length(),1E-6);
}

TEST(length_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  CHECK_EQUAL(0,empty.length());
}

TEST(area_open){
  TestContour test_data;
  Contour& open = test_data.open;
  
  // NOt implemented - should be 0
}

TEST(area_closed){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  // Not implemented
  
}

TEST(area_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  // NOt implemented - should be 0
  
}

TEST(closing_gap_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK_EQUAL(0,empty.closing_gap());
}

TEST(closing_gap_open){
  TestContour test_data;
  Contour& open = test_data.open;
  
  CHECK_CLOSE( open.length(), open.closing_gap(), 1E-6);
}

TEST(closing_gap_closed){
  TestContour test_data;
  Contour& closed = test_data.closed;
  CHECK_EQUAL(0,closed.closing_gap());
}

TEST(close_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK_EQUAL(0,empty.size());
  CHECK_EQUAL(0,empty.length());
  CHECK(!empty.is_closed());
  
  empty.close();
  
  CHECK_EQUAL(0,empty.size());
  CHECK_EQUAL(0,empty.length());
  CHECK(empty.is_closed());
}

TEST(close_open){
  TestContour test_data;
  Contour& open = test_data.open;

  CHECK_EQUAL(4,open.size());
  CHECK_CLOSE(sqrt(27),open.length(),1E-6);
  CHECK(!open.is_closed());
  
  open.close();
  
  CHECK_EQUAL(5,open.size());
  CHECK_CLOSE(2*sqrt(27),open.length(),1E-6);
  CHECK(open.is_closed());
}

TEST(close_close){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK_EQUAL(4,closed.size());
  CHECK(closed.is_closed());
  
  closed.close();
  
  CHECK_EQUAL(4,closed.size());
  CHECK(closed.is_closed());
}

TEST(planar_axis_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK_EQUAL(-1,empty.planar_axis());
}

TEST(planar_noplanar){
  TestContour test_data;
  Contour& open = test_data.open;
  
  CHECK_EQUAL(-1,open.planar_axis());
  
}

TEST(planar_axis){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK_EQUAL(2,closed.planar_axis());
}

TEST(range_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  auto r = empty.range(0);
  CHECK_EQUAL(0,r.first);
  CHECK_EQUAL(0,r.second);
  
  r = empty.range(1);
  CHECK_EQUAL(0,r.first);
  CHECK_EQUAL(0,r.second);
  
  r = empty.range(2);
  CHECK_EQUAL(0,r.first);
  CHECK_EQUAL(0,r.second);
  
}

TEST(range){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  auto r = closed.range(0);
  CHECK_EQUAL(0,r.first);
  CHECK_EQUAL(1,r.second);
  
  r = closed.range(1);
  CHECK_EQUAL(0,r.first);
  CHECK_EQUAL(1,r.second);
  
  r = closed.range(2);
  CHECK_EQUAL(1,r.first);
  CHECK_EQUAL(1,r.second);
  
  
}

TEST(planar_proj_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK_EQUAL(0,empty.planar_projection(0).size());
  CHECK_EQUAL(0,empty.planar_projection(1).size());
  CHECK_EQUAL(0,empty.planar_projection(2).size());
  
}

TEST(planar_proj){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  auto v = closed.planar_projection(2);
  
  CHECK(geometry::equal(v[0],geometry::planar_point(0,0)));
  CHECK(geometry::equal(v[1],geometry::planar_point(1,1)));
  CHECK(geometry::equal(v[2],geometry::planar_point(0,1)));
}

TEST(orientation_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK(empty.clockwise_oriented(0) == false);
  CHECK(empty.clockwise_oriented(1) == false);
  CHECK(empty.clockwise_oriented(2) == false);
}

TEST(orientation){
  TestContour test_data;
  Contour& closed = test_data.closed;
  CHECK(closed.clockwise_oriented(2) == false);
}

TEST(reverse_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  CHECK(empty.clockwise_oriented(0) == false);
  CHECK(empty.clockwise_oriented(1) == false);
  CHECK(empty.clockwise_oriented(2) == false);
  empty.reverse();
  CHECK(empty.clockwise_oriented(0) == false);
  CHECK(empty.clockwise_oriented(1) == false);
  CHECK(empty.clockwise_oriented(2) == false);
  
}

TEST(reverse_open){
  TestContour test_data;
  Contour& open = test_data.open;
  
  CHECK_CLOSE(0, geometry::distance(*open.begin(),point_type(0,0,0)),1E-6);
  open.reverse();
  CHECK_CLOSE(0, geometry::distance(*open.begin(),point_type(3,3,3)),1E-6);
}

TEST(reverse_closed){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK(closed.clockwise_oriented(2) == false);
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  closed.reverse();
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  CHECK(closed.clockwise_oriented(2) == true);
}

TEST(rotate_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  
  // Just make sure it doesnt fail
  
  CHECK_EQUAL(0,empty.size());
  CHECK_EQUAL(0,empty.length());
  empty.rotate(empty.begin());
  CHECK_EQUAL(0,empty.size());
  CHECK_EQUAL(0,empty.length());
  
}

TEST(rotate_open){
  TestContour test_data;
  Contour& open = test_data.open;
  
  // Open shouldn rotate
  CHECK_CLOSE(0, geometry::distance(*open.begin(),point_type(0,0,0)),1E-6);
  open.rotate(std::next(open.begin(),1));
  CHECK_CLOSE(0, geometry::distance(*open.begin(),point_type(0,0,0)),1E-6);
}

TEST(rotate_end){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  closed.rotate(closed.end()); // Dont do anything
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  
}

TEST(rotate_begin){
  TestContour test_data;

  Contour& closed = test_data.closed;
  
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  closed.rotate(closed.begin());
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  
}

TEST(rotate_closed){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  auto prev = *std::next(closed.begin(),1);
  
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),point_type(0,0,1)),1E-6);
  closed.rotate(std::next(closed.begin(),1));
  CHECK_CLOSE(0, geometry::distance(*closed.begin(),prev),1E-6);
  CHECK_CLOSE(0, geometry::distance(*std::prev(closed.end(),1),prev),1E-6);
  
}

TEST(barycenter_empty){
  TestContour test_data;
  Contour& empty = test_data.empty;
  CHECK_CLOSE(0, geometry::distance(empty.barycenter(),point_type(0,0,0)),1E-6);
}

TEST(barycenter){
  TestContour test_data;
  Contour& closed = test_data.closed;
  
  CHECK_CLOSE(0.0, geometry::distance(closed.barycenter(),point_type(1.0/3,2.0/3,1)),1E-6);
}

} // End contour tests
