---
currentSection: measures
currentSubsection:
currentItem:
---
# Measures

Measures are functions that take a single reference to an [element of a neuron](data_model.html) or a set of them and compute some output value, the measure. We can distinguish between single and set measures, depending on whether they take one or more references as input. Single elements references (e.g. a single Node) are simply C++ references, whereas sets are `std::vector` of `std::reference_wrapper`.

All classes, functions, etc. related to selectors are defined in the `neurostr::measure` namespace. You can include their headers individually or take them all by adding the header file `measure.h`

Measures are intended to be combined with [Selectors](selectors.html) and [Aggregators](#aggregators) to create complex and meaningful measures with low coding effort. You can implement your own measures and, if they have the adequate signature, use them as any other predefined measure.

## Prebuilt measures <a id="predef"></a>

NeuroSTR includes a huge library of predefined measures some new, others already presented in the scientific literature or implemented in existing neuroanatomy tools.

Predefined measures are organized in the same way as [Selectors](selectors.html), by their input element type: all measure functions that take either a single node or a node set as input fall into the *Node* category. You can find more details about each measure by clicking on their name.

You might notice (and it seems odd) that there are very few Neurite and Neuron measures, but it is on purpose. Since we can use [Selectors](selectors.html) and [Aggregators](#aggregators) along with measures to create new measures, we focus on defining "low level" measures, that can be use to create "high level measures". Check the [Create a measure](#create) to see a simple example of this.

### [Node Measures](measures/predefined.html#node)

- [X,Y,Z component](measures/predefined.html#node_component)
- [Radius, Diameter](measures/predefined.html#node_radius)
- [Centrifugal order](measures/predefined.html#node_order)
- [Distance to parent](measures/predefined.html#node_parent_length)
- [Compartment volume](measures/predefined.html#node_volume)
- [Compartment surface](measures/predefined.html#node_surface)
- [Compartment section area](measures/predefined.html#node_section)
- [Local Hillman taper rate](measures/predefined.html#node_hillman)
- [Local Burker taper rate](measures/predefined.html#node_burker)
- [Distance to root](measures/predefined.html#node_rootdist)
- [Distance to soma](measures/predefined.html#node_somadist)
- [Path length to root](measures/predefined.html#node_rootpath)
- [Number of descendants](measures/predefined.html#node_desccount)
- [Non-aligned minimum box volume](measures/predefined.html#node_boxvol)
- [Vector to parent](measures/predefined.html#node_parentvector)
- [Local bifurcation angle](measures/predefined.html#node_localbif)
- [Local elongation angle](measures/predefined.html#node_localelong)
- [Extreme angle](measures/predefined.html#node_extreme)
- [Local orientation](measures/predefined.html#node_localorientation)
- [In terminal branch](measures/predefined.html#node_interminalbranch)
- [Distance to closest segment](measures/predefined.html#node_distclosest)
- [Fractal dimension](measures/predefined.html#node_fractal)

 ---

### [Branch Measures](measures/predefined.html#branch)

- [Hillman taper rate](measures/predefined.html#branch_hillman)
- [Burker taper rate](measures/predefined.html#branch_burker)
- [Tortuosity](measures/predefined.html#branch_tortuosity)
- [Node count](measures/predefined.html#branch_size)
- [Branch index](measures/predefined.html#branch_index)
- [Centrifugal order](measures/predefined.html#branch_order)
- [Child diameter ratio](measures/predefined.html#branch_childdimratio)
- [Parent-Child diameter ratio](measures/predefined.html#branch_parentchildiamratio)
- [Partition asymmetry](measures/predefined.html#branch_partition)
- [Rall power fit](measures/predefined.html#branch_rall)
- [Pk](measures/predefined.html#branch_pk)
- [Hillman threshold](measures/predefined.html#branch_hillman_threshold)
- [Local bifurcation angle](measures/predefined.html#branch_localbif)
- [Remote bifurcation angle](measures/predefined.html#branch_remotebif)
- [Local bifurcation angle](measures/predefined.html#branch_localbif)
- [Remote bifurcation angle](measures/predefined.html#branch_remotebif)
- [Local tilt angle](measures/predefined.html#branch_localtilt)
- [Remote tilt angle](measures/predefined.html#branch_remotetilt)
- [Local plane vector](measures/predefined.html#branch_localplane)
- [Remote plane vector](measures/predefined.html#branch_remoteplane)
- [Local torque angle](measures/predefined.html#branch_localtorque)
- [Remote torque angle](measures/predefined.html#branch_remotetorque)
- [Length](measures/predefined.html#branch_length)
- [Intersects](measures/predefined.html#branch_intersects)

---

### [Neurite Measures](measures/predefined.html#neurite)

- [Root is soma](measures/neurite.html#rootsoma)

---

### [Neuron Measures](measures/predefined.html#neuron)

- [Has soma](measures/predefined.html#neuron_hassoma)
- [Neurite count](measures/predefined.html#neuron_neurite_count)
- [Neurite type count](measures/predefined.html#neuron_neurite_type_count)
- [Soma surface](measures/predefined.html#neuron_soma_surface)

---

### [Generic Measures](measures/predefined.html#generic)

- [Set size](measures/predefined.html#generic_setsize)

---

###[L-measure Measures](measures/predefined.html#lmeasure)

- [Soma surface](measures/predefined.html#lmeasure_somasurface)
- [Number of stems](measures/predefined.html#lmeasure_nstems)
- [Number of bifurcations](measures/predefined.html#lmeasure_nbifs)
- [Number of branches](measures/predefined.html#lmeasure_nbranches)
- [Number of terminal tips](measures/predefined.html#lmeasure_nterminals)
- [Width, Height and Depth](measures/predefined.html#lmeasure_width)
- [Diameter](measures/predefined.html#lmeasure_diameter)
- [Diameter power](measures/predefined.html#lmeasure_diameterpow)
- [Compartment length](measures/predefined.html#lmeasure_length)
- [Branch length](measures/predefined.html#lmeasure_branchlength)
- [Compartment surface](measures/predefined.html#lmeasure_surface)
- [Branch surface](measures/predefined.html#lmeasure_branchsurface)
- [Compartment section area](measures/predefined.html#lmeasure_section_area)
- [Compartment volume](measures/predefined.html#lmeasure_volume)
- [Branch volume](measures/predefined.html#lmeasure_branch_volume)
- [Distance to root](measures/predefined.html#lmeasure_rootdist)
- [Path length to root](measures/predefined.html#lmeasure_rootpath)
- [Branch centrifugal order](measures/predefined.html#lmeasure_branchorder)
- [Node terminal degree](measures/predefined.html#lmeasure_terminaldegree)
- [Branch terminal degree](measures/predefined.html#lmeasure_branch_terminaldegree)
- [Taper 1: Burker taper rate](measures/predefined.html#lmeasure_burker)
- [Taper 2: Hillman taper rate](measures/predefined.html#lmeasure_hillman)
- [Contraction](measures/predefined.html#lmeasure_contraction)
- [Fragmentation](measures/predefined.html#lmeasure_fragmentation)
- [Partition asymmetry](measures/predefined.html#lmeasure_partition_asymmetry)
- [Rall's power](measures/predefined.html#lmeasure_rall)
- [Pk fitted value](measures/predefined.html#lmeasure_pkfit)
- [Pk classic and squared](measures/predefined.html#lmeasure_pkclassic)
- [Local bifurcation amplitude](measures/predefined.html#lmeasure_local_bif)
- [Remote bifurcation amplitude](measures/predefined.html#lmeasure_remote_bif)
- [Local bifurcation tilt](measures/predefined.html#lmeasure_local_tilt)
- [Remote bifurcation tilt](measures/predefined.html#lmeasure_remote_tilt)
- [Local bifurcation torque](measures/predefined.html#lmeasure_local_torque)
- [Remote bifurcation_torque](measures/predefined.html#lmeasure_remote_torque)
- [Terminal bifurcation diameter](measures/predefined.html#lmeasure_terminaldiam)
- [Hillman threshold](measures/predefined.html#lmeasure_hillman_threshold)
- [Fractal dimension](measures/predefined.html#lmeasure_fractal_dimension)

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

- To measure the [Branch] length, the [`branch_length`](measures/predefined.html#branch_length) is the obvious choice.
- Since we want to find the average value for every branch in the neuron. To select all branches in a neuron we have the [`neuron_branch_selector`](selectors/predefined.html#neuron_branch).

Let's stop here to plan our next step. We want to combine the [`branch_length`](measures/predefined.html#branch_length) measure with the [`neuron_branch_selector`](selectors/predefined.html#neuron_branch) in some specific way to create the measure. Since the selector already has the input that we want (a single neuron), we need to transform the measure to take a set of branches and output the average length, so it can be combined with the selector. In plain words, we want to measure the length of every [Branch] in a set and average the results. If you go back to the [measure operations](#operations) section you will find the [`measureEachAggregate`](#eachaggr) function, which does exactly what we need:

- The *f* argument is the [`branch_length`](measures/predefined.html#branch_length) measure.
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
