#ifndef NEUROSTR_SELECTOR_SELECTOR_TRAITS_H_
#define NEUROSTR_SELECTOR_SELECTOR_TRAITS_H_

namespace neurostr {
namespace selector {

template <typename T>
using selector_reference = std::reference_wrapper<T>;

template <typename T>
using const_selector_reference = std::reference_wrapper<const T>;

template <typename T>
using selector_iterator = typename std::vector<selector_reference<T>>::iterator;  

template <typename T>
using const_selector_iterator = typename std::vector<const_selector_reference<T>>::iterator;  

using neuron_reference  = selector_reference<Neuron>;
using neurite_reference  = selector_reference<Neurite>;
using branch_reference  = selector_reference<Branch>;
using node_reference  = selector_reference<Node>;

using const_neuron_reference  = const_selector_reference<Neuron>;
using const_neurite_reference  = const_selector_reference<Neurite>;
using const_branch_reference  = const_selector_reference<Branch>;
using const_node_reference  = const_selector_reference<Node>;

template <bool, typename T>
struct type_chooser {
  using type = std::remove_reference_t<std::remove_const_t<T>>; // False, is a reference
};

template <typename T>
struct type_chooser<true,T> {
  using type = std::remove_const_t<typename T::value_type::type>; // True: Is an iterator to a wrapped reference
};

// Selector func traits
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
