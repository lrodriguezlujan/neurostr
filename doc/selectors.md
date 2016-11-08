---
currentSection: selectors
currentSubsection:
currentItem:
---
# Selectors
This section reviews what are NeuroSTR selector functions and how to use them. Selectors are a key component in the NeuroSTR architecture. All classes, functions, etc. related to selectors are defined in the `neurostr::selector` namespace. You can include their headers individually or take them all by adding the header file `selector.h`

## Basics  <a id="basics"></a>
The selector concept is quite simple: A selector is a function that takes one or more references to [elements of a neuron](goals_architecture.html) (or the neuron itself) as input, and returns one or more elements as output. Easy, isn't it?

![Selector basics][selector_basics]

Single elements references (e.g. a single Node) are simply C++ references, whereas sets are `std::vector` of `std::reference_wrapper`. So, looking at the input and output arity we distinguish four selector function types:
1. Single input - single output
```
  [](const ElementA& n) => const ElementB& {}
```
1. Single input - set output
```
  [](const ElementA& n) => std::vector<std::reference_wrapper<ElementB>> {}
```

1. Set input - single output
```
  [](const reference_iter& beg, const reference_iter& end) => const ElementB& {}
```

1. Set input - set output
```
  [](const reference_iter<A>& beg, const reference_iter<A>& end)
          => std::vector<std::reference_wrapper<ElementB>> {}
```

Here we use `reference_iter<Element>` as shorthand for
```
std::vector<std::reference_wrapper<Element>>::iterator
```
 Any function with signature equal to one of these, can be used as selector in *NeuroSTR* and it is compatible with all selector functionality in the library. Along the documentation, we might mention **filter functions** which are just *Set input - set output (type 4)* selectors that return a subset of a given set of elements.

---

## Predefined selectors <a id="predef"></a>

NeuroSTR includes a relatively large set of predefined selector functions. They are organized in four categories, according to their input element type. For example, all selector functions that take either a single node or a node set as input fall into the *Node* category.

Here is the list of available selectors, you can find more details about each selector by clicking on their name:

### [Node Selectors](selectors/node.html)

