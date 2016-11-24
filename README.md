# NeuroSTR

A C++ Neuroanatomy Library.

*Alpha version 0.0.1*

NeuroSTR is a neuroanatomy toolbox for C++. It reads and processes three-dimensional neuron reconstructions in the most common file formats and offers a huge set of functions and utilities to work with them.

## Documentation

[Check out the documentation!](https://lrodriguezlujan.github.io/neurostr)

## Dependencies

NeuroSTR uses [CMake](http://cmake.org) as a general build tool. It requires **CMake 3.2.0 or superior**.

The library uses some of the C++14 standard features, so it needs a compiler with C++14 support.

| Compiler | Version | Tested |
|:--|:--|:--
| [g++](https://gcc.gnu.org/) | >5 | Tested: 5.4.1 |

NeuroSTR also uses the following software depèndencies, some of them are header libraries bundled in the package:

| Library | Version | License |  Bundled | What for?
| :-- | :--: | :--: | :--:
| [Boost](http://www.boost.org/) | >1.62.0 | [BSL-1](http://www.boost.org/users/license.html) | No | Everything... |


| [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) | 3.X | [MPL-2](https://www.mozilla.org/en-US/MPL/2.0/) | No | Singular value decomposition and quaternion calculation |
| [tree.hh](http://tree.phi-sci.com/) | 3.1 | [GPL2/3](https://www.gnu.org/licenses/) | Yes | Neurite tree structure container |
| [rapidJSON](http://rapidjson.org/) | 1.1.0 | [MIT](https://opensource.org/licenses/MIT) | Yes | JSON file read/write |
| [spdlog](https://github.com/gabime/spdlog) | 0.11.0 | [MIT](https://opensource.org/licenses/MIT) | Yes | [Logging](classes/log.html) |
| [base-n](https://github.com/azawadzki/base-n) | 1.0 |  [MIT](https://opensource.org/licenses/MIT) | Yes | Write binary data (image) as base64 string |
| (optional) [UnitTest++](https://github.com/unittest-cpp/unittest-cpp) | 1.6.1 | [MIT](https://opensource.org/licenses/MIT) | No | Unit tests |

Specifically, these are the boost libraries used in NeuroSTR:

- [Geometry](http://www.boost.org/doc/libs/release/libs/geometry/) (header only)
- [Iterator](http://www.boost.org/doc/libs/release/libs/iterator/) (header only)
- [Any](http://www.boost.org/doc/libs/release/libs/any/) (header only)
- [Tokenizer](http://www.boost.org/doc/libs/release/libs/tokenizer/) (header only)
- [Format](http://www.boost.org/doc/libs/release/libs/format/) (header only)
- [Math](http://www.boost.org/doc/libs/release/libs/math/) (header only)
- [Filesystem](http://www.boost.org/doc/libs/release/libs/filesystem/)
- [Program options](http://www.boost.org/doc/libs/release/libs/program_options/)

## Install

1. Create a directory called `build` in the NeuroSTR source directory
1. Change to `build` directory and run the `cmake ..` command to configure your build and generate the *Makefile*. On Windows you can do the same with the *cmake-gui* app.
1. Run `make` from the `build` directory to compile the library and tools.
1. Run `make install` from the `build` directory to install the library headers, binaries and their bundled dependencies.

**Note:** To speed up the compilation process you can parallelize it using the `-j` flag in the `make` command. For example, to use 8 parallel threads the command will be `make -j 8 neurostr`

The `make install` command will copy the library headers, binaries and their bundled dependencies to the following directories in the install directory:

- `lib/neurostr/` for the library binary
- `bin/` for the executables
- `include/neurostr` for the library headers
- `include/` for the bundled headers

There are several variables that you can set while running the `cmake` command to change the default install directory (`/usr/local`) or to avoid installing the bundled libraries or the executables:

| Flag | Default value | What it does...|
|:--| :--: |:-
|`CMAKE_INSTALL_PREFIX` | `/usr/local` | Default install directory |
|`NO_INSTALL_BUNDLED` | `false` | If true, bundled headers are not installed |
|`NO_INSTALL_RAPIDJSON` | `false` | If true, rapidjson headers are not installed |
|`NO_INSTALL_SPDLOG` | `false` | If true, spdlog headers are not installed |
|`NO_INSTALL_TREE` | `false` | If true, tree.hh header is not installed |
|`NO_INSTALL_BASEN` | `false` | If true, basen.hhp header is not installed |
|`NO_INSTALL_TOOLS` | `false` | If true, executables are not installed |

For example, this will install the library but not the tools at `/home/cig/local`:

`cmake -DCMAKE_INSTALL_PREFIX="/home/cig/local" -DNO_INSTALL_TOOLS=true ..`

**Warning:** You will probably need super user privileges to install the library in the default install directory.
