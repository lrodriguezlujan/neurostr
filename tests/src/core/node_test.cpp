#include <unittest++/UnitTest++.h>
#include "core/node.h"

TEST(node_empty_constructor) {
  neurostr::Node n;
  CHECK_EQUAL(n.id(), -1);
}

TEST(node_partial_constructor) {
  neurostr::Node n(1);
  CHECK_EQUAL(n.id(), 1);
  CHECK_EQUAL(n.radius(), 0);
  CHECK_EQUAL(neurostr::geometry::get<0>(n.position()), 0);
  CHECK_EQUAL(neurostr::geometry::get<1>(n.position()), 0);
  CHECK_EQUAL(neurostr::geometry::get<2>(n.position()), 0);
}

TEST(node_full_constructor) {
  neurostr::Node n(2, 1, 2, 3, 4);
  CHECK_EQUAL(n.id(), 2);
  CHECK_EQUAL(n.radius(), 4);
  CHECK_EQUAL(neurostr::geometry::get<0>(n.position()), 1);
  CHECK_EQUAL(neurostr::geometry::get<1>(n.position()), 2);
  CHECK_EQUAL(neurostr::geometry::get<2>(n.position()), 3);
}

TEST(node_equality_operator) {
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

TEST(node_distance_empty) {
  neurostr::Node a, b, c(1, 1, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),-1);
  CHECK_EQUAL(a.distance(b.position()),-1);
  CHECK_EQUAL(a.distance(c),-1);
  CHECK_EQUAL(c.distance(a),-1);
}

TEST(node_distance_self) {
  neurostr::Node a(1, 1, 0, 0, 1);
  CHECK_EQUAL(a.distance(a),0);
  CHECK_EQUAL(a.distance(a.position()),0);
}

TEST(node_distance_nonzero) {
  neurostr::Node a(1, 1, 0, 0, 1), b(1, 0, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),1);
  CHECK_EQUAL(a.distance(b.position()),1);
}

TEST(node_distance_symmetric) {
  neurostr::Node a(1, 1, 0, 0, 1), b(1, 0, 0, 0, 1);
  CHECK_EQUAL(a.distance(b),b.distance(a));
  CHECK_EQUAL(a.distance(b.position()),b.distance(a.position()));
}

TEST(node_vectorTo_empty) {
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

TEST(node_vectorTo_origin) {
  neurostr::Node a(1, 1, 1, 1, 1), b(1,0,0,0,1);
  neurostr::point_type p=a.vectorTo(b);
  CHECK_EQUAL(neurostr::geometry::get<0>(p), -neurostr::geometry::get<0>(a.position()));
  CHECK_EQUAL(neurostr::geometry::get<1>(p), -neurostr::geometry::get<1>(a.position()));
  CHECK_EQUAL(neurostr::geometry::get<2>(p), -neurostr::geometry::get<2>(a.position()));
}
