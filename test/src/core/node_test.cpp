#include <unittest++/UnitTest++.h>
#include <neurostr/core/node.h>
#include <neurostr/core/branch.h>

SUITE(Node_tests){

using Node = neurostr::Node;
using point_type = neurostr::point_type;  

TEST(empty_constructor) {
  neurostr::Node n;
  CHECK_EQUAL(n.id(), -1);
  CHECK_EQUAL(n.radius(), 0);
  CHECK_EQUAL(n.x(), 0);
  CHECK_EQUAL(n.y(), 0);
  CHECK_EQUAL(n.z(), 0);
  CHECK(!n.valid_branch());
  CHECK(!n.valid_parent());
}

TEST(id_constructor) {
  neurostr::Node n(1);
  CHECK_EQUAL(n.id(), 1);
  CHECK_EQUAL(n.radius(), 0);
  CHECK_EQUAL(neurostr::geometry::get<0>(n.position()), 0);
  CHECK_EQUAL(neurostr::geometry::get<1>(n.position()), 0);
  CHECK_EQUAL(neurostr::geometry::get<2>(n.position()), 0);
  CHECK_EQUAL(n.x(), 0);
  CHECK_EQUAL(n.y(), 0);
  CHECK_EQUAL(n.z(), 0);
  CHECK(!n.valid_branch());
  CHECK(!n.valid_parent());
}

TEST(full_constructor) {
  neurostr::Node n(2, 1, 2, 3, 4);
  CHECK_EQUAL(n.id(), 2);
  CHECK_EQUAL(n.radius(), 4);
  CHECK_EQUAL(neurostr::geometry::get<0>(n.position()), 1);
  CHECK_EQUAL(neurostr::geometry::get<1>(n.position()), 2);
  CHECK_EQUAL(neurostr::geometry::get<2>(n.position()), 3);
  CHECK_EQUAL(n.x(), 1);
  CHECK_EQUAL(n.y(), 2);
  CHECK_EQUAL(n.z(), 3);
  CHECK(!n.valid_branch());
  CHECK(!n.valid_parent());
}

TEST(equality_operator) {
  neurostr::Node a, b, c(1, 1, 0, 0, 1), d(1, 2, 0, 1, 2), e(2);
  CHECK(a == a);
  CHECK(a == b);
  CHECK(a != c);
  CHECK(a != d);
  CHECK(a != e);
  CHECK(b == b);
  CHECK(b == a);
  CHECK(b != c);
  CHECK(b != d);
  CHECK(b != e);
  CHECK(c != a);
  CHECK(c != b);
  CHECK(c == c);
  CHECK(c == d);
  CHECK(c != e);
  CHECK(d != a);
  CHECK(d != b);
  CHECK(d == c);
  CHECK(d == d);
  CHECK(d != e);
  CHECK(e != a);
  CHECK(e != b);
  CHECK(e != c);
  CHECK(e != d);
  CHECK(e == e);
}

TEST(distance_empty) {
  neurostr::Node a, b, c(1, 1, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),-1);
  CHECK_EQUAL(a.distance(b.position()),-1);
  CHECK_EQUAL(a.distance(c),-1);
  CHECK_EQUAL(c.distance(a),-1);
}

TEST(distance_self) {
  neurostr::Node a(1, 1, 0, 0, 1);
  CHECK_EQUAL(a.distance(a),0);
  CHECK_EQUAL(a.distance(a.position()),0);
}

TEST(distance_nonzero) {
  neurostr::Node a(1, 1, 0, 0, 1), b(1, 0, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),1);
  CHECK_EQUAL(a.distance(b.position()),1);
}

TEST(distance_symmetric) {
  neurostr::Node a(1, 1, 0, 0, 1), b(1, 0, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),b.distance(a));
  CHECK_EQUAL(a.distance(b.position()),b.distance(a.position()));
}

TEST(vectorTo_empty) {
  neurostr::Node a(1, 1, 0, 0, 1), b;
  neurostr::point_type p=a.vectorTo(b);
  CHECK_EQUAL(neurostr::geometry::get<0>(p), 0);
  CHECK_EQUAL(neurostr::geometry::get<1>(p), 0);
  CHECK_EQUAL(neurostr::geometry::get<2>(p), 0);
  p = b.vectorTo(a);
  CHECK_EQUAL(neurostr::geometry::get<0>(p), 0);
  CHECK_EQUAL(neurostr::geometry::get<1>(p), 0);
  CHECK_EQUAL(neurostr::geometry::get<2>(p), 0);
}

TEST(vectorTo_origin) {
  neurostr::Node a(1, 1, 1, 1, 1), b(1,0,0,0,1);
  neurostr::point_type p=a.vectorTo(b);
  CHECK_EQUAL(neurostr::geometry::get<0>(p), -neurostr::geometry::get<0>(a.position()));
  CHECK_EQUAL(neurostr::geometry::get<1>(p), -neurostr::geometry::get<1>(a.position()));
  CHECK_EQUAL(neurostr::geometry::get<2>(p), -neurostr::geometry::get<2>(a.position()));
}

// Traslate
TEST(traslate){
  neurostr::Node a(1, 1, 1, 1, 1);
  a.traslate(neurostr::point_type(1,1,1));
  CHECK(neurostr::geometry::equal(a.position(),neurostr::point_type(2,2,2)));
  a.traslate(neurostr::point_type(0,0,0));
  CHECK(neurostr::geometry::equal(a.position(),neurostr::point_type(2,2,2)));
}

