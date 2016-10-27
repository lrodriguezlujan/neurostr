#include <unittest++/UnitTest++.h>
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

SUITE(neuron_tests){

using namespace neurostr;

// Test neurite structure
struct SampleNeuron {
  SampleNeuron() : neuron_example("test") {
    
    // Add simple soma
    neuron_example.add_soma(Node(1,0,0,0,0));
    
    // Add a simple tree node axon
    Neurite* axon = new Neurite(1,NeuriteType::kAxon);
    axon->set_root(Node(1,0,0,0,0));
    axon->insert_node(axon->begin_branch(),Node(2,0,0,-1,0));
    axon->insert_node(axon->begin_branch(),Node(3,0,0,-2,0));
    axon->insert_node(axon->begin_branch(),Node(4,0,0,-3,0));
    neuron_example.add_neurite(axon);
    
    // Another simple apical
    Neurite* apical = new Neurite(2,NeuriteType::kApical);
    apical->set_root(Node(1,0,0,0,0));
    apical->insert_node(apical->begin_branch(),Node(5,0,0,1,0));
    apical->insert_node(apical->begin_branch(),Node(6,0,0,2,0));
    apical->insert_node(apical->begin_branch(),Node(7,0,0,3,0));
    apical->insert_node(apical->begin_branch(),Node(8,0,0,4,0));
    neuron_example.add_neurite(apical);
    
    // Two dendrites
    Neurite* d1 = new Neurite(3,NeuriteType::kDendrite);
    d1->set_root(Node(1,0,0,0,0));
    d1->insert_node(d1->begin_branch(),Node(9,0,1,0,0));
    d1->insert_node(d1->begin_branch(),Node(10,0,2,0,0));
    neuron_example.add_neurite(d1);
    
    Neurite* d2 = new Neurite(4,NeuriteType::kDendrite);
    d2->set_root(Node(1,0,0,0,0));
    d2->insert_node(d2->begin_branch(),Node(11,1,0,0,0));
    d2->insert_node(d2->begin_branch(),Node(12,1,0,0,0)); // NUll segment
    neuron_example.add_neurite(d2);
  }
  
  ~SampleNeuron(){};
  
  Neuron neuron_example;
};

// Neuron
TEST(empty_constructor) {
  Neuron n;
  CHECK_EQUAL(0,n.size());
  CHECK_EQUAL(std::string(),n.id());
  CHECK_EQUAL(0,n.node_count());
  CHECK_EQUAL(false, n.has_soma());
  
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}

TEST(id_constructor) {
  Neuron n(std::string("TEST"));
  CHECK_EQUAL(0,n.size());
  CHECK_EQUAL(std::string("TEST"),n.id());
  CHECK_EQUAL(0,n.node_count());
  CHECK_EQUAL(false, n.has_soma());
  
  auto bp = n.begin_properties();
  auto ep = n.end_properties();
  CHECK_EQUAL(std::distance(bp,ep), 0);
}


TEST(soma_constructor) {
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

TEST(size_reg){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(4,n.size());
}

TEST(size_empty){
  Neuron n;
  CHECK_EQUAL(0,n.size());
}

TEST(node_count){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  CHECK_EQUAL(11, n.node_count()); // soma dont count
  n.erase_axon();
  CHECK_EQUAL(8, n.node_count()); // updates
}

TEST(node_count_empty){
 Neuron n;
 CHECK_EQUAL(0, n.node_count());
}


TEST(add_neurite_single) {
  
 // Insert in empty tree 
 Neuron n;
 CHECK_EQUAL(0, n.size());
 
 Neurite* neurite_a = new Neurite(1);
 
 n.add_neurite(neurite_a);
 CHECK_EQUAL(1, n.size());
 CHECK_EQUAL(1, n.begin_neurite()->id());
}

TEST(add_neurite_set){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
 
  CHECK_EQUAL(4, n.size()); 
  Neurite* neurite_a = new Neurite(5,NeuriteType::kUndefined);
  n.add_neurite(neurite_a);
  CHECK_EQUAL(5, n.size()); 
}

TEST(add_soma_vector){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,std::distance(n.begin_soma(),n.end_soma()));
  std::vector<Node> new_soma_ps = {Node(13),Node(14)};
  n.add_soma(new_soma_ps); // This should b done with iterators!
  CHECK_EQUAL(3,std::distance(n.begin_soma(),n.end_soma()));
}

TEST(add_soma_vector_empty){
  Neuron n;
  
  CHECK_EQUAL(0,std::distance(n.begin_soma(),n.end_soma()));
  std::vector<Node> new_soma_ps = {Node(13),Node(14)};
  n.add_soma(new_soma_ps); 
  CHECK_EQUAL(2,std::distance(n.begin_soma(),n.end_soma()));
}

TEST(add_soma_node){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,std::distance(n.begin_soma(),n.end_soma()));
  n.add_soma(Node(13)); 
  CHECK_EQUAL(2,std::distance(n.begin_soma(),n.end_soma()));
}

