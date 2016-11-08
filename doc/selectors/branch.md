---
currentSection: selectors
currentSubsection: predef
currentItem: branch
---
# Branch selectors

All branch selectors are implemented in the file `selector/branch_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neurite selector <a id="neurite"></a>

**Function**:  `branch_neurite_selector`

**Description**: Selects the neurite that the given branch belongs to

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Neurite] | Single|

## Parent branch selector <a id="parent"></a>

**Function**:  `branch_parent_selector`

**Description**: Selects the parent branch of the given branch. If the given branch doesn't have a parent branch (it is the root), returns it.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Single|

## Sibling branch selector <a id="sibling"></a>

**Function**:  `branch_parent_selector`

**Description**: Selects the sibling branch of the given branch. If the given branch doesn't have a sibling branch (it is the root or the tree is ill defined), returns it. If the branch has more than one sibling selects the first one.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Single|


## Last node selector <a id="last_node"></a>

**Function**:  `branch_last_node_selector`

**Description**: Selects the last node in the branch. If the branch is empty returns the root node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Single|

## First node selector <a id="first_node"></a>

**Function**:  `branch_first_node_selector`

**Description**: Selects the first node in the branch. If the branch is empty returns the root node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Single|

## All nodes selector <a id="nodes"></a>

**Function**:  `branch_node_selector`

**Description**: Select all nodes in the branch (excluded the root)

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Node] | Set|

## Subtree selector <a id="subtree"></a>

**Function**:  `branch_subtree_selector`

**Description**: Selects the given branch and all its descendants.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Set|

## Stem selector <a id="stem"></a>

**Function**:  `branch_stem_selector`

**Description**: Selects the given branch and all the branches in the path to the neurite's root.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Single | [Branch] | Set|

## Centrifugal order filter <a id="order"></a>

**NOTE**: This is a selector factory function. Selector factories create selector functions given some parameters.

**Function**:  `branch_order_filter_factory`

**Parameters**:
  - order *integer* : The Centrifugal order to select

**Description**: Selects all branches in the set with given centrifugal order *order*

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Branch] | Set | [Branch] | Set|


[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
