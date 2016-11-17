---
currentSection: measures
currentSubsection:
currentItem:
---
# Measures

Measures are functions that take a single reference to an [element of a neuron](goals_architecture.html) or a set of them and compute some output value, the measure. We can distinguish between single and set measures, depending on whether they take one or more references as input. Single elements references (e.g. a single Node) are simply C++ references, whereas sets are `std::vector` of `std::reference_wrapper`.

All classes, functions, etc. related to selectors are defined in the `neurostr::measure` namespace. You can include their headers individually or take them all by adding the header file `measure.h`

Measures are intended to be combined with [Selectors](selectors.html) and [Aggregators](#aggregators) to create complex and meaningful measures with low coding effort. You can implement your own measures and, if they have the adequate signature, use them as any other predefined measure.

## Predefined <a id="predef"></a>

NeuroSTR includes a huge library of predefined measures some new, others already presented in the scientific literature or implemented in existing neuroanatomy tools.

Predefined measures are organized in the same way as [Selectors](selectors.html), by their input element type: all measure functions that take either a single node or a node set as input fall into the *Node* category. You can find more details about each measure by clicking on their name.

You might notice (and it seems odd) that there are very few Neurite and Neuron measures, but it is on purpose. Since we can use [Selectors](selectors.html) and [Aggregators](#aggregators) along with measures to create new measures, we focus on defining "low level" measures, that can be use to create "high level measures". Check the [Create a measure](#create) to see a simple example of this.

### [Node Measures](measures/node.html)

- [X,Y,Z component](measures/node.html#component)
- [Radius, Diameter](measures/node.html#radius)
- [Centrifugal order](measures/node.html#order)
- [Distance to parent](measures/node.html#parent_length)
- [Compartment volume](measures/node.html#volume)
- [Compartment surface](measures/node.html#surface)
- [Compartment section area](measures/node.html#section)
- [Local Hillman taper rate](measures/node.html#hillman)
- [Local Burker taper rate](measures/node.html#burker)
- [Distance to root](measures/node.html#rootdist)
- [Distance to soma](measures/node.html#somadist)
- [Path length to root](measures/node.html#rootpath)
- [Number of descendants](measures/node.html#desccount)
- [Non-aligned minimum box volume](measures/node.html#boxvol)
- [Vector to parent](measures/node.html#parentvector)
- [Local bifurcation angle](measures/node.html#localbif)
- [Local elongation angle](measures/node.html#localelong)
- [Extreme angle](measures/node.html#extreme)
- [Local orientation](measures/node.html#localorientation)
- [In terminal branch](measures/node.html#interminalbranch)
- [Distance to closest segment](measures/node.html#distclosest)
- [Fractal dimension](measures/node.html#fractal)

 ---

### [Branch Measures](measures/branch.html)

- [Hillman taper rate](measures/branch.html#hillman)
- [Burker taper rate](measures/branch.html#burker)
- [Tortuosity](measures/branch.html#tortuosity)
- [Node count](measures/branch.html#size)
- [Branch index](measures/branch.html#index)
- [Centrifugal order](measures/branch.html#order)
- [Child diameter ratio](measures/branch.html#childdimratio)
- [Parent-Child diameter ratio](measures/branch.html#parentchildiamratio)
- [Partition asymmetry](measures/branch.html#partition)
- [Rall power fit](measures/branch.html#rall)
- [Pk](measures/branch.html#pk)
- [Hillman threshold](measures/branch.html#hillman_threshold)
- [Local bifurcation angle](measures/branch.html#localbif)
- [Remote bifurcation angle](measures/branch.html#remotebif)
- [Local bifurcation angle](measures/branch.html#localbif)
- [Remote bifurcation angle](measures/branch.html#remotebif)
- [Local tilt angle](measures/branch.html#localtilt)
- [Remote tilt angle](measures/branch.html#remotetilt)
- [Local plane vector](measures/branch.html#localplane)
- [Remote plane vector](measures/branch.html#remoteplane)
- [Local torque angle](measures/branch.html#localtorque)
- [Remote torque angle](measures/branch.html#remotetorque)
- [Length](measures/branch.html#length)
- [Intersects](measures/branch.html#intersects)

---

### [Neurite Measures](measures/neurite.html)

- [Root is soma](measures/neurite.html#rootsoma)

---

### [Neuron Measures](measures/neuron.html)

- [Has soma](measures/neuron.html#hassoma)
- [Neurite count](measures/neuron.html#neurite_count)
- [Neurite type count](measures/neuron.html#neurite_type_count)
- [Soma surface](measures/neuron.html#soma_surface)

---

### [Generic Measures](measures/generic.html)

- [Set size](measures/generic.html#set)

---

###[L-measure Measures](measures/lmeasure.html)

- [Soma surface](measures/lmeasure.html#somasurface)
- [Number of stems](measures/lmeasure.html#nstems)
- [Number of bifurcations](measures/lmeasure.html#nbifs)
- [Number of branches](measures/lmeasure.html#nbranches)
- [Number of terminal tips](measures/lmeasure.html#nterminals)
- [Width, Height and Depth](measures/lmeasure.html#width)
- [Diameter](measures/lmeasure.html#diameter)
- [Diameter power](measures/lmeasure.html#diameterpow)
- [Compartment length](measures/lmeasure.html#length)
- [Branch length](measures/lmeasure.html#branchlength)
- [Compartment surface](measures/lmeasure.html#surface)
- [Branch surface](measures/lmeasure.html#branchsurface)
- [Compartment section area](measures/lmeasure.html#section_area)
- [Compartment volume](measures/lmeasure.html#volume)
- [Branch volume](measures/lmeasure.html#branch_volume)
- [Distance to root](measures/lmeasure.html#rootdist)
- [Path length to root](measures/lmeasure.html#rootpath)
- [Branch centrifugal order](measures/lmeasure.html#branchorder)
- [Node terminal degree](measures/lmeasure.html#terminaldegree)
- [Branch terminal degree](measures/lmeasure.html#branch_terminaldegree)
- [Taper 1: Burker taper rate](measures/lmeasure.html#burker)
- [Taper 2: Hillman taper rate](measures/lmeasure.html#hillman)
- [Contraction](measures/lmeasure.html#contraction)
- [Fragmentation](measures/lmeasure.html#fragmentation)
- [Partition asymmetry](measures/lmeasure.html#partition_asymmetry)
- [Rall's power](measures/lmeasure.html#rall)
- [Pk fitted value](measures/lmeasure.html#pkfit)
- [Pk classic and squared](measures/lmeasure.html#pkclassic)
- [Local bifurcation amplitude](measures/lmeasure.html#local_bif)
- [Remote bifurcation amplitude](measures/lmeasure.html#remote_bif)
- [Local bifurcation tilt](measures/lmeasure.html#local_tilt)
- [Remote bifurcation tilt](measures/lmeasure.html#remote_tilt)
- [Local bifurcation torque](measures/lmeasure.html#local_torque)
- [Remote bifurcation_torque](measures/lmeasure.html#remote_torque)
- [Terminal bifurcation diameter](measures/lmeasure.html#terminaldiam)
- [Hillman threshold](measures/lmeasure.html#hillman_threshold)
- [Fractal dimension](measures/lmeasure.html#fractal_dimension)

---


## Aggregators <a id="aggregators"></a>

Aggregators are just functions that compute an aggregate value (e.g the mean) from a set of measures. They are an easy way to get summary values for certain "low level" measures at "high level" elements (Neuron and Neurite). For example, we might want to compute the average branch length in a neurite or neuron, that can be done easily with aggregator functions. Of course aggregators are simple wrappers over well known standard library functions, but they allow us to detect coding errors early in compile time instead of provoking runtime errors.

These are the aggregator functions and factory functions included in the library:

### Sum  <a id="sum"></a>

**What it does:** Adds up all the values in the given set starting at *zero*.

**Parameters:** *zero* - Starting value

**Function signature:** `(const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T `

**Factory function signature:** `sum_aggr_factory(T zero)`

---

### Average and Standard deviation <a id="mean"></a>


**What it does:** Computes the average and optionally the standard deviation of the given set of values.

**Parameters:** *zero* - Zero value

#### Mean only

**Factory function signature:** `avg_aggr_factory(T zero)`

**Function signature:** `(const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T `

#### With standard deviation

**Factory function signature:** `mean_sd_factory(T zero)`

**Function signature:** `(const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> std::array<T,2>`

---

### Maximum and Minimum <a id="max"></a>

**What it does:** Returns the maximum/minimum value in the given set

#### Maximum

**Function signature:** `max = [](const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T`

#### Minimum

**Function signature:** `min = [](const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T`

---

### Median <a id="range"></a>

**What it does:** Computes the median of the given set

**Function signature:** `median = [](const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T`

---

### Range <a id="range"></a>

**What it does:** Computes the value difference between the set maximum and minimum values

**Function signature:** `range_length = [](const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> T`

---

### Summary <a id="summary"></a>

**What it does:** Computes sum, min, max, median, mean and standard deviation for the given set of values. It returns them in a structure *aggr_pack* that contains those fields.

**Parameters:** *zero* - Zero value

**Function signature:** `(const detail::iterator_type<U>& b, const detail::iterator_type<U>& e) -> aggr_pack<U,T>`

**Factory function signature:** `all_aggr_factory(T zero)`

---

## Operations <a id="operations"></a>

### Measure each <a id="each"></a>

**What it does:** Transforms a measure that that takes a single element in one that takes an element set. As consequence the resultant measure outputs a vector of values.

**Restrictions:** The given measure *f* must take a single element as input

**Function signature:** `measureEach(const Fn& f)`

### Measure each and aggregate <a id="eachaggr"></a>

**What it does:** Transforms a measure that that takes a single element in one that takes an element set and then applies an aggregator function over the resultant set of values.

**Restrictions:**
  - The given measure *f* must take a single element as input
  - The aggregation function *aggr* must be compatible with the measure outut type

**Function signature:** `measureEachAggregate(const Fn& f, const Aggr& aggr)`

### Selector composition <a id="composition"></a>

**What it does:** Applies the given measure to the selector output, creating a new measure with different input (actually, the selector's input) but same output.

**Restrictions:**
  - The given measure *measure* input signature must match selector's output

**Function signature:** `selectorMeasureCompose(const S& selector, const M& measure)`

### Measure tuple <a id="tuple"></a>

**What it does:** Applies several measures to the same element(s) and returns the result in a tuple. This saves computation time if the element selection procedure is time consuming.

**Restrictions:**
  - The given measures *measures* must have the same input signature

**Function signature:** `createMeasureTuple(const Measures&... measures )`

## [L-measure](http://cng.gmu.edu:8080/Lm/) measures <a id="create"></a>

## Create a measure <a id="create"></a>

### Easy level: Neuron average branch length

TO-DO

### Intermediate level: Neuron average branch fractal dimension

TO-DO