// Scale ref
TEST(scale_reference){
  neurostr::Node a(1, 1, 1, 1, 1);
  a.scale(0.5,point_type(1,0,0));
  CHECK_CLOSE(1, a.x(), 1E-3);
  CHECK_CLOSE(0.5, a.y(), 1E-3);
  CHECK_CLOSE(0.5, a.z(), 1E-3);
}

// Scale axis
TEST(scale_axis){
  neurostr::Node a(1, 2, 2, 2, 1);
  a.scale(0.5,1,1.1);
  CHECK_CLOSE(1, a.x(), 1E-3);
  CHECK_CLOSE(2, a.y(), 1E-3);
  CHECK_CLOSE(2.2, a.z(), 1E-3);
}

// Rotate
TEST(rotation_ortho){
  neurostr::Node a(1, 1, 2, 1, 1);
  // Traslate works
  auto rot = neurostr::geometry::align_vectors(a.position(),point_type(2,1,1));
  a.rotate(rot);
  CHECK_CLOSE(2, a.x(), 1E-3);
  CHECK_CLOSE(1, a.y(), 1E-3);
  CHECK_CLOSE(1, a.z(), 1E-3);
}

TEST(rotation_nonortho){
  neurostr::Node a(1, 1, 1, 1, 1);
  // Traslate works
  auto rot = neurostr::geometry::align_vectors(a.position(),point_type(1,1,0.5));
  a.rotate(rot);
  CHECK_CLOSE(1.154, a.x(), 1E-3);
  CHECK_CLOSE(1.154, a.y(), 1E-3);
  CHECK_CLOSE(0.577, a.z(), 1E-3);
}

TEST(rotation_stay){
  neurostr::Node a(1, 1, 1, 1, 1);
  // Traslate works
  auto rot = neurostr::geometry::align_vectors(a.position(),point_type(2,2,2));
  a.rotate(rot);
  CHECK_CLOSE(1, a.x(), 1E-3);
  CHECK_CLOSE(1, a.y(), 1E-3);
  CHECK_CLOSE(1, a.z(), 1E-3);
}

// Local basis
/*TEST(local_basis){
  
  
}*/

// Parent
TEST(set_parent){
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  CHECK(!a.valid_parent());
  CHECK_THROW(a.parent(),std::logic_error); // Invalid access
  
  a.parent(&a_parent);
  CHECK(a.valid_parent());
  CHECK(a.parent() == a_parent);
}

TEST(set_null_parent){
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  CHECK(!a.valid_parent());
  CHECK_THROW(a.parent(),std::logic_error); // Invalid access
  
  a.parent(&a_parent);
  CHECK(a.valid_parent());
  
  a.parent(nullptr);
  CHECK(!a.valid_parent());
  CHECK_THROW(a.parent(),std::logic_error); // Invalid access
}

// Branch
TEST(set_branch){
  std::vector<int> id{1,2,3};
  neurostr::Branch b(id,0);
  neurostr::Node a(1, 1, 1, 1, 1);
  
  CHECK(!a.valid_branch());
  CHECK_THROW(a.branch(),std::logic_error); // Invalid access
  
  a.branch(&b);
  CHECK(a.valid_branch());
  CHECK(a.branch() == b);
}

TEST(set_null_branch){
  std::vector<int> id{1,2,3};
  neurostr::Branch b(id,0);
  neurostr::Node a(1, 1, 1, 1, 1);
  
  CHECK(!a.valid_branch());
  CHECK_THROW(a.branch(),std::logic_error); // Invalid access
  
  a.branch(&b);
  CHECK(a.valid_branch());
  
  a.branch(nullptr);
  CHECK(!a.valid_branch());
  CHECK_THROW(a.branch(),std::logic_error); // Invalid access
}

// Position
TEST(set_position_pt){
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  
  CHECK_CLOSE(1,a.length(a_parent),1E-5);
  
  // Position changes
  a.position(point_type(2,1,-1));
  CHECK(neurostr::geometry::equal(a.position(),point_type(2,1,-1)));
  
  // Position change invalidate length cached value
  CHECK_CLOSE(std::sqrt(2),a.length(a_parent),1E-5);
}

TEST(set_position_xyz){
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  
  CHECK_CLOSE(1,a.length(a_parent),1E-5);
  
  // Position changes
  a.position(1,2,-1);
  CHECK(neurostr::geometry::equal(a.position(),point_type(1,2,-1)));
  
  // Position change invalidate length cached value
  CHECK_CLOSE(std::sqrt(2),a.length(a_parent),1E-5);
}

// Length
TEST(length_extern){
  
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  CHECK_CLOSE(1,a.length(a_parent),1E-5);
  // Cahched
  a.invalidate_length();
  CHECK_CLOSE(0,a.length(a),1E-5);
}

TEST(length_parent){
  
  neurostr::Node a(1, 1, 1, 1, 1);
  neurostr::Node a_parent(0, 1, 1, 0, 1);
  
  a.parent(&a_parent);
  CHECK_CLOSE(1,a.length(),1E-5);
  // This should invalidate length
  a.parent(&a);
  CHECK_CLOSE(0,a.length(),1E-5);
}


}
