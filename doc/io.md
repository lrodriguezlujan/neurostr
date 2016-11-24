---
currentSection: io
currentSubsection:
currentItem:
---
# Input/Output

<a id="parsers"></a>

## Parsers

Parsers are classes that read a [Reconstruction] from an input stream `std::istream`. All parsers inherit from a common virtual class `Parser` in the `neurostr::io` namespace. This virtual class (it can be seen as an interface) defines the functions that you, as user, will use in any parser, and a public constructor that take an `istream` as parameter. The functions of the common interface are:

#### Read

The pure virtual read function imposes a common signature for the parser read functionality. It reads the data from the stream given in the parser constructor and output an `std::unique_ptr` (pointer that involves data ownership) to a [Reconstruction] object. The name string parameter is used to give a name to the reconstruction and, in some cases, to name also the neurons inside the reconstruction if no other name is given. Read function implementations are supposed to register the incidences (count) during the reading process using the error and warning management described in the next section. Also, expect them to make use of the `NSTR_LOG` macro to register errors and warnings in the log.

```cpp
std::unique_ptr<Reconstruction> read(const std::string& name)
```

There are 4 parsers implemented in NeuroSTR:

- The `SWCParser`, that reads [SWC files](io/format.html#SWC).
- The `ASCParser`, that reads [Neurolucida ASCII files](io/format.html#ASC).
- The `DATParser`, that reads [Neurolucida DAT files](io/format.html#DAT). Please remember that DAT files are binary when opening the input stream.
- The `JSONParser`, that reads [JSON files](io/format.html#JSON) (with some specific format restrictions).

Please, check the [Parser class](#) documentation for further details.

#### Error and Warning management

Parsers are expected to be error tolerant (up to some extent). Although detailed error messages are supposed to be registered by the log (`NSTR_LOG`) function, parser class included some basic functions to keep track of how many errors occur and their type. These functions are:

- `error` Returns the error count
- `warn` Returns the warning count
- `critical` Returns true if the last error has been critical
- `reset_errors` Sets all counts to 0 and critical flag to false.

If you plan to develop your own parser, please check the [Parser class](classes/io.html#class_io__parser) documentation for further details.

---

#### Auxiliary functions

Parser dispatchers are a pair of auxiliary functions to ease the task to read a reconstruction from a file. Both functions, defined in `neurostr::io` namespace are:

-   `Parser* get_parser_by_ext(const std::string& ext)` Given a file extension, returns a pointer to the parser that should be use to read the file.
-   `std::unique_ptr<Reconstruction> read_file_by_ext(const std::string& path)` Given a file path. Picks a parser based on its extension, read the file and returns a pointer to the reconstruction.

<a id="writers"></a>

## Writers

Parsers are classes that write a given [Reconstruction] into a output stream `std::ostream` following some predefined format. At the moment, just [SWC](io/format.html#SWC) and [JSON](io/format.html#JSON) file formats are supported by the `SWCWriter` and `JSONWriter` respectively. Check the data format specification and the writers documentation for further details about how to use them.

[Reconstruction]: data_model.html#reconstruction
[Contour]: data_model.html#contour
[Neuron]: data_model.html#neuron
[Neurite]: data_model.html#neurite
[Branch]: data_model.html#branch
[Node]: data_model.html#node
