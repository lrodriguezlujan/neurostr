#include <unittest++/UnitTest++.h>
#include "core/geometry.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"

SUITE(geometry_tests){
using namespace neurostr::geometry;

TEST(static_get){
  point_type p(1,2,3);
  CHECK_EQUAL(1,get<0>(p));
  CHECK_EQUAL(2,get<1>(p));
  CHECK_EQUAL(3,get<2>(p));
}

TEST(static_get_planar){
  planar_point p(1,2);
  CHECK_EQUAL(1,get<0>(p));
  CHECK_EQUAL(2,get<1>(p));
}

TEST(getx){
  point_type p(1,2,3);
  CHECK_EQUAL(1,getx(p));
}

TEST(gety){
  point_type p(1,2,3);
  CHECK_EQUAL(2,gety(p));
}

TEST(getz){
  point_type p(1,2,3);
  CHECK_EQUAL(3,getz(p));
}

TEST(dyn_get){
  point_type p(1,2,3);
  CHECK_EQUAL(1,get(p,0));
  CHECK_EQUAL(2,get(p,1));
  CHECK_EQUAL(3,get(p,2));
}

TEST(planar_proj_static){
  point_type p(1,2,3);
  planar_point p0 = planar_projection<0>(p);
  CHECK_EQUAL(2,get<0>(p0));
  CHECK_EQUAL(3,get<1>(p0));
  
  planar_point p1 = planar_projection<1>(p);
  CHECK_EQUAL(1,get<0>(p1));
  CHECK_EQUAL(3,get<1>(p1));
  
  planar_point p2 = planar_projection<2>(p);
  CHECK_EQUAL(1,get<0>(p2));
  CHECK_EQUAL(2,get<1>(p2));
}

TEST(planar_proj_dyn){
  point_type p(1,2,3);
  planar_point p0 = planar_projection(p,0);
  CHECK_EQUAL(2,get<0>(p0));
  CHECK_EQUAL(3,get<1>(p0));
  
  planar_point p1 = planar_projection(p,1);
  CHECK_EQUAL(1,get<0>(p1));
  CHECK_EQUAL(3,get<1>(p1));
  
  planar_point p2 = planar_projection(p,2);
  CHECK_EQUAL(1,get<0>(p2));
  CHECK_EQUAL(2,get<1>(p2));
}

TEST(distance){
  point_type p(1,0,0);
  point_type q(0,0,0);
  point_type r(1,1,1);
  
  CHECK_CLOSE(1,distance(p,q),1E-6);
  CHECK_EQUAL(distance(q,p),distance(p,q));
  
  CHECK_CLOSE(0,distance(p,p),1E-6);
  
  CHECK_CLOSE(sqrt(3),distance(q,r),1E-6);
}

TEST(vector_to){
  point_type p(1,0,0);
  point_type q(0,0,0);
  point_type r(1,1,1);
  
  CHECK_CLOSE(0,distance(r,vectorFromTo(q,r)),1E-6);
  CHECK_CLOSE(0,distance(point_type(0,1,1),vectorFromTo(p,r)),1E-6);
  CHECK_CLOSE(0,distance(point_type(0,0,0),vectorFromTo(p,p)),1E-6);
}

TEST(traslate){
  point_type p(0,0,0);
  point_type t(1,0,0);
  
  traslate(p,t);
  CHECK_CLOSE(0,distance(p,t),1E-6);
}

TEST(traslate_zero){
  point_type p(1,0,1);
  point_type t(0,0,0);
  
  traslate(p,t);
  CHECK_CLOSE(0,distance(p,p),1E-6);
}

TEST(scale_ref){
  point_type p(1,0,0);
  point_type q(1,0,1);
  point_type r(0,0,0);
  
  scale(p,0.5,r);
  CHECK_CLOSE(0,distance(p,point_type(0.5,0,0)),1E-6);
  
  scale(q,0.5,r);
  CHECK_CLOSE(0,distance(q,point_type(0.5,0,0.5)),1E-6);

}

TEST(scale_ref_zero){
  
  point_type p(1,0,0);
  point_type q(1,0,1);
  point_type r(1,3,2);
  
  scale(p,0.0,r);
  CHECK_CLOSE(0,distance(p,r),1E-6);
  
  scale(q,0.0,r);
  CHECK_CLOSE(0,distance(q,r),1E-6);
}

TEST(scale_axis){
  point_type p(1,1,1);
  scale(p,0.3,0.5,0.7);
  CHECK_CLOSE(0,distance(p,point_type(0.3,0.5,0.7)),1E-6);
}

TEST(crossprod){
  point_type p(1,0,0);
  point_type q(0,1,0);
  
  CHECK_CLOSE(0,distance(cross_product(p,q),point_type(0,0,1)),1E-6);
}

TEST(crossprod_zero){
  point_type p(0,0,0);
  point_type q(1,1,1);
  
  CHECK_CLOSE(0,distance(cross_product(p,q),point_type(0,0,0)),1E-6);
}

TEST(crossprod_same){
  point_type p(1,0,0);
  point_type q(1,0,0);
  
  CHECK_CLOSE(0,distance(cross_product(p,q),point_type(0,0,0)),1E-6);
}

TEST(euclidean_norm){
  point_type p(0,0,0);
  point_type q(1,1,1);
  
  CHECK_CLOSE(0,norm(p),1E-6);
  CHECK_CLOSE(sqrt(3),norm(q),1E-6);
}

TEST(equality){
  point_type p(0,0,0);
  point_type r(0,0,0);
  point_type s(1E-6,0,0);
  
  CHECK(equal(p,p));
  CHECK(equal(p,r));
}

TEST(inequality){
  point_type p(0,0,0);
  point_type q(1,1,1);
  point_type s(1E-6,0,0);
  
  CHECK(!equal(p,q));
  CHECK(!equal(p,s));
  CHECK(!equal(q,s));
}
/* Need a good example for this 
TEST(get_basis){
  
}

TEST(get_basis_failure){
  
}
*/

TEST(segment_segment_distance_parallel){
  point_type p(0,0,0);
  point_type q(1,0,0);
  point_type r(0,1,0);
  point_type s(1,1,0);
  
  CHECK_CLOSE(1,segment_segment_distance(p,q,r,s),1E-6);
}

TEST(segment_segment_distance_crossing){
  point_type p(0,0,0);
  point_type q(1,0,0);
  point_type r(0.5,0.5,0);
  point_type s(0.5,-0.5,0);
  
  CHECK_CLOSE(0,segment_segment_distance(p,q,r,s),1E-6);
}

TEST(segment_segment_distance_nonparallel){
  point_type p(0,0,0);
  point_type q(1,0,0);
  point_type r(1,10.5,0);
  point_type s(1,0.5,0);
  CHECK_CLOSE(0.5,segment_segment_distance(p,q,r,s),1E-6);
}


TEST(vector_aligment_sq){
  
  point_type p(1,0,0);
  point_type q(0,1,0);
  
  auto quat = align_vectors(p,q);
  Eigen::Vector3f tmp( getx(p), gety(p),getz(p));
  
  // Apply quaternion
  tmp = quat * tmp;
  
  CHECK_CLOSE(0.0,distance(point_type(tmp[0],tmp[1],tmp[2]),q),1E-6);
}

TEST(vector_aligment_aligned){
  point_type p(1,0,0);
  point_type q(1,0,0);
  
  auto quat = align_vectors(p,q);
  Eigen::Vector3f tmp( getx(p), gety(p),getz(p));
  
  // Apply quaternion
  tmp = quat * tmp;
  
  CHECK_CLOSE(0.0,distance(point_type(tmp[0],tmp[1],tmp[2]),q),1E-6); 
}

TEST(vector_aligment_opposite){
  
  point_type p(1,0,0);
  point_type q(-1,0,0);
  
  auto quat = align_vectors(p,q);
  Eigen::Vector3f tmp( getx(p), gety(p),getz(p));
  
  // Apply quaternion
  tmp = quat * tmp;
  
  CHECK_CLOSE(0.0,distance(point_type(tmp[0],tmp[1],tmp[2]),q),1E-6);  
}

TEST(vector_aligment_reg){
  
  point_type p(1,1,0);
  point_type q(0,1,1);
  
  auto quat = align_vectors(p,q);
  Eigen::Vector3f tmp( getx(p), gety(p),getz(p));
  
  // Apply quaternion
  tmp = quat * tmp;
  
  CHECK_CLOSE(0.0,distance(point_type(tmp[0],tmp[1],tmp[2]),q),1E-6);
}

TEST(vector_aligment_zero){
  
  point_type p(1,1,0);
  point_type q(0,0,0);
  
  auto quat = align_vectors(p,q);
  
  // Undefined behaviour
  CHECK(Eigen::Quaternionf::Identity().isApprox(quat));
}


TEST(segment_box_intersection_reg){
  box_type b( point_type(0,0,0), point_type(1,1,1));
  segment_type s( point_type(0.5,0.5,0.5), point_type(1.1,0.5,0.5) );
  point_type i;
  
  CHECK(segment_box_intersection(b,s,i));
  CHECK_CLOSE(0,distance(i,point_type(1,0.5,0.5)),1E-6);
}

TEST(segment_box_intersection_limit_plane){
 
  box_type b( point_type(0,0,0), point_type(1,1,1));
  segment_type s( point_type(0.5,0.5,0.5), point_type(1.1,0.5,0.5) );
  segment_type r( point_type(0.5,1,0), point_type(1,1,0) );
  point_type i;
  
  CHECK(segment_box_intersection(b,s,i));
  CHECK_CLOSE(0,distance(i,point_type(1,0.5,0.5)),1E-6); 
  
  CHECK(segment_box_intersection(b,r,i)); // Point could be any
}

TEST(segment_box_intersection_limit_corner){
  box_type b( point_type(0,0,0), point_type(1,1,1));
  segment_type s( point_type(1,1,1), point_type(1.1,1.1,1.1) );
  point_type i;
  
  CHECK(segment_box_intersection(b,s,i));
  CHECK_CLOSE(0,distance(i,point_type(1,1,1)),1E-6); 
}

TEST(segment_box_intersection_nointersect_out){
  
  box_type b( point_type(0,0,0), point_type(1,1,1));
  segment_type s( point_type(1.1,1.1,1.1), point_type(1.2,1.2,1.2) );
  point_type i;
  
  CHECK(!segment_box_intersection(b,s,i));

}

TEST(segment_box_intersection_nointersect_in){
  
  box_type b( point_type(0,0,0), point_type(1,1,1));
  segment_type s( point_type(0.1,0.1,0.1), point_type(0.2,0.2,0.2) );
  point_type i;
  
  CHECK(!segment_box_intersection(b,s,i));

}

TEST(segment_cross_plane_reg){
  
  segment_type s1( point_type(0,0,0), point_type(1,0,0) );
  segment_type s2( point_type(0,0,0), point_type(0,1,0) );
  segment_type s3( point_type(0,0,0), point_type(0,0,1) );
  point_type i;
  
  CHECK(segment_cross_plane<0>(s1,point_type(0.5,0.5,0.5), i ));
  CHECK_CLOSE(0, distance(i, point_type(0.5,0,0)),1E-6);
  CHECK(segment_cross_plane<1>(s2,point_type(0.5,0.5,0.5), i ));
  CHECK_CLOSE(0, distance(i, point_type(0,0.5,0)),1E-6);
  CHECK(segment_cross_plane<2>(s3,point_type(0.5,0.5,0.5), i ));
  CHECK_CLOSE(0, distance(i, point_type(0,0,0.5)),1E-6);
}

TEST(segment_cross_plane_limit){
  segment_type s1( point_type(0,0,0), point_type(1,0,0) );
  segment_type s2( point_type(0,0,0), point_type(0,1,0) );
  segment_type s3( point_type(0,0,0), point_type(0,0,1) );
  point_type i;
  
  CHECK(segment_cross_plane<0>(s1,point_type(1,1,1), i ));
  CHECK_CLOSE(0, distance(i, point_type(1,0,0)),1E-6);
  CHECK(segment_cross_plane<1>(s2,point_type(1,1,1), i ));
  CHECK_CLOSE(0, distance(i, point_type(0,1,0)),1E-6);
  CHECK(segment_cross_plane<2>(s3,point_type(1,1,1), i ));
  CHECK_CLOSE(0, distance(i, point_type(0,0,1)),1E-6);
}

TEST(segment_cross_plane_no){
    segment_type s1( point_type(0,0,0), point_type(1,0,0) );
  segment_type s2( point_type(0,0,0), point_type(0,1,0) );
  segment_type s3( point_type(0,0,0), point_type(0,0,1) );
  point_type i;
  
  CHECK(!segment_cross_plane<0>(s1,point_type(2,2,2), i ));
  CHECK(!segment_cross_plane<1>(s2,point_type(2,2,2), i ));
  CHECK(!segment_cross_plane<2>(s3,point_type(2,2,2), i ));
}

TEST(min_component_static){
  point_type p(1,1,0);
  point_type q(0,0,1);
  
  min_component<0>(p,q);
  CHECK_EQUAL(0,getx(q));
  
  min_component<1>(p,q);
  CHECK_EQUAL(0,gety(q));
  
  min_component<2>(p,q);
  CHECK_EQUAL(0,getz(q));
  
}

TEST(max_component_static){
  
  point_type p(1,1,0);
  point_type q(0,0,1);
  
  max_component<0>(p,q);
  CHECK_EQUAL(1,getx(q));
  
  max_component<1>(p,q);
  CHECK_EQUAL(1,gety(q));
  
  max_component<2>(p,q);
  CHECK_EQUAL(1,getz(q));
}

TEST(max_by_component_static){
  point_type p(1,1,0);
  point_type q(0,0,1);
  max_by_component(p,q);
  CHECK(equal(q,point_type(1,1,1)));
}

TEST(min_by_component_static){
  point_type p(1,1,0);
  point_type q(0,0,1);
  min_by_component(p,q);
  CHECK(equal(q,point_type(0,0,0)));
}

TEST(box_ax_length_static){
  box_type b( point_type(0,0,0), point_type(1,2,3));
  CHECK_EQUAL(1,axisLength<Axis::X_POS>(b));
  CHECK_EQUAL(2,axisLength<Axis::Y_POS>(b));
  CHECK_EQUAL(3,axisLength<Axis::Z_POS>(b));
  
  CHECK_EQUAL(0,axisLength<Axis::X_NEG>(b));
  CHECK_EQUAL(0,axisLength<Axis::Y_NEG>(b));
  CHECK_EQUAL(0,axisLength<Axis::Z_NEG>(b));
}

/*
TEST(polygon_planar_reg){
  std::vector<point_type> poly({
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  });
  
  auto planar_poly = as_planar_polygon(poly);
  //¿¿ 
}*/

TEST(polygon_planar_singlepoint){
  std::vector<point_type> poly({ point_type(0,0,0)  });
  CHECK_EQUAL(0, num_points(as_planar_polygon(poly)));
}

TEST(polygon_planar_empty){
  std::vector<point_type> poly;
  CHECK_EQUAL(0, num_points(as_planar_polygon(poly)));
}

/*
TEST(polygon_planar_segment){
  
}*/

TEST(negate_point){
  point_type p(1,2,3);
  negate(p);
  CHECK_EQUAL(-1,getx(p));
  CHECK_EQUAL(-2,gety(p));
  CHECK_EQUAL(-3,getz(p));
}

TEST(negate_zero){
  point_type p(0,-1,0);
  negate(p);
  CHECK_EQUAL(0,getx(p));
  CHECK_EQUAL(1,gety(p));
  CHECK_EQUAL(0,getz(p));
}

TEST(barycenter_reg){
  std::vector<point_type> poly({
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  });
  
  point_type p = barycenter(poly);
  
  CHECK_CLOSE(1.0/3,getx(p),1E-6);
  CHECK_CLOSE(1.0/3,gety(p),1E-6);
  CHECK_EQUAL(0,getz(p));
}

TEST(barycenter_empty){
  std::vector<point_type> poly;
  point_type p = barycenter(poly);
  CHECK_EQUAL(0.0,norm(p));
}

TEST(barycenter_single){
  std::vector<point_type> poly({ point_type(1,0,0)});
  point_type p = barycenter(poly);
  CHECK(equal(p,point_type(1,0,0)));
}

TEST(normalize_reg){
  point_type p(1,1,1);
  normalize(p);
  CHECK_CLOSE(1/sqrt(3),getx(p),1E-6);
  CHECK_CLOSE(1/sqrt(3),gety(p),1E-6);
  CHECK_CLOSE(1/sqrt(3),getz(p),1E-6);
}

TEST(normalize_unit){
  point_type p(1,0,0),
  normalize(p);
  CHECK_EQUAL(1,getx(p));
  CHECK_EQUAL(0,gety(p));
  CHECK_EQUAL(0,getz(p));
}

TEST(normalize_zero){
  point_type p(0,0,0),
  normalize(p);
  CHECK_EQUAL(0,norm(p));
}

TEST(v_v_angle_reg){
  point_type p(1,0,0);
  point_type q(std::cos(M_PI/4),std::sin(M_PI/4),0);
  point_type r(std::cos(-M_PI/4),std::sin(-M_PI/4),0);
  
  CHECK_CLOSE(M_PI/4,vector_vector_angle(p,q),1E-6);
  CHECK_CLOSE(M_PI/4,vector_vector_angle(p,r),1E-6);
}

TEST(v_v_angle_same){
  point_type p(1,0,0);
  
  CHECK_CLOSE(0,vector_vector_angle(p,p),1E-6);
}

TEST(v_v_angle_opposite){
  point_type p(1,0,0);
  point_type q(-1,0,0);
  CHECK_CLOSE(M_PI,vector_vector_angle(p,q),1E-6);
}

TEST(box_box_inters){
  box_type b1( point_type(0,0,0), point_type(1,1,1));
  box_type b2( point_type(0.5,0.5,0.5), point_type(1.5,1.5,1.5));
  
  CHECK(box_box_intersection(b1,b2));
}

TEST(box_box_inters_same){
  
  box_type b1( point_type(0,0,0), point_type(1,1,1));
  
  CHECK(box_box_intersection(b1,b1));
  
}

TEST(box_box_inters_facelimit){
  box_type b1( point_type(0,0,0), point_type(1,1,1));
  box_type b2( point_type(1,0,0), point_type(1.5,1.5,1.5));
  
  CHECK(box_box_intersection(b1,b2));
}

TEST(box_box_inters_cornerlimit){
  box_type b1( point_type(0,0,0), point_type(1,1,1));
  box_type b2( point_type(1,1,1), point_type(1.5,1.5,1.5));
  
  CHECK(box_box_intersection(b1,b2));
}

TEST(box_box_inters_no){
  
  box_type b1( point_type(0,0,0), point_type(1,1,1));
  box_type b2( point_type(1.1,1.1,1.1), point_type(1.5,1.5,1.5));
  
  CHECK(!box_box_intersection(b1,b2));
}

/**
TEST(lineseg_dist_reg){
  
}

TEST(lineseg_dist_same){
  
}

TEST(lineseg_dist_single){
  
}

TEST(lineseg_dist_empty){
  
}*/

TEST(bbox_reg){
  std::vector<point_type> poly({
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0),
    point_type(0,0,1)
  });
  
  box_type b = bounding_box(poly);
  CHECK_CLOSE(0, distance(b.min_corner(),point_type(0,0,0)),1E-6);
  CHECK_CLOSE(0, distance(b.max_corner(),point_type(1,1,1)),1E-6);
}

