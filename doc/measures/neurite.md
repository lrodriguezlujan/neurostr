---
currentSection: measures
currentSubsection: predef
currentItem: neurite
---
# Neurite selectors {#neurite}

### Root is soma <a id="neurite_rootsoma"> </a>

**Function:** `root_is_soma`

**Description:** Returns true if the [Neurite] is attached to the soma

**Output:** Boolean flag. True if the [Neurite] root is a soma point (or it is inside the soma)

**Details:** `root_is_soma` measure just calls the `Neurite.root_is_soma()` member function which checks if the root branch of the neurite has a root node.

---

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
[Soma]: ../goals_architecture.html#soma