TEST(neurite_iterator){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_neurite() != n.end_neurite());
  CHECK_EQUAL(4,std::distance(n.begin_neurite(),n.end_neurite()));
}

TEST(neurite_iterator_empty){
  Neuron n;
  CHECK(n.begin_neurite() == n.end_neurite());
}

TEST(soma_iterator){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_soma() != n.end_soma());
  CHECK_EQUAL(1,std::distance(n.begin_soma(),n.end_soma()));
}

TEST(soma_iterator_empty){
  Neuron n;
  CHECK(n.begin_soma() == n.end_soma());
}

TEST(axon_iterator){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_axon() != n.end_axon());
  CHECK_EQUAL(1,std::distance(n.begin_axon(),n.end_axon()));
}

TEST(axon_iterator_empty){
  Neuron n;
  CHECK(n.begin_axon() == n.end_axon());
}

TEST(axon_iterator_noaxon){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_axon() != n.end_axon());
  CHECK_EQUAL(1,std::distance(n.begin_axon(),n.end_axon()));
  n.erase_axon();
  CHECK(n.begin_axon() == n.end_axon());
}

TEST(apical_iterator){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_apical() != n.end_apical());
  CHECK_EQUAL(1,std::distance(n.begin_apical(),n.end_apical()));
}

TEST(apical_iterator_empty){
  Neuron n;
  CHECK(n.begin_apical() == n.end_apical());
}

TEST(apical_iterator_noapical){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_apical() != n.end_apical());
  CHECK_EQUAL(1,std::distance(n.begin_apical(),n.end_apical()));
  n.erase_apical();
  CHECK(n.begin_apical() == n.end_apical());
}

TEST(dendrite_iterator){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_dendrite() != n.end_dendrite());
  CHECK_EQUAL(2,std::distance(n.begin_dendrite(),n.end_dendrite()));
}

TEST(dendrite_iterator_empty){
  Neuron n;
  CHECK(n.begin_dendrite() == n.end_dendrite());
}

TEST(dendrite_iterator_nodend){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.begin_dendrite() != n.end_dendrite());
  CHECK_EQUAL(2,std::distance(n.begin_dendrite(),n.end_dendrite()));
  n.erase_dendrites();
  CHECK(n.begin_dendrite() == n.end_dendrite());
}

TEST(axon_count){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,n.axon_count());
  
}

TEST(axon_count_noaxon){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_axon();
  CHECK_EQUAL(0,n.axon_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.axon_count());
}

TEST(apical_count){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,n.apical_count());
}

TEST(apical_count_noapical){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_apical();
  CHECK_EQUAL(0,n.apical_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.apical_count());
}

TEST(dend_count){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(2,n.dendrite_count());
}

TEST(dend_count_nodend){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_dendrites();
  CHECK_EQUAL(0,n.dendrite_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.dendrite_count());
}

TEST(has_soma){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK(n.has_soma());
}

TEST(has_soma_nosoma){
  Neuron n;
  CHECK(!n.has_soma());
  
}

TEST(find_node_exists_axon){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find(Node(3));
  CHECK(f.begin() != f.end());
  CHECK_EQUAL(3,f->id());
  
}

TEST(find_node_exists_apical){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  auto f = n.find(Node(7));
  CHECK(f.begin() != f.end());
  CHECK_EQUAL(7,f->id());
}

TEST(find_node_exists_dendrite){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find(Node(9));
  CHECK(f.begin() != f.end());
  CHECK_EQUAL(9,f->id());
}

TEST(find_node_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find(Node(14));
  CHECK(f.begin() == f.end());
}

TEST(find_node_id){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find(9);
  CHECK(f.begin() != f.end());
  CHECK_EQUAL(9,f->id());
}

TEST(find_node_id_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  // Just dont exists
  auto f = n.find(14);
  CHECK(f.begin() == f.end());
  
  // Dont find soma nodes
  auto fs = n.find(1);
  CHECK(fs.begin() == fs.end());
}

TEST(find_node_soma_exists){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find_soma(Node(1));
  CHECK(f != n.end_soma());
  CHECK_EQUAL(1,f->id());
}

TEST(find_node_soma_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  // Dont find neuro nodes
  auto f = n.find_soma(Node(2));
  CHECK(f == n.end_soma());
  
  f = n.find_soma(Node(20));
  CHECK(f == n.end_soma());
}

TEST(find_node_soma_id){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find_soma(1);
  CHECK(f != n.end_soma());
  CHECK_EQUAL(1,f->id());
}

TEST(find_node_soma_id_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto f = n.find_soma(2);
  CHECK(f == n.end_soma());
  
  f = n.find_soma(20);
  CHECK(f == n.end_soma());
}

// Correct - TO DO (See neurite )