TEST(bbox_single){
  std::vector<point_type> poly({
    point_type(0,0,0)
  });
  
  box_type b = bounding_box(poly);
  CHECK_CLOSE(0, distance(b.min_corner(),point_type(0,0,0)),1E-6);
  CHECK_CLOSE(0, distance(b.max_corner(),point_type(0,0,0)),1E-6);
}

TEST(bbox_empty){
  std::vector<point_type> poly;
  
  box_type b = bounding_box(poly);
  CHECK_CLOSE( 0, distance(b.min_corner(),point_type(0,0,0)),1E-6);
  CHECK_CLOSE( 0, distance(b.max_corner(),point_type(0,0,0)),1E-6);
}

TEST(v_v_directed_angle_reg){
  point_type p(1,0,0);
  point_type q(std::cos(M_PI/4),std::sin(M_PI/4),0);
  point_type r(std::cos(-M_PI/4),std::sin(-M_PI/4),0);
  
  CHECK_CLOSE(M_PI/4,vector_vector_directed_angle(p,q),1E-6);
  CHECK_CLOSE(M_PI/4,vector_vector_directed_angle(p,r),1E-6);
}

TEST(v_v_directed_angle_same){
  point_type p(1,0,0);
  
  CHECK_CLOSE(0,vector_vector_directed_angle(p,p),1E-6);
}

