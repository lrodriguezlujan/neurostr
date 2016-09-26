#ifndef NEUROSTR_SELECTOR_UNIVERSAL_SELECTOR_H_
#define NEUROSTR_SELECTOR_UNIVERSAL_SELECTOR_H_

#include <functional>

#include "selector/selector.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"


namespace neurostr {
namespace selector {
  
/** STATIC Self selector */
template <typename T>
auto self_selector_factory(){
  return [](T& item) -> T&{ return item;};
} 

// Property related selector
  
// IN: Set Out: Set
template <typename T>
auto property_exists_factory(const std::string& key){
  using reference = std::reference_wrapper<T>;
  return [k_ = key](const typename std::vector<reference>::iterator & b,
                    const typename std::vector<reference>::iterator & e ) 
                    -> std::vector<reference> {
        std::vector<reference> st;
        for (auto it = b; it != e; ++it) {
          if( it->get().properties.exists(k_) )
            st.emplace_back(*it);
        }
        return st;
  };
};

// IN: Set Out: Set
template <typename T, typename V>
auto property_exists_factory(const std::string& key, V value){
  using reference = std::reference_wrapper<T>;
  //using value_type = V;
  return [k_ = key, v_ = value](const typename std::vector<reference>::iterator& b,
                               const typename std::vector<reference>::iterator& e ) 
                               -> std::vector<reference> {
        std::vector<reference> st;
        for (auto it = b; it != e; ++it) {
          if( it->get().properties.exists(k_) &&  
              it->get().properties.get(k_) == v_ )
            st.emplace_back(*it);
        }
        return st;
  };
};



  
} // Selector
} // Neurostr


#endif
