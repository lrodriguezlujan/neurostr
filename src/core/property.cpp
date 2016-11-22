#include "core/property.h"

namespace neurostr{
  
  PropertyMap::PropertyMap() : storage_(){};
  
  PropertyMap::const_iterator PropertyMap::find(const std::string& k) const {
      return storage_.find(k);
  }
  
  std::pair<PropertyMap::iterator,bool> PropertyMap::set(
    const PropertyMap::property_type& p) {
      return storage_.insert(p);
  }
  
  std::pair<PropertyMap::iterator,bool> PropertyMap::set(const std::string& k) {
      return storage_.insert(property_type(k, boost::any()));
  }
  
  std::pair<PropertyMap::iterator,bool> 
    PropertyMap::set(const std::string& k, int v) {
    return storage_.emplace(k, v);
  }
  
  std::pair<PropertyMap::iterator,bool> 
    PropertyMap::set(const std::string& k, bool v) {
    return storage_.emplace(k, v);
  }
  
  std::pair<PropertyMap::iterator,bool> 
  PropertyMap::set(const std::string& k, float v) {
      return storage_.emplace(k, v);
  }
  std::pair<PropertyMap::iterator,bool> 
  PropertyMap::set(const std::string& k,const std::string v) {
      return storage_.emplace(k, v);
  }
  
  std::pair<PropertyMap::iterator,bool> 
  PropertyMap::set(const std::string& k,const point_type v) {
      return storage_.emplace(k, v);
  }
  
  std::pair<PropertyMap::iterator,bool> 
  PropertyMap::set(const std::string& k,boost::any v) {
      return storage_.emplace(k, v);
  }
  
  bool PropertyMap::exists(const std::string& k) const {
      return storage_.count(k) > 0;
  }
    
  void PropertyMap::remove(const std::string& k){
      storage_.erase(k);
  }
  
  void PropertyMap::remove(const iterator& i){
    if(i!=end())
      storage_.erase(i);
  }
  
  PropertyMap::map_type::size_type PropertyMap::size() const{
      return storage_.size();
  }
  
  PropertyMap::const_iterator PropertyMap::begin() const {
      return storage_.begin();
  }
  
  PropertyMap::iterator PropertyMap::begin(){
      return storage_.begin();
  }
  
  PropertyMap::const_iterator PropertyMap::end() const {
      return storage_.end();
  }
  
  PropertyMap::iterator PropertyMap::end(){
      return storage_.end();
  }
  
  std::string PropertyMap::value_as_string(const PropertyMap::property_type& p){
      if (empty(p)) return std::string();
      else if (is<std::string>(p)) return value<std::string>(p);
      else if (is<int>(p)) return std::to_string(value<int>(p));
      else if (is<float>(p)) return std::to_string(value<float>(p));
      else if (is<bool>(p)) if(value<bool>(p)) return std::string("true"); else return std::string("false");
      else if (is<point_type>(p)){
        char buff[30];
        snprintf(buff, sizeof(buff), "%.3f %.3f %.3f",  
          geometry::get<0>(value<point_type>(p)), 
          geometry::get<1>(value<point_type>(p)), 
          geometry::get<2>(value<point_type>(p)));
        
        return std::string(buff);
      } else {
        return std::string("PROPERTY TYPE NOT SUPPORTED");
      }
  }
  
  bool PropertyMap::empty(const PropertyMap::property_type& p){
    return p.second.empty();
  }
  
  const std::string& PropertyMap::key(const PropertyMap::property_type& p){
    return p.first;
  }
  
  /**** WITH PROPERTIES ***/
  WithProperties::WithProperties() : properties() {};
  
  std::pair<PropertyMap::iterator,bool> 
  WithProperties::add_property(const std::string& key) {
      return properties.set(
        std::pair<std::string, boost::any>(key, boost::any()));
  }
  
  std::pair<PropertyMap::iterator,bool> 
  WithProperties::add_property(const std::pair<std::string, boost::any>& v) {
      return properties.set(v);
  }
  
  PropertyMap::const_iterator 
  WithProperties::get_property(const std::string& key) const {
      return properties.find(key); 
    }
  
}; // neurostr namespace
