#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "io/JSONParser.h"

SUITE(json_parser_tests){
  
  using namespace neurostr::io;
  
  const std::string test_files_folder = std::string("../data/test_data/json/"); 
  
  struct json_parser_data {
    json_parser_data(const std::string& s) 
      : is( test_files_folder + s)
      , parser(is)
      , rec(nullptr) {
        if(!is) CHECK(false);
        else {
          rec=parser.read("test");
          
        }
    }
      
    ~json_parser_data(){};
    
    std::ifstream is;
    JSONParser  parser;
    std::unique_ptr<neurostr::Reconstruction> rec;
  };
  
  // Basic checks
  void basic_jsonparser_checks(const JSONParser& p, const neurostr::Neuron& n, 
                          bool crit, 
                          int err_count, 
                          int warn_count,
                          bool has_soma,
                          int neurite_count, 
                          int node_count){
    // Critical flag
    CHECK_EQUAL(crit,p.critical());
    
    // Error count
    CHECK_EQUAL(err_count,p.error());
    
    // warning count
    CHECK_EQUAL(warn_count,p.warn());
    
    // HAS SOMA
    CHECK_EQUAL(n.has_soma(),has_soma);
    
    // Number of neurites
    CHECK_EQUAL(n.size(),neurite_count);
    
    // Number of nodes
    CHECK_EQUAL(n.node_count(),node_count);

  }
  
  // OK CASES
  TEST(empty){
    // Rapid json treats empty file as errors
    json_parser_data test_data("empty.json");
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(1,test_data.parser.error());
    CHECK_EQUAL(true,test_data.parser.critical());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(empty_reconstruction){
    json_parser_data test_data("empty_reconstruction.json");
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(single_contour){
    json_parser_data test_data("single_contour.json");
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
    
    CHECK_EQUAL(1, r.n_contours());
    CHECK_EQUAL("test",r.contour_begin()->name());
    CHECK_EQUAL(4,r.contour_begin()->size());
    CHECK_EQUAL(true,r.contour_begin()->is_closed());
    
  }
  
  TEST(single_property){
    json_parser_data test_data("single_property.json"); 
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
    
    CHECK_EQUAL(3, r.properties.size());
    CHECK(r.properties.exists("key1"));
    CHECK(r.properties.exists("key2"));
    CHECK(r.properties.exists("key3"));
    CHECK_EQUAL("value",r.properties.get<std::string>("key1"));
    CHECK_EQUAL(0.0,r.properties.get<float>("key2"));
    CHECK_EQUAL(true,r.properties.get<bool>("key3"));
  }
  
  TEST(empty_neuron){
    json_parser_data test_data("empty_neuron.json"); 
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,false,0,0);
    }
  }
  
  TEST(empty_neuron_soma){
    json_parser_data test_data("empty_neuron_soma.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,0,0);
    }
  }
  
  TEST(simple_neuron_dendrite){
    json_parser_data test_data("simple_neuron_dendrite.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.dendrite_count());
    }
  }
  
  TEST(simple_neuron_axon){
    json_parser_data test_data("simple_neuron_axon.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.axon_count());
    }
  }
  
  TEST(simple_neuron_apical){
    json_parser_data test_data("simple_neuron_apical.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.apical_count());
    }
  }
  
  TEST(simple_tree){
    json_parser_data test_data("simple_tree.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,1,7);
      CHECK_EQUAL(1,n.dendrite_count());
      
      // Check structure
      CHECK_EQUAL(5,n.begin_dendrite()->size());
      CHECK_EQUAL(2,n.begin_dendrite()->max_centrifugal_order());
    }
  }
  
  TEST(real){
    json_parser_data test_data("real.json");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      JSONParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_jsonparser_checks(p,n,false,0,0,true,8,2026);
    }
  }
}

