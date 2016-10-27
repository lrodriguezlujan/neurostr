#include <unittest++/UnitTest++.h>
#include <boost/iterator/filter_iterator.hpp>
#include "core/neurite_type.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"



SUITE(neurite_tests){
  
  using namespace neurostr;

// Test neurite structure
struct SampleNeurite {
  SampleNeurite() : neurite_example(1,NeuriteType::kDendrite) {
    // Remember - root node is not part of the neurite
    neurite_example.insert_node(neurite_example.begin_node(),Node(1));
    neurite_example.insert_node(1,Node(2));
    neurite_example.insert_node(2,Node(3));
    neurite_example.insert_node(3,Node(4));
    neurite_example.insert_node(4,Node(5));
    neurite_example.insert_node(3,Node(6));
    neurite_example.insert_node(5,Node(7));
    neurite_example.insert_node(5,Node(8));
    
    neurite_example.correct();
  }
  
  ~SampleNeurite(){};
  
  Neurite neurite_example;
};
  
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


TEST(typed_constructor) {
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_EQUAL(n.size(),0);
  CHECK_EQUAL(n.id(),1);
  CHECK_EQUAL(n.type(), NeuriteType::kDendrite);
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}


TEST(type){
  Neurite n1(1, NeuriteType::kDendrite);
  CHECK_EQUAL(n1.type(), NeuriteType::kDendrite);
  
  Neurite n2(1);
  CHECK_EQUAL(n2.type(), NeuriteType::kUndefined);
}

TEST(id){
  Neurite n1(1, NeuriteType::kDendrite);
  CHECK_EQUAL(n1.id(),1);
}

TEST(neuron_exists){
  Neurite n(1, NeuriteType::kDendrite);
  Neuron neuron("TEST");
  
  n.neuron(&neuron);
  CHECK_EQUAL(neuron.id(),n.neuron().id());
}

TEST(neuron_fails){
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_THROW(n.neuron(),std::logic_error);
}

TEST(has_root_no_branch){
  Neurite n(1, NeuriteType::kDendrite);
  CHECK(!n.has_root());
}

TEST(has_root_true){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK(n.has_root());
}

TEST(has_root_false){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root();
  CHECK(!n.has_root());
}

TEST(overwrite_empty_root){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK(n.has_root());
  n.set_root();
  CHECK(!n.has_root());
}

TEST(overwrite_nonempty_root){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK(n.has_root());
  n.set_root(Node(2));
  CHECK(n.has_root());
}

TEST(order_empty){
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_EQUAL(-1,n.max_centrifugal_order());
}

TEST(order_single){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK_EQUAL(0,n.max_centrifugal_order());
}

TEST(order_reg){
  SampleNeurite test_data;
  CHECK_EQUAL(2,test_data.neurite_example.max_centrifugal_order());
}

TEST(size_empty){
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_EQUAL(0,n.size());
}

TEST(size_reg){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK_EQUAL(1,n.size());
  n.append_branch(n.begin_branch(),Branch());
  CHECK_EQUAL(2,n.size());
}

TEST(size_testdata){
  SampleNeurite test_data;
  CHECK_EQUAL(5,test_data.neurite_example.size());
}

TEST(node_count_empty){
  Neurite n(1, NeuriteType::kDendrite);
  CHECK_EQUAL(0,n.node_count());
}

TEST(node_count_only_root){
  Neurite n(1, NeuriteType::kDendrite);
  n.set_root(Node(1));
  CHECK_EQUAL(0,n.node_count());
}

TEST(node_count){
  SampleNeurite test_data;
  CHECK_EQUAL(8,test_data.neurite_example.node_count());
}

TEST(type_set) {
  Neurite n;
  CHECK_EQUAL(n.type(), NeuriteType::kUndefined);
  n.type(NeuriteType::kApical);
  CHECK_EQUAL(n.type(), NeuriteType::kApical);
}

TEST(id_set) {
  Neurite n;
  CHECK_EQUAL(n.id(),-1);
  n.id(22);
  CHECK_EQUAL(n.id(),22);
}

TEST(branch_iterator_dfs){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_EQUAL(5,std::distance(n.begin_branch(), n.end_branch()));
  CHECK_EQUAL("1",n.begin_branch()->idString());
  CHECK_EQUAL("1-1",std::next(n.begin_branch(),1)->idString());
  CHECK_EQUAL("1-1-1",std::next(n.begin_branch(),2)->idString());
  CHECK_EQUAL("1-1-2",std::next(n.begin_branch(),3)->idString());
  CHECK_EQUAL("1-2",std::next(n.begin_branch(),4)->idString());
}

TEST(branch_iterator_dfs_subtree){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_EQUAL(3,std::distance(n.begin_branch_subtree(std::next(n.begin_branch(),1)), 
                              n.end_branch_subtree(std::next(n.begin_branch(),1))));
  
  auto it = n.begin_branch_subtree(std::next(n.begin_branch(),1));
  CHECK_EQUAL("1-1",it->idString());
  CHECK_EQUAL("1-1-1",std::next(it,1)->idString());
  CHECK_EQUAL("1-1-2",std::next(it,2)->idString());
}

// Need to fix Tree.hh
/*
TEST(branch_order_iterator){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_EQUAL(2, std::distance(n.begin_fixed_order(2),n.end_fixed_order(2)));
  auto it = n.begin_fixed_order(2);
  CHECK_EQUAL("1-1-1",std::next(it,0)->idString());
  CHECK_EQUAL("1-1-2",std::next(it,2)->idString());
}
*/

TEST(leaf_iterator){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_EQUAL(3, std::distance(n.begin_leaf(),n.end_leaf()));
}

TEST(stem_iterator){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_EQUAL(3, std::distance(n.begin_stem(std::next(n.begin_branch(),2)),n.end_stem(std::next(n.begin_branch(),2))));
}

TEST(find_branch_exists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  auto f = n.find( *std::next(n.begin_branch(),2) );
  CHECK(f == std::next(n.begin_branch(),2) );
}

TEST(find_branch_noexists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  auto f = n.find( Branch() );
  CHECK(f == n.end_branch() );
}

TEST(find_node_exists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  auto f = n.find(3);
  CHECK(f->id() == 3);
}

TEST(find_node_noexists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  auto f = n.find(13);
  CHECK(f == n.end_node());
}

TEST(branch_sibling_exists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
}

TEST(branch_sibling_noexists){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
}

TEST(insert_node_empty){
 // Insert in empty tree 
 Neurite n_a(1);
 n_a.insert_node(n_a.begin_node(), Node(1) );
 CHECK_EQUAL(1, n_a.size());
 CHECK_EQUAL(1, n_a.node_count());
 CHECK_EQUAL(Node(1), *n_a.begin_node());  
}

TEST(insert_empty_branch){
  // Insert in an empty branch
 Neurite n_b(2);
 n_b.insert_node(n_b.begin_node(), Node(1) );
 CHECK_EQUAL(1, n_b.size());
 CHECK_EQUAL(1, n_b.node_count());
 CHECK_EQUAL(Node(1), *n_b.begin_node());
}

TEST(insert_node_pos_end){
  // Insert in the last position of a terminal branch
  Neurite n_b(2);
 n_b.insert_node(n_b.begin_node(), Node(1) );
 n_b.insert_node(n_b.begin_node(), Node(2) );
 CHECK_EQUAL(1, n_b.size());
 CHECK_EQUAL(2, n_b.node_count());
 CHECK_EQUAL(Node(2), *(--n_b.end_node()) );
  
}

TEST(insert_node_pos_middle){
 // Force split
  Neurite n_b(2);
 n_b.insert_node(n_b.begin_node(), Node(1) );
 n_b.insert_node(n_b.begin_node(), Node(2) );
 n_b.insert_node(n_b.begin_node(), Node(3) );
 CHECK_EQUAL(3, n_b.size());
 CHECK_EQUAL(3, n_b.node_count()); 
}

TEST(insert_node_parent_sp){
  Neurite n_a(1);
 
 // Insert with parent -1
 n_a.insert_node(-1, Node(1));
 CHECK_EQUAL(1, n_a.size());
 CHECK_EQUAL(1, n_a.node_count());
 CHECK_EQUAL(Node(1), *n_a.begin_node());  
}

TEST(insert_node_parent_notfound){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  CHECK_THROW(n.insert_node(13,Node(14)),std::runtime_error);
  
}

TEST(insert_node_parent_last){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  n.insert_node(8,Node(9));
  auto f = n.find(9);
  CHECK(f != n.end_node());
  CHECK(f->id() == 9);
  --f;
  CHECK(f->id() == 8);
}

TEST(insert_node_parent_split){
  SampleNeurite test_data;
  Neurite& n = test_data.neurite_example;
  
  n.insert_node(4,Node(9));
  auto f = n.find(9);
  CHECK(f != n.end_node());
  CHECK(f->id() == 9);
}


// Split correct in different ops
TEST(correct){
  //TODO - 
}

// Scale, normalize branches etc etc just apply a function to each branch

TEST(child_order){
  //TODO
}


TEST(equality_operator) {
  Neurite n_a(1), n_b(2), n_c(1);
  CHECK(n_a != n_b);
  CHECK(n_a == n_c);
}

TEST(properties){
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

TEST(append_branch){
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

TEST(remove_empty_branch_empty){
  Neurite n(1);
  CHECK(!n.remove_empty_branches());
}

TEST(remove_empty_branch){
  Neurite n(1);
  n.set_root();
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),1),Node(2)); // This branch (1-1)  stays
  n.append_branch(n.begin_branch(),Branch()); //  This branch (1-2 should be deleted)
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(n.remove_empty_branches());
  CHECK_EQUAL(2,n.size());
  auto f = n.find(2); // Check that branch 2 is still there
  CHECK(f.begin() != f.end());
}