TEST(v_v_directed_angle_opposite){
  point_type p(1,0,0);
  point_type q(-1,0,0);
  
  CHECK_CLOSE(M_PI,vector_vector_directed_angle(p,q),1E-6);
}


TEST(triangle_border_reg){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.5,0,0);
  point_type r(0,0.5,0);
  
  CHECK(in_triangle_border(t,q)); 
  CHECK(in_triangle_border(t,r));
}

TEST(triangle_border_vertex){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0,0,0);
  point_type r(1,0,0);
  point_type s(1,0,0);
  
  CHECK(in_triangle_border(t,q));
  CHECK(in_triangle_border(t,r));
  CHECK(in_triangle_border(t,s));
}

TEST(triangle_border_out){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(1,1,1);
  point_type s(1,0,1);
  
  CHECK(!in_triangle_border(t,q)); 
  CHECK(!in_triangle_border(t,s));
}

TEST(triangle_border_in){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.1,0.1,0);
  
  CHECK(!in_triangle_border(t,q));
}

TEST(triangle_vertex){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0,0,0);
  point_type r(1,0,0);
  point_type s(1,0,0);
  
  CHECK(is_triangle_vertex(t,q));
  CHECK(is_triangle_vertex(t,r));
  CHECK(is_triangle_vertex(t,s));
}

