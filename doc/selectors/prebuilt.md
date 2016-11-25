---
currentSection: selectors
currentSubsection: predef
currentItem:
---

# Prebuilt selectors

euroSTR includes a relatively large set of prebuilt selector functions. They are organized in four categories, according to their input element type. For example, all selector functions that take either a single node or a node set as input fall into the *Node* category.

Here is the list of available selectors, you can find more details about each selector by clicking on their name:

### [Node Selectors](#node_selectors)

- [Self selector](#node_self)
- [Parent node selector](#node_parent)
- [Parent branch selector](#node_branch)
- [Subtree selector](#node_subtree)
- [Subtree terminals selector](#node_subtree_terminals)
- [Stem selector](#node_stem)
- [Descendant selector](#node_descendants)
- [Bifurcation nodes filter](#node_bifurcation)
- [Terminal nodes filter](#node_terminal)

 ---

### [Branch Selectors](#branch_selectors)

- [Parent neurite selector](#branch_neurite)
- [Parent branch selector](#branch_parent)
- [Sibling branch selector](#branch_sibling)
- [Last node selector](#branch_last_node)
- [First node selector](#branch_first_node)
- [All nodes selector](#branch_nodes)
- [Subtree selector](#branch_subtree)
- [Stem selector](#branch_stem)
- [Centrifugal order filter](#branch_order)

---

### [Neurite Selectors](#neurite_selectors)

- [Neuron selector](#neurite_neuron)
- [Node set selector](#neurite_nodes)
- [Branch set selector](#neurite_branches)
- [First branch selector](#neurite_first_branch)
- [Bifurcation nodes selector](#neurite_bifurcation_nodes)
- [Terminal nodes selector](#neurite_terminal_nodes)
- [Terminal branches selector](#neurite_terminal_branches)
- [Non terminal branches selector](#neurite_nonterminal)
- [Pre-terminal branches selector](#neurite_preterminal)
- [Terminal bifurcation node selector](#neurite_terminal_bif)
- [Dendrite filter](#neurite_type)
- [Apical filter](#neurite_type)
- [Axon filter](#neurite_type)

---

### [Neuron Selectors](#neuron_selectors)

- [Neurites selector](#neuron_neurites)
- [Branch selector](#neuron_branch)
- [Nodes selector](#neuron_nodes)

---

### [Generic Selectors](#generic_selectors)

- [Generic self selector](#generic_self)
- [Property exists filter](#generic_property)
- [Unique filter](#generic_unique)

---

# Node selectors {#node}

All node selectors are implemented in the file `selector/node_selector.h`. They belong to the namespace  `neurostr::selector`.

## Self selector <a id="node_self"></a>

**Function**:  `node_self`

**Description**: Dummy function. Returns the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Single|


## Parent node selector <a id="node_parent"></a>

**Function**: `node_parent`

**Description**: Select the parent node of the given node. If it doesn't exists, returns the node itself.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Single|


## Parent branch selector <a id="node_branch"></a>

**Function**: `node_branch_selector`

**Description**: Selects the branch that the node belongs to.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Branch] | Single|

## Subtree selector <a id="node_subtree"></a>

**Function**: `node_subtree_selector`

**Description**: Selects all nodes that are descendants of the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Subtree terminals selector <a id="node_subtree_terminals"></a>

**Function**: `node_subtree_terminals`

**Description**: Selects all terminal tips in the subtree of the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Stem selector <a id="node_stem"></a>

**Function**: `node_stem_selector`

**Description**: Selects all nodes in the path from the given node to the neurite root.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Descendant selector <a id="node_descendants"></a>

**Function**: `node_descendants`

**Description**: Selects all nodes that have the given node as parent

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Bifurcation nodes filter <a id="node_bifurcation"></a>

**Function**: `node_bifurcation_selector`

**Description**: Given a set of nodes select those which are bifurcations

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Terminals nodes filter <a id="node_terminal"></a>

**Function**: `node_terminal_selector`

**Description**: Given a set of nodes select those which are terminal tips

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

---

# Branch selectors {#branch}

All branch selectors are implemented in the file `selector/branch_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neurite selector <a id="branch_neurite"></a>

**Function**:  `branch_neurite_selector`

**Description**: Selects the neurite that the given branch belongs to

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Neurite] | Single|

## Parent branch selector <a id="branch_parent"></a>

**Function**:  `branch_parent_selector`

**Description**: Selects the parent branch of the given branch. If the given branch doesn't have a parent branch (it is the root), returns it.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Single|

## Sibling branch selector <a id="branch_sibling"></a>

**Function**:  `branch_parent_selector`

**Description**: Selects the sibling branch of the given branch. If the given branch doesn't have a sibling branch (it is the root or the tree is ill defined), returns it. If the branch has more than one sibling selects the first one.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Single|


## Last node selector <a id="branch_last_node"></a>

**Function**:  `branch_last_node_selector`

**Description**: Selects the last node in the branch. If the branch is empty returns the root node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Single|

## First node selector <a id="branch_first_node"></a>

**Function**:  `branch_first_node_selector`

**Description**: Selects the first node in the branch. If the branch is empty returns the root node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Single|

## All nodes selector <a id="branch_nodes"></a>

**Function**:  `branch_node_selector`

**Description**: Select all nodes in the branch (excluded the root)

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Set|

## Subtree selector <a id="branch_subtree"></a>

**Function**:  `branch_subtree_selector`

**Description**: Selects the given branch and all its descendants.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Set|

## Stem selector <a id="branch_stem"></a>

**Function**:  `branch_stem_selector`

**Description**: Selects the given branch and all the branches in the path to the neurite's root.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Set|

## Centrifugal order filter <a id="branch_order"></a>

**NOTE**: This is a selector factory function. Selector factories create selector functions given some parameters.

**Function**:  `branch_order_filter_factory`

**Parameters**:
  - order *integer* : The Centrifugal order to select

**Description**: Selects all branches in the set with given centrifugal order *order*

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Set | [Branch] | Set|

---

# Neurite selectors {#neurite}

Neurite selectors are implemented in the header file `selector/neurite_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neuron selector <a id="neurite_neuron"></a>

**Function**:  `neurite_neuron_selector = [](const Neurite& n) -> const Neuron& `

**Description**: Selects the neuron that the given neurite belongs to

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Neuron] | Single|

## Node set selector <a id="neurite_nodes"></a>

**Function**:  `neurite_node_selector = [](const Neurite& n) ->  std::vector<const_node_reference>`

**Description**: Selects all nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Branch set selector <a id="neurite_branches"></a>

**Function**:  `neurite_branch_selector = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|


## First branch selector <a id="neurite_first_branch"></a>

**Function**:  `neurite_first_branch_selector = [](const Neurite& n) -> const Branch&`

**Description**:Selects the neurite's first branch (root branch)

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Single|

## Bifurcation nodes selector <a id="neurite_bifurcation_nodes"></a>

**Function**:  `neurite_bifurcation_selector = [](const Neurite& n) -> std::vector<const_node_reference>`

**Description**: Selects all bifurcation nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Terminal nodes selector <a id="neurite_terminal_nodes"></a>

**Function**:  `neurite_terminal_selector = [](const Neurite& n) -> std::vector<const_node_reference>`

**Description**: Selects all terminal nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Terminal branches selector <a id="neurite_terminal_branches"></a>

**Function**:  `neurite_terminal_branches = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects terminal branches in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|

## Non terminal branches selector <a id="neurite_nonterminal"></a>

**Function**:  `neurite_non_terminal_branches = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite but the terminal ones

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|

## Pre-terminal branches selector <a id="neurite_preterminal"></a>

**Function**:  `neurite_pre_terminal_branches = [](const Neurite &n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite that have at least one daughter branch that is terminal

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|


## Terminal bifurcation node selector <a id="neurite_terminal_bif"></a>

**Function**:  `neurite_terminal_bifurcations = [](const Neurite &n) -> std::vector<const_node_reference>`

**Description**: Selects all bifurcations in the neurite where at least one of their descendants is a terminal branch

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Set | [Node] | Set|

## Neurite type filter <a id="neurite_type"></a>

**NOTE**: This is a selector factory function. Selector factories create selector functions given some parameters.

**Function**:  `neurite_type_selector`

**Parameters**:
  - **type** - *NeuriteType* : The type to select

**Description**: Selects all neurites of given type

**Aliases**:
  - `dendrite_selector` Selects dendrite neurites
  - `axon_selector` Selects axon neurites
  - `apical_selector` Selects apical neurites

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Set | [Neurite] | Set|

---

# Neuron selectors {#neuron}

Neuron selectors are implemented in the header file `selector/neuron_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neurites selector <a id="neuron_neurites"></a>

**Function**:  `neuron_neurites = [](const Neuron &n) -> std::vector<const_neurite_reference>`

**Description**: Selects neurites in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Neurite] | Set|

## Branch selector <a id="neuron_branch"></a>

**Function**:  `neuron_neurites = [](const Neuron &n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in every neurite in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Branch] | Set|


## Nodes selector <a id="neuron_nodes"></a>

**Function**:  `neuron_node_selector = [](const Neuron &n) -> std::vector<const_node_reference>`

**Description**: Selects all nodes in every neurite in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Node] | Set|

---

<a id="generic_selectors"></a>

# Generic selectors

[Node]: ../data_model.html#node
[Branch]: ../data_model.html#branch
[Neurite]: ../data_model.html#neurite
[Neuron]: ../data_model.html#neuron
