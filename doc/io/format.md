---
currentSection: io
currentSubsection: formats
currentItem:
---
# Input
text

<a id="SWC"></a>

## Standard SWC  

The standard SWC files are tabular text files (ASCII encoded) with two types of lines, the header/comment lines and the data lines. A simple SWC file look as follows:

```
# This is a SWC example file
# with some header lines
#
# With space-delimited data fields: Node ID Type X Y Z Diameter Parent ID
1 1 0.0 0.0 0.0 0.1 -1
```

SWC files are contain only one neuron per file, and don't contain other structures such as markers or contours. Parent nodes are required to be declared before their descendants.

### Header

Header/comment lines start with the pound character '#'. The whole line is considered a comment. Although we call them *header lines*, comments can be placed anywhere in the file.

Reconstruction properties can be placed in header lines of the SWC file, but this functionality is not standard. The parser identifies keywords (property names) in the comments and stores the rest of the line as its value.

```
# Region Hippocampus
# Creature Rat
# MyOwnKey This is the property value if myownkey is a registered key
#
# Note that the property format is: Key/Name[Space]Value
```

There are 16 default keys (check the list below), but you can add or remove any key to the list. Key matching is case-insensitive, so you don't need to worry about upper or lower case characters. All property values are processed as strings and added to the reconstruction property map.

**Default property keys**
- Original_source
- Creature
- Region
- Field
- Layer
- Field/Layer
- Type
- Contributor
- Reference
- Raw
- Extras
- Soma_area
- Shrinkage_correction
- Version_number
- Version_date
- Scale

### Data

Data lines are simple text line with space-separated values for storing data in a tabular structure. Each line/record contains 7 data fields that corresponds to one [Node](../goal) in the reconstruction.

#### Data fields

