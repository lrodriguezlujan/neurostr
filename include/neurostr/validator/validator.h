#ifndef NEUROSTR_VALIDATOR_VALIDATOR_H_
#define NEUROSTR_VALIDATOR_VALIDATOR_H_

#include <iostream>
#include <functional>

//#include <boost/format.hpp>

#include <neurostr/selector/selector.h>
#include <neurostr/selector/neuron_selector.h>
#include <neurostr/selector/neurite_selector.h>
#include <neurostr/selector/branch_selector.h>
#include <neurostr/selector/node_selector.h>

#include <neurostr/measure/measure.h>
#include <neurostr/core/neuron.h>

#include <neurostr/validator/checks.h>

namespace neurostr {
namespace validator {

  
// TODO:: Validator traits
  

/**
 * @class ValidatorItem
 * @file validator.h
 * @brief Auxiliar class for the validator class. It contains a reference
 * to a validated element, the measure value and the check function result.
 */
template <typename T, typename V>
  class ValidatorItem {
    
    
    public:
    
    // Element type (Neuron, neurite, branch or node)
    using type = T;
    
    // Measure value type
    using value_type = V;
    
    /**
     * @brief Default empty constructor
     */
    ValidatorItem() :
      element(), value(), valid(false) {};
    
    /**
     * @brief Creates an item with the given parameters
     * @param el Validated element reference
     * @param val Measure value
     * @param is_valid Check function value
     */
    ValidatorItem(T& el, value_type val, bool is_valid) :
      element(el), value(val), valid(is_valid) {};
    
    /** Validated element **/
    std::reference_wrapper<T> element;
    
    /** Measure value **/
    V                         value;
    
    /** Check function value **/
    bool                      valid;
    
    /**
     * @brief Creates a JSON object with the full ID for the given element
     * @return JSON ID Object string
     */
    std::string element_id_json() const{
      return "{ " + element_id_json_(element.get()) + " }";
    };
    
    /**
     * @brief Returns an string with the element name (Neuron, Neurite, Branch or Node)
     * @return Element type string
     */
    std::string element_type() const {
      return element_name(element);
    }
    
    /**
     * @brief Writes the Item to the given stream as a JSON object
     * @param os Output stream
     * @return JSON Object with type, id, value and pass result.
     */
    std::ostream& toJSON( std::ostream& os) const {
      os << "{ " <<
        "\"type\" : " << escape_string(element_type()) << ", " << std::endl << 
        "\"id\" : " << element_id_json() << "," << std::endl << 
        "\"value\" : " << escape_string(value) << " ," << std::endl;
        if(valid){
          os << "\"pass\" : true" << std::endl << "}";
        } else {
          os << "\"pass\" : false" << std::endl << "}";
        }
      return os;
    }
    
    
    
    private:
    
    /**
     * @brief Generic template that writes the v parameter as a string
     * @param v Element to be written as string
     * @return String
     */
    template <typename U>
    std::string escape_string(const U& v) const{
      return std::to_string(v);
    }
    
    /**
     * @brief Escapes a string using double quotes
     * @param v String to escape
     * @return String
     */
    std::string escape_string(const std::string& v) const{
      return "\"" + v + "\"";
    }
    
    /**
     * @brief Escapes a string using double quotes
     * @param v String to escape
     * @return String
     */
    std::string escape_string(const char* v) const{
      return "\"" + std::string(v) + "\"";
    }

    /**
     * @brief Writes the Neuron id as json field
     * @param n Neuron
     * @return JSON field string
     */
    std::string element_id_json_(const Neuron& n) const{
      return escape_string("neuron") + " : " + escape_string(n.id());
    }
    
    /**
     * @brief Writes the Neurite and neuron Id as json field
     * @param n Neurite
     * @return JSON field string
     */
    std::string element_id_json_(const Neurite& n) const{
      return element_id_json_(n.neuron()) + ",\n" + escape_string("neurite") + " : " + std::to_string(n.id());
    }
    
    /**
     * @brief Writes the Branch, Neurite and neuron Id as json field
     * @param n Branch
     * @return JSON field string
     */
    std::string element_id_json_(const Branch& n) const{
      return element_id_json_(n.neurite()) + ",\n" + escape_string("branch") + " : " + escape_string(n.idString());
    }
    
    /**
     * @brief Writes the Node, Branch, Neurite and neuron Id as json field
     * @param n Node
     * @return JSON field string
     */
    std::string element_id_json_(const Node& n) const{
      return element_id_json_(n.branch()) + ",\n" + escape_string("node") + " : " + std::to_string(n.id());
    }
    

    /**
     * @brief Returns Name type for neuron
     * @param n Neuron
     * @return Neuron String
     */
    std::string element_name(const Neuron& n) const{
      return "Neuron";
    }
    
    /**
     * @brief Returns Name type for neurite
     * @param n Neurite
     * @return Neurite String
     */
    std::string element_name(const Neurite& n) const{
      return "Neurite";
    }
    
    /**
     * @brief Returns Name type for branch
     * @param n Branch
     * @return Branch String
     */
    std::string element_name(const Branch& n) const{
      return "Branch";
    }
    
