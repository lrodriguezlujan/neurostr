---
currentSection: class
currentSubsection: io
currentItem:
---
# namespace `io` {#namespace_io}

IO namespace contains write/read functionality for most common file formats.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``ASCParser``](#class_io__a_s_c_parser)    |
`class `[``DATParser``](#class_io__d_a_t_parser)    |
`class `[``JSONParser``](#class_io__j_s_o_n_parser)    |
`class `[``JSONWriter``](#class_io__j_s_o_n_writer)    |
`class `[``Parser``](#class_io__parser)    |
`class `[``SWCParser``](#class_io__s_w_c_parser)    |
`class `[``SWCWriter``](#class_io__s_w_c_writer)    |
`struct `[``contour_info``](#struct_io_contour__info)    | [Contour](core.html#class__contour) header in DAT files.
`struct `[``marker_type``](#struct_io_marker__type)    | Markerset structure for NL files.
`struct `[``subtree_info``](#struct_io_subtree__info)    | SubTree header in DAT files.
`struct `[``tree_info``](#struct_io_tree__info)    | Tree header in DAT files.

---

# class `ASCParser` {#class_io__a_s_c_parser}

```cpp
class ASCParser
  : public neurostr::io::Parser
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  ASCParser(std::istream & stream)` | Creates a ASC parser.
`public inline  ~ASCParser()` | Default.
`public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` | Reads a reconstruction from the stream.
`protected `[`block_type`](#namespace_io_1afaa11ac86606a3d09b761ace634cf00d)` next_block_type(bool in_block)` | Deduces the type of the next block.
`protected void process_(`[`Reconstruction`](core.html#class_reconstruction)` & r)` | Process a single reconstruction.
`protected PropertyMap::property_type process_property()` | Process a property in the stream.
`protected `[`Node`](core.html#class_node)` process_sample()` | Process a sample (node) in the stream.
`protected Neurite::branch_iterator process_container_(const Neurite::branch_iterator & pos)` | Process a Tree (or contour) inserting the nodes in the container as children of the given parent.

## Members


### `public inline  ASCParser(std::istream & stream)` {#class_io__a_s_c_parser_1a4281053f992187a93904c0fb835c7a46}

Creates a ASC parser.

#### Parameters
* `s` Input stream to read from





#### Returns
A ASC parser

---

### `public inline  ~ASCParser()` {#class_io__a_s_c_parser_1afd4cab77214ac891d319b60905edc412}

Default.



---

### `public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` {#class_io__a_s_c_parser_1a46ff65c270e10cddcea9ae467bdc3dfe}

Reads a reconstruction from the stream.

#### Parameters
* `name` [Reconstruction](core.html#class_reconstruction) ID





#### Returns
Unique ptr to the reconstruction (Ownership)

---

### `protected `[`block_type`](#namespace_io_1afaa11ac86606a3d09b761ace634cf00d)` next_block_type(bool in_block)` {#class_io__a_s_c_parser_1a4fe263349601b214f110842ca646786b}

Deduces the type of the next block.

#### Parameters
* `in_block` Flag: Called inside another block





#### Returns
block type

---

### `protected void process_(`[`Reconstruction`](core.html#class_reconstruction)` & r)` {#class_io__a_s_c_parser_1a7dd84e15a11a30f3dfd2d828cbe2914c}

Process a single reconstruction.

#### Parameters
* `r` [Reconstruction](core.html#class_reconstruction) to be fill

---

### `protected PropertyMap::property_type process_property()` {#class_io__a_s_c_parser_1a18a695cfd56901d37e10ecb4ef6ace70}

Process a property in the stream.

#### Returns
Extracted property

---

### `protected `[`Node`](core.html#class_node)` process_sample()` {#class_io__a_s_c_parser_1a51dd3968142e4c0ab453d995e2d988e0}

Process a sample (node) in the stream.

#### Returns
[Node](core.html#class_node)

---

### `protected Neurite::branch_iterator process_container_(const Neurite::branch_iterator & pos)` {#class_io__a_s_c_parser_1acde7b14efc0aa8e001bef830ab6f0fa0}

Process a Tree (or contour) inserting the nodes in the container as children of the given parent.

#### Parameters
* `parent` Point of insertion





#### Returns
Last point of insertion


---

# class `DATParser` {#class_io__d_a_t_parser}

```
class DATParser
  : public neurostr::io::Parser
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  DATParser(std::istream & stream)` | Creates a DAT parser.
`public inline  ~DATParser()` | Default.
`public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string &)` | Reads a reconstruction from the stream.
`protected bool valid_header()` | Checks that the header is correct.
`protected std::string process_string(std::size_t len)` | Process binary string block.
`protected `[`Node`](core.html#class_node)` process_sample()` | Process binary sample block.
`protected PropertyMap::property_type process_property()` | Process binary property block.
`protected `[`marker_type`](#struct_io_marker__type)` process_markerset()` | Proces binary markeset block.
`protected std::vector< `[`Node`](core.html#class_node)` > process_samplelist_()` | Process sample list block.
`protected std::vector< PropertyMap::property_type > process_proplist_()` | Porcess list of properties.
`protected std::vector< `[`marker_type`](#struct_io_marker__type)` > process_markersetlist_()` | Process list of markers.
`protected std::size_t process_container_(const Neurite::branch_iterator & pos)` | Process container block in buffer.
`protected void process_block_(`[`Reconstruction`](core.html#class_reconstruction)` & r)` | Process block in buffer.
`protected void skip_block()` | Skips current block in buffer.

## Members

### `public inline  DATParser(std::istream & stream)` {#class_io__d_a_t_parser_1accfd60cb87cf61102d058287a36842bd}

Creates a DAT parser.

#### Parameters
* `s` Input stream to read from





#### Returns
A DAT parser

---

### `public inline  ~DATParser()` {#class_io__d_a_t_parser_1af5cc747f09dd5924c91bf39a483f8b75}

Default.



---

### `public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string &)` {#class_io__d_a_t_parser_1a5d1c835f4fbcfb9e4d6ff32973717b6c}

Reads a reconstruction from the stream.

#### Parameters
* `name` [Reconstruction](core.html#class_reconstruction) ID





#### Returns
Unique ptr to the reconstruction (Ownership)

---

### `protected bool valid_header()` {#class_io__d_a_t_parser_1a242dff70aa930ad91597048e12e7a561}

Checks that the header is correct.

#### Returns
True if header is valid

---

### `protected std::string process_string(std::size_t len)` {#class_io__d_a_t_parser_1a2c3459475f6e5269ef292648fe6b726e}

Process binary string block.

#### Parameters
* `len` String length





#### Returns
String

---

### `protected `[`Node`](core.html#class_node)` process_sample()` {#class_io__d_a_t_parser_1a961e72137c4c234214d2e5118f28eb39}

Process binary sample block.

#### Returns
[Node](core.html#class_node)

---

### `protected PropertyMap::property_type process_property()` {#class_io__d_a_t_parser_1a2f067db0775c753fa0e57ffdc653ff19}

Process binary property block.

#### Returns
Property

---

### `protected `[`marker_type`](#struct_io_marker__type)` process_markerset()` {#class_io__d_a_t_parser_1a1e378e0c180503f53006c83ce5366533}

Proces binary markeset block.

#### Returns
Marker

---

### `protected std::vector< `[`Node`](core.html#class_node)` > process_samplelist_()` {#class_io__d_a_t_parser_1acd5afed8d8d51c2510a66d4bb184cdc4}

Process sample list block.

#### Returns
[Node](core.html#class_node) vector

---

### `protected std::vector< PropertyMap::property_type > process_proplist_()` {#class_io__d_a_t_parser_1a63fbc378663483a61324340395d4892a}

Porcess list of properties.

#### Returns
Property vector

---

### `protected std::vector< `[`marker_type`](#struct_io_marker__type)` > process_markersetlist_()` {#class_io__d_a_t_parser_1aaa78418656baa71a62a72b9f841980b5}

Process list of markers.

#### Returns
Vector of markers

---

### `protected std::size_t process_container_(const Neurite::branch_iterator & pos)` {#class_io__d_a_t_parser_1a727bd6be60a4afb7dcbb0a3dcd589752}

Process container block in buffer.

#### Parameters
* `pos` Insertion position





#### Returns
Number of bytes extended

---

### `protected void process_block_(`[`Reconstruction`](core.html#class_reconstruction)` & r)` {#class_io__d_a_t_parser_1a08317b18972148486669be5704bdb293}

Process block in buffer.

#### Parameters
* `r` [Reconstruction](core.html#class_reconstruction) to fill

---

### `protected void skip_block()` {#class_io__d_a_t_parser_1a31d4ca1a0cdd1b03b57229f9d37bbc2d}

Skips current block in buffer.




---

# class `JSONParser` {#class_io__j_s_o_n_parser}

```
class JSONParser
  : public neurostr::io::Parser
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  JSONParser(std::istream & stream)` | Creates a JSON parser.
`public inline  ~JSONParser()` | Default.
`public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` | Reads a reconstruction from the stream.

## Members


### `public inline  JSONParser(std::istream & stream)` {#class_io__j_s_o_n_parser_1a8d24951c56b9ea05ca0e5f7c63a79210}

Creates a JSON parser.

#### Parameters
* `s` Input stream to read from





#### Returns
JSON parser

---

### `public inline  ~JSONParser()` {#class_io__j_s_o_n_parser_1a0220ff0fd0f2c9597dea7d248f86dee1}

Default.



---

### `public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` {#class_io__j_s_o_n_parser_1a4c04c2788638cf4a9cdef1558fec434b}

Reads a reconstruction from the stream.

#### Parameters
* `name` [Reconstruction](core.html#class_reconstruction) ID





#### Returns
Unique ptr to the reconstruction (Ownership)


---

# class `JSONWriter` {#class_io__j_s_o_n_writer}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  JSONWriter(std::ostream & s,bool pretty)` | Creates a writer over the given output stream.
`public inline  ~JSONWriter()` | Default.
`public void write(const `[`neurostr::Reconstruction`](core.html#class_reconstruction)` & r)` | Writes a reconstruction.
`public void writeNeuron(const `[`neurostr::Neuron`](core.html#class_neuron)` & n)` | Writes a single neuron (wo rec.
`protected void writePoint(const neurostr::point_type & point)` | Writes a point object as {x,y,z}.
`protected void writeProperty(const neurostr::PropertyMap::const_iterator & p)` | Writes the given property as key:value.
`protected void writeSoma(const `[`neurostr::Neuron`](core.html#class_neuron)` & n)` | Writes the neuron soma as {nodes:[nodes]}.
`protected void writeContour(const `[`neurostr::Contour`](core.html#class__contour)` & c)` | Writes the given contour as an object.
`protected void writePropertyMap(const `[`neurostr::PropertyMap`](#class__property_map)` & pm)` | Writes the property map as an object {}.
`protected void writeNeurite(const `[`neurostr::Neurite`](core.html#class_neurite)` & n)` | Writes the neurite as an object { id:, type: , tree:}.
`protected void writeBranch(const neurostr::Neurite::tree_type::iterator_base & b,const `[`neurostr::Neurite`](core.html#class_neurite)` & n)` | Writes the given branch (member of n) as {root: node, properties: , nodes:[], children:[] }.
`protected void writeNode(const `[`neurostr::Node`](core.html#class_node)` & n)` | Writes a single node as {id,x,y,z,r,properties:{}}.

## Members


### `public  JSONWriter(std::ostream & s,bool pretty)` {#class_io__j_s_o_n_writer_1a919b74a083b573424b790554032c351d}

Creates a writer over the given output stream.

#### Parameters
* `s` Stream


* `pretty` If true, ouptut is prettyfied

---

### `public inline  ~JSONWriter()` {#class_io__j_s_o_n_writer_1a9451d8d0e762d6d10cc65130f6b2649d}

Default.



---

### `public void write(const `[`neurostr::Reconstruction`](core.html#class_reconstruction)` & r)` {#class_io__j_s_o_n_writer_1a6c9eb643f187431fac37562a6d9aa49f}

Writes a reconstruction.

#### Parameters
* `r` [Reconstruction](core.html#class_reconstruction)

---

### `public void writeNeuron(const `[`neurostr::Neuron`](core.html#class_neuron)` & n)` {#class_io__j_s_o_n_writer_1abd91c1647f3b723a749b0ae1e1661c19}

Writes a single neuron (wo rec.

contours)
#### Parameters
* `n` [Neuron](core.html#class_neuron)

---

### `protected void writePoint(const neurostr::point_type & point)` {#class_io__j_s_o_n_writer_1a6b4272449a21c1e7bf3d92525b866e02}

Writes a point object as {x,y,z}.

#### Parameters
* `point` 3D Point

---

### `protected void writeProperty(const neurostr::PropertyMap::const_iterator & p)` {#class_io__j_s_o_n_writer_1ae849967e57f7e43bbfe0c388cb181a6f}

Writes the given property as key:value.

#### Parameters
* `p` Property iterator

---

### `protected void writeSoma(const `[`neurostr::Neuron`](core.html#class_neuron)` & n)` {#class_io__j_s_o_n_writer_1ab0c824ff96a4f017c2168e61fa4e6266}

Writes the neuron soma as {nodes:[nodes]}.

#### Parameters
* `n` [Neuron](core.html#class_neuron)

---

### `protected void writeContour(const `[`neurostr::Contour`](core.html#class__contour)` & c)` {#class_io__j_s_o_n_writer_1a3042d90ce677118928559196d4c8e871}

Writes the given contour as an object.

[Contour](core.html#class__contour) points are in a array
#### Parameters
* `c` [Contour](core.html#class__contour)

---

### `protected void writePropertyMap(const `[`neurostr::PropertyMap`](#class__property_map)` & pm)` {#class_io__j_s_o_n_writer_1a21a341202c33b450be074bd7b2136408}

Writes the property map as an object {}.

#### Parameters
* `pm` Property map

---

### `protected void writeNeurite(const `[`neurostr::Neurite`](core.html#class_neurite)` & n)` {#class_io__j_s_o_n_writer_1ab315c2e4f8a4228b86f6f5551a336045}

Writes the neurite as an object { id:, type: , tree:}.

#### Parameters
* `n` [Neurite](core.html#class_neurite)

---

### `protected void writeBranch(const neurostr::Neurite::tree_type::iterator_base & b,const `[`neurostr::Neurite`](core.html#class_neurite)` & n)` {#class_io__j_s_o_n_writer_1a420a15878cd69cd016af8f502d5988b9}

Writes the given branch (member of n) as {root: node, properties: , nodes:[], children:[] }.

#### Parameters
* `b` [Branch](core.html#class_branch) iterator


* `n` [Neurite](core.html#class_neurite)

---

### `protected void writeNode(const `[`neurostr::Node`](core.html#class_node)` & n)` {#class_io__j_s_o_n_writer_1aef7b6e9240b9c470920d2c83e6a2352c}

Writes a single node as {id,x,y,z,r,properties:{}}.

#### Parameters
* `n` [Node](core.html#class_node)


---

# class `Parser` {#class_io__parser}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  Parser(std::istream & s)` | Constructs copy the istream reference.
`public inline virtual  ~Parser()` |
`public  Parser(const `[`Parser`](#class_io__parser)` &) = delete` | Deleted copy constructor.
`public `[`Parser`](#class_io__parser)` & operator=(const `[`Parser`](#class_io__parser)` &) = delete` | Deleted copy operator.
`public inline void reset_errors()` | Set the error count to the default state.
`public inline int error() const` | Get number of errors.
`public inline int warn() const` | Get number of warnigs.
`public inline bool critical() const` | Critical error flag.
`public std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` | Reads a reconstruction from the stream and returns a unique_ptr.
`protected std::istream & stream_` | Input stream variable.
`protected int error_count` | Error status.
`protected int warn_count` |
`protected bool critical_error` |
`protected inline void process_error(const std::exception & e)` | Processes the error, log it and increments the error count.

## Members


### `public inline  Parser(std::istream & s)` {#class_io__parser_1a41dc46858894bf40bc1a25b746db8f46}

Constructs copy the istream reference.

#### Parameters
* `s` Input stream

---

### `public inline virtual  ~Parser()` {#class_io__parser_1adff96012a3fc1487c4880afca2e3e25a}





---

### `public  Parser(const `[`Parser`](#class_io__parser)` &) = delete` {#class_io__parser_1a39aee4432fefafb571b200514a6ac254}

Deleted copy constructor.



---

### `public `[`Parser`](#class_io__parser)` & operator=(const `[`Parser`](#class_io__parser)` &) = delete` {#class_io__parser_1a4abdb30ae04711c7e9d96e0766c464ac}

Deleted copy operator.



---

### `public inline void reset_errors()` {#class_io__parser_1ac92fb6a6e75751939f42c60398e2b407}

Set the error count to the default state.



---

### `public inline int error() const` {#class_io__parser_1ae4b4264a278ae16bbc90680e7c88b0ca}

Get number of errors.

#### Returns
Error count

---

### `public inline int warn() const` {#class_io__parser_1ac90c5a65a09477652821241d520a229e}

Get number of warnigs.

#### Returns
Warning count

---

### `public inline bool critical() const` {#class_io__parser_1a123021c0facace7209c522ca22e1138c}

Critical error flag.

#### Returns
True if a critical error has happened.

---

### `public std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` {#class_io__parser_1a0b263f5851fe1fbf15f8f2ff8da1bffa}

Reads a reconstruction from the stream and returns a unique_ptr.

#### Parameters
* `name` [Reconstruction](core.html#class_reconstruction) ID





#### Returns
Unique ptr to the reconstruction (Ownership)

---

### `protected std::istream & stream_` {#class_io__parser_1af23a76f4ddea0e6220955345009c52b0}

Input stream variable.



---

### `protected int error_count` {#class_io__parser_1a5a8625f53a7b72e90fc27ad9a5eff33b}

Error status.



---

### `protected int warn_count` {#class_io__parser_1a3925a66a3d456e10188fe1f424a7705d}





---

### `protected bool critical_error` {#class_io__parser_1ae87fbae44066fc9a34edfdb9b1f21028}





---

### `protected inline void process_error(const std::exception & e)` {#class_io__parser_1aef43762839d79e57a709637d6035799a}

Processes the error, log it and increments the error count.

#### Parameters
* `e` Error


---

# class `SWCParser` {#class_io__s_w_c_parser}

```
class SWCParser
  : public neurostr::io::Parser
```  



luis

28/10/16

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const char comment_char` |
`public const size_t field_count` |
`public  SWCParser(std::istream & s)` | Creates a SWC parser with default separators (space)
`public  SWCParser(std::istream & s,const std::string & sep)` | Creates a SWC parser with given separators.
`public  ~SWCParser()` | Default.
`public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` | Reads a reconstruction from the stream.
`public bool is_key(const std::string & s) const` | Checks if the given string is a known property name.
`public void add_property_key(const std::string &)` | Adds a string to the set of recognized property keys.
`public void remove_property_key(const std::string &)` | Removes a string of the set of recognized property keys.
`public const std::set< std::string > & get_property_keys() const` | Retrieves the set of recognized property keys.
`protected separator sep_` |
`protected `[`Neuron`](core.html#class_neuron)` * neuron_` |
`protected std::set< std::string > property_keys_` |

## Members


### `public const char comment_char` {#class_io__s_w_c_parser_1ac39e7742d234ea90e458e12043933e9a}





---

### `public const size_t field_count` {#class_io__s_w_c_parser_1add660a818d25a32783b734328109624b}





---

### `public  SWCParser(std::istream & s)` {#class_io__s_w_c_parser_1aae94a52eb73e510dcde2e3882fcf54ca}

Creates a SWC parser with default separators (space)

#### Parameters
* `s` Input stream to read from





#### Returns
A SWC parser

---

### `public  SWCParser(std::istream & s,const std::string & sep)` {#class_io__s_w_c_parser_1a561b86a2f30f1d2ff6f881569cff94ba}

Creates a SWC parser with given separators.

#### Parameters
* `s` Input stream


* `sep` String of separator characters





#### Returns
A SWC parser

---

### `public  ~SWCParser()` {#class_io__s_w_c_parser_1a2c4d8a15cd3153a34639e44087a185cd}

Default.



---

### `public virtual std::unique_ptr< `[`Reconstruction`](core.html#class_reconstruction)` > read(const std::string & name)` {#class_io__s_w_c_parser_1a10437ca1a53c80a0ccc41025aae8b30c}

Reads a reconstruction from the stream.

For SWC files the return will always consist of a reconstruction with exactly one neuron and no contour
#### Parameters
* `name` [Reconstruction](core.html#class_reconstruction) ID





#### Returns
Unique ptr to the reconstruction (Ownership)

---

### `public bool is_key(const std::string & s) const` {#class_io__s_w_c_parser_1ae24c59f1d8a9a28a26c094e14e42ec13}

Checks if the given string is a known property name.

#### Parameters
* `s` String to check





#### Returns
True if the string is in the property key set

---

### `public void add_property_key(const std::string &)` {#class_io__s_w_c_parser_1ab5c3b3a353a7dde327b3a3e9bc4c0f50}

Adds a string to the set of recognized property keys.

#### Parameters
* `s` String to add

---

### `public void remove_property_key(const std::string &)` {#class_io__s_w_c_parser_1a0cef22f421e8ca4557d6ceabc93aefe3}

Removes a string of the set of recognized property keys.

#### Parameters
* `s` String to add

---

### `public const std::set< std::string > & get_property_keys() const` {#class_io__s_w_c_parser_1ae163365eb0c33ceefb875c72f72a7295}

Retrieves the set of recognized property keys.

#### Returns
Set of strings

---

### `protected separator sep_` {#class_io__s_w_c_parser_1a78c400aff05579899681b6ec5be0c073}





---

### `protected `[`Neuron`](core.html#class_neuron)` * neuron_` {#class_io__s_w_c_parser_1ae0046bb01cf2943f8330e44bfa55c4ce}





---

### `protected std::set< std::string > property_keys_` {#class_io__s_w_c_parser_1a52c84546713ca2bbf7d5e98fdbaf4015}






---

# class `SWCWriter` {#class_io__s_w_c_writer}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const char comment_char` |
`public const int no_parent_id` |
`public  SWCWriter(std::ostream &)` | Creates a writer over the given stream.
`public  ~SWCWriter()` |
`public std::ostream & write(`[`Neuron`](core.html#class_neuron)` &) const` | Writes the given neuron in SWC format.
`protected void writeHeader(`[`Neuron`](core.html#class_neuron)` &) const` | Writes document header.
`protected void writeData(`[`Neuron`](core.html#class_neuron)` &) const` | Writes [Neuron](core.html#class_neuron) node positions (SWC DATA)

## Members


### `public const char comment_char` {#class_io__s_w_c_writer_1a33e3411bb9578026ffa0fedeac96dd70}





---

### `public const int no_parent_id` {#class_io__s_w_c_writer_1a78c2aa365ef0acfef712e954020f7f63}





---

### `public  SWCWriter(std::ostream &)` {#class_io__s_w_c_writer_1a8a6d49931b7c0469aad29ab952c4f74e}

Creates a writer over the given stream.

#### Returns
[SWCWriter](#class_io__s_w_c_writer)

---

### `public  ~SWCWriter()` {#class_io__s_w_c_writer_1aabe7d01639bc9a7ca975902c14d1dd85}





---

### `public std::ostream & write(`[`Neuron`](core.html#class_neuron)` &) const` {#class_io__s_w_c_writer_1a0ade9b9f2e949b13a49348f584b17838}

Writes the given neuron in SWC format.

#### Returns
Output stream reference

---

### `protected void writeHeader(`[`Neuron`](core.html#class_neuron)` &) const` {#class_io__s_w_c_writer_1a0c160de31da5f1055950da486013e77e}

Writes document header.

Static header + properties as comments

---

### `protected void writeData(`[`Neuron`](core.html#class_neuron)` &) const` {#class_io__s_w_c_writer_1a54dadd3ec177eb3907a85295a76ecb1d}

Writes [Neuron](core.html#class_neuron) node positions (SWC DATA)




---

# struct `contour_info` {#struct_io_contour__info}


[Contour](core.html#class__contour) header in DAT files.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::uint16_t closed` |
`public std::uint8_t face_color` |
`public std::uint8_t back_color` |

## Members


### `public std::uint16_t closed` {#struct_io_contour__info_1a4cf89e08b8de78314e1d624f0b09c8f4}





---

### `public std::uint8_t face_color` {#struct_io_contour__info_1a5f3b2d781fa9d76032f4acd766115630}





---

### `public std::uint8_t back_color` {#struct_io_contour__info_1a540e6a96260f2a04ec9882005a01ca3c}






---

# struct `marker_type` {#struct_io_marker__type}


Markerset structure for NL files.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public std::string name` |
`public std::uint8_t color` |
`public std::vector< property_type > properties` |
`public std::vector< `[`Node`](core.html#class_node)` > samples` |

## Members


### `public std::string name` {#struct_io_marker__type_1a67a9f33791d4fdacdfe083b8a18ce5be}





---

### `public std::uint8_t color` {#struct_io_marker__type_1a4b5b80b828c9dbb29a4b80ceb2b74eb5}





---

### `public std::vector< property_type > properties` {#struct_io_marker__type_1a7cb4d574f7c72944c42efa9c8b49ebc3}





---

### `public std::vector< `[`Node`](core.html#class_node)` > samples` {#struct_io_marker__type_1a50ee62f0e72af18d009bb6e457d0a35e}






---

# struct `subtree_info` {#struct_io_subtree__info}


SubTree header in DAT files.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public uint16_t value1` |
`public uint16_t value2` |

## Members


### `public uint16_t value1` {#struct_io_subtree__info_1aaeb1f9cbd685020f0e1a7efeda372245}





---

### `public uint16_t value2` {#struct_io_subtree__info_1a56654a3ae5c20d2655f6b5b71041c75b}






---

# struct `tree_info` {#struct_io_tree__info}


Tree header in DAT files.



## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`tree_type_cd`](#namespace_io_1af221fa2a265eae62fc8a3327203fa2a6)` type` |
`public uint8_t face_color` |
`public uint8_t back_color` |

## Members


### `public `[`tree_type_cd`](#namespace_io_1af221fa2a265eae62fc8a3327203fa2a6)` type` {#struct_io_tree__info_1aa33774c5d1d2038d8bd887b314cde67e}





---

### `public uint8_t face_color` {#struct_io_tree__info_1a7fa9500ef8426472d6991f80a179144e}





---

### `public uint8_t back_color` {#struct_io_tree__info_1a9186732b21bc4e238cd0d0b817f90a7b}
