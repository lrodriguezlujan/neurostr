---
currentSection: class
currentSubsection: measure
currentItem:
---
# namespace `measure` {#namespace_measure}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[``aggregate``](#namespace_aggregate)    | Namespace that contains aggregate-related functions and traits
`template <typename Fn> auto measureEach(const Fn& f)` | Converts a single-input measure into a set measure that applies the original measure to each element of the input set
`template <typename Fn, typename Aggr> auto measureEachAggregate(const Fn& f, const Aggr& aggr)` | Converts a single-input measure into a set measure that applies the original measure to each element of the input set and then aggregates the  output.
`template <typename S, typename M> auto selectorMeasureCompose(const S& selector, const M& measure)` | Creates a new measure as result of the composition of the selector and the measure (M o S). Types and arity must match
`template <typename... Measures> auto createMeasureTuple(const Measures&... measures )` | Creates a measure that applies several measures to the same input and returns their result in a tuple
`template <typename F> struct measure_func_traits` |Measure function traits. Extracts input type, input arity and output type.

## Members

### `public template<typename Fn>`  <br/>`auto measureEach(const Fn& f)` {#measure_each}

Convert a single-input measure into a set measure that applies the original measure to each element of the input set

#### Parameters
* `f` Original single-input measure


#### Returns
Set input measure

---

### `public template<typename Fn, typename Aggr>`  <br/>`auto measureEachAggregate(const Fn& f, const Aggr& aggr)` {#measure_each_aggregate}

Converts a single-input measure into a set measure that applies the original measure to each element of the input set and then aggregates the  output.

#### Parameters
* `f` Original single-input measure


* `aggr` Aggregator function


#### Returns
Set-input - aggregated output measure

---

### `public template<typename S, typename M>`  <br/>`auto selectorMeasureCompose(const S& selector, const M& measure)` {#selector_measure}

Creates a new measure as result of the composition of the selector and the measure (M o S). Types and arity must match

#### Parameters
* `selector` Selector

* `measure` Measure

#### Returns
Composed measure

---

### `public template<typename... Measures>`  <br/>`auto createMeasureTuple(const Measures&... measures )` {#measure_tuple}

Creates a measure that applies several measures to the same input and returns their result in a tuple

#### Parameters
* `measures` Measures to combine in the tuple

#### Returns
Measure with same input and tuple output

---

# Trait `measure_func_traits<F>` {#trait_measure__func__traits}

Measure function traits. Extracts input type, input arity and output type.

```cpp
template <typename F> struct measure_func_traits {  
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  using out_type = typename base_traits::result_type;

  using base_in_type = typename std::remove_reference_t<
                          typename base_traits::template arg<0>>;
  using in_type = typename detail::type_chooser<in_set, base_in_type>::type;
};
```

---

# namespace `aggregate` {#namespace_aggregate}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``aggr_func_traits``](#aggr__func__traits)        | Aggregator function traits. Extracts input and output types

## Members

### Trait `struct `[``aggr_func_traits``](#aggr__func__traits) {#aggr__func__traits}

Aggregator function traits. Extracts input and output types from the F function

```cpp
template <typename F> struct aggr_func_traits {

  using base_traits = neurostr::traits::function_traits<F>;

  using out_type = typename base_traits::result_type;
  using base_in_type = typename std::remove_const_t<std::remove_reference_t<
                          typename base_traits::template arg<0>>>;
  using in_type = typename base_in_type::value_type;
};
```

# Predefined Measure & Aggregate Functions

Go to the [predefined function section](../measures/predefined.html)
