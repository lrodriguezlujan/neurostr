#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <neurostr/io/nl_structure.h>
#include <neurostr/io/ASCParser.h>

#define ASC_TEST_DATA_SUBDIR "test_data/asc/"

SUITE(NL_ASC_parser_tests){
  
  using namespace neurostr::io;
  
  const char* env_test_data_dir = std::getenv("NSTR_TEST_DIR");
  const std::string test_files_folder = env_test_data_dir?std::string(env_test_data_dir) +  ASC_TEST_DATA_SUBDIR : ASC_TEST_DATA_SUBDIR; 
  
  struct asc_parser_data {
    asc_parser_data(const std::string& s) 
      : is( test_files_folder + s)
      , parser(is)
      , rec(nullptr) {
        if(!is) CHECK(false);
        else {
          rec=parser.read("test"); 
          
        }
    }
      
    ~asc_parser_data(){};
    
    std::ifstream is;
    ASCParser  parser;
    std::unique_ptr<neurostr::Reconstruction> rec;
  };
  
  // Basic checks
  void basic_ascparser_checks(const ASCParser& p, const neurostr::Neuron& n, 
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
    asc_parser_data test_data("empty.asc");
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(false,test_data.parser.critical());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(empty_comment){
    asc_parser_data test_data("empty_comment.asc");
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(false,test_data.parser.critical());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(single_property){
    asc_parser_data test_data("single_property.asc");
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
    CHECK_EQUAL(2, r.properties.size());
    CHECK(r.properties.exists("key1"));
    CHECK(r.properties.exists("key2"));
  }
  
  TEST(single_rgb_property){
    asc_parser_data test_data("single_rgb_property.asc"); 
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
    CHECK_EQUAL(1, r.properties.size());
    CHECK(r.properties.exists("color"));
  }
  
  TEST(single_contour){
    asc_parser_data test_data("single_contour.asc"); 
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
    CHECK_EQUAL(1, r.n_contours());
    CHECK_EQUAL(4, r.contour_begin()->size());
  }
  TEST(single_marker){
    asc_parser_data test_data("single_marker.asc"); 
    neurostr::Reconstruction& r = *test_data.rec;
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(0,test_data.parser.error());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(single_soma){
    asc_parser_data test_data("single_soma.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,0,0);
    }
  }
  
  TEST(simple_dendrite){
    asc_parser_data test_data("simple_dendrite.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.dendrite_count());
    }
  }
  
  TEST(simple_apical){
    asc_parser_data test_data("simple_apical.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.apical_count());
    }
  }
  
  TEST(simple_axon){
    asc_parser_data test_data("simple_axon.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(1,n.axon_count());
    }
  }
  
    TEST(simple_untyped){
    asc_parser_data test_data("simple_untyped.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,1,3);
      CHECK_EQUAL(0,n.axon_count());
      CHECK_EQUAL(0,n.apical_count());
      CHECK_EQUAL(0,n.dendrite_count());
    }
  }
  
  TEST(simple_tree){
    asc_parser_data test_data("simple_tree.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,1,7);
      CHECK_EQUAL(1,n.dendrite_count());
      
      // Check structure
      CHECK_EQUAL(5,n.begin_dendrite()->size());
      CHECK_EQUAL(2,n.begin_dendrite()->max_centrifugal_order());
    }
  }
  
  TEST(real){
    asc_parser_data test_data("real.asc");
    CHECK(test_data.rec->size() == 3);
    if(test_data.rec->size() >= 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,0,0,true,7,914);
    }
  }
  
  //////////////
  // ERROR CASES
  //////////////
  
  TEST(malformed){
    asc_parser_data test_data("malformed.asc");
    CHECK(test_data.rec->size() == 0);
    CHECK_EQUAL(true,test_data.parser.critical());
  }
  
  TEST(truncated){
    asc_parser_data test_data("truncated.asc");
    CHECK(test_data.rec->size() == 1); // Partial reconstruction
    CHECK_EQUAL(2,test_data.parser.error());
    CHECK_EQUAL(true,test_data.parser.critical());
    CHECK_EQUAL(0,test_data.parser.warn());
  }
  
  TEST(missing_fields){
    asc_parser_data test_data("missing_fields.asc");  
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
    
      basic_ascparser_checks(p,n,false,1,0,true,1,6);
    }
  }
  
  TEST(non_numeric){
    asc_parser_data test_data("non_numeric.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      basic_ascparser_checks(p,n,false,1,0,true,1,6);
    }
  }
  
  TEST(negative_radius){
    asc_parser_data test_data("negative_radius.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      basic_ascparser_checks(p,n,false,1,0,true,1,6);
    }
  }
  
  TEST(extra_field){
    asc_parser_data test_data("extra_field.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      basic_ascparser_checks(p,n,false,1,0,true,1,6);
    }
  }
  
  TEST(non_numeric_rgb){
    asc_parser_data test_data("non_numeric_rgb.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      basic_ascparser_checks(p,n,false,1,0,true,1,7);
    }
  }
  
  TEST(extra_field_property){
    asc_parser_data test_data("extra_field_property.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      basic_ascparser_checks(p,n,false,1,0,true,1,7);
    }
  }
  
  TEST(unexpected_block_marker){
    asc_parser_data test_data("unexpected_block_marker.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,1,0,true,1,7);
    }
  }
  
  TEST(malformed_spine){
    asc_parser_data test_data("malformed_spine.asc");
    CHECK(test_data.rec->size() == 1);
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,1,0,true,1,7);
    }
  }
  
  TEST(unexpected_block_in_tree){
    asc_parser_data test_data("unexpected_block_tree.asc");
    CHECK(test_data.rec->size() == 1); 
    if(test_data.rec->size() == 1){
      neurostr::Neuron&n = *(test_data.rec->begin());
      ASCParser&p = test_data.parser;
      
      // No errors - no warns - no crit - empty
      basic_ascparser_checks(p,n,false,1,0,true,1,7);
    }
  }
  
  
  
  


} // END SUITE
