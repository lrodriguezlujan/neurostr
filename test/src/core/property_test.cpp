#include <unittest++/UnitTest++.h>
#include "core/property.h"

SUITE(property_tests){
using namespace neurostr;

// Test empty constructor props
TEST(empty_constructor){
  
  PropertyMap p;
  
  CHECK_EQUAL(0,p.size());
  CHECK(p.begin()==p.end());
  
}

TEST(iterator_constructor){
  
  std::vector<PropertyMap::property_type> props;
  
  props.push_back(PropertyMap::property_type("A",boost::any()));
  props.push_back(PropertyMap::property_type("B",boost::any(3)));
  props.push_back(PropertyMap::property_type("C",boost::any(3.0f)));
  props.push_back(PropertyMap::property_type("D",boost::any(true)));
  
  PropertyMap p(props.begin(),props.end());
  
  CHECK_EQUAL(4,p.size());
  CHECK_EQUAL(4, std::distance(p.begin(),p.end()));
  CHECK_EQUAL(true,p.exists("A"));
  CHECK_EQUAL(3,p.get<int>("B"));
  CHECK_EQUAL(3.0f,p.get<float>("C"));
  CHECK_EQUAL(true,p.get<bool>("D"));
}

TEST(key_finder_exists){
  
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK( p.find("A") != p.end() );
  
}

TEST(key_finder_fail){
  
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK( p.find("D") == p.end() );
  
}

TEST(get_exists){
  
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK_EQUAL( 3, p.get<int>("B"));
  CHECK_EQUAL( 3.0f, p.get<float>("C"));
}

TEST(get_fails){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  CHECK_THROW(p.get<int>("D"),std::exception);
}

TEST(set_property){
  
  PropertyMap p;
  p.set(PropertyMap::property_type("A",boost::any()));
  
  CHECK(p.exists("A"));
  CHECK(p.empty(*p.find("A")));
}

TEST(set_property_empty){
  PropertyMap p;
  p.set("A");
  
  CHECK(p.exists("A"));
  CHECK(p.empty(*p.find("A")));
}

TEST(set_property_int){
  PropertyMap p;
  p.set("A",1);
  
  CHECK(p.exists("A"));
  CHECK_EQUAL(1,p.get<int>("A"));
}

TEST(set_property_bool){
  PropertyMap p;
  p.set("A",false);
  
  CHECK(p.exists("A"));
  CHECK_EQUAL(false,p.get<bool>("A"));
}

TEST(set_property_float){
  PropertyMap p;
  p.set("A",1.0f);
  
  CHECK(p.exists("A"));
  CHECK_EQUAL(1.0f,p.get<float>("A"));
}

TEST(set_property_string){
  PropertyMap p;
  p.set("A",std::string("TEST"));
  
  CHECK(p.exists("A"));
  CHECK_EQUAL( std::string("TEST"),p.get<std::string>("A"));
}

TEST(set_property_point){
  PropertyMap p;
  p.set("A",point_type(1,1,1));
  
  CHECK(p.exists("A"));
  CHECK(geometry::equal(point_type(1,1,1),p.get<point_type>("A")));
}

TEST(set_property_any){
  PropertyMap p;
  p.set("A",boost::any());
  
  CHECK(p.exists("A"));
  CHECK(p.empty(*p.find("A")));
}

TEST(exists_key){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK(p.exists("A"));
  CHECK(p.exists("B"));
  CHECK(p.exists("C"));
}

TEST(dont_exist){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK(!p.exists("D"));
}

TEST(remove_existing_key){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK(p.exists("B"));
  CHECK_EQUAL(3,p.size());
  
  p.remove("B");
  
  CHECK(!p.exists("B"));
  CHECK_EQUAL(2,p.size());
  
  CHECK(p.begin() != p.end());
  
  p.remove("A");
  p.remove("C");
 
  CHECK(p.begin()==p.end());
  CHECK_EQUAL(0,p.size());
}

TEST(remove_nonexisting_key){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK_EQUAL(3,p.size());
  
   p.remove("D");
   
  CHECK_EQUAL(3,p.size());
}


TEST(remove_iterator){
  
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK_EQUAL(3,p.size());
  p.remove(p.begin());
  CHECK_EQUAL(2,p.size());
  
}

TEST(remove_end_iterator){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  
  CHECK_EQUAL(3,p.size());
  p.remove(p.end());
  CHECK_EQUAL(3,p.size());
}

TEST(size_empty){
  PropertyMap p;
  CHECK_EQUAL(0,p.size());
}

TEST(size_nonempty){
  PropertyMap p;
  p.set("A");
  p.set("B",3);
  p.set("C",3.0f);
  p.set("C",4.0f); // This should be ignored
  
  CHECK_EQUAL(3,p.size());
}

} // End suite
