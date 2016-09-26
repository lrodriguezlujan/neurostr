#include <unittest++/UnitTest++.h>
#include <boost/iterator/filter_iterator.hpp>
#include "core/neurite_type.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"


using namespace neurostr;

TEST(neurite_empty_constructor) {
  Neurite n;
  CHECK_EQUAL(n.size(),0);
  CHECK_EQUAL(n.id(),-1);
  CHECK_EQUAL(n.type(), NeuriteType::kUndefined);
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}

TEST(neurite_id_constructor) {
  Neurite n(1);
  CHECK_EQUAL(n.size(),0);
  CHECK_EQUAL(n.id(),1);
  CHECK_EQUAL(n.type(), NeuriteType::kUndefined);
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}


TEST(neurite_typed_constructor) {
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_EQUAL(n.size(),0);
  CHECK_EQUAL(n.id(),1);
  CHECK_EQUAL(n.type(), NeuriteType::kDendrite);
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}

TEST(neurite_type_set) {
  Neurite n;
  CHECK_EQUAL(n.type(), NeuriteType::kUndefined);
  n.type(NeuriteType::kApical);
  CHECK_EQUAL(n.type(), NeuriteType::kApical);
}

TEST(neurite_id_set) {
  Neurite n;
  CHECK_EQUAL(n.id(),-1);
  n.id(22);
  CHECK_EQUAL(n.id(),22);
}

TEST(neurite_equality_operator) {
  Neurite n_a(1), n_b(2), n_c(1);
  CHECK(n_a != n_b);
  CHECK(n_a == n_c);
}

TEST(neurite_properties){
  Neurite n;
  
  // Add values
  CHECK_EQUAL(std::distance(n.begin_properties(),n.end_properties()), 0);
  n.add_property( std::string("KEY"));
  CHECK_EQUAL(n.begin_properties()->first, std::string("KEY"));
  CHECK_EQUAL(std::distance(n.begin_properties(),n.end_properties()), 1);
  n.add_property( std::string("KEY2"));
  CHECK_EQUAL(std::distance(n.begin_properties(),n.end_properties()), 2);
  n.add_property(std::string("KEY3"), 5);
  CHECK_EQUAL(std::distance(n.begin_properties(),n.end_properties()), 3);
  
  // Get values
  CHECK_EQUAL( n.properties.get<int>(std::string("KEY3")),5);
}

TEST(neurite_add_root){
  
  Neurite n_a(1);
  
  CHECK_EQUAL(0, n_a.size());
  CHECK_EQUAL(0, n_a.node_count());
  
  // Add empty root node
  n_a.set_root();
  
  // root branch
  CHECK_EQUAL(1, n_a.size());
  CHECK_EQUAL(0, n_a.node_count());
  
}

TEST(neurite_set_root){
  
  Neurite n_a(1);
  
  // Add empty root node
  n_a.set_root();
  
  // root branch
  CHECK_EQUAL(1, n_a.size());
  CHECK_EQUAL(0, n_a.node_count());
  CHECK_EQUAL(false, n_a.has_root());
  
  // Change root
  n_a.set_root(Node(1));
  CHECK_EQUAL(1, n_a.size());
  CHECK_EQUAL(0, n_a.node_count());
  CHECK_EQUAL(true, n_a.has_root());
  CHECK_EQUAL(Node(1), n_a.root());
  
  // Set root not empty
  Neurite n_b(1);
  n_b.set_root(Node(1));
  CHECK_EQUAL(1, n_b.size());
  CHECK_EQUAL(0, n_b.node_count());
  CHECK_EQUAL(true, n_b.has_root());
  CHECK_EQUAL(Node(1), n_b.root());
}

TEST(neurite_insert_node_pos) {
  
 // Insert in empty tree 
 Neurite n_a(1);
 n_a.insert_node(n_a.begin_node(), Node(1) );
 CHECK_EQUAL(1, n_a.size());
 CHECK_EQUAL(1, n_a.node_count());
 CHECK_EQUAL(Node(1), *n_a.begin_node());
 
 // Insert in an empty branch
 Neurite n_b(2);
 n_b.set_root();
 n_b.insert_node(n_b.begin_node(), Node(1) );
 CHECK_EQUAL(1, n_b.size());
 CHECK_EQUAL(1, n_b.node_count());
 CHECK_EQUAL(Node(1), *n_b.begin_node());
 
 // Insert in the last position of a terminal branch
 n_b.insert_node(n_b.begin_node(), Node(2) );
 CHECK_EQUAL(1, n_b.size());
 CHECK_EQUAL(2, n_b.node_count());
 CHECK_EQUAL(Node(2), *(--n_b.end_node()) );
 
 // Force split
 n_b.insert_node(n_b.begin_node(), Node(3) );
 CHECK_EQUAL(3, n_b.size());
 CHECK_EQUAL(3, n_b.node_count()); 
}

TEST(neurite_insert_node_id) {
 // Create base neurite
 Neurite n_a(1);
 
 // Insert with parent -1
 n_a.insert_node(-1, Node(1));
 CHECK_EQUAL(1, n_a.size());
 CHECK_EQUAL(1, n_a.node_count());
 CHECK_EQUAL(Node(1), *n_a.begin_node());
 
 // Try to insert again (should fail)
 CHECK_THROW(n_a.insert_node(-1, Node(2)),std::runtime_error);
 // Insert to a nonexisting node
 CHECK_THROW(n_a.insert_node(3, Node(2)),std::runtime_error);

 // Do it right
 n_a.insert_node(1, Node(2));
 CHECK_EQUAL(1, n_a.size());
 CHECK_EQUAL(2, n_a.node_count());
 CHECK_EQUAL(Node(2), *(--n_a.end_node()));
 
}

TEST(neurite_append_branch){
  Neurite n_a(1);
  
  CHECK_EQUAL(0, n_a.size());
  
  // Add empty root node
  n_a.set_root();
  
  CHECK_EQUAL(1, n_a.size());
  
  // Append branch
  n_a.append_branch(n_a.begin_branch(), Branch() );
  CHECK_EQUAL(2, n_a.size());
  
  n_a.append_branch(n_a.begin_branch(), Branch() );
  CHECK_EQUAL(3, n_a.size());
}



// TODO correct
