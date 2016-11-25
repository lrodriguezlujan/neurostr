---
currentSection: measures
currentSubsection:
currentItem:
---
# Measures

Measures are functions that take a single reference to an [element of a neuron](data_model.html) or a set of them and compute some output value, the measure. We can distinguish between single and set measures, depending on whether they take one or more references as input. Single elements references (e.g. a single Node) are simply C++ references, whereas sets are `std::vector` of `std::reference_wrapper`.

All classes, functions, etc. related to selectors are defined in the `neurostr::measure` namespace. You can include their headers individually or take them all by adding the header file `measure.h`

Measures are intended to be combined with [Selectors](selectors.html) and [Aggregators](#aggregators) to create complex and meaningful measures with low coding effort. You can implement your own measures and, if they have the adequate signature, use them as any other prebuilt measure.

## Prebuilt measures <a id="predef"></a>

NeuroSTR includes a huge library of prebuilt measures some new, others already presented in the scientific literature or implemented in existing neuroanatomy tools.

Prebuilt measures are organized in the same way as [Selectors](selectors.html), by their input element type: all measure functions that take either a single node or a node set as input fall into the *Node* category. You can find more details about each measure by clicking on their name.

You might notice (and it seems odd) that there are very few Neurite and Neuron measures, but it is on purpose. Since we can use [Selectors](selectors.html) and [Aggregators](#aggregators) along with measures to create new measures, we focus on defining "low level" measures, that can be use to create "high level measures". Check the [Create a measure](#create) to see a simple example of this.

### [Node Measures](measures/prebuilt.html#node)

- [X,Y,Z component](measures/prebuilt.html#node_component)
- [Radius, Diameter](measures/prebuilt.html#node_radius)
- [Centrifugal order](measures/prebuilt.html#node_order)
- [Distance to parent](measures/prebuilt.html#node_parent_length)
- [Compartment volume](measures/prebuilt.html#node_volume)
- [Compartment surface](measures/prebuilt.html#node_surface)
- [Compartment section area](measures/prebuilt.html#node_section)
- [Local Hillman taper rate](measures/prebuilt.html#node_hillman)
- [Local Burker taper rate](measures/prebuilt.html#node_burker)
- [Distance to root](measures/prebuilt.html#node_rootdist)
- [Distance to soma](measures/prebuilt.html#node_somadist)
- [Path length to root](measures/prebuilt.html#node_rootpath)
- [Number of descendants](measures/prebuilt.html#node_desccount)
- [Non-aligned minimum box volume](measures/prebuilt.html#node_boxvol)
- [Vector to parent](measures/prebuilt.html#node_parentvector)
- [Local bifurcation angle](measures/prebuilt.html#node_localbif)
- [Local elongation angle](measures/prebuilt.html#node_localelong)
- [Extreme angle](measures/prebuilt.html#node_extreme)
- [Local orientation](measures/prebuilt.html#node_localorientation)
- [In terminal branch](measures/prebuilt.html#node_interminalbranch)
- [Distance to closest segment](measures/prebuilt.html#node_distclosest)
- [Fractal dimension](measures/prebuilt.html#node_fractal)

 ---

### [Branch Measures](measures/prebuilt.html#branch)

- [Hillman taper rate](measures/prebuilt.html#branch_hillman)
- [Burker taper rate](measures/prebuilt.html#branch_burker)
- [Tortuosity](measures/prebuilt.html#branch_tortuosity)
- [Node count](measures/prebuilt.html#branch_size)
- [Branch index](measures/prebuilt.html#branch_index)
- [Centrifugal order](measures/prebuilt.html#branch_order)
- [Child diameter ratio](measures/prebuilt.html#branch_childdimratio)
- [Parent-Child diameter ratio](measures/prebuilt.html#branch_parentchildiamratio)
- [Partition asymmetry](measures/prebuilt.html#branch_partition)
- [Rall power fit](measures/prebuilt.html#branch_rall)
- [Pk](measures/prebuilt.html#branch_pk)
- [Hillman threshold](measures/prebuilt.html#branch_hillman_threshold)
- [Local bifurcation angle](measures/prebuilt.html#branch_localbif)
- [Remote bifurcation angle](measures/prebuilt.html#branch_remotebif)
- [Local bifurcation angle](measures/prebuilt.html#branch_localbif)
- [Remote bifurcation angle](measures/prebuilt.html#branch_remotebif)
- [Local tilt angle](measures/prebuilt.html#branch_localtilt)
- [Remote tilt angle](measures/prebuilt.html#branch_remotetilt)
- [Local plane vector](measures/prebuilt.html#branch_localplane)
- [Remote plane vector](measures/prebuilt.html#branch_remoteplane)
- [Local torque angle](measures/prebuilt.html#branch_localtorque)
- [Remote torque angle](measures/prebuilt.html#branch_remotetorque)
- [Length](measures/prebuilt.html#branch_length)
- [Intersects](measures/prebuilt.html#branch_intersects)

---

### [Neurite Measures](measures/prebuilt.html#neurite)

- [Root is soma](measures/prebuilt.html#neurite_rootsoma)

---

### [Neuron Measures](measures/prebuilt.html#neuron)

- [Has soma](measures/prebuilt.html#neuron_hassoma)
- [Neurite count](measures/prebuilt.html#neuron_neurite_count)
- [Neurite type count](measures/prebuilt.html#neuron_neurite_type_count)
- [Soma surface](measures/prebuilt.html#neuron_soma_surface)

---

### [Generic Measures](measures/prebuilt.html#generic)

- [Set size](measures/prebuilt.html#generic_setsize)

---

###[L-measure Measures](measures/prebuilt.html#lmeasure)

- [Soma surface](measures/prebuilt.html#lmeasure_somasurface)
- [Number of stems](measures/prebuilt.html#lmeasure_nstems)
- [Number of bifurcations](measures/prebuilt.html#lmeasure_nbifs)
- [Number of branches](measures/prebuilt.html#lmeasure_nbranches)
- [Number of terminal tips](measures/prebuilt.html#lmeasure_nterminals)
- [Width, Height and Depth](measures/prebuilt.html#lmeasure_width)
- [Diameter](measures/prebuilt.html#lmeasure_diameter)
- [Diameter power](measures/prebuilt.html#lmeasure_diameterpow)
- [Compartment length](measures/prebuilt.html#lmeasure_length)
- [Branch length](measures/prebuilt.html#lmeasure_branchlength)
- [Compartment surface](measures/prebuilt.html#lmeasure_surface)
- [Branch surface](measures/prebuilt.html#lmeasure_branchsurface)
- [Compartment section area](measures/prebuilt.html#lmeasure_section_area)
- [Compartment volume](measures/prebuilt.html#lmeasure_volume)
- [Branch volume](measures/prebuilt.html#lmeasure_branch_volume)
- [Distance to root](measures/prebuilt.html#lmeasure_rootdist)
- [Path length to root](measures/prebuilt.html#lmeasure_rootpath)
- [Branch centrifugal order](measures/prebuilt.html#lmeasure_branchorder)
- [Node terminal degree](measures/prebuilt.html#lmeasure_terminaldegree)
- [Branch terminal degree](measures/prebuilt.html#lmeasure_branch_terminaldegree)
- [Taper 1: Burker taper rate](measures/prebuilt.html#lmeasure_burker)
- [Taper 2: Hillman taper rate](measures/prebuilt.html#lmeasure_hillman)
- [Contraction](measures/prebuilt.html#lmeasure_contraction)
- [Fragmentation](measures/prebuilt.html#lmeasure_fragmentation)
- [Partition asymmetry](measures/prebuilt.html#lmeasure_partition_asymmetry)
- [Rall's power](measures/prebuilt.html#lmeasure_rall)
- [Pk fitted value](measures/prebuilt.html#lmeasure_pkfit)
- [Pk classic and squared](measures/prebuilt.html#lmeasure_pkclassic)
- [Local bifurcation amplitude](measures/prebuilt.html#lmeasure_local_bif)
- [Remote bifurcation amplitude](measures/prebuilt.html#lmeasure_remote_bif)
- [Local bifurcation tilt](measures/prebuilt.html#lmeasure_local_tilt)
- [Remote bifurcation tilt](measures/prebuilt.html#lmeasure_remote_tilt)
- [Local bifurcation torque](measures/prebuilt.html#lmeasure_local_torque)
- [Remote bifurcation_torque](measures/prebuilt.html#lmeasure_remote_torque)
- [Terminal bifurcation diameter](measures/prebuilt.html#lmeasure_terminaldiam)
- [Hillman threshold](measures/prebuilt.html#lmeasure_hillman_threshold)
- [Fractal dimension](measures/prebuilt.html#lmeasure_fractal_dimension)

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
  - The aggregation function *aggr* must be compatible with the measure output type

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

## Create a measure {#create}

This section will show you how to define new measure functions using already existing selector and measures with little code. Although the selector/measure structure is designed to ease the process of creating new measures, it may seem a bit...hard to use at first. We will introduce the concept with a very simple measure, the average branch length in a neuron.

Additionally to the two examples shown below, you can find more examples of selector/measure usage in the source code of the [feature extractor utils](utils.html#neuritefeature) and in the [L-measure definitions](measures/lmeasure.html).

### Neuron average branch length

First of all, we should define the measure we want to create. Specifically, we need to point out the input, output and what does it measure. In this example, our measure is pretty simple:

| Input | Output | Description
|:--|:--|:--
|Single neuron | Float number | Average branch length in the neuron

Then, we should find the selectors and measures that will build up our new measure.

- To measure the [Branch] length, the [`branch_length`](measures/prebuilt.html#branch_length) is the obvious choice.
- Since we want to find the average value for every branch in the neuron. To select all branches in a neuron we have the [`neuron_branch_selector`](selectors/prebuilt.html#neuron_branch).

Let's stop here to plan our next step. We want to combine the [`branch_length`](measures/prebuilt.html#branch_length) measure with the [`neuron_branch_selector`](selectors/prebuilt.html#neuron_branch) in some specific way to create the measure. Since the selector already has the input that we want (a single neuron), we need to transform the measure to take a set of branches and output the average length, so it can be combined with the selector. In plain words, we want to measure the length of every [Branch] in a set and average the results. If you go back to the [measure operations](#operations) section you will find the [`measureEachAggregate`](#eachaggr) function, which does exactly what we need:

- The *f* argument is the [`branch_length`](measures/prebuilt.html#branch_length) measure.
- The *aggr* argument is the aggregate function [`avg_aggr_factory`](#mean) for floats, that is `avg_aggr_factory<float,float>(0)`

Then, our intermediate measure will look like this:

```cpp
measureEachAggregate(branch_length, avg_aggr_factory<float,float>(0));
```

Now, we can use the [`selectorMeasureCompose`](#composition) function to join the neuron branch selector with our intermediate measure. This will output the measure that we have defined at the beginning:

```cpp
  selectorMeasureCompose(
    neuron_branch_selector,
    measureEachAggregate(branch_length, avg_aggr_factory<float,float>(0)));
```