|Position|Field|Type|Description|
|:--|:--|:--|:--|
|1| Node ID| Non negative integer  | Node unique ID. Ususally starts at 1
|2| Node type ID| Non negative integer | Node type ([Type table](#swc_nodetype))
|3| X value| Real number | Node x position
|4| Y value| Real number | Node y position
|5| Z value| Real number | Node z position
|6| Diameter| Non negative Real number | Node diameter value
|7| Parent node ID| -1 or non negative integer| Parent node ID. -1 For no parent node.

<a id="swc_nodetype"></a>

#### Node types

|Type ID| Value|
|:--|:--|
|0| Undefined|
|1| Soma |
|2| Axon |
|3| Dendrite|
|4| Apical |
|5| Other|

### Errors

The SWC parser is tolerant to errors. This means that it will try to continue parsing the document when he find faulty lines. These errors will be registered as warnings in the logger and the faulty lines are usually skipped. You should check the warning count after reading a file.

#### Error types

|Error| Description | Line is discarded?|
|:--|:--|:--:|
| **Missing fields** | The data line has less than 7 fields | Yes
| **Field type mismatch** | The value of some data field doesn't match the expect type | Yes
| **Negative diameter value** | The diameter value is negative | Yes
| **Orphan node** | Can't find the parent node in the reconstruction | Yes
| **Extra fields** | There are extra fields at the end of the data line | Yes

<a id="ASC"></a>

## Neurolucida ASCII

**WARNING:** The Neurolucida ASCII format specification is not available. This means that the parser and all the content in this section is based on knowledge extracted from a variety of sample files. If you have a valid ASC file that isn't accepted by the parser, please contact us to fix the issue.

The Neurolucida ASCII (so called ASC files) are the ASCII encoded text format used by the Neurolucida neuron reconstruction software. The ASC files are built by blocks in a tree-structure.

The ASC files support inline comments starting with the semicolon character:

```
; This is a valid comment that spans until the end of the line
(x y z d) ; This is also a valid comment
```

Blocks are delimited by special character sequences. These are the delimiter characters for our parser:

|Character| Action|
|:--:|:--|
| `;` | Inline comment |
| `(` | Block start |
| `)` | Block end |
| &#124; | Sibling branch start. It is equivalent to `)(`. |
| `<` | Spine start|
| `>` | Spine end |
| `""`| String escape|

The parser works as follows:
1. Skips comments, spaces and empty lines until it finds a *stopper* character
2. If the *stopper* is a block start character, it tries to read the first value to infer the block type
3. If the block is determined as a *Tree* block, processes it recursively (go to 1), otherwise it process the block according to the deduced type.
4. Go to 1 until it finds a block end character or the file ends

#### Block types

| Block | Description | Detection logic |
|:--|:--|:--|
|Contour | Set of samples that delimit an area | It is the only named block. Starts with a escaped string
|Tree | Container. First block of the tree ([Neurite]) - can contain properties, samples, etc.| Got an empty value when trying to read inside the block
|Property | Key-value pair, values can be empty, string, numeric or colors | First value is a non-escaped string
|Marker set | Tags in the reconstruction | Like properties but with special names: doublecircle, filledcircle...
|Sample | Reconstruction [Node] (x,y,z,d) | First value is numeric
|Sub tree  | Containers inside a tree ([Branch]) | Got an empty value when trying to read inside the block and we are already inside a tree block.
|Spine | Spine position mark. We ignore it | Spine start detected

A single ASC file can contain several neurons. Neurons' somas are contours with the name "cellbody" (and also an empty property with name "cellbody"). Somas are required to be defined before their trees ([Neurite]). For each soma contour a new neuron is created in the reconstruction. Trees are attached to the closest soma in the reconstruction. The parser assigns an auto-incremental ID (starting at 1) to each [Node] in the file.

### Errors

The ASC parser is tolerant to errors. This means that it will try to recover from error found when parsing the document. It tries to skip the faulty blocks (and emits a warning), but if it cannot recover from the error, it will emit one. All warnings and errors are registered through the logger, and can be checked after calling the `read` function.

#### Error types

|Error| Description | Block is discarded?|
|:--|:--|:--:|
| **Wrong termination** | Block end was expected but some other character/value was found | Yes
| **Type mismatch** | Block or value types don't match the expected ones | Yes
| **End of file reached** | EOF reached while trying to recover from a error | Yes - Fatal
| **Non empty ended** | Unexpected value at the end of a block | Yes

 <a id="DAT"></a>

## Neurolucida DAT

**WARNING:** The Neurolucida binary DAT format specification is not available. This means that the parser and all the content in this section is based on knowledge extracted from a variety of sample files. If you have a valid DAT file that isn't accepted by the parser, please contact us to fix the issue. The current specification is an extension of the [NLMorphologyConverter  documentation](http://neuronland.org/NLMorphologyConverter/MorphologyFormats/NeurolucidaDAT/Spec.html)

The Neurolucida DAT files are the binary (little-endian) format used by the Neurolucida neuron reconstruction software. The DAT files are build by blocks in a tree-structure like the ASC files. Obviously, DAT files don't support comments and they are not "human-readable".

The DAT files start with a 70-byte header and end with a 4-byte footer. The parser verifies that the header matches before staring to read the file and emits an error if the footer don't match.

All data blocks share a 6 byte long common header (block header). This header identifies the type of the block and its size (including any sub-blocks). However, in practices, we notice that the size declared in some blocks don't match their real size.

#### Block header

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Block type | 0 | 2 | Block types as a 16-bit unsigned int|
| Block size | 2 | 4 | Block size as a 32-bit unsigned int. This size includes the header itself and all sub-blocks|

There are [18 block types](http://neuronland.org/NLMorphologyConverter/MorphologyFormats/NeurolucidaDAT/Spec.html) that can be identified by the `block type` field value. Most of them are processed by the parser, and their information added to the reconstruction, but a little subset is either skipped or ignored

#### Block types

| Block type | Hex value | Processed | Ignored | Comments |
| :--        | :--       | :--       | :--     | :--   |
| String        | `0x0001` | Yes  | No | |
| Sample        | `0x0101` | Yes  | No| |
| Sample List   | `0x0103` | Yes  | No| |
| Property      | `0x0104` | Yes  | No| |
| Property list | `0x0105` | Yes  | No| |
| Contour       | `0x0201` | Yes  | No| |
| Tree          | `0x0202` | Yes  | No| |
| Sub Tree      | `0x0203` and `0x0209` | Yes / No  | No| Second subtree id is not processed |
| Markerset     | `0x0204` | Yes  | Yes| Usually the declared size don't match the real size. Expect warnings |
| Markerset list| `0x0205` | Yes  | Yes| Usually the declared size don't match the real size. Expect warnings |
| Spine         | `0x0206` | Yes  | Yes| |
| Spine list    | `0x0207` | Yes  | Yes| |
| Text          | `0x0208` | No  | -| |
| Thumbnail     | `0x0401` | No  | -| |
| Description   | `0x0402` | No  | -| |
| Image         | `0x0403` | Yes  | No| Image is store as a base64 encoded string in a property called 'image'|

A single DAT file can contain several neurons. Neurons' somas are contours with an empty property with name "cellbody". Somas are required to be defined before their trees ([Neurite]). For each soma contour a new neuron is created in the reconstruction. Trees are attached to the closest soma in the reconstruction. Trees ([Neurite]) and subtrees ([Branch]) are processed recursively to build the neurites gradually.

### Block details

<a id="strblock"></a>

#### String block

String blocks contain ASCII-encoded strings. The string are not usually null-ended (that is, the last character is not `\0`), so the string length is the total block length minus the header size (6 bytes). This is done by the `get_value` function.

<a id="sampleblock"></a>

#### Sample block

Sample blocks are the representation of [Node]s in the file. They contain the position, diameter and section (slice number) of each node. The parser assigns an auto-incremental ID (starting at 1) to each [Node] in the file. The data which follows the header is:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| X position | 0 | 4 | X position as a 32-bit float number
| Y position | 4 | 4 | Y position as a 32-bit float number
| Z position | 8 | 4 | Z position as a 32-bit float number
| Diameter   | 12 | 4 | Diameter position as a 32-bit float number
| Section    | 16 | 2 | Section as a 16-bit unsigned integer

<a id="propblock"></a>

#### Property block

Property blocks are key-value pairs where the value can be empty, a string, or a number. Properties are inserted in the property map of the neuron element that contains them (usually a [Neuron] or [Neurite]). The data which follows the header is:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Property name | 0 | Variable (*s_len*) | Property name. A [String block](#strblock)
| Has value flag | *s_len* | 2 | A 16-bit unsigned integer. If it is not equal to 0 the property is not empty (it has a value).
| String valued flag | *s_len* + 2 | 2 | Flag as a 16-bit unsigned integer. If it is not equal to 0 the property value is A [string block](#strblock)
| Value   | *s_len* + 4 | Variable | Property value. Either a 32-bit float number or a [string block](#strblock)

#### Contour block

Contour blocks are plain containers with usually a [sample list](#sampleblock) and some [properties](#propblock). They have a contour block header with some common properties:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Closed flag | 0 | 2 | A 16-bit unsigned integer. If it is not equal to 0 the contour is closed. Stored as a bool-valued property named "closed"
| Face color |2 | 3 | Three bytes (RGB) that determine the contour face (line) color. Stored as a hexstring-valued property named "face_color" (#RRGGBB)
| Back color | 5 | 3 | Three bytes (RGB) that determine the contour back (fill) color. Stored as a hexstring-valued property named "back_color" (#RRGGBB)

Additionally, there are some properties that appear in almost every contour with some auxiliar information about the contour:

| Property name | Value type | Description
| :-- | :--: | :--|
| filldensity | Float | Contour fill opacity
| name | [String](#strblock) | Contour name
| resolution | Float | Unknwon

#### Markerset block

Markers are simply tags located in the 3D space. Probably their position matches the position of a existing [Node], but it is not confirmed yet. They contain the following block after the header:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Marker name | 0 | Variable (*s_len*) | Marker name. A [String block](#strblock)
| Unknown | *s_len* | 4 | Unknown. RGBA color? flags? 32-bit float? To be determined.
| Property list | *s_len* + 4 | Variable (*p_len*) | Marker properties
| Sample list   | *s_len* + *p_len* + 4 | Variable | Marker positions. Usually a single sample node.

Markers are processed and a `marker_type` structure is filled with their data, but the it is not added to the reconstruction (maybe in the future...).

#### Tree block

Tree blocks are complex containers that contain other blocks (sample, subtree, properties, markers...). They are the representation of a [Neurite] in the file. There is a tree-specific header following the block header:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Neurite type | 0 | 2 | A 16-bit unsigned integer. Numeric ID for the Neurite type.
| Face color |2 | 3 | Three bytes (RGB) that determine the face (line) color. Stored as a hexstring-valued property named "face_color" (#RRGGBB)
| Back color | 5 | 3 | Three bytes (RGB) that determine the back (fill) color. Stored as a hexstring-valued property named "back_color" (#RRGGBB)

The tree type codes are:

| Tree type | Hex value |
| :--        | :--       |
| Axon        | `0x00` |
| Dendrite        | `0x01` |
| Apical   | `0x02` |

Then the tree block can contain any block but tree, contour, text, thumbnail, image or description nodes. The blocks within a tree block can appear in any order.

#### Subtree block

Tree blocks are complex containers that contain other blocks (sample, subtree, properties, markers...). They are the representation of a [Branch] in the file. They have a 4-byte header following the block header which meaning is unknown:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Unknown | 0 | 4 | Unknown. RGBA color? flags? 32-bit float? To be determined.

Then the subtree block can contain any block but tree, contour, text, thumbnail, image or description nodes. The blocks within a subtree block can appear in any order.

#### List blocks

There are four possible types of list blocks: sample list, property list, marker list and spine list. All list block share the same header following the block header:

| Field | Offset (bytes) | Length (bytes) | Description
| :-- | :--: | :--|
| Number of elements | 0 | 2 | Number of blocks in the list as a 16-bit unsigned integer
| Content | 2 | variable | Set of blocks (sample, property, marker or spine) that are part of the list

### Errors

The DAT parser is tolerant to errors. It will try to recover from error found when parsing the document. It tries to skip the faulty blocks (and emits a warning), but if it cannot recover from the error, it will emit one. All warnings and errors are registered in the logger, and their count can be checked after calling the `read` function.

#### Error types

|Error| Description | Block is discarded?| Critical? (parsing stops) |
|:--|:--|:--:|:--:
| **Invalid header** | Header check failed | Yes | Yes
| **Buffer expansion required** | Blocks spans past the declared size | No | No
| **Missing block name** | First inner block is not a string in named blocks | Yes | No
| **Block type don't match** | Got a unexpected block type | Yes | No
| **Missing block** | Unexpected block ending | Yes | No
| **Buffer size exceeded** | Block size greater than the buffer size. This is probably a consequence of a previous error | Yes | Yes
| **Unexpected End of File** | EOF reached while reading a block (wrong footer?) | Yes | Yes

<a id="JSON"></a>

## JSON  

**NOTE:** The structure defined in this section is work in progress and might change drastically in the close future.

The JSON (acronym of JavaScript Object notation) is syntactically  identical to the code used for creating objects in JavaScript. In practice, it has become a lightweight data-interchange format across different applications and languages. Here we propose a JSON structure to represent three-dimensional neuron reconstructions, initially defined for our own use.

So you might wonder, why JSON?. We wanted a format easy to read and write for both humans and computer programs. There are JSON parsers and writers for every programming language, or at least for the popular ones. Also, we need a file format capable of storing complex structures and easy to extend in the future. [Here](http://www.w3schools.com/js/js_json_syntax.asp) you can learn about syntax and get some examples.

The proposed structure is a hierarchical structure, somewhat similar to the structure used in the Neurolucida formats. We define 8 objects (blocks) to be part of our structure. Each one corresponds to a data structure in the [data model](../data_model.html)(with a couple of exceptions). In bottom-top order, the objects are:

- **3DPoint** A three dimensional point
- **PropertyMap** Set of key-value pairs
- **Node**  Equivalent to data model [Node]
- **Branch** Equivalent to data model [Branch]
- **Neurite** Equivalent to data model [Neurite]
- **Neuron**   Equivalent to data model [Neuron]
- **Contour**  Equivalent to data model [Contour]
- **Reconstruction**  Equivalent to data model [Reconstruction]

A valid JSON document can be a single *Neuron* or *Reconstruction* object. Below you can find the specifications for each object type. Please note that you can add extra elements to any object described here, as long as they do not have the same key as a required member.

<a id="json_point"></a>

### 3DPoint Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| x | Number | Yes | x coordinate value
| y | Number | Yes | y coordinate value
| z | Number | Yes | z coordinate value

##### Example

```json
{
  "x" : 1.0,
  "y" : 0.0,
  "z" : 0.0
}
```
---

<a id="json_propertymap"></a>

### PropertyMap Object

Property map are simply objects whose members are properties. The member's name is the property key and its value is the property value. However, not every property value is accepted:

##### Accepted values

| Value type | Representation |
| :-- | :--: |
| Empty value | `"empty" : []` |
| Integer | `"integer" : 10` |
| Float | `"float" : 3.14` |
| Boolean | ` "bool_A" : true, "bool_B" : false` |
| String | `"string" : "text"` |
| Point | [3DPoint object](#json_point) -  `"point" : {"x" : 1.0, "y" : 0.0, "z" : 0.0}` |


##### Example

```json
{
  "description" : "this is an example property map",
  "creature" : "rat",
  "width" : 100.00,
  "height" : 100.00,
  "some random number" : 1,
  "this is a good example?" : false
}
```

---

<a id="json_node"></a>

### Node Object

Node objects can be seen as a point objects with some extra required fields and, optionally, a property map.

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| id | Integer (>= 0)| Yes | Node unique ID
| x | Number | Yes | Node x coordinate value
| y | Number | Yes | Node y coordinate value
| z | Number | Yes | Node z coordinate value
| r | Number (>= 0) | Yes | Node radius
| properties | [Property Map](#json_propertymap) | No | Node properties

##### Example

```json
{
  "id" : 42,
  "x" : 1.0,
  "y" : 1.0,
  "z" : 1.0,
  "r" : 0.01,
  "properties" : {
    "fake" : true
  }
}
```

---

<a id="json_branch"></a>

### Branch Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| root | [Node object](#json_node)| No (but it will show a wanrning msg) | Branch root node
| nodes | Array of [Node objects](#json_node) | Yes | Nodes which are part of the [Branch]
| properties | [Property Map](#json_propertymap) | No | Branch properties
| children | Array of Branch objects | No | Daughter branches of the given one

##### Example

```json
{
  "root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
	"nodes" : [
	   { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0}
	],
	"children":[
    {
		    "root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
				"nodes" : [
				      { "id": 6, "x": 4.0, "y": 1.0, "z" : 1.0 , "r": 0.0}
				]
		},
		{
		    "root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
				"nodes" : [
  			     { "id": 7, "x": 4.0, "y": 1.0, "z" : -1.0 , "r": 0.0}
				]
    }
  ]
}
```

---

<a id="json_neurite"></a>

### Neurite Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| id | Integer (>= 0)| Yes | Neurite unique ID
| type | Integer | Yes | Neurite [SWC Type](#swc_nodetype)
| tree | [Branch object](#json_branch) | Yes | Neurite's root [Branch]
| properties | [Property Map](#json_propertymap) | No | Neurite properties

##### Example

```json
{
					"id" : 1,
					"type" : 3,
					"tree" : {
						"root" : { "id": 1, "x": 0.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
						"nodes" : [
							{ "id": 2, "x": 1.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 3, "x": 2.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0}
						],
						"children":[
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0}
								],
								"children":[
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 6, "x": 4.0, "y": 1.0, "z" : 1.0 , "r": 0.0}
										]
									},
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 7, "x": 4.0, "y": 1.0, "z" : -1.0 , "r": 0.0}
										]
									}
								]
							},
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 8, "x": 4.0, "y": -1.0, "z" : 0.0 , "r": 0.0}
								]
							}
						]
          }
}
```

---

<a id="json_neuron"></a>

### Neuron Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| id | String| Yes | Neuron ID / name
| soma | Soma object | No | Neuron's soma
| neurites | Array of [Neurite objects](#json_neurite) | Yes | Neuron neurites
| properties | [Property Map](#json_propertymap) | No | Neuron properties

A soma object is only required to have a member called "nodes", which is an array of [Node objects](#json_node).

##### Example

```json
{
			"id" : "test neuron",
			"neurites" : [
				{
					"id" : 1,
					"type" : 3,
					"tree" : {
						"root" : { "id": 1, "x": 0.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
						"nodes" : [
							{ "id": 2, "x": 1.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 3, "x": 2.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0}
						],
						"children":[
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0}
								],
								"children":[
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 6, "x": 4.0, "y": 1.0, "z" : 1.0 , "r": 0.0}
										]
									},
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 7, "x": 4.0, "y": 1.0, "z" : -1.0 , "r": 0.0}
										]
									}
								]
							},
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 8, "x": 4.0, "y": -1.0, "z" : 0.0 , "r": 0.0}
								]
							}
						]
					}
				}
			],
			"soma" : {
				"nodes" : [
					{ "id": 1, "x": 0.0, "y": 0.0, "z" : 0.0 , "r": 0.0}
				]
			}
}
```


---

<a id="json_contour"></a>

### Contour Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| name | String| Yes | Contour name
| face_color | Soma object | Yes | RGB hex border color string
| back_color| String | Yes | RGB hex fill color string
| closed| Boolean | Yes | If true, the countour is closed
| fill| Float | Yes | Contour fill color opacity
| resolution| Float | Yes | Contour resolution (actual meaning - unknown)
| points| Array of [3DPoint objects](#json_point) | Yes | Conour points (ordered)
| properties | [Property Map](#json_propertymap) | No | Contour properties

##### Example

```json
{
			"name" : "test",
			"face_color" : "#000000",
			"back_color" : "#FFFFFF",
			"closed" : true,
			"fill" : 1.0,
			"resolution" : 1.0,
			"points" : [
				{ "x" : 1.0, "y" : 1.0, "z" : 1.0},
				{ "x" : 2.0, "y" : 2.0, "z" : 1.0},
				{ "x" : 1.0, "y" : 2.0, "z" : 1.0},
				{ "x" : 1.0, "y" : 1.0, "z" : 1.0}
			]
}
```

---

<a id="json_reconstruction"></a>

### Reconstruction Object

##### Members

| Key | Type | Is mandatory? | Description |
| :-- | :-- | :--:| :-- |
| neurons | Array of [Neuron objects](#json_neuron)| Yes | Reconstruction neurons
| contours | Array of [Contour objects](#json_contour) | No |  Reconstruction contours
| properties | [Property Map](#json_propertymap) | No | Reconstruction properties

##### Example

```json
{
	"neurons" : [
		{
			"id" : "test",
			"neurites" : [
				{
					"id" : 1,
					"type" : 3,
					"tree" : {
						"root" : { "id": 1, "x": 0.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
						"nodes" : [
							{ "id": 2, "x": 1.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 3, "x": 2.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
							{ "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0}
						],
						"children":[
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0}
								],
								"children":[
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 6, "x": 4.0, "y": 1.0, "z" : 1.0 , "r": 0.0}
										]
									},
									{
										"root" : { "id": 5, "x": 4.0, "y": 1.0, "z" : 0.0 , "r": 0.0},
										"nodes" : [
											{ "id": 7, "x": 4.0, "y": 1.0, "z" : -1.0 , "r": 0.0}
										]
									}
								]
							},
							{
								"root" : { "id": 4, "x": 3.0, "y": 0.0, "z" : 0.0 , "r": 0.0},
								"nodes" : [
									{ "id": 8, "x": 4.0, "y": -1.0, "z" : 0.0 , "r": 0.0}
								]
							}
						]
					}
				}
			],
			"soma" : {
				"nodes" : [
					{ "id": 1, "x": 0.0, "y": 0.0, "z" : 0.0 , "r": 0.0}
				]
			}
		}
	]
}
```

---

### Errors

The JSON parser is tolerant to errors. It will try to recover from error found when parsing the document. It tries to skip the faulty objects (and emits a warning), but if the JSON file is malformed or the document is empty it will emit a critical error. All warnings and errors are registered in the logger, and their count can be checked after calling the `read` function.

#### Error types

|Error| Description | Object is discarded?| Critical? (parsing stops) |
|:--|:--|:--:|:--:
| **Empty document** | Document/Stream is empty | Yes | Yes
| **Malformed JSON** | JSON Parsing error | Yes | Yes
| **Missing field** | Mandatory field is missing | Yes | No
| **Wrong field type** | Unexpeted field type | Yes | No
| **Unrecognized property type** | Property value is not one of the accepted types | Yes | No
| **Negative radius** | Node radius is negative | Yes | No
| **Unrooted branch** | Branch with no root declared | No | No

---

[Node]: ../data_model.html#node
[Branch]: ../data_model.html#branch
[Neurite]: ../data_model.html#neurite
[Neuron]: ../data_model.html#neuron
[Contour]: ../data_model.html#contour
[Reconstruction]: ../data_model.html#reconstruction
