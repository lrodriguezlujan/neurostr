---
currentSection: selectors
currentSubsection: predef
currentItem: node
---
# Node selectors

All node selectors are implemented in the file `selector/node_selector.h`. They belong to the namespace  `neurostr::selector`.

## Self selector <a id="self"></a>

**Function**:  `node_self`

**Description**: Dummy function. Returns the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Single|


## Parent node selector <a id="parent"></a>

**Function**: `node_parent`

**Description**: Select the parent node of the given node. If it doesn't exists, returns the node itself.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Single|


## Parent branch selector <a id="branch"></a>

**Function**: `node_branch_selector`

**Description**: Selects the branch that the node belongs to.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Branch] | Single|

## Subtree selector <a id="subtree"></a>

**Function**: `node_subtree_selector`

**Description**: Selects all nodes that are descendants of the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Subtree terminals selector <a id="subtree_terminals"></a>

**Function**: `node_subtree_terminals`

**Description**: Selects all terminal tips in the subtree of the given node.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Stem selector <a id="stem"></a>

**Function**: `node_stem_selector`

**Description**: Selects all nodes in the path from the given node to the neurite root.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Descendant selector <a id="descendants"></a>

**Function**: `node_descendants`

**Description**: Selects all nodes that have the given node as parent

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Bifurcation nodes filter <a id="bifurcation"></a>

**Function**: `node_bifurcation_selector`

**Description**: Given a set of nodes select those which are bifurcations

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

## Terminals nodes filter <a id="terminal"></a>

**Function**: `node_terminal_selector`

**Description**: Given a set of nodes select those which are terminal tips

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Node] | Single | [Node] | Set|

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
