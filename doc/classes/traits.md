---
currentSection: class
currentSubsection: traits
currentItem:
---

# namespace `traits` {#namespace_traits}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`Trait `[``function_traits``](#struct_traits_function__traits)    | Extract basic information from a functor like out type, arg type, arity...
`Trait `[``is_vector``](#struct_traits_is__vector)    | Is vector template trait
`Trait `[``is_base_of_template``](#struct_traits_is_base_of_template)    | Is base of template base trait.

---

# Trait `function_traits` {#struct_traits_function__traits}
Extracts basic information from a functor like out type, arg type, arity...

```cpp
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
```

---

# Trait `is_vector` {#struct_traits_is__vector}
Trait that checks if the given type is a vector.

```cpp
template <typename T, typename _ = void> struct is_vector {
  static const bool value;
};
```

---
# Trait `is_base_of_template` {#struct_traits_is_base_of_template}

Checks whether C is base of T

```cpp
template <typename T, template <typename...> class C>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()))
```
