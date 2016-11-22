#ifndef NEUROSTR_SELECTOR_SELECTOR_OPERATIONS_H_
#define NEUROSTR_SELECTOR_SELECTOR_OPERATIONS_H_

#include <functional>
#include <boost/iterator.hpp>

#include <neurostr/core/traits.h>
#include <neurostr/selector/detail/selector_operations_detail.h>
#include <neurostr/selector/selector_traits.h>

#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>

namespace neurostr {
namespace selector {
  
/**
 * @brief Recursive template for selector composition
 * @param f1 First function
 * @param f2 Second function
 * @param fns.. Rest..
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) != 0>* = nullptr>
constexpr auto compose_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return compose_selector(detail::compose_selector_pair(f1, f2), fns...);
};


/**
 * @brief Recursive template for selector composition. Base case.
 * @param f1 First function
 * @param f2 Second function
 * @return f1 o f2
 */
template <typename F1, typename F2, typename... Funcs, std::enable_if_t<sizeof...(Funcs) == 0>* = nullptr>
constexpr auto compose_selector(const F1& f1, const F2& f2, Funcs... fns) {
  return detail::compose_selector_pair(f1, f2);
};


// Single output to set output templates. 3 cases

/**
* @brief Converts a selector with single output in one with set output 
* Case: selector input is SET Output is SINGLE
**/
template <typename F,
          std::enable_if_t<!selector_func_traits<F>::out_set && 
                            selector_func_traits<F>::in_set >* = nullptr>
constexpr auto selector_out_single_to_set(const F& f){
  
   using f_traits      = selector_func_traits<F>;
   
   using reference_out = std::reference_wrapper<const typename f_traits::out_type>;
   using reference_in  = std::reference_wrapper<const typename f_traits::in_type>;
   
   // Create Function
   return [f_ = f](const typename std::vector<reference_in>::iterator& b, 
                   const typename std::vector<reference_in>::iterator& e)
                    -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      ret.push_back(f_(b,e));
      return ret;
   };
}; // End template selector_out_single_to_set


/**
* @brief Converts a selector with single output in one with set output 
* Case: selector input is SINGLE Output is SINGLE
**/
template <typename F,
          std::enable_if_t<!selector_func_traits<F>::out_set && 
                           !selector_func_traits<F>::in_set >* = nullptr>
constexpr auto selector_out_single_to_set(const F& f){
  
   using f_traits      = selector_func_traits<F>;
   
   using reference_out = std::reference_wrapper<const typename f_traits::out_type>;
   using in  = typename f_traits::in_type;
   
   // Create Function
   return [f_ = f](const in& n) -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      ret.push_back(f_(n));
      return ret;
   };
}; // End template selector_out_single_to_set

/**
* @brief Converts a selector with single output in one with set output 
* Case: Output is already set
**/
template <typename F,
          std::enable_if_t<selector_func_traits<F>::out_set >* = nullptr>
constexpr auto selector_out_single_to_set(const F& f){
  return f;
}; // End template selector_out_single_to_set

// END  Single output to set output templates


// Single input to set input (join) templates. 3 cases

/**
* @brief Converts a selector with single input in one with set input 
* Case: selector input is SINGLE Output is SET
**/
template <typename F,
          std::enable_if_t<!selector_func_traits<F>::in_set && 
                            selector_func_traits<F>::out_set >* = nullptr>
constexpr auto selector_in_single_to_set(const F& f){
  
   using f_traits      = selector_func_traits<F>;
   
   using reference_out = std::reference_wrapper<const typename f_traits::out_type>;
   using reference_in  = std::reference_wrapper<const typename f_traits::in_type>;
   
   // Create join function
   return [f_ = f](const typename std::vector<reference_in>::iterator& b, 
                   const typename std::vector<reference_in>::iterator& e)
                    -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      for (auto it = b; it != e; ++it) {
        auto sel = f_(it->get());
        for(auto el = sel.begin() ; el != sel.end() ; ++el){
          ret.emplace_back(el->get());
        }
      }
      return ret;
   };    
}; // End template selector_out_single_to_set


/**
* @brief Converts a selector with single input in one with set input 
* Case: selector input is SINGLE Output is SINGLE
**/
template <typename F,
          std::enable_if_t<!selector_func_traits<F>::in_set && 
                           !selector_func_traits<F>::out_set >* = nullptr>
constexpr auto selector_in_single_to_set(const F& f){
  
   using f_traits      = selector_func_traits<F>;
   
   using reference_out = std::reference_wrapper<const typename f_traits::out_type>;
   using reference_in  = std::reference_wrapper<const typename f_traits::in_type>;
   
   // Create function
   return [f_ = f](const typename std::vector<reference_in>::iterator& b, 
                   const typename std::vector<reference_in>::iterator& e)
                    -> std::vector<reference_out> {
      std::vector<reference_out> ret;
      for (auto it = b; it != e; ++it) {
        ret.emplace_back(f_(it->get()));
      }
      return ret;
   };
}; // End template selector_out_single_to_set

/**
* @brief Converts a selector with single output in one with set output 
* Case: Output is already set
**/
template <typename F,
          std::enable_if_t<selector_func_traits<F>::in_set >* = nullptr>
constexpr auto selector_in_single_to_set(const F& f){
  return f;
}; 

