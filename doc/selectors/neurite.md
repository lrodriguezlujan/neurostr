---
currentSection: selectors
currentSubsection: predef
currentItem: neurite
---
# Neurite selectors

Neurite selectors are implemented in the header file `selector/neurite_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neuron selector <a id="neuron"></a>

**Function**:  `neurite_neuron_selector = [](const Neurite& n) -> const Neuron& `

**Description**: Selects the neuron that the given neurite belongs to

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Neuron] | Single|

## Node set selector <a id="nodes"></a>

**Function**:  `neurite_node_selector = [](const Neurite& n) ->  std::vector<const_node_reference>`

**Description**: Selects all nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Branch set selector <a id="branches"></a>

**Function**:  `neurite_branch_selector = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|


## First branch selector <a id="first_branch"></a>

**Function**:  `neurite_first_branch_selector = [](const Neurite& n) -> const Branch&`

**Description**:Selects the neurite's first branch (root branch)

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Single|

## Bifurcation nodes selector <a id="bifurcation_nodes"></a>

**Function**:  `neurite_bifurcation_selector = [](const Neurite& n) -> std::vector<const_node_reference>`

**Description**: Selects all bifurcation nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Terminal nodes selector <a id="terminal_nodes"></a>

**Function**:  `neurite_terminal_selector = [](const Neurite& n) -> std::vector<const_node_reference>`

**Description**: Selects all terminal nodes in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Node] | Set|

## Terminal branches selector <a id="terminal_branches"></a>

**Function**:  `neurite_terminal_branches = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects terminal branches in the neurite.

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|

## Non terminal branches selector <a id="nonterminal"></a>

**Function**:  `neurite_non_terminal_branches = [](const Neurite& n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite but the terminal ones

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|

## Pre-terminal branches selector <a id="preterminal"></a>

**Function**:  `neurite_pre_terminal_branches = [](const Neurite &n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neurite that have at least one daughter branch that is terminal

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Single | [Branch] | Set|


## Terminal bifurcation node selector <a id="terminal_bif"></a>

**Function**:  `neurite_terminal_bifurcations = [](const Neurite &n) -> std::vector<const_node_reference>`

**Description**: Selects all bifurcations in the neurite where at least one of their descendants is a terminal branch

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neurite] | Set | [Node] | Set|

## Neurite type filter <a id="type"></a>

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

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
