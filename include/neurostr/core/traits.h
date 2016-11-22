#ifndef NEUROSTR_CORE_TRAITS_H_
#define NEUROSTR_CORE_TRAITS_H_

#include <vector>
#include <tuple>

namespace neurostr {
namespace traits {

  /**
   * @brief Check if template C is base of Ts..
   * @return True type if C is base of T
   */
template <template <typename...> class C, typename... Ts> std::true_type is_base_of_template_impl(const C<Ts...>*);

/**
* @brief Base false case for the template
* @return False type if C is base of T
*/
template <template <typename...> class C> std::false_type is_base_of_template_impl(...);

/**
 * @brief Check if template C is base of T
 * @return true o false type
 */
template <typename T, template <typename...> class C>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));


/**
 * @brief Base false trait is vector
 */
template <typename T, typename _ = void> struct is_vector {
  static const bool value = false;
};

/**
 * @brief Traits that checks if T is a vector instance
 */
template <class T> struct is_vector<std::vector<T>> {
  static bool const value = true;
};


/**
 * @class function_traits
 * @brief Extract basic information from a fuctor like out type, arg type, arity...
 */
template <typename T> struct function_traits : public function_traits<decltype(&T::operator())> {};
// For generic types, directly use the result of the signature of its 'operator()'
template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const>
    // we specialize for pointers to member function
    {
  enum {
    arity = sizeof...(Args)
  };
  // arity is the number of arguments.

  template <int i> using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;

  typedef ReturnType result_type;
};



}  // traits
}  // neurostr

#endif
