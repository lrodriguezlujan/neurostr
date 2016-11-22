---
currentSection: validation
currentSubsection:
currentItem:
---
# Neuron validation

---

## Validator {#validator}

The [validator class template](classes/validator.html#class_validator) in the key component to validate a reconstruction. The validator works at neuron level, that is, it validates a neuron or its sub-components. To create a new validator you just need a [Measure](measures.html) that takes a single element (Neuron, Neurite, Branch or Node) as input and a [Check](#checks) function that accepts the measure output value.

```cpp
template <typename M, typename C>
class Validator {
  Validator(M measure, C check){}
}
```

The measure is applied to every Neurite/Branch/Node in the Neuron or to the neuron itself, and then the output value is given to the check function, that determines whether the value pass the check (returning a true boolean value) or not. This is stored in a [ValidatorItem](classes/validator.html#class_validator_item) structure within the validator.

```cpp
template <typename M, typename C>
void Validator<M,C>::validate(const Neuron& n)
```

The [ValidatorItem](classes/validator.html#class_validator_item) is basically a container with:
- *element*: A reference to the validated element
- *value*: The measure value
- *valid*: The check function evaluated over *value*

There are a bunch of [predefined check functions](classes/validator.html#checks) and [validators](classes/validator.html#predefined) included in the library. All validations described in the [Predefined validations](classes/validator.html#predefined) sections are included in the [Validator tool](tools.html#validator) bundled with the library. Details about the [validator class template](classes/validator.html#class_validator) and the [ValidatorItem](classes/validator.html#class_validator_item) are available in the [validator namespace](classes/validator.html) documentation.

The Validator class and the ValidatorItem class as well have a `toJSON` method that writes the validation results in a easily readable JSON format (the [Validator tool](tools.html#validator) output uses this function). The output specifications are detailed [at the end of this section](#output).

---

## Checks {#checks}

Any function that takes a single value as input and outputs a boolean qualifies as check. The only restriction is that the check function input must match the measure function output. There are a couple of [simple check functions](classes/validator.html#checks) already implemented in the library:

### `public const auto is_true` {#validator_1a128a16765e070295d35571f6d10b0742}

Checks that a given boolean is true

---

### `public const auto is_false` {#validator_1afacaa9569f94681110397b10b978e131}

Checks that a given boolean is false

---

### `public const auto empty_string` {#validator_1acb1df86eff8e9f3ad364e1b3c077695b}

Checks that a given string is empty

---

### `public template<typename T>`  <br/>`inline auto range_check_factory(T min,T max)` {#validator_1aed93cdcdc407542ac556b3a69c62ce3e}

Range check factory. Checks that a given value is in the range [min, max)

#### Parameters
* `min` Range minimum


* `max` Range maximum

---

## JSON Output {#output}

The `toJSON` method in the [validator class template](classes/validator.html#class_validator) writes the results into an output stream as a JSON Object with the following fields:
- *name*: The name given to the validator. Usually a short test name. e.g. "Planar neurite validation"
- *description*: Test description. e.g. "Fails if the non-axis aligned box volume of the neurite is lower than predefined threshold"
- *neuron_id*: The validated neuron ID
- *pass*: Boolean. True if the neuron (or all its sub-elements) passed the test
- *results*: An array of Validation Items

```json
{
        "description": "Fails when the branch tortuosity falls below 1.010000",
        "name": "Linear branch validator",
        "neuron_id": "simple_tree",
        "pass": false,
        "results": [ ]
}
```

In turn, a Validation Item is also written as a JSON Objects with:
- *id*: A JSON object that identifies the tested element.
- *type*: A string that identifies the type of the tested element. It can be "Neuron", "Neurite", "Branch" or "Node"
- *value*: The measure value.
- *pass*: The result of the check function over the measure value.

And the ID object has:
- *neuron*: The Neuron name string.
- *neurite*: The Neurite ID (int). Present when the element type is Node, Branch or Neurite.
- *branch*: The Branch ID as a string. Present when the element type is Node or Branch.
- *node*: The Node ID (int). Present only if the element type is Node

```json
{
                "id": {
                    "branch": "1-2",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
}
```
