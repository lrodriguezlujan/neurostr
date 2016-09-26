#include <unittest++/UnitTest++.h>
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

using namespace neurostr;

// Neuron
TEST(neuron_empty_constructor) {
  Neuron n;
  CHECK_EQUAL(0,n.size());
  CHECK_EQUAL(std::string(),n.id());
  CHECK_EQUAL(0,n.node_count());
  CHECK_EQUAL(false, n.has_soma());
  
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}

TEST(neuron_id_constructor) {
  Neuron n(std::string("TEST"));
  CHECK_EQUAL(0,n.size());
  CHECK_EQUAL(std::string("TEST"),n.id());
  CHECK_EQUAL(0,n.node_count());
  CHECK_EQUAL(false, n.has_soma());
  
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}


TEST(neuron_soma_constructor) {
  std::vector<Node> soma{Node(1),Node(2),Node(3)};
  Neuron n(std::string("TEST"),soma);
  
  CHECK_EQUAL(0,n.size());
  CHECK_EQUAL(std::string("TEST"),n.id());
  CHECK_EQUAL(0,n.node_count());
  CHECK_EQUAL(true, n.has_soma());
  
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(0, std::distance(bp,ep));
  
  auto bs = n.begin_soma();
  auto es = n.end_soma();
  CHECK_EQUAL(soma.size(), std::distance(bs,es));
}


TEST(neuron_properties){
  Neuron n;
  
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
  CHECK_EQUAL( n.properties.get<int>(std::string("KEY3")), 5);
  
}


TEST(neuron_insert_neurite) {
  
 // Insert in empty tree 
 Neuron n;
 CHECK_EQUAL(0, n.size());
 
 Neurite* neurite_a = new Neurite(1);
 
 n.add_neurite(neurite_a);
 CHECK_EQUAL(1, n.size());
 CHECK_EQUAL(1, n.begin_neurite()->id());
}

TEST(neuron_add_soma) {
 // Create base neurite
 Neuron n;
 
 CHECK_EQUAL(false, n.has_soma());
 
 // Insert
 n.add_soma(Node(1));
 CHECK_EQUAL(true, n.has_soma());
 
 auto bs = n.begin_soma();
 auto es = n.end_soma();
 CHECK_EQUAL(1, std::distance(bs,es));
}

// TODO: Lot of missing tests