- [Self selector](selectors/node.html#self)
- [Parent node selector](selectors/node.html#parent)
- [Parent branch selector](selectors/node.html#branch)
- [Subtree selector](selectors/node.html#subtree)
- [Subtree terminals selector](selectors/node.html#subtree_terminals)
- [Stem selector](selectors/node.html#stem)
- [Descendant selector](selectors/node.html#descendants)
- [Bifurcation nodes filter](selectors/node.html#bifurcation)
- [Terminal nodes filter](selectors/node.html#terminal)

 ---

### [Branch Selectors](selectors/branch.html)

- [Parent neurite selector](selectors/branch.html#neurite)
- [Parent branch selector](selectors/branch.html#parent)
- [Sibling branch selector](selectors/branch.html#sibling)
- [Last node selector](selectors/branch.html#last_node)
- [First node selector](selectors/branch.html#first_node)
- [All nodes selector](selectors/branch.html#nodes)
- [Subtree selector](selectors/branch.html#subtree)
- [Stem selector](selectors/branch.html#stem)
- [Centrifugal order filter](selectors/branch.html#order)

---

### [Neurite Selectors](selectors/neurite.html)

- [Neuron selector](selectors/neurite.html#neuron)
- [Node set selector](selectors/neurite.html#nodes)
- [Branch set selector](selectors/neurite.html#branches)
- [First branch selector](selectors/neurite.html#first_branch)
- [Bifurcation nodes selector](selectors/neurite.html#bifurcation_nodes)
- [Terminal nodes selector](selectors/neurite.html#terminal_nodes)
- [Terminal branches selector](selectors/neurite.html#terminal_branches)
- [Non terminal branches selector](selectors/neurite.html#nonterminal)
- [Pre-terminal branches selector](selectors/neurite.html#preterminal)
- [Terminal bifurcation node selector](selectors/neurite.html#terminal_bif)
- [Neurite type filter](selectors/neurite.html#type)
- [Dendrite filter](selectors/neurite.html#type)
- [Apical filter](selectors/neurite.html#type)
- [Axon filter](selectors/neurite.html#type)

---

### [Neuron Selectors](selectors/neuron.html)

- [Neurites selector](selectors/neuron.html#neurites)
- [Branch selector](selectors/neuron.html#branch)
- [Nodes selector](selectors/neuron.html#nodes)

---

### [Generic Selectors](selectors/generic.html)

- [Generic self selector](selectors/generic.html#self)
- [Property exists filter](selectors/generic.html#property)
- [Unique filter](selectors/generic.html#unique)

---

## Selector operations <a id="operations"></a>

So far, we have a (large) set of selector functions that might cover our needs. But, imagine that we need a essential selector that, unfortunately, we forgot to implement. Wouldn't be nice to be able to reuse other selectors?. That's where selector operations become really useful. Now we proceed to describe the operations available, but in the [next section](#create) we show you how to use the selector operations to create a new useful selector. At the moment all operations are templated operations, in other words they are done in compile time, in the close future neuroSTR will support execution time operations.

There are two classes of selector operations: selector functions inner operations and selection set operations. The latter, are operations that combine the output of two selectors, whereas the first are regular function operation over selectors.

### [Inner operations](selectors/operations.html#inner)

- [Composition](selectors/operations.html#compose)
- [Single Output to Set](selectors/operations.html#out_to_set)
- [Single Input to Set (foreach)](selectors/operations.html#in_to_set)
- [Combined Foreach](selectors/operations.html#foreach)

---

### [Set operations](selectors/operations.html#set)

- [Union](selectors/operations.html#union)
- [Intersection](selectors/operations.html#intersection)
- [Asymmetric Difference](selectors/operations.html#diff)

---

## Create a selector <a id="create"></a>

So far you have read all about selectors but you still feel like a fish out of water. To ease your mind we will show you how to create a new selector in 5 lines. Let's start by picking a predefined selector that seems "hard" to implement: [Pre-termianl branches selector](selectors/neurite.html#preterminal).

1. The [Pre-termianl branches selector](selectors/neurite.html#preterminal) selects all branches in a neurite which have at least one daughter branch that is terminal. Instead of writing it from scratch we will use the selector operations. Selecting all terminal branches in the neurite seems like a good start, so we use the [Terminal branches selector](selectors/neurite.html#terminal_branches).
```
  using namespace ns = neurostr::selector;
  ns::neurite_terminal_branches();
```

1. Since we want the pre-terminal seems pretty obvious that we should use the [Parent branch selector](selectors/branch.html#parent) somewhere. Actually we want to select the parent of each terminal branch...that is exactly what the [Combined Foreach](selectors/operations.html#foreach) operation does:
```
  ns::selector_foreach(ns::neurite_terminal_branches,
                       ns::branch_parent_selector);
```

1. That's it, we're done!...Nope!, we don't. What if the neurite has only one branch? We should select and empty set (and the parent selector don't work that way). We need to remove the first branch from the terminal branches selection first. We can select the first branch with the [First branch selector](selectors/neurite.html#first_branch), but the [Asymmetric Difference](selectors/operations.html#diff) operator requires both arguments to output a set (and to have the same input type), so first we convert the [First branch selector](selectors/neurite.html#first_branch) to an output set selector:
```
  ns::selector_out_single_to_set(ns::neurite_first_branch_selector);
```

1. Then we can remove it from the terminal branches selection
```
  ns::diff_selector_factory(ns::neurite_terminal_branches,
                            ns::selector_out_single_to_set(ns::neurite_first_branch_selector));
```

1. Finally, we can create our selector in one (really long) line. Of course, for the sake of code readability, you ought to store intermediate results in auxiliar variables:
```
  auto preterminal_selector = ns::selector_foreach(

                                ns::diff_selector_factory(ns::neurite_terminal_branches,
                                                          ns::selector_out_single_to_set(ns::neurite_first_branch_selector)),
                                ns::branch_parent_selector);
```
[//]: # "Images"

[selector_basics]: figures/selector_basics.png "Selector basic schema"
