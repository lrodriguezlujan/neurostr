#include <unittest++/UnitTest++.h>
#include "core/node.h"
#include "core/branch.h"

using namespace neurostr;

TEST(branch_empty_constructor) {
  Branch b;
  CHECK_EQUAL(b.size(),0);
  CHECK_EQUAL(b.has_root(), false);
  CHECK_EQUAL(b.id().size(), 0);
  CHECK_EQUAL(b.order(), -1);
}


TEST(branch_partial_constructor) {
  Node r(1);
  Branch::id_type id{0,0,0};
  Branch b{id,1,r};
  CHECK_EQUAL(b.size(),0);
  CHECK_EQUAL(b.has_root(), true);
  CHECK_EQUAL(b.id().size(), 3);
  CHECK_EQUAL(b.order(), 1);
  CHECK(b.root()==r);
}

TEST(branch_full_constructor) {
  Node r(1),a(2),c(3);
  std::vector<Node> nodes{a,c};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  CHECK_EQUAL(b.size(),2);
  CHECK_EQUAL(b.has_root(), true);
  CHECK_EQUAL(b.id().size(), 3);
  CHECK_EQUAL(b.order(), 1);
  CHECK(b.root()==r);
  CHECK(b.first()==a);
  CHECK(b.last()==c);
}

TEST(branch_push_back) {
  Node r(1),a(2);
  Branch::id_type id{0,0,0};
  Branch b{id,1,r};
  
  // Copy pushback
  b.push_back(a);
  CHECK(b.last()==a);
  
  // Move pushback
  b.push_back(Node(3));
  CHECK(b.last()==Node(3));
}

TEST(branch_insert) {
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  // Front
  b.insert(b.begin(),d);
  CHECK(b.first()==d);
  
  // Back
  b.insert(b.end(),e);
  CHECK(b.last()==e);
  
  // Middle
  b.insert(++b.begin(),f);
  CHECK( *(++b.begin())==f);
}

TEST(branch_equality_op) {
  Node r(1),a(2),c(3),d(4),e(5);
  std::vector<Node> nodes_1{a,c};
  std::vector<Node> nodes_2{a,c,d};
  std::vector<Node> nodes_3{a,c,e};
  // Ids
  Branch::id_type id_1{0,0,1};
  Branch::id_type id_2{0,1,1};
  Branch::id_type id_3{0,1};
  Branch b_1{id_1,1,r,nodes_1};
  Branch b_2{id_3,1,r,nodes_3};
  Branch b_3{id_1,1,r,nodes_3};
  Branch b_4{id_2,1,r,nodes_3};
  Branch b_5{id_1,1,a,nodes_1};
  Branch b_6{id_3,1,r,nodes_2};
  
  // Different id size
  CHECK( b_1 != b_2);
  
  // Different node size
  CHECK( b_1 != b_3);
  
  // Id does not match
  CHECK( b_1 != b_4);
  
  // Root not match
  CHECK( b_1 != b_5);
  
  // Nodes not match
  CHECK( b_6 != b_2);
  
  // Equal
  CHECK( b_1 == b_1);
}
