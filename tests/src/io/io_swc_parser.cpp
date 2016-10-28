#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "io/SWCParser.h"

SUITE(swc_parser_tests){
  
  using namespace neurostr::io;
  
  const std::string test_files_folder = std::string("../data/test_data/swc/");
  
  struct swc_parser_data {
    swc_parser_data(const std::string& s) 
      : is( test_files_folder + s)
      , parser(is)
      , rec(nullptr) {
        if(!is) CHECK(false);
        else {
          rec=parser.read("test");
          
        }
    }
      
    ~swc_parser_data(){};
    
    std::ifstream is;
    SWCParser  parser;
    std::unique_ptr<neurostr::Reconstruction> rec;
  };
  
  // Basic checks
  void basic_swcparser_checks(const SWCParser& p, const neurostr::Neuron& n, 
                          bool crit, 
                          int err_count, 
                          bool has_soma,
                          int neurite_count, 
                          int node_count){
    // Critical flag
    CHECK_EQUAL(crit,p.critical());
    
    // Error count
    CHECK_EQUAL(err_count,p.error());
    
    // HAS SOMA
    CHECK_EQUAL(n.has_soma(),has_soma);
    
    // Number of neurites
    CHECK_EQUAL(n.size(),neurite_count);
    
    // Number of nodes
    CHECK_EQUAL(n.node_count(),node_count);

  }
  
  // OK CASES
  TEST(empty){
    swc_parser_data test_data("empty.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit - empty
      basic_swcparser_checks(p,n,false,0,false,0,0);
    }
    
  }
  
  TEST(header_only){
    swc_parser_data test_data("header_only.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit - empty
      basic_swcparser_checks(p,n,false,0,false,0,0);
    }
  }
  
  TEST(simple_dendrite){
    swc_parser_data test_data("simple_dendrite.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit 
      basic_swcparser_checks(p,n,false,0,true,1,3);
      CHECK_EQUAL(1,n.dendrite_count());
    }
  }
  
  TEST(simple_axon){
    swc_parser_data test_data("simple_axon.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit 
      basic_swcparser_checks(p,n,false,0,true,1,3);
      CHECK_EQUAL(1,n.axon_count());
    }
  }
  
  TEST(simple_apical){
    swc_parser_data test_data("simple_apical.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit 
      basic_swcparser_checks(p,n,false,0,true,1,3);
      CHECK_EQUAL(1,n.apical_count());
    }
  }
  
  TEST(simple_tree){
    swc_parser_data test_data("simple_tree.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,0,true,1,7);
      CHECK_EQUAL(1,n.dendrite_count());
      
      // Check structure
      CHECK_EQUAL(5,n.begin_dendrite()->size());
      CHECK_EQUAL(2,n.begin_dendrite()->max_centrifugal_order());
    }
  }
  
  TEST(real){
    swc_parser_data test_data("real.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,0,true,8,2026);
    }
  }
  
  // ERROR CASES
  TEST(missing_fields){
    swc_parser_data test_data("missing_fields.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      // We ignore empty lines without considering it an error
      basic_swcparser_checks(p,n,false,2,true,1,5);
    }
  }
  
  TEST(extra_fields){
    swc_parser_data test_data("extra_fields.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      
      // Extra fields are ignored - but we emit a warning
      basic_swcparser_checks(p,n,false,0,true,1,7);
      // We have the extra fields warning
      CHECK_EQUAL(1,p.warn());
    }
  }
  
  TEST(wrong_id){
    swc_parser_data test_data("wrong_id_type.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,2,true,1,5);
    }
  }
  
  TEST(wrong_num){
    swc_parser_data test_data("wrong_numeric_fields.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,2,true,1,5);
    }
  }
  
  TEST(wrong_parent){
    swc_parser_data test_data("wrong_parent_type.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,2,true,1,5);
    }
  }
  
  TEST(orphan){
    swc_parser_data test_data("orphan_node.swc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      SWCParser&p = test_data.parser;
      
      // No errors - no crit
      basic_swcparser_checks(p,n,false,1,true,1,6);
    }
  }
}
