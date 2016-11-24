---
currentSection: class
currentSubsection: selector
currentItem:
---
# namespace `selector` {#namespace_selector}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``selector_func_traits<F>``](#struct_selector__func__traits)        | Selector function traits.
`struct `[``type_chooser<bool, T>``](#struct_type__chooser)        | Trait that extracts the selector i/o type.
`public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto compose_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector composition.
`public template<typename F,>`  <br/>`inline constexpr auto selector_out_single_to_set(const F & f)` | Converts a selector with single output in one with set output
`public template<typename F>`  <br/>`inline constexpr auto selector_in_single_to_set(const F & f)` | Converts a selector with single output in one with set output
`public template<typename F1,typename F2>`  <br/>`inline constexpr auto selector_foreach(const F1 & f1,const F2 & f2)` | Creates a new selector that applies the selector f2 to each selected element of f1.
`public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto union_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector union.
`public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto intersection_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector intersection.
`public template<typename F1,typename F2>`  <br/>`inline constexpr auto diff_selector_factory(const F1 & f_1,const F2 & f_2)` | Assymetric difference.

## Members

### `struct `[``type_chooser<bool,T>``](#struct_type__chooser) {#struct_type__chooser}

Trait that extracts the selector i/o type. The first template parameter is a set indicator. If true, T is assumed to be an iterator

```cpp
struct type_chooser {
  using type = ...
};
```

---

### `struct `[``selector_func_traits<F>``](#struct_selector__func__traits) {#struct_selector__func__traits}

Selector function traits. Extracts selector arity, input and output types

```cpp
template <typename F> struct selector_func_traits {
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  constexpr static bool out_set = (traits::is_vector<typename base_traits::result_type>::value);
  using out_type = typename type_chooser<out_set, typename base_traits::result_type>::type;
  using base_in_type = typename std::remove_reference_t<std::remove_const_t<typename base_traits::template arg<0>>>;
  using in_type = typename type_chooser<in_set, base_in_type>::type;
};
```

---

### `public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto compose_selector(const F1 & f1,const F2 & f2,Funcs... fns)` {#classneurostr_1_1selector_1a2f1af7649d3e014fc359364326c1e4e6}

Recursive template for selector composition.

#### Parameters
* `f1` First function


* `f2` Second function


* `fns` Rest


#### Returns
f1 o f2 o rest

---

### `public template<typename F>`  <br/>`inline constexpr auto selector_out_single_to_set(const F & f)` {#classneurostr_1_1selector_1adbc114e99173928f0f9e9cf2f9e5bec5}

Converts a selector with single output in one with set output.


---

### `public template<typename F>`  <br/>`inline constexpr auto selector_in_single_to_set(const F & f)` {#classneurostr_1_1selector_1a2bb476f7a789709890f24024c1c3f471}

Converts a selector with single output in one with set output

---

### `public template<typename F1,typename F2>`  <br/>`inline constexpr auto selector_foreach(const F1 & f1,const F2 & f2)` {#classneurostr_1_1selector_1a728c2b0bab05b1da545a47860d6ca13c}

Creates a new selector that applies the selector f2 to each selected element of f1.

#### Parameters
* `f1` First selector (that selects a set)


* `f2` Second selector (input a single element)

---

### `public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto union_selector(const F1 & f1,const F2 & f2,Funcs... fns)` {#classneurostr_1_1selector_1adb8be89d8e7e7961e71fb436813fad66}

Recursive template for selector union.

Base case.
#### Parameters
* `f1` First function


* `f2` Second function

#### Returns
Join selector

---

### `public template<typename F1,typename F2,typename... Funcs>`  <br/>`inline constexpr auto intersection_selector(const F1 & f1,const F2 & f2,Funcs... fns)` {#classneurostr_1_1selector_1a8bf989ed64d5df2dd1cd2a7f5bb970fe}

Recursive template for selector intersection.

Base case.
#### Parameters
* `f1` First function


* `f2` Second function

#### Returns
Intersection selector

---

### `public template<typename F1,typename F2>`  <br/>`inline constexpr auto diff_selector_factory(const F1 & f_1,const F2 & f_2)` {#classneurostr_1_1selector_1a778a354bac0e25f8fe3d2bf2402bb9f6}

Asymmetric difference.

#### Parameters
* `f_1` Base set


* `f_2` Difference set

#### Returns
Difference selector


---

# Prebuilt Selector Functions

Go to the [prebuilt Selectors section](../selectors/prebuilt.html)
