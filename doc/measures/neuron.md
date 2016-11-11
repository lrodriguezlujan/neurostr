---
currentSection: measures
currentSubsection: predef
currentItem: neuron
---
# Neuron selectors
text

### Neuron has soma <a id="hassoma"> </a>

**Function:** `has_soma`

**Description:** Returns true if the neuron has at least one soma node.

**Output:** Boolean flag. True if the [Soma] is defined in the [Neuron]

**Details:** `has_soma` measure just calls the `Neuron.has_soma()` member function which checks if the number of soma points in the neuron is greater than 0.

---

### Neurite count <a id="neurite_count"> </a>

**Function:** `neuron_neurite_count`

**Description:** Returns the number of [Neurite]s in the [Neuron].

**Output:** Non-negative integer value. The number of [Neurite]s (of any type) in the [Neuron].

---

### Neurite type count <a id="neurite__type_count"> </a>

**Function:** `neuron_type_counter` (factory method)

**Parameters:** **type** - *NeuriteType* - Neurite type.

**Description:** Returns the number of [Neurite]s in the [Neuron] of certain type.

**Instances:**
  - `neuron_dendrite_counter` Counts the number of dendrites in the [Neuron]
  - `neuron_axon_counter` Counts the number of axons in the [Neuron]
  - `neuron_apical_counter` Counts the number of apical dendrites in the [Neuron]

**Output:** Non-negative integer value. The number of [Neurite]s of type *type* in the [Neuron].

---

### Soma surface area <a id="soma_surface"> </a>

**Function:** `soma_surface`

**Description:** Returns the [Soma] surface area under spherical shape assumption.

**Output:** Non-negative real value. The computed soma surface area.

**Details:** If there are several soma points, the computed area is the surface of the sphere centered at the soma barycenter with radius the average distance from the barycenter to the external border of the sphere. Otherwise, for a sigle-point [Soma], the sphere surface area is computed.

---

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
[Soma]: ../goals_architecture.html#soma
