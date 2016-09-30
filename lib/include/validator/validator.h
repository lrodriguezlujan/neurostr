#ifndef NEUROSTR_VALIDATOR_VALIDATOR_H_
#define NEUROSTR_VALIDATOR_VALIDATOR_H_

#include <iostream>
#include <functional>

#include "selector/selector.h"
#include "selector/neuron_selector.h"
#include "selector/neurite_selector.h"
#include "selector/branch_selector.h"
#include "selector/node_selector.h"

#include "measure/measure.h"
#include "core/neuron.h"

#include "validator/checks.h"

namespace neurostr {
namespace validator {

  
// TODO:: Validator traits
  
// Auxiliar structs

// Auxiliar class
template <typename T, typename V>
  class ValidatorItem {
    
    
    public:
    using type = T;
    using value_type = V;
    
    ValidatorItem() :
      element(), value(), valid(false) {};
    
    ValidatorItem(T& el, value_type val, bool is_valid) :
      element(el), value(val), valid(is_valid) {};
    
    std::reference_wrapper<T> element;
    V                         value;
    bool                      valid;
    
    // Full validation ID
    std::string element_id() const{
      return element_id_(element.get());
    };
    
    private:
    

    std::string element_id_(Neuron& n) const{
      return std::string("Neuron: ") + n.id();
    }
    
    std::string element_id_(Neurite& n) const{
      return element_id_(n.neuron()) + std::string(", neurite: ") + std::to_string(n.id());
    }
    
    std::string element_id_(Branch& n) const{
      return element_id_(n.neurite()) + std::string(", branch: ") + n.idString();
    }
    
    std::string element_id_(Node& n) const{
      return element_id_(n.branch()) + std::string(", Node: ") + std::to_string(n.id());
    }
  };



template <typename M, typename C> 
class Validator {
  
  public:
  
  // Typedefs
  using measure_traits = measure::measure_func_traits<M>;
  using in_type = typename measure_traits::in_type;
  using value_type = typename measure_traits::out_type;
  using check_traits = check_func_traits<C>;
  using storage_type = std::vector<ValidatorItem<in_type,value_type> >;
  
  // Data elements
  private:
  
  template<typename T> struct type { }; // Auxiliar
  
  // Data
  M measure_;
  C checker_;
  const Neuron* neuron_;
  // Validation
  storage_type results_;
 
  public:
  // Constructor
  Validator(M measure, C check)
      : measure_(measure), checker_(check), neuron_(nullptr), results_() {
        
    static_assert(!measure_traits::in_set, "Measure input is not a single element");
    static_assert(std::is_convertible<value_type,typename check_traits::in_type>::value,"");
  };

  // Always validate neurons as a whole. Even if the measure is for nodes, branches...
  void validate(const Neuron& n) {

    // Clear results
    results_.clear();
  
    // Set neuron
    neuron_ = &n;
    
    // Run!
    run<in_type>();
  }
  
  template <typename T>
  void run(type<T>());
  
  typename storage_type::const_iterator begin() const {
    return results_.begin();
  }
  
  typename storage_type::const_iterator end() const {
    return results_.end();
  }
  
  typename storage_type::size_type size() const {
    return results_.size();
  }

  bool pass() const {
    return std::all_of(results_.begin(), results_.end(), [](const auto& i) -> bool { return i.valid; });
  };

 private:
  
  // Execute depending on the type
  template <typename T> 
  void run() {
    run(type<const T>());
  }
  
  template <typename T> 
  void run(type<const T>) {
  }
  
  
  
  void run(type<const Neuron>){
    // Just execute the measure and the checker for the neuron
    value_type v = measure_(*neuron_);
    bool pass = checker_(v);
    results_.emplace_back(*neuron_, v, pass);
  };
  
  void run(type<const Neurite>){
    // Select neurites and run
    auto sel = selector::neuron_neurites(*neuron_);
    value_type v ;
    
    for( auto it = sel.begin(); it != sel.end() ; ++it ){
      v = measure_(it->get());
      results_.emplace_back(it->get(), v, checker_(v));
    }
  };
  
  void run(type<const Branch>){
    auto sel = selector::compose_selector(
      selector::selector_in_single_to_set(selector::neurite_branch_selector), 
      selector::neuron_neurites)(*neuron_);
    
    value_type v ;
    
    for( auto it = sel.begin(); it != sel.end() ; ++it ){
      v = measure_(it->get());
      results_.emplace_back(it->get(), v, checker_(v));
    }
  };
  
  void run(type<const Node>){
    // Select neurites and run
    auto sel = selector::neuron_node_selector(*neuron_);
    value_type v ;
    
    for( auto it = sel.begin(); it != sel.end() ; ++it ){
      v = measure_(it->get());
      results_.emplace_back(it->get(), v, checker_(v));
    }
  };
};

// std::ostream& operator<<(std::ostream& os, const Validator::ValidatorItem& item);

template <typename T, typename V> 
std::ostream& operator<<(std::ostream& os, const ValidatorItem<T,V>& it){
  os << "Element: " << it.element_id() << std::endl;
  os << "Value: " << it.value << std::endl;
  os << "Pass: " << it.valid << std::endl;
  return os;
};

// So we can use auto and skip all that typing.
template <typename M, typename C>
constexpr Validator<M,C> create_validator(const M& measure, const C& check) {
  return Validator<M,C>(measure, check);
};

// Examples

}  // validation
}  // neurostr

#endif