TEST(remove_empty_branch_root){
  Neurite n(1);
  n.set_root(); // Empty root, cant remove it
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),1),Node(1)); // This branch (1-1)  stays
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),2),Node(2)); // This branch (1-2)  stays
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(!n.remove_empty_branches());
  CHECK_EQUAL(3,n.size());
}

TEST(remove_empty_branch_none){
  Neurite n(1);
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),1),Node(2)); // This branch (1-1)  stays
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),2),Node(3)); // This branch (1-2)  stays
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(!n.remove_empty_branches());
  CHECK_EQUAL(3,n.size());
}

TEST(remove_empty_branch_multiple){
   Neurite n(1);
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch()); // Empty branch
  n.append_branch(std::next(n.begin_branch(),1),Branch()); // Empty branch
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(n.remove_empty_branches());
  CHECK_EQUAL(1,n.size());
}

// Collapse single
TEST(collapse_single_branch_empty){
  Neurite n(1);
  CHECK(!n.collapse_single_branches());
}

TEST(collapse_single_branch){
  Neurite n(1);
  n.set_root();
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),1),Node(2));
  n.insert_node(std::next(n.begin_branch(),1),Node(3));
  
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(2,n.size());
  CHECK(n.collapse_single_branches());
  CHECK_EQUAL(1,n.size());
  
  auto f = n.find(2);
  CHECK(f.begin() != f.end());
  
  f = n.find(3);
  CHECK(f.begin() != f.end());
}


TEST(collapse_single_branch_none){
  Neurite n(1);
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),1),Node(2)); // This branch (1-1)  stays
  n.append_branch(n.begin_branch(),Branch());
  n.insert_node(std::next(n.begin_branch(),2),Node(3)); // This branch (1-2)  stays
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(!n.collapse_single_branches());
  CHECK_EQUAL(3,n.size());
}

TEST(collapse_single_branch_multiple){
   Neurite n(1);
  n.insert_node(n.begin_branch(),Node(1)); // Root with one node
  n.append_branch(n.begin_branch(),Branch()); 
  n.insert_node(std::next(n.begin_branch(),1), Node(2));
  n.append_branch(std::next(n.begin_branch(),1),Branch());
  n.insert_node(std::next(n.begin_branch(),2), Node(3));
  
  n.reassign_branch_ids();
  
  CHECK_EQUAL(3,n.size());
  CHECK(n.collapse_single_branches());
  CHECK_EQUAL(1,n.size());
  
  auto f = n.find(2);
  CHECK(f.begin() != f.end());
  
  f = n.find(3);
  CHECK(f.begin() != f.end());
}

// TODO correct
} // End neurite suite
