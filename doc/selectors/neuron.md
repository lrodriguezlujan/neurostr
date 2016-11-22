---
currentSection: selectors
currentSubsection: predef
currentItem: neuron
---
# Neuron selectors

Neuron selectors are implemented in the header file `selector/neuron_selector.h`. They belong to the namespace  `neurostr::selector`.

## Neurites selector <a id="neurites"></a>

**Function**:  `neuron_neurites = [](const Neuron &n) -> std::vector<const_neurite_reference>`

**Description**: Selects neurites in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Neurite] | Set|

## Branch selector <a id="branch"></a>

**Function**:  `neuron_branch_selector = [](const Neuron &n) -> std::vector<const_branch_reference>`

**Description**: Selects all branches in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Branch] | Set|


## Nodes selector <a id="nodes"></a>

**Function**:  `neuron_node_selector = [](const Neuron &n) -> std::vector<const_node_reference>`

**Description**: Selects all nodes in every neurite in the neuron

**Types**:

|Input type|Input cardinality|Output type|Output cardinality|
|:---|:---|:---|:---|
| [Neuron] | Single | [Node] | Set|


[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
