#ifndef NEUROSTR_SELECTOR_UNIVERSAL_SELECTOR_H_
#define NEUROSTR_SELECTOR_UNIVERSAL_SELECTOR_H_

#include <functional>

#include <neurostr/selector/selector_traits.h>
#include <neurostr/core/node.h>
#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>


namespace neurostr {
namespace selector {
  
/** STATIC Self selector */
template <typename T>
auto self_selector_factory(){
  return [](const T& item) -> const T&{ return item;};
} 

// Property related selector
  
// IN: Set Out: Set
template <typename T>
auto property_exists_factory(const std::string& key){
  using reference = const_selector_reference<T>;
  return [k_ = key](const const_selector_iterator<T>& b,
                    const const_selector_iterator<T>& e ) 
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
  using reference = const_selector_reference<T>;
  using type = V;
  
  //using value_type = V;
  return [k_ = key, v_ = value](const const_selector_iterator<T>& b,
                                const const_selector_iterator<T>& e ) 
                                -> std::vector<reference> {
        std::vector<reference> st;
        for (auto it = b; it != e; ++it) {
          PropertyMap& p = it->get().properties;
          if( p.exists(k_) &&  
              p.get<type>(k_) == v_ )
            st.emplace_back(*it);
        }
        return st;
  };
};

  // Unique selector
// IN: SET OUT: SET
template <typename T>
struct unique_selector{
  using reference = const_selector_reference<T>;
  std::vector<reference> operator() (const const_selector_iterator<T>& b,
                                     const const_selector_iterator<T>& e ) {
    // Copy vector
    std::vector<reference> ret(b,e);
    
    // unique
    std::unique(ret.begin(),ret.end(), [](const reference& a, 
                                          const reference &b){
      return a.get() == b.get();
    });
    
    return ret;
  }
};

  
} // Selector
} // Neurostr


#endif
