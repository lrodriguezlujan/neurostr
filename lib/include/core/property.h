#ifndef NEUROSTR_CORE_PROPERTY_MAP_H_
#define NEUROSTR_CORE_PROPERTY_MAP_H_

#include <map>
#include <string>
#include <boost/any.hpp>
#include <cstdio>
#include "core/geometry.h"

namespace neurostr{
 
/**
 * @class PropertyMap
 * @author luis
 * @date 28/09/16
 * @file property.h
 * @brief Propert map auxiliar clase. stores properties for node,branch, neurite... etc
 */
class PropertyMap {
  
  public:
    using property_type = std::pair<std::string, boost::any>;
    using map_type      = std::map<std::string, boost::any>;
    using iterator      = map_type::iterator;
    using const_iterator= map_type::const_iterator;
  
  private:
    map_type storage_;
  
  public:
    
    /**
     * @brief Initializes an empty property map
     */
    PropertyMap();
    
    /**
     * @brief Initializes a property map with the content in the range
     * @param begin property begin iterator
     * @param end property end iterator
     */
    template <typename Iter>
    PropertyMap(const Iter& begin, const Iter& end) : storage_(begin,end) {};
    
    /**
     * @brief Returns the property with key k
     * @param k Property key
     * @return Const iterator. End() if no property with key k exists
     */
    const_iterator find(const std::string& k) const;
    
    /**
     * @brief Returns the value of the poperty with key k
     * @param k Key
     * @return Property value
     */
    template <typename T>
    T get(const std::string& k) const {
      return value<T>(*(storage_.find(k)));
    }
    
    /**
     * @brief Adds a new property to the map
     * @param p Property to add 
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const property_type& p);
    
    /**
     * @brief Adds an empty property to the map
     * @param k Property key
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k);
    
     /**
     * @brief Adds a new int valued property to the map
     * @param k Property key
     * @param v Property value
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k, int v);
    
    /**
     * @brief Adds a new float valued property to the map
     * @param k Property key
     * @param v Property value
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k, float v);
    
    /**
     * @brief Adds a new string valued property to the map
     * @param k Property key
     * @param v Property value
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k,const std::string v);
    
    /**
     * @brief Adds a new point valued property to the map
     * @param k Property key
     * @param v Property value
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k,const point_type v);
    
    /**
     * @brief Adds a property to the map
     * @param k Property key
     * @param v Property value
     * @return pair(iterator, T/F property added)
     */
    std::pair<iterator,bool> set(const std::string& k,boost::any v);
    
    /**
     * @brief Property exists
     * @param k Property name
     * @return True if the property exists
     */
    bool exists(const std::string& k) const ;
    
    /**
     * @brief Deletes a property
     * @param k Poperty key
     */
    void remove(const std::string& k);
    
    
    /**
     * @brief Deletes a property
     * @param i property iterator
     */
    void remove(const iterator& i);
    
    /**
     * @brief Property map size
     * @return  Number of properties in the map
     */
    map_type::size_type size() const;
    
    /**
     * @brief Property begin iterator
     * @return iterator
     */
    const_iterator begin() const ;
    
    /**
     * @brief Property end iterator
     * @return iterator
     */
    const_iterator end() const ;
  
  /**
   * @brief Property value as string
   * @param p Property
   * @return value as string
   */
  static std::string value_as_string(const property_type& p);
  
  /**
   * @brief Checks if a property value is of some type
   * @param p Property type
   * @return True if the property value is of type T
   */
  template <typename T>
  static bool is(const property_type& p){
    return p.second.type() == typeid(T);
  };
  
  /**
   * @brief Returns the property value casted to T
   * @param p Property
   * @return  Property value
   */
  template <typename T>
  static T value(const property_type& p){
    return boost::any_cast<T>(p.second);
  };
  
  /**
   * @brief Checks whether a property is empty 
   * @param p property
   * @return  True if p is empty
   */
  static bool empty(const property_type& p);
  
  /**
   * @brief Gets property key
   * @param p Property
   * @return Property key
   */
  static const std::string& key(const property_type& p);
};

/**
 * @class WithProperties
 * @author luis
 * @date 28/09/16
 * @file property.h
 * @brief Base class for neuron , neurite ... to have a property map
 */
class WithProperties{
  
  public:    
  
    /**
     * @brief create an empty property map
     */
    WithProperties() ;
    
    // Copy
    WithProperties(const WithProperties& other) = default;
    WithProperties& operator=(const WithProperties& b) = default;

    // Move
    WithProperties(WithProperties&& b) = default;
    WithProperties& operator=(WithProperties&& b) = default;

    // Store
    PropertyMap properties;
    
    /**
     * @brief Proprerty begin iterator
     * @return property iterator
     */
    auto begin_properties() const { return properties.begin(); }
    
    /**
     * @brief Property end iterator
     * @return property iterator
     */
    auto end_properties() const { return properties.end(); }
    
    /**
     * @brief Adds a property
     * @param key Property key
     * @param v Property value
     * @return property iterator
     */
    template <typename T> 
    auto add_property(const std::string& key, const T& v) {
      return properties.set(std::pair<std::string, boost::any>(key, v));
    }

    /**
     * @brief Adds an empty property
     * @param key Property key
     * @return property iterator 
     */
    std::pair<PropertyMap::iterator,bool> add_property(const std::string& key);

    /**
     * @brief Adds a property
     * @param v Propery
     * @return property iterator
    */
    std::pair<PropertyMap::iterator,bool> 
    add_property(const std::pair<std::string, boost::any>& v);
    
    /**
     * @brief Get property
     * @param key Property key
     * @return property iterator
     */
    PropertyMap::const_iterator  get_property(const std::string& key) const;
};

using property_type  = PropertyMap::property_type;
  
} // neurostr

#endif