TEST(triangle_vertex_border){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.5,0,0);
  point_type r(0,0.5,0);
  
  CHECK(!is_triangle_vertex(t,q));
  CHECK(!is_triangle_vertex(t,r));
}

TEST(triangle_vertex_in){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.1,0.1,0);
  
  CHECK(!is_triangle_vertex(t,q));
}

TEST(triangle_vertex_out){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(1,1,1);
  point_type s(1,0,1);
  
  CHECK(!is_triangle_vertex(t,q));
  CHECK(!is_triangle_vertex(t,s));
}


TEST(within_triangle_in){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.1,0.1,0);
  CHECK(within_triangle(t,q)); 
  
}

TEST(within_triangle_vertex){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0,0,0);
  point_type r(1,0,0);
  point_type s(1,0,0);
  
  CHECK(within_triangle(t,q));
  CHECK(within_triangle(t,r));
  CHECK(within_triangle(t,s));
}

TEST(within_triangle_border){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(0.5,0,0);
  point_type r(0,0.5,0);
  
  CHECK(within_triangle(t,q));
  CHECK(within_triangle(t,r));
}

TEST(within_triangle_plane_out){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(1,1,0);
  CHECK(!within_triangle(t,q));
}

TEST(within_triangle_noplane){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  point_type q(1,1,1);
  CHECK(!within_triangle(t,q));
}

TEST(triangle_area_reg){
  triangle_type t = {
    point_type(0,0,0),
    point_type(1,0,0),
    point_type(0,1,0)
  };
  
  CHECK_CLOSE(0.5, triangle_area(t), 1E-6);
}

TEST(triangle_area_zero){
  triangle_type t = {
    point_type(0,0,0),
    point_type(0,1,0),
    point_type(0,1,0)
  };
  
  CHECK_CLOSE(0.0, triangle_area(t), 1E-6);
}

// NOTE: RDP simplifier, Discrete Frechet and TriangleMesh (will) have their own
// test suites. (TODO)

} // End suite geometry test