TEST(remove_null_segments){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(11, n.node_count());
  // Should remove node 12
  auto f = n.find(12);
  CHECK(f.begin() != f.end());
  n.remove_null_segments();
  
  CHECK_EQUAL(10, n.node_count());
  f = n.find(12);
  CHECK(f.begin() == f.end());
}

TEST(remove_null_segments_no){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.remove_null_segments();
  CHECK_EQUAL(10, n.node_count());
  n.remove_null_segments();
  CHECK_EQUAL(10, n.node_count());
}

TEST(soma_barycenter_single){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_CLOSE(0,geometry::distance(n.soma_barycenter(),point_type(0,0,0)),1E-6);
}

TEST(soma_barycenter_empty){
  Neuron n;
  CHECK_CLOSE(0,geometry::distance(n.soma_barycenter(),point_type(0,0,0)),1E-6);
}

TEST(soma_barycenter){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.add_soma(Node(13,0.5,0.5,0.5,0));
  CHECK_CLOSE(0,geometry::distance(n.soma_barycenter(),point_type(0.25,0.25,0.25)),1E-6);
}

// Scale traslate rotates...etc already tested

TEST(center_empty){
  Neuron n;
  
  n.center();// Dont do anything
}

TEST(center){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.add_soma(Node(13,0.5,0.5,0.5,0));
  n.center();
  CHECK_CLOSE(0,geometry::distance(n.soma_barycenter(),point_type(0,0,0)),1E-6);
}

TEST(erase){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  // Erase first n
  CHECK_EQUAL(4,n.size());
  n.erase(n.begin_neurite());
  CHECK_EQUAL(3,n.size());
}

TEST(erase_end){
  
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(4,n.size());
  n.erase(n.end_neurite());
  CHECK_EQUAL(4,n.size());
  
  Neuron n2;
  
  CHECK_EQUAL(0,n2.size());
  n2.erase(n2.end_neurite());
  n2.erase(n2.begin_neurite());
}

TEST(erase_axon){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,n.axon_count());
  n.erase_axon();
  CHECK_EQUAL(0,n.axon_count());
}

TEST(erase_axon_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_axon();
  CHECK_EQUAL(0,n.axon_count());
  n.erase_axon();
  CHECK_EQUAL(0,n.axon_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.axon_count());
  n2.erase_axon();
  CHECK_EQUAL(0,n2.axon_count());
}

TEST(erase_apical){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(1,n.apical_count());
  n.erase_apical();
  CHECK_EQUAL(0,n.apical_count());
}

TEST(erase_apical_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_apical();
  CHECK_EQUAL(0,n.apical_count());
  n.erase_apical();
  CHECK_EQUAL(0,n.apical_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.apical_count());
  n2.erase_apical();
  CHECK_EQUAL(0,n2.apical_count());
}

TEST(erase_dendrites){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  CHECK_EQUAL(2,n.dendrite_count());
  n.erase_dendrites();
  CHECK_EQUAL(0,n.dendrite_count());
}

TEST(erase_dendrites_noexist){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  n.erase_dendrites();
  CHECK_EQUAL(0,n.dendrite_count());
  n.erase_dendrites();
  CHECK_EQUAL(0,n.dendrite_count());
  
  Neuron n2;
  CHECK_EQUAL(0,n2.dendrite_count());
  n2.erase_dendrites();
  CHECK_EQUAL(0,n2.dendrite_count());
}

TEST(apical_up){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  // TODO
}

TEST(apical_up_noapical){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto prev_pos = n.begin_axon()->begin_node()->position();
  n.erase_apical();
  n.set_apical_up();
  CHECK(geometry::equal(n.begin_axon()->begin_node()->position(),prev_pos));
}

TEST(basal_roots_xz){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  //TODO
}

TEST(basal_roots_xz_single){
  //TODO
}

TEST(basal_roots_xz_empty){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto prev_pos = n.begin_axon()->begin_node()->position();
  n.erase_dendrites();
  n.set_basal_roots_xz();
  CHECK(geometry::equal(n.begin_axon()->begin_node()->position(),prev_pos));
}

TEST(bbox){
  SampleNeuron test_data;
  Neuron& n = test_data.neuron_example;
  
  auto box = n.boundingBox();
  CHECK_CLOSE(0,geometry::distance(box.max_corner(), point_type(1,2,4)),1E-6);
  CHECK_CLOSE(0,geometry::distance(box.min_corner(), point_type(0,0,-3)),1E-6);
  
}

TEST(bbox_empty){
  Neuron n;
  
  auto box = n.boundingBox();
  CHECK_CLOSE(0,geometry::distance(box.max_corner(), point_type(0,0,0)),1E-6);
  CHECK_CLOSE(0,geometry::distance(box.min_corner(), point_type(0,0,0)),1E-6);
  
}

// Reconstruction tests in separate file

} // End neuron tests