    /**
     * @brief Returns Name type for node
     * @param n Node
     * @return Node String
     */
    std::string element_name(const Node& n) const{
      return "Node";
    }
};


/**
 * @class Validator
 * @file validator.h
 * @brief Validator class template build up from a Measure and a Check function
 */
template <typename M, typename C> 
class Validator {
  
  public:
  
  // MEasure function traits
  using measure_traits = measure::measure_func_traits<M>;
  
  // Measure input type
  using in_type = typename measure_traits::in_type;
  
  // Measure value type
  using value_type = typename measure_traits::out_type;
  
  // Check function traits
  using check_traits = check_func_traits<C>;
  
  // Shorthand for vector of ValidatorItems
  using storage_type = std::vector<ValidatorItem<in_type,value_type> >;
  
  // Data elements
    private:
  
  // Auxiliar type structure for template resolution
  template<typename T> struct type { };
  
  // Data
  
  // Validator Measure function
  M measure_;
  
  // Validator Check function
  C checker_;
  
  // Validated neuron pointer
  const Neuron* neuron_;
  
  
  // Validation result vector
  storage_type results_;
  
  // Validation short name
  std::string name_;
  
  // Validation description
  std::string desc_;
 
    public:
  
  /**
   * @brief Creates a validator with given measure and check functions
   * @param measure Measure function. Should take a single element as imput
   * @param check Check function. Should take a single measure value as input
   * @return Validator
   */
  Validator(M measure, C check)
      : measure_(measure), checker_(check), neuron_(nullptr), results_() {
        
    static_assert(!measure_traits::in_set, "Measure input is not a single element");
    static_assert(std::is_convertible<value_type,typename check_traits::in_type>::value,"");
  };

  /**
   * @brief Runs the validation for the given Neuron
   * @param n  Neuron to be validated
   */
  void validate(const Neuron& n) {

    // Clear results
    results_.clear();
  
    // Set neuron
    neuron_ = &n;
    
    // Run!
    run<in_type>();
  }

  /**
   * @brief Begin const bidirectional iterator to the validation results
   * @return Bidirectional iterator to ValidatorItem
   */
  typename storage_type::const_iterator begin() const {
    return results_.begin();
  }
  
  /**
   * @brief End const bidirectional iterator to the validation results
   * @return Bidirectional iterator to ValidatorItem
   */
  typename storage_type::const_iterator end() const {
    return results_.end();
  }
  
  /**
   * @brief Returns the number of validated items
   * @return Number of validated items
   */
  typename storage_type::size_type size() const {
    return results_.size();
  }
  
  /**
   * @brief Sets the validation name
   * @param s Validation shortname
   */
  void set_name(const std::string& s) {
    name_ = s;
  }
  
  /**
   * @brief Sets the validation description string
   * @param s Validation description
   */
  void set_description(const std::string& s) {
    desc_ = s;
  }

  /**
   * @brief Check if all validated elements passed the check function
   * @return True if all elements passed
   */
  bool pass() const {
    return std::all_of(results_.begin(), results_.end(), [](const auto& i) -> bool { return i.valid; });
  };
  
  /**
   * @brief Writes the validator (name and description), the neuron id and the
   * results as a JSON string in the given stream
   * @param os Output stream
   * @param failuresOnly Write only failing ValidatorItem
   * @return Stream
   */
  std::ostream& toJSON( std::ostream& os, 
                       bool failuresOnly = true) const {
    return toJSON(os,name_,desc_,failuresOnly);
  }
                       
  /**
   * @brief Writes the validator, the neuron id and the
   * results as a JSON string in the given stream
   * @param os Output stream
   * @param name Validation shortname
   * @param desc Validation description
   * @param failuresOnly Write only failing ValidatorItem
   * @return 
   */
  std::ostream& toJSON( std::ostream& os, 
                       const std::string& name, 
                       const std::string& desc,
                       bool failuresOnly = true) const {
    
     os << "{ ";
     
     if(name.size() > 0) {
          os << "\"name\" : \"" << name << "\", " << std::endl;
     }
     
     if(desc.size() > 0) {
          os << "\"description\" : \"" << desc << "\", " << std::endl;
     }
     
     os << "\"neuron_id\" : \"" << neuron_->id() << "\" ," << std::endl;
     
     if(pass()) {
       os << "\"pass\" : true , " << std::endl;
     } else {
       os << "\"pass\" : false , " << std::endl;
     }
     
     os << "\"results\" : [";
       
    bool first = true;
     for(auto it = results_.begin(); it != results_.end() ; ++it){
       if(!failuresOnly || !it->valid){
         if(!first){
          os << ", " << std::endl;
          
         }
         it->toJSON(os);
         first = false;
          
       }
     }
     os << "]" << std::endl << "}";

     return os;
  }
  

  private:
 
   /**
    * @brief Runs the validation for the given element type.
    */
  template <typename T>
  void run(type<T>());
  

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

// So we can use auto and skip all that typing.
template <typename M, typename C>
constexpr Validator<M,C> create_validator(const M& measure, const C& check,const std::string& name,const std::string& desc) {
  Validator<M,C> v(measure, check);
  v.set_name(name);
  v.set_description(desc);
  return v;
};

// Examples

}  // validation
}  // neurostr

#endif
