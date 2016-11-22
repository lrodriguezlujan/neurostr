#ifndef NEUROSTR_SELECTOR_SELECTOR_TRAITS_H_
#define NEUROSTR_SELECTOR_SELECTOR_TRAITS_H_

namespace neurostr {
namespace selector {

/**
 * @brief Selector reference template with std::reference_wrapper
 */
template <typename T>
using selector_reference = std::reference_wrapper<T>;

/**
 * @brief Selector const reference template with std::reference_wrapper
 */
template <typename T>
using const_selector_reference = std::reference_wrapper<const T>;

/**
 * @brief Iterator template over a selected set
 */
template <typename T>
using selector_iterator = typename std::vector<selector_reference<T>>::iterator;  

/**
 * @brief Iterator template over a selected set
 */
template <typename T>
using const_selector_iterator = typename std::vector<const_selector_reference<T>>::iterator;  

/**
 * @brief Reference to Neuron
 */
using neuron_reference  = selector_reference<Neuron>;

/**
 * @brief Reference to Neurite
 */
using neurite_reference  = selector_reference<Neurite>;

/**
 * @brief Reference to Branch
 */
using branch_reference  = selector_reference<Branch>;

/**
 * @brief Reference to Node
 */
using node_reference  = selector_reference<Node>;

/**
 * @brief Constant Reference to Neuron
 */
using const_neuron_reference  = const_selector_reference<Neuron>;

/**
 * @brief Constant Reference to Neurite
 */
using const_neurite_reference  = const_selector_reference<Neurite>;

/**
 * @brief Constant Reference to Branch
 */
using const_branch_reference  = const_selector_reference<Branch>;

/**
 * @brief Constant Reference to Node
 */
using const_node_reference  = const_selector_reference<Node>;

/**
 * @struct type_chooser
 * @brief Trait that extracts the selector i/o type. The first boolean template
 * parameter is a set indicator. If true, T is assumed to be an iterator
 */
template <bool, typename T>
struct type_chooser {
  using type = std::remove_reference_t<std::remove_const_t<T>>; // False, is a reference
};

template <typename T>
struct type_chooser<true,T> {
  using type = std::remove_const_t<typename T::value_type::type>; // True: Is an iterator to a wrapped reference
};

/**
 * @struct selector_func_traits
 * @brief Selector function traits. Extracts selector arity, input and output types
 */
template <typename F> struct selector_func_traits {
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  constexpr static bool out_set = (traits::is_vector<typename base_traits::result_type>::value);
  //constexpr static bool is_const = 

  using out_type = typename type_chooser<out_set, typename base_traits::result_type>::type;

  // In "set" selector funcs accept iterators!
  using base_in_type = typename std::remove_reference_t<std::remove_const_t<typename base_traits::template arg<0>>>;
  using in_type = typename type_chooser<in_set, base_in_type>::type;
};

} // end selector ns
} // End neurostr ns


#endif
