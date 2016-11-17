---
currentSection: arch
currentSubsection: modules
currentItem:
---
# Library Architecture

## Library modules  <a id="modules"></a>

NeuroSTR is structured in five heavily interrelated modules:

### Core <a id="core"></a>

The core module is the angular stone of the library, as its name suggests. It contains all classes described in the [Data model](#model) section, as well as other additional functionality such as the basic geometry functions, properties, log, etc. All core functionality is in the namespace `neurostr`. Please make yourself familiar with the core module before trying to use the library, you will need it.

**What's in the core module?:**
- Property map classes - *property.h/c*
- Log functions - *log.h/c*
- Geometry functions - *geometry.h/c*
- Node class - *node.h/c*
- Branch class - *branch.h/c*
- Neurite class and neurite type enumeration - *neurite.h/c, neurite_type.h*
- Neuron class - *neuron.h/c*
- Contour class - *contour.h/c*
- Tree class (from: [tree.hh](http://tree.phi-sci.com/) ) - *tree.hh*
- Template traits - *traits.h*

---

### IO <a id="core"></a>

The *input/output* module contains the classes that read/write files containing reconstructions. All IO functionality is in the namespace `neurostr::io`. There are parsers for the SWC, Neurolucida ASCII, Neurolucida DAT and JSON formats, and writers for the SWC and JSON formats. For more information about the module and its functionality check out the [Input/output section](io.html).

**What's in the io module?:**
- Parser abstract class - *parser.h , parser_dispatcher.h*
- Neurolucida auxiliar structures - *nl_structure.h*
- SWC Parser - *SWCParser.h/c*
- SWC Writer - *SWCWriter.h/c*
- Neurolucida ASCII Parser - *ASCParser.h/c*
- Neurolucida DAT Parser - *DATParser.h/c*
- JSON Parser - *JSONParser.h/c*
- JSON Writer - *JSONWriter.h/c*

---

### Selectors <a id="selector"></a>

A selector is a function that takes one or more elements of a neuron, and return other elements of that same neuron. An example can be a selector that given a branch, returns its root node. All selector-related functions and classes are in the namespace `neurostr::selector`. Please check the module documentation in the [Selector section](selector.html).

**What's in the selector module?:**
- Shorthand to include everything - *selector.h*
- [Selectors with node as input](selectors/node.html) - *node_selector.h*
- [Selectors with branch as input](selectors/branch.html) - *branch_selector.h*
- [Selectors with neurite as input](selectors/neurite.html) - *neurite_selector.h*
- [Selectors with neuron as input](selectors/neuron.html) - *neuron_selector.h*
- [Generic selectors](selectors/generic.html) - *universal_selector.h*
- [Selector operations](selectors/operations.html#inner) - *selector_operations.h*
- [Selector set operations](selectors/operations.html#set) - *selector_set_operations.h*

---

### Measures <a id="measure"></a>

A measure is a function that given one or several elements of a neuron, return a value based on the input, the measure. An example can be a measure that given a branch, returns its total length. All measure-related functions and classes are in the namespace `neurostr::measure`. Please check the module documentation in the [Measure section](measures.html).

**What's in the selector module?:**
- Shorthand to include everything - *measure.h*
- Template traits - *measure_traits.h*
- [Measure with node as input](measures/node.html) - *node_measure.h*
- [Measure with branch as input](measures/branch.html) - *branch_measure.h*
- [Measure with neurite as input](measures/neurite.html) - *neurite_measure.h*
- [Measure with neuron as input](measures/neuron.html) - *neuron_measure.h*
- [L-measure definitions](measures/lmeasure.html) - *lmeasure_decl.h*
- [Generic measures](measures/generic.html) - *universal_measure.h*
- [Measure operations](measures/operations.html) - *measure_operations.h*
- [Selector set operations](selectors/operations.html#set) - *selector_set_operations.h*
- [Aggregators](measures.html#aggregators) - *aggregate.h*
- Aggregators traits - *aggregator_traits.h*

---

### Methods <a id="methods"></a>

TO-DO

---
