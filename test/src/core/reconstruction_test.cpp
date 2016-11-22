#include <unittest++/UnitTest++.h>
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

SUITE(reconstruction_tests){

using namespace neurostr;

// Test neurite structure
struct SampleReconstruction {
  SampleReconstruction() : reconstruction_example("test") {
    
    Neuron* neuron_example = new Neuron("test 1");
    // Add simple soma
    neuron_example->add_soma(Node(1,0,0,0,0));
    
    // Add a simple tree node axon
    Neurite* axon = new Neurite(1,NeuriteType::kAxon);
    axon->set_root(Node(1,0,0,0,0));
    axon->insert_node(axon->begin_branch(),Node(2,0,0,-1,0));
    axon->insert_node(axon->begin_branch(),Node(3,0,0,-2,0));
    axon->insert_node(axon->begin_branch(),Node(4,0,0,-3,0));
    neuron_example->add_neurite(axon);
    
    // Another simple apical
    Neurite* apical = new Neurite(2,NeuriteType::kApical);
    apical->set_root(Node(1,0,0,0,0));
    apical->insert_node(apical->begin_branch(),Node(5,0,0,1,0));
    apical->insert_node(apical->begin_branch(),Node(6,0,0,2,0));
    apical->insert_node(apical->begin_branch(),Node(7,0,0,3,0));
    apical->insert_node(apical->begin_branch(),Node(8,0,0,4,0));
    neuron_example->add_neurite(apical);
    
    // Two dendrites
    Neurite* d1 = new Neurite(3,NeuriteType::kDendrite);
    d1->set_root(Node(1,0,0,0,0));
    d1->insert_node(d1->begin_branch(),Node(9,0,1,0,0));
    d1->insert_node(d1->begin_branch(),Node(10,0,2,0,0));
    neuron_example->add_neurite(d1);
    
    Neurite* d2 = new Neurite(4,NeuriteType::kDendrite);
    d2->set_root(Node(1,0,0,0,0));
    d2->insert_node(d2->begin_branch(),Node(11,1,0,0,0));
    d2->insert_node(d2->begin_branch(),Node(12,1,0,0,0)); // NUll segment
    neuron_example->add_neurite(d2);
    
    reconstruction_example.addNeuron(neuron_example);
    reconstruction_example.addContour(Contour());
  }
  
  ~SampleReconstruction(){};
  
  Reconstruction reconstruction_example;
};

TEST(empty_constructor){
  Reconstruction r;
  CHECK_EQUAL(0,r.size());
  CHECK_EQUAL(r.id(),std::string());
}

TEST(id_constructor){
  
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  
  CHECK_EQUAL(1,r.size());
  CHECK_EQUAL(r.id(),std::string("test"));
}

TEST(add_neuron){
  
  Reconstruction r;
  
  CHECK_EQUAL(0,r.size());
  r.addNeuron(new Neuron("1"));
  CHECK_EQUAL(1,r.size());
  CHECK_EQUAL("1",r.begin()->id());
  r.addNeuron(new Neuron("2"));
  CHECK_EQUAL(2,r.size());
  CHECK_EQUAL("1",r.begin()->id());
  CHECK_EQUAL("2",std::next(r.begin(),1)->id());
  r.addNeuron(nullptr);
  CHECK_EQUAL(2,r.size());
  
}

TEST(add_contour){
  Reconstruction r;
  CHECK_EQUAL(0,r.n_contours());
  r.addContour(Contour());
  CHECK_EQUAL(1,r.n_contours());
  r.addContour(Contour());
  CHECK_EQUAL(2,r.n_contours());
}

TEST(contour_iterator_empty){
  Reconstruction r;
  CHECK(r.contour_begin() == r.contour_end());
}

TEST(contour_iterator){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  CHECK_EQUAL(1, std::distance(r.contour_begin(),r.contour_end()));
  CHECK_EQUAL(0, r.contour_begin()->size());
}

TEST(get_id){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  CHECK_EQUAL("test",r.id());
}

TEST(contour_count){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  
  CHECK_EQUAL(r.n_contours(),1);
}

TEST(neuron_count){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  
  CHECK_EQUAL(r.size(),1);
}

TEST(node_count){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  
  CHECK_EQUAL(r.begin()->node_count(),r.node_count());
}

/* 
TEST(closest_soma){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
}*/

TEST(neuron_iterator_empty){
  Reconstruction r;
  CHECK(r.begin() == r.end());
}

TEST(neuron_iterator){
  SampleReconstruction test_data;
  Reconstruction& r = test_data.reconstruction_example;
  CHECK_EQUAL(1, std::distance(r.begin(),r.end()));
  CHECK_EQUAL(std::string("test 1"), r.begin()->id());
}




}// Reconstruction tests
