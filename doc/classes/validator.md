---
currentSection: class
currentSubsection: validator
currentItem:
---


# namespace `validator` {#namespace_validator}

Validator namespace contains the validator template class and the prebuilt validators and check functions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``Validator``](#class_validator)    |
`class `[``ValidatorItem``](#class_validator_item)    |
`class `[``check_func_traits``](#struct_check__func__traits)        |
`public const auto is_true` | Dummy. Checks that a given boolean is true
`public const auto is_false` | Dummy. Checks that a given boolean is false
`public const auto empty_string` | Dummy. Checks that a given string is empty
`public template<typename T>`  <br/>`inline auto range_check_factory(T min,T max)` | Range check factory. Checks that a given value is in the range [min, max)
`public const auto neurites_attached_to_soma` | Neurite validator. Checks that neurites are attached to the soma
`public const auto neuron_has_soma` | Neuron validator. Checks that neuron soma is defined
`public const auto no_trifurcations_validator` | Node validator. Checks that the number of descendants of a node is at most 2.
`public const auto zero_length_segments_validator` | Node validator. Checks that the length of the compartment associated to each node is not zero.
`public const auto radius_length_segments_validator` | Node validator. Check that the distance between two consecutive nodes is greater than the sum of their radii.
`public const auto increasing_radius_validator` | Node validator. Checks that the node radius is not increasing.
`public const auto segment_collision_validator` | Node validator. Check that the node compartment don't collide with any other compartment in the reconstruction
`public const auto extreme_angles_validator` | Node validator. Check that the elongation/bifurcation angle are not too high to be plausible
`public inline auto planar_reconstruction_validator_factory(float min)` | Neurite validator. Verifies that neurite reconstruction is not planar by checking that its non-axis aligned box volume is over the minimum value (close to 0)
`public inline auto dendrite_count_validator_factory(unsigned int min,unsigned int max)` | Neuron validator. Checks that the number of dendrites in the neuron is in the range [min,max)
`public inline auto apical_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of apical dendrites in the neuron is not greater than 2
`public inline auto axon_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of axons in the neuron is not greater than 2
`public inline auto linear_branches_validator_factory(float min)` | Branch validator. Verifies that the branch reconstruction is not a prefect straight line by checking that its tortuosity value is not equal to 1
`public inline auto branch_collision_validator_factory(bool ignore_diams)` | Branch validator. Check that the Branch dont collide with any other branch in the neuron

---

# class `Validator` {#class_validator}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  Validator(M measure,C check)` | Creates a validator with given measure and check functions.
`public inline void validate(const Neuron & n)` | Runs the validation for the given Neuron.
`public inline storage_type::const_iterator begin() const` | Begin const bidirectional iterator to the validation results.
`public inline storage_type::const_iterator end() const` | End const bidirectional iterator to the validation results.
`public inline storage_type::size_type size() const` | Returns the number of validated items.
`public inline void set_name(const std::string & s)` | Sets the validation name.
`public inline void set_description(const std::string & s)` | Sets the validation description string.
`public inline bool pass() const` | Check if all validated elements passed the check function.
`public inline std::ostream & toJSON(std::ostream & os,bool failuresOnly) const` | Writes the validator (name and description), the neuron id and the results as a JSON string in the given stream.
`public inline std::ostream & toJSON(std::ostream & os,const std::string & name,const std::string & desc,bool failuresOnly) const` | Writes the validator, the neuron id and the results as a JSON string in the given stream.


## Members

---


### `public inline  Validator(M measure,C check)` {#class_validator_1a2ea05efa57aa1bcb4bb7b7c7f3e8c102}

Creates a validator with given measure and check functions.

#### Parameters
* `measure` Measure function. Should take a single element as imput


* `check` Check function. Should take a single measure value as input





#### Returns
[Validator](#class_validator)

---

### `public inline void validate(const Neuron & n)` {#class_validator_1a3bb743dfaff3fd772115478682c77e11}

Runs the validation for the given Neuron.

#### Parameters
* `n` Neuron to be validated

---

### `public inline storage_type::const_iterator begin() const` {#class_validator_1a68b3697fb5cc756710e80d8b2384e7dc}

Begin const bidirectional iterator to the validation results.

#### Returns
Bidirectional iterator to [ValidatorItem](#class_validator_item)

---

### `public inline storage_type::const_iterator end() const` {#class_validator_1a12ced46941085d69d268c7260d501a9d}

End const bidirectional iterator to the validation results.

#### Returns
Bidirectional iterator to [ValidatorItem](#class_validator_item)

---

### `public inline storage_type::size_type size() const` {#class_validator_1aac32ae7f1163d05eb3670e68e4c1ca19}

Returns the number of validated items.

#### Returns
Number of validated items

---

### `public inline void set_name(const std::string & s)` {#class_validator_1a4cbfc0b4ac1cfa167fd633cd42b0849c}

Sets the validation name.

#### Parameters
* `s` Validation shortname

---

### `public inline void set_description(const std::string & s)` {#class_validator_1a9581bb7ff40d6528510b417f5184aac2}

Sets the validation description string.

#### Parameters
* `s` Validation description

---

### `public inline bool pass() const` {#class_validator_1a026af77c6d04a7e81c0cb170e5b4f444}

Check if all validated elements passed the check function.

#### Returns
True if all elements passed

---

### `public inline std::ostream & toJSON(std::ostream & os,bool failuresOnly) const` {#class_validator_1ad66cfc6465ce75ddfdc7b3ea915ba468}

Writes the validator (name and description), the neuron id and the results as a JSON string in the given stream.

#### Parameters
* `os` Output stream


* `failuresOnly` Write only failing [ValidatorItem](#class_validator_item)





#### Returns
Stream

---

### `public inline std::ostream & toJSON(std::ostream & os,const std::string & name,const std::string & desc,bool failuresOnly) const` {#class_validator_1a9642cbe9cc468782746dd347cf2ec03e}

Writes the validator, the neuron id and the results as a JSON string in the given stream.

#### Parameters
* `os` Output stream


* `name` Validation shortname


* `desc` Validation description


* `failuresOnly` Write only failing [ValidatorItem](#class_validator_item)

#### Returns

 Output stream

---

# class `ValidatorItem` {#class_validator_item}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::reference_wrapper< T > element` | Validated element.
`public V value` | Measure value.
`public bool valid` | Check function value.
`public inline  ValidatorItem()` | Default empty constructor.
`public inline  ValidatorItem(T & el,`[`value_type`](#class_validator_item_1a63c24f7557578f2ee2de9329117e6e99)` val,bool is_valid)` | Creates an item with the given parameters.
`public inline std::string element_id_json() const` | Creates a JSON object with the full ID for the given element.
`public inline std::string element_type() const` | Returns an string with the element name (Neuron, Neurite, Branch or Node)
`public inline std::ostream & toJSON(std::ostream & os) const` | Writes the Item to the given stream as a JSON object.


## Members

---

### `public std::reference_wrapper< T > element` {#class_validator_item_1ae391872de0bdc2ae9f6c41d08325955d}

Validated element.



---

### `public V value` {#class_validator_item_1a16d624a3647be1ca846d2d85850eaab2}

Measure value.



---

### `public bool valid` {#class_validator_item_1a7810f1c3e7f87501682f9211f02ff8d8}

Check function value.



---

### `public inline  ValidatorItem()` {#class_validator_item_1a443d2a678fdc8ab3451162eb149ec924}

Default empty constructor.



---

### `public inline  ValidatorItem(T & el,`[`value_type`](#class_validator_item_1a63c24f7557578f2ee2de9329117e6e99)` val,bool is_valid)` {#class_validator_item_1aefaf2aa192ab5f982d4856937b38b2a4}

Creates an item with the given parameters.

#### Parameters
* `el` Validated element reference


* `val` Measure value


* `is_valid` Check function value

---

### `public inline std::string element_id_json() const` {#class_validator_item_1a2411272581911ccb2909fdd301ef4ece}

Creates a JSON object with the full ID for the given element.

#### Returns
JSON ID Object string

---

### `public inline std::string element_type() const` {#class_validator_item_1a93aa844e2207f1982f8e289d833ce474}

Returns an string with the element name (Neuron, Neurite, Branch or Node)

#### Returns
Element type string

---

### `public inline std::ostream & toJSON(std::ostream & os) const` {#class_validator_item_1ace622c47b152ec2c395bcb1eb47bb629}

Writes the Item to the given stream as a JSON object.

#### Parameters
* `os` Output stream





#### Returns
JSON Object with type, id, value and pass result.


---


# Checks {#checks}

### `public const auto is_true` {#validator_1a128a16765e070295d35571f6d10b0742}

Dummy. Checks that a given boolean is true

---

### `public const auto is_false` {#validator_1afacaa9569f94681110397b10b978e131}

Dummy.

Checks that a given booelan is false

---

### `public const auto empty_string` {#validator_1acb1df86eff8e9f3ad364e1b3c077695b}

Dummy.

Checks that a given string is empty

---

### `public template<typename T>`  <br/>`inline auto range_check_factory(T min,T max)` {#validator_1aed93cdcdc407542ac556b3a69c62ce3e}

Range check factory. Checks that a given value is in the range [min, max)

#### Parameters
* `min` Range minimum


* `max` Range maximum


---

# Prebuilt validators {#prebuilt}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const auto neurites_attached_to_soma` | Neurite validator. Checks that neurites are attached to the soma
`public const auto neuron_has_soma` | Neuron validator. Checks that neuron soma is defined
`public const auto no_trifurcations_validator` | Node validator. Checks that the number of descendants of a node is at most 2.
`public const auto zero_length_segments_validator` | Node validator. Checks that the length of the compartment associated to each node is not zero.
`public const auto radius_length_segments_validator` | Node validator. Check that the distance between two consecutive nodes is greater than the sum of their radii.
`public const auto increasing_radius_validator` | Node validator. Checks that the node radius is not increasing.
`public const auto segment_collision_validator` | Node validator. Check that the node compartment don't collide with any other compartment in the reconstruction
`public const auto extreme_angles_validator` | Node validator. Check that the elongation/bifurcation angle are not too high to be plausible
`public inline auto planar_reconstruction_validator_factory(float min)` | Neurite validator. Verifies that neurite reconstruction is not planar by checking that its non-axis aligned box volume is over the minimum value (close to 0)
`public inline auto dendrite_count_validator_factory(unsigned int min,unsigned int max)` | Neuron validator. Checks that the number of dendrites in the neuron is in the range [min,max)
`public inline auto apical_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of apical dendrites in the neuron is not greater than 2
`public inline auto axon_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of axons in the neuron is not greater than 2
`public inline auto linear_branches_validator_factory(float min)` | Branch validator. Verifies that the branch reconstruction is not a prefect straight line by checking that its tortuosity value is not equal to 1
`public inline auto branch_collision_validator_factory(bool ignore_diams)` | Branch validator. Check that the Branch dont collide with any other branch in the neuron

---

### `public const auto neurites_attached_to_soma` {#prebuilt_1a78eeeb043ae6bcf33355dd2754f05dc8}

Neurite validator. Checks that neurites are attached to the soma

---

### `public const auto neuron_has_soma` {#prebuilt_1aaf136d622198e95e7efe541ca484a9d6}

Neuron validator. Checks that neuron soma is defined

---

### `public const auto no_trifurcations_validator` {#prebuilt_1a0d795a5b610517517dad4ba5fa3281bc}

Node validator. Checks that the number of descendants of a node is at most 2.

---

### `public const auto zero_length_segments_validator` {#prebuilt_1a9c69478babbe3ea515c49fa04d9c66d7}

Node validator. Checks that the length of the compartment associated to each node is not zero.

---

### `public const auto radius_length_segments_validator` {#prebuilt_1a3f03c313d1982c1d71827b3ed57d0cc1}

Node validator. Check that the distance between two consecutive nodes is greater than the sum of their radii.

---

### `public const auto increasing_radius_validator` {#prebuilt_1abd8929d37cf263276eca4b64dae686c9}

Node validator. Checks that the node radius is not increasing.

---

### `public const auto segment_collision_validator` {#prebuilt_1aef6d8066ae78ef9a0b798ce9319837aa}

Node validator. Check that the node compartment don't collide with any other compartment in the reconstruction

---

### `public const auto extreme_angles_validator` {#prebuilt_1a7b0bc777b0f06fac95cd200c49b839c7}

Node validator. Check that the elongation/bifurcation angle are not too high to be plausible

---

### `public inline auto planar_reconstruction_validator_factory(float min)` {#prebuilt_1a83541495d8df9fa3234cf79a8599feeb}

Neurite validator. Verifies that neurite reconstruction is not planar by checking that its non-axis aligned box volume is over the minimum value (close to 0)

---

### `public inline auto dendrite_count_validator_factory(unsigned int min,unsigned int max)` {#prebuilt_1a228addaee18ae1e77d231bc65b9f0c05}

Neuron validator. Checks that the number of dendrites in the neuron is in the range [min,max)

---

### `public inline auto apical_count_validator_factory(bool strict)` {#prebuilt_1a2b2f9e14c1b2407ca096e3173c9cd655}

Neuron validator. Checks that the number of apical dendrites in the neuron is not greater than 2

#### Parameters

* `strict` If true, Neurons with no apical dendrite are rejected

---

### `public inline auto axon_count_validator_factory(bool strict)` {#prebuilt_1a93ccef0d48f3cbe568f51e3bc9e9e799}

Neuron validator. Checks that the number of axons in the neuron is not greater than 2

#### Parameters

* `strict` If true, Neurons with no axon are rejected

---

### `public inline auto linear_branches_validator_factory(float min)` {#prebuilt_1a6f0ff22924f955b1df400bf0fbc650b6}

Branch validator.Verifies that the branch reconstruction is not a prefect straight line by checking that its tortuosity value is not equal to 1

#### Parameters

* `min` Minimum accepted tortuosity value

---

### `public inline auto branch_collision_validator_factory(bool ignore_diams)` {#prebuilt_1a05c24c03d592c4fc0b77b158da740f2f}

Branch validator. Check that the Branch dont collide with any other branch in the neuron

#### Parameters
* `ignore_diams` If true, node diameter value are ignored