/**
 * @brief Creates a new selector that applies the selector f2 to each selected element of f1
 * @param f1 First selector (that selects a set)
 * @param f2 Secpmd selector (input a single element)
 * @note Template for f1 single input and f2 single output
 */
template <typename F1, typename F2,
          std::enable_if_t<!selector_func_traits<F1>::in_set >* = nullptr,
          std::enable_if_t<!selector_func_traits<F2>::out_set >* = nullptr>
constexpr auto selector_foreach(const F1& f1, const F2& f2){
 
  
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;

  static_assert( !f2_traits::in_set, ""  );  
  static_assert( std::is_convertible< 
                  typename f1_traits::out_type,
                  typename f2_traits::in_type>::value, "" );
  
  using reference_out = std::reference_wrapper<const typename f2_traits::out_type>;
  using in  = typename f1_traits::in_type;
  
  return [f1_ = f1, f2_ = f2](const in& r) -> std::vector<reference_out> {
      auto sel = f1_(r);
      std::vector<reference_out> ret;
      ret.reserve(size(sel));
      for(auto it = sel.begin(); it != sel.end() ; ++it){
        ret.emplace_back(f2_(it->get()));
      }
      return ret;
  };
};

/**
 * @brief Creates a new selector that applies the selector f2 to each selected element of f1
 * @param f1 First selector (that selects a set)
 * @param f2 Secpmd selector (input a single element)
 * @note Template for f1 single input and f2 set output
 */
template <typename F1, typename F2,
          std::enable_if_t<!selector_func_traits<F1>::in_set >* = nullptr,
          std::enable_if_t<selector_func_traits<F2>::out_set >* = nullptr>
constexpr auto selector_foreach(const F1& f1, const F2& f2){
 
  
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;

  static_assert( !f2_traits::in_set, ""  );  
  static_assert( std::is_convertible< 
                  typename f1_traits::out_type,
                  typename f2_traits::in_type>::value, "" );
  
  using reference_out = std::reference_wrapper<const typename f2_traits::out_type>;
  using in  = typename f1_traits::in_type;
  
  return [f1_ = f1, f2_ = f2](const in& r) -> std::vector<reference_out> {
      auto sel = f1_(r);
      std::vector<reference_out> ret;
      for(auto it = sel.begin(); it != sel.end() ; ++it){
        auto aux =  f2_(it->get());
        for(auto it2 = aux.begin(); it2 != aux.end() ; ++it2){
          ret.emplace_back(*it2);
        }
      }
      return ret;
  };
};

/**
 * @brief Creates a new selector that applies the selector f2 to each selected element of f1
 * @param f1 First selector (that selects a set)
 * @param f2 Secpmd selector (input a single element)
 * @note Template for f1 set input and f2 single output
 */
template <typename F1, typename F2,
          std::enable_if_t<selector_func_traits<F1>::in_set >* = nullptr,
          std::enable_if_t<!selector_func_traits<F2>::out_set >* = nullptr>
constexpr auto selector_foreach(const F1& f1, const F2& f2){
 
  
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;

  static_assert( !f2_traits::in_set, ""  );  
  static_assert( std::is_convertible< 
                  typename f1_traits::out_type,
                  typename f2_traits::in_type>::value, "" );
  
  using reference_out = std::reference_wrapper<const typename f2_traits::out_type>;
  using reference_in = std::reference_wrapper<const typename f1_traits::in_type>;
  
  return [f1_ = f1, f2_ = f2](const reference_in& b, const reference_in& e) -> std::vector<reference_out> {
      auto sel = f1_(b,e);
      std::vector<reference_out> ret;
      ret.reserve(size(sel));
      for(auto it = sel.begin(); it != sel.end() ; ++it){
        ret.emplace_back(f2_(it->get()));
      }
      return ret;
  };
};

/**
 * @brief Creates a new selector that applies the selector f2 to each selected element of f1
 * @param f1 First selector (that selects a set)
 * @param f2 Secpmd selector (input a single element)
 * @note Template for f1 set input and f2 set output
 */
template <typename F1, typename F2,
          std::enable_if_t<selector_func_traits<F1>::in_set >* = nullptr,
          std::enable_if_t<selector_func_traits<F2>::out_set >* = nullptr>
constexpr auto selector_foreach(const F1& f1, const F2& f2){
 
  
  using f1_traits      = selector_func_traits<F1>;
  using f2_traits      = selector_func_traits<F2>;

  static_assert( !f2_traits::in_set, ""  );  
  static_assert( std::is_convertible< 
                  typename f1_traits::out_type,
                  typename f2_traits::in_type>::value, "" );
  
  using reference_out = std::reference_wrapper<const typename f2_traits::out_type>;
  using reference_in = std::reference_wrapper<const typename f1_traits::in_type>;
  
  return [f1_ = f1, f2_ = f2](const reference_in& b, const reference_in& e) -> std::vector<reference_out> {
      auto sel = f1_(b,e);
      std::vector<reference_out> ret;
      for(auto it = sel.begin(); it != sel.end() ; ++it){
        auto aux =  f2_(it->get());
        for(auto it2 = aux.begin(); it2 != aux.end() ; ++it2){
          ret.emplace_back(*it2);
        }
      }
      return ret;
  };
};
// END  Single input to set input templates





} // end selector ns
} // End neurostr ns

#endif
