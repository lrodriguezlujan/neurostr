#ifndef NEUROSTR_CORE_PROPERTY_MAP_H_
#define NEUROSTR_CORE_PROPERTY_MAP_H_

#include <map>
#include <string>
#include <boost/any.hpp>
#include <cstdio>
#include "core/geometry.h"

namespace neurostr{
 
// Could template this...not really needed
// Base on property map
class PropertyMap {
  
  public:
    using property_type = std::pair<std::string, boost::any>;
    using map_type      = std::map<std::string, boost::any>;
    using iterator      = map_type::iterator;
    using const_iterator      = map_type::const_iterator;
  
  private:
    map_type storage_;
  
  public:
    
    PropertyMap() : storage_(){};
    
    template <typename Iter>
    PropertyMap(const Iter& begin, const Iter& end) : storage_(begin,end) {};
    
    const_iterator find(const std::string& k) const {
      return storage_.find(k);
    }
    
    template <typename T>
    T get(const std::string& k) const {
      return value<T>(*(storage_.find(k)));
    }
    
        // Restrict accepted types
    std::pair<iterator,bool> set(const property_type& p) {
      return storage_.insert(p);
    }
    
    std::pair<iterator,bool> set(const std::string& k) {
      return storage_.insert(property_type(k, boost::any()));
    }
    
    // Restrict accepted types
    std::pair<iterator,bool> set(const std::string& k,const int v) {
      return storage_.emplace(k, v);
    }
    
    std::pair<iterator,bool> set(const std::string& k,const float v) {
      return storage_.emplace(k, v);
    }
    
    std::pair<iterator,bool> set(const std::string& k,const std::string v) {
      return storage_.emplace(k, v);
    }
    
    std::pair<iterator,bool> set(const std::string& k,const point_type v) {
      return storage_.emplace(k, v);
    }
    
    std::pair<iterator,bool> set(const std::string& k,boost::any v) {
      return storage_.emplace(k, v);
    }
    
    bool exists(const std::string& k) const {
      return storage_.count(k) > 0;
    }
    
    void remove(const std::string& k){
      storage_.erase(k);
    }
    
    void remove(const iterator& i){
      storage_.erase(i);
    }
    
    map_type::size_type size() const{
      return storage_.size();
    }
    
    const_iterator begin() const {
      return storage_.begin();
    }
    
    const_iterator end() const {
      return storage_.end();
    }
  // Static common functions
  static std::string value_as_string(const property_type& p){
      if (empty(p)) return std::string();
      else if (is<std::string>(p)) return value<std::string>(p);
      else if (is<int>(p)) return std::to_string(value<int>(p));
      else if (is<float>(p)) return std::to_string(value<float>(p));
      else if (is<point_type>(p)){
        char buff[30];
        snprintf(buff, sizeof(buff), "%.3f %.3f %.3f",  
          geometry::get<0>(value<point_type>(p)), 
          geometry::get<1>(value<point_type>(p)), 
          geometry::get<2>(value<point_type>(p)));
        
        return std::string(buff);
      }
      else return std::string();
  };
  
  template <typename T>
  static bool is(const property_type& p){
    return p.second.type() == typeid(T);
  };
  
  template <typename T>
  static T value(const property_type& p){
    return boost::any_cast<T>(p.second);
  };
  
  static bool empty(const property_type& p){
    return p.second.empty();
  }
  
  static const std::string& key(const property_type& p){
    return p.first;
  }
};

class WithProperties{
  
  public:    
    WithProperties() : properties() {};
    
    WithProperties(const WithProperties& other) = default;
    WithProperties& operator=(const WithProperties& b) = default;

    // Move
    WithProperties(WithProperties&& b) = default;
    WithProperties& operator=(WithProperties&& b) = default;

  
    PropertyMap properties;
    auto begin_properties() const { return properties.begin(); }
    auto end_properties() const { return properties.end(); }
    
    template <typename T> 
    auto add_property(const std::string& key, const T& v) {
      return properties.set(std::pair<std::string, boost::any>(key, v));
    }

    auto add_property(const std::string& key) {
      return properties.set(
        std::pair<std::string, boost::any>(key, boost::any()));
    }

    auto add_property(const std::pair<std::string, boost::any>& v) {
      return properties.set(v);
    }
    
    auto get_property(const std::string& key) const { 
      return properties.find(key); 
    }
};

using property_type  = PropertyMap::property_type;
  
} // neurostr

#endif
