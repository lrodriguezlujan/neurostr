#include <unittest++/UnitTest++.h>
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"

SUITE(branch_tests){
using namespace neurostr;

TEST(empty_constructor) {
  Branch b;
  CHECK_EQUAL(b.size(),0);
  CHECK(!b.has_root());
  CHECK_EQUAL(b.id().size(), 0);
  CHECK_EQUAL(b.order(), -1);
  CHECK(!b.valid_neurite());
}


TEST(partial_constructor) {
  Node r(1);
  Branch::id_type id{0,0,0};
  Branch b{id,1,r};
  CHECK_EQUAL(b.size(),0);
  CHECK_EQUAL(b.has_root(), true);
  CHECK_EQUAL(b.id().size(), 3);
  CHECK_EQUAL(b.order(), 1);
  CHECK(b.root()==r);
  CHECK(!b.valid_neurite());
}

TEST(full_constructor) {
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
  CHECK(!b.valid_neurite());
}

TEST(order_set){
  Branch::id_type id{0,0,0};
  Branch b{id,1};
  
  CHECK_EQUAL(b.order(),1);
  b.order(2);
  CHECK_EQUAL(b.order(),2);
}

TEST(id_set){
  Branch::id_type id{0,0,0};
  Branch::id_type id_b{0,0,1};
  Branch b{id,1};
  
  for(unsigned int i = 0 ; i<id.size() ; ++i){
    CHECK_EQUAL(b.id()[i],id[i]);
  }
  
  b.id(id_b);
  for(unsigned int i = 0 ; i<id.size() ; ++i){
    CHECK_EQUAL(b.id()[i],id_b[i]);
  }
}

TEST(id_string){
  Branch::id_type id{1,2,3};
  Branch::id_type id_b{};
  Branch b{id,1};
  
  CHECK_EQUAL(b.idString(),std::string("1-2-3"));
  
  b.id(id_b);
  CHECK_EQUAL(b.idString(),std::string());
}

TEST(set_neurite){
  Neurite n(1);
  Branch b{};
  
  CHECK(!b.valid_neurite());
  
  b.neurite(&n);
  CHECK(b.valid_neurite());
  CHECK_EQUAL(b.neurite(),n);
}

TEST(set_null_neurite){
  Neurite n(1);
  Branch b{};
  
  CHECK(!b.valid_neurite());
  
  b.neurite(&n);
  CHECK(b.valid_neurite());
  CHECK_EQUAL(b.neurite(),n);
  
  b.neurite(nullptr);
  CHECK(!b.valid_neurite());
}

TEST(root_set_cp){
  Node a(1);
  Branch b{};
  
  CHECK(!b.has_root());
  
  // copy
  b.root(a);
  CHECK(b.has_root());
  CHECK_EQUAL(b.root(),a);
}

TEST(root_set_mv){
  Branch b{};
  
  CHECK(!b.has_root());
  
  // move (Rvalue)
  b.root(Node(1));
  CHECK(b.has_root());
  CHECK_EQUAL(b.root(),Node(1));
}

// Access first
TEST(access_first){
  Node a(1),c(2);
  Branch::id_type id{0,0,1};
  Branch b{id,1};  
  
  // Try to access first -> error
  CHECK_THROW(b.first(), std::logic_error);
  
  // Add node (cp)
  b.push_back(a);
  CHECK(b.first() == a);
  
  // add another node - dont change
  b.push_back(c);
  CHECK(b.first() == a);
  
  // Remove first - change
  b.erase(b.begin());
  CHECK(b.first() == c);
  
  // Another
  b.clear();
  CHECK_THROW(b.first(), std::logic_error);
}

TEST(access_last){
  Node a(1),c(2);
  Branch::id_type id{0,0,1};
  Branch b{id,1};  
  
  // Try to access first -> error
  CHECK_THROW(b.last(), std::logic_error);
  
  // Add node (cp)
  b.push_back(a);
  CHECK(b.last() == a);
  
  // add another node -  change
  b.push_back(c);
  CHECK(b.last() == c);
  
  // Remove first - dont change
  b.erase(b.begin());
  CHECK(b.last() == c);
  
  // Another
  b.clear();
  CHECK_THROW(b.last(), std::logic_error);
}

TEST(push_back) {
  Node a(2);
  Branch::id_type id{0,0,0};
  Branch b{id,1};
  
  // Copy pushback
  b.push_back(a);
  CHECK(b.last()==a);
  
  // Move pushback
  b.push_back(Node(3));
  CHECK(b.last()==Node(3));
}

TEST(insert) {
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

TEST(equality_op) {
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

TEST(erase_single){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove first node
  b.erase(b.begin());
  CHECK(b.size() == 4);
  CHECK(b.first() == c);
  
  // Remove node in the middle
  b.erase(std::next(b.begin(),1));
  CHECK(b.size() == 3);
  CHECK(*std::next(b.begin(),1) == e);
  
  // Remove last
  b.erase(std::prev(b.end(),1));
  CHECK(b.size() == 2);
  CHECK(b.last() == e);
}

TEST(erase_single_end){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove empty
  b.erase(b.end());
  CHECK(b.size() == 5);
  CHECK(b.first() == a);
}

TEST(erase_range_begin){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove first two nodes
  b.erase(b.begin(), std::next(b.begin(),2));
  CHECK(b.size() == 3);
  CHECK(b.first() == d);
}

TEST(erase_range_end){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove first two nodes
  b.erase(std::prev(b.end(),2), b.end());
  CHECK(b.size() == 3);
  CHECK(b.last() == d);
}

TEST(erase_range_mid){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove first two nodes
  b.erase(std::next(b.begin(),1),std::prev(b.end(),1));
  CHECK(b.size() == 2);
  CHECK(b.last() == f);
  CHECK(b.first() == a);
}

TEST(erase_range_empty){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  // Remove first two nodes
  b.erase(b.begin(),b.begin());
  CHECK(b.size() == 5);
}

// Clear fn

TEST(clear){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.first() == a);
  CHECK(b.size() == 5);
  
  b.clear();
  CHECK(b.size() == 0);
  
}

TEST(clear_empty){
  Branch::id_type id{0,0,1};
  Branch b{id,1};
  
  CHECK(b.size() == 0);
  b.clear();
  CHECK(b.size() == 0);
}


// Split
TEST(split_begin){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  Branch bs = b.split(b.begin());
  
  CHECK(b.size() == 1);
  CHECK(bs.size() == 4);
  CHECK(b.last() == bs.root());
}

TEST(split_end){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  Branch bs = b.split(b.end());
  
  CHECK(b.size() == 5);
  CHECK(bs.size() == 0);
  CHECK(!bs.has_root());
}

TEST(split_mid){
  Node r(1),a(2),c(3),d(4),e(5),f(6);
  std::vector<Node> nodes{a,c,d,e,f};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  Branch bs = b.split(std::next(b.begin(),2));
  
  CHECK(b.size() == 3);
  CHECK(bs.size() == 2);
  CHECK(b.first() == a);
  CHECK(b.last() == d);
  CHECK(bs.first() == e);
  CHECK(bs.last() == f);
  CHECK(bs.root() == b.last());
}

TEST(simplifiy_empty){
  Branch::id_type id{0,0,1};
  Branch b{id,1};
  b.simplify(1);
  CHECK(b.size() == 0);
}

TEST(simplifiy_single){
  Node r(1),a(2);
  std::vector<Node> nodes{a};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  b.simplify(1);
  CHECK(b.size() == 1);
}

TEST(simplifiy_regular){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK(b.size() == 3);
  b.simplify(0.1); // Should remove A (in the line r-c
  CHECK(b.size() == 2);
  CHECK(b.first() == c);
  CHECK(b.last() == d);
}

TEST(scale_empty){
  Node r(1,0,0,0,1);
  Branch::id_type id{0,0,1};
  Branch b{id,1,r};
  
  b.scale(1E6);
  CHECK(neurostr::geometry::equal(r.position(),b.root().position()));
}

TEST(scale_unit){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  b.scale(1);
  
  CHECK(neurostr::geometry::equal(r.position(),b.root().position()));
  
  CHECK(neurostr::geometry::equal(a.position(),b.first().position()));
  CHECK(neurostr::geometry::equal(d.position(),b.last().position()));
}

TEST(scale_half){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  b.scale(0.5);
  
  CHECK(neurostr::geometry::equal(r.position(),b.root().position()));
  
  CHECK_CLOSE(0, b.first().distance(point_type(0.5,0.5,0.5)), 1E-3);
  CHECK_CLOSE(0, b.last().distance(point_type(1.5,0.5,1)), 1E-3);
}

TEST(scale_xyz_empty){
  Node r(1,0,0,0,1);
  Branch::id_type id{0,0,1};
  Branch b{id,1,r};
  
  b.scale(1E6,1E6,0);
  CHECK(neurostr::geometry::equal(r.position(),b.root().position()));
}

TEST(scale_xyz_unit){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  b.scale(1,1,1);
  
  CHECK_CLOSE(0,r.distance(b.root()), 1E-3);
  CHECK_CLOSE(0,a.distance(b.first()), 1E-3);
  CHECK_CLOSE(0,d.distance(b.last()), 1E-3);
}

TEST(scale_xyz){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  b.scale(2,1,0);
  
  CHECK_CLOSE(0,r.distance(b.root()), 1E-3);
  CHECK_CLOSE(2,b.first().x(), 1E-3);
  CHECK_CLOSE(1,b.first().y(), 1E-3);
  CHECK_CLOSE(0,b.first().z(), 1E-3);
  
  CHECK_CLOSE(6,b.last().x(), 1E-3);
  CHECK_CLOSE(1,b.last().y(), 1E-3);
  CHECK_CLOSE(0,b.last().z(), 1E-3);
}

TEST(traslate_empty){
  Branch::id_type id{0,0,1};
  Branch b{id,1};
  
  b.traslate(point_type(1,1,1));
}

TEST(traslate_root){
  Node r(1,0,0,0,1);
  Branch::id_type id{0,0,1};
  Branch b{id,1,r};
  
  b.traslate(point_type(1,1,1));
  CHECK_CLOSE(0,b.root().distance(point_type(1,1,1)),1E-3);
}

TEST(traslate){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,2,2,2,1),d(4,3,1,2,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  b.traslate(point_type(1,1,1));
  
  CHECK_CLOSE(sqrt(3),r.distance(b.root()), 1E-3);
  CHECK_CLOSE(sqrt(3),a.distance(b.first()), 1E-3);
  CHECK_CLOSE(sqrt(3),d.distance(b.last()), 1E-3);
}

TEST(null_segments_empty){
  Branch::id_type id{0,0,1};
  Branch b{id,1};
  
  CHECK_EQUAL(b.size(),0);
  b.remove_null_segments();
  CHECK_EQUAL(b.size(),0);
}

TEST(null_segments_single){
  Node r(1,0,0,0,1),a(2,0,0,0,0);
  std::vector<Node> nodes{a};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK_EQUAL(b.size(),1);
  b.remove_null_segments(); // Should remove a
  CHECK_EQUAL(b.size(),0);
}

TEST(null_segments_single_no){
  Node r(1,0,0,0,1),a(2,1,0,0,0);
  std::vector<Node> nodes{a};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK_EQUAL(b.size(),1);
  b.remove_null_segments();
  CHECK_EQUAL(b.size(),1);
}

TEST(null_segments_set){
  Node r(1,0,0,0,1),a(2,1,1,1,1),c(3,1,1,1,1),d(4,1,1,1,1);
  std::vector<Node> nodes{a,c,d};
  Branch::id_type id{0,0,1};
  Branch b{id,1,r,nodes};
  
  CHECK_EQUAL(b.size(),3);
  b.remove_null_segments(); // Remove everything but a
  CHECK_EQUAL(b.size(),1);
  CHECK_EQUAL(b.first(),a);
}

//TODO: Discrete frechet - need to test the geometry part first



} // Branch tests
