---
currentSection: tools
---

# Tools {#tools}

## Format Converter {#converter}

Given a reconstruction file, the converter guess the format by the file extension and reads it. Optionally, it tries to correct errors in the reconstruction and applies a simplification algorithm over the branches. Finally it writes out the reconstruction in [SWC](io/format.html#SWC) or [JSON](io/format.html#JSON) format.

**Executable name:** *NeuroConverter*

#### Options {#converter_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| output | o | Yes | - | Output file
| format | f | Yes | - | Output file format string ([swc](io/format.html#SWC) or [json](io/format.html#JSON))
| correct | c | No | False | The converter calls the correct method on each neuron in the reconstruction
| eps | e | No | 0.0 | Error tolerance for the [Ramer-Douglas-Peucker](https://es.wikipedia.org/wiki/Algoritmo_de_Ramer%E2%80%93Douglas%E2%80%93Peucker) simplification algorithm applied at branch level.
| verbose | v | No | False | Verbose output. Sets the log level to debug

#### Use case {#converter_example}

Imagine that we want to convert the input file `fancy_neuron.dat` into a more "readable" format, like JSON `fancy_readable_neuron.json`. Also we want to remove zero-length compartments in the reconstruction, but we don't want to simplify it in any way. To do so, we just need to execute the following command in a BASH console:

```bash
./NeuroConverter -i fancy_neuron.dat -f json -o fancy_readable_neuron.json -c
```

#### Help message

```bash
./NeuroConverter --help
Allowed options:
  -h [ --help ]         Produce help message
  -i [ --input ] arg    Neuron reconstruction file
  -f [ --format ] arg   Output format (swc or json)
  -o [ --output ] arg   Output file
  -c [ --correct ]      Try to correct errors in the reconstruction
  -e [ --eps ] arg (=0) Output file
  -v [ --verbose ]      Verbose log output

Example: NeuroConverter -i test.swc -o test.json -f json
```
---

## Neurite Feature Extractor {#neuritefeature}

The neurite feature extractor computes a set of prebuilt measure for each neurite in the reconstruction. Measure values are not aggregated in any way, they are returned as-is (usually as vectors). Optionally, it tries to correct errors in the reconstruction.

The output (in the standard output stream) is a non prettyfied JSON array that contains for each [Neurite]:

- The neuron name (field: *neuron*)
- The neurite type (field: *neurite_type*)
- The neurite ID (field: *neurite*)
- An object *measures*. The specific measures inside this object are described in the [Measures](#neuritefeature_measures) section.

Some measures might use the logging interface to inform about errors or unexpected conditions.

**Executable name:** *NeuriteFeatureExtractor*

#### Options {#neuritefeature_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| correct | c | No | False | The converter calls the correct method on each neuron in the reconstruction
| omitapical | - | No | false | If set, apical dendrite is not measured
| omitaxon | - | No | false | If set, axon is not measured
| omitdend | - | No | false | If set, dendrites are not measured

#### Output example {#neuritefeature_example}

``` json
[
    {
        "measures": {
            "N_bifurcations": [
                2
            ],
            "N_branches": [
                5
            ],
            "N_nodes": [
                7
            ],
            "box_volume": [
                12.2872
            ],
            "branch_fractal_dimension": [
                0.632963,
                0.908842,
                0.908842,
                1.01944,
                1.01944
            ],
            "branch_length": [
                3,
                1.41421,
                1.41421,
                1,
                1
            ],
            "branch_surface": [
                0,
                0,
                0,
                0,
                0
            ],
            "branch_tortuosity": [
                1,
                1,
                1,
                1,
                1
            ],
            "branch_volume": [
                0,
                0,
                0,
                0,
                0
            ],
            "burker_taper_rate": [
                0,
                0,
                0,
                0,
                0
            ],
            "child_diam_ratio": [
                0,
                0
            ],
            "local_bifurcation_angle": [
                1.5708,
                3.14159
            ],
            "local_tilt_angle": [
                0.785398,
                1.5708
            ],
            "local_torque_angle": [
                0,
                0
            ],
            "node_length": [
                1,
                1,
                1,
                1.41421,
                1.41421,
                1,
                1
            ],
            "node_root_dist": [
                1,
                2,
                3,
                4.12311,
                4.12311,
                4.24264,
                4.24264
            ],
            "node_root_path": [
                0,
                1,
                2,
                3.41421,
                3.41421,
                4.41421,
                4.41421
            ],
            "partition_asymmetry": [
                1,
                0
            ],
            "remote_bifurcation_angle": [
                1.5708,
                3.14159
            ],
            "remote_tilt_angle": [
                0.785398,
                1.5708
            ],
            "remote_torque_angle": [
                0,
                0
            ],
            "terminal_branch_length": [
                1.41421,
                1,
                1
            ],
            "terminal_branch_order": [
                1,
                2,
                2
            ],
            "terminal_nodes_root_dist": [
                4.12311,
                4.24264,
                4.24264
            ],
            "terminal_nodes_root_path": [
                3.41421,
                4.41421,
                4.41421
            ]
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    }
]
```

#### Help message {#neuritefeature_help}

```bash
Allowed options:
  -h [ --help ]         Produce help message
  -i [ --input ] arg    Neuron reconstruction file
  -c [ --correct ]      Try to correct the errors in the reconstruction
  --omitapical          Ignore the apical dendrite
  --omitaxon            Ignore the axon
  --omitdend            Ignore the non-apical dendrites

Example: NeuriteFeatureExtractor -i test.swc
```

#### Measures {#neuritefeature_measures}

| Measure key | Description | Value type | Details
|:--|:--|:--:|--:
| `N_bifurcations` | Bifurcation node count | Single integer | |
| `N_branches` | Branch count | Single integer| |
| `N_nodes` | Node count | Single integer | |
| `node_length` | Node compartment length | Float vector | |
| `box_volume` |  Neurite non axis aligned box volume | Single float | |
| `node_root_dist` | Node euclidean distance to neurite's root | Float vector | |
| `node_root_path` | Node path distance to neurite's root | Float vector | |
| `branch_length` | Branch total length | Float vector | |
| `branch_volume` | Branch total volume | Float vector | Assumes truncated cone shape
| `branch_surface` | Branch total surface | Float vector | Assumes truncated cone shape
| `terminal_branch_length` | Total length of terminal branches | Float vector | |
| `terminal_branch_order` | Centrifugal order of terminal branches | Integer vector | |
| `terminal_nodes_root_dist` | Terminal tip euclidean distance to the root | Float vector | |
| `terminal_nodes_root_path` | Terminal tip path distance to the root | Float vector | |
| `branch_tortuosity` | Branch tortuosity measure | Float vector | |
| `hill_taper_rate` | Hillman taper rate per Branch | Float vector | |
| `burker_taper_rate` | Burker taper rate per branch | Float vector | |
| `branch_fractal_dimension` | Branch fractal dimension | Float vector | |
| `local_bifurcation_angle` | Bifurcation amplitude from local vectors | Float vector | Only for non-terminal branches
| `local_tilt_angle` | Bifurcation tilt from local vectors | Float vector | Only for non-terminal branches
| `local_torque_angle` | Bifurcation torque from local vectors | Float vector | Only for non-terminal branches
| `remote_bifurcation_angle` | Bifurcation amplitude from remote vectors | Float vector | Only for non-terminal branches
| `remote_tilt_angle` | Bifurcation tilt from remote vectors | Float vector | Only for non-terminal branches
| `remote_torque_angle` | Bifurcation torque from remote vectors | Float vector | Only for non-terminal branches
| `child_diam_ratio` | Bifurcation child diameter ratio | Float vector | Only for non-terminal branches
| `partition_asymmetry` | Partition asymmetry at the bifurcation node | Float vector | Only for non-terminal branches

---

## Branch Feature Extractor {#branchfeature}

The branch feature extractor computes a set of prebuilt measure for each branch in the reconstruction. Optionally, it tries to correct errors in the reconstruction.

The output (in the standard output stream) is a non prettyfied JSON array that contains for each [Branch]:

- The neuron name (field: *neuron*)
- The neurite type (field: *neurite_type*)
- The neurite ID (field: *neurite*)
- The branch ID (field: *branch*)
- An object *measures*. The specific measures inside this object are described in the [Measures](#branchfeature_measures) section.

Some measures might use the logging interface to inform about errors or unexpected conditions.

**Executable name:** *BranchFeatureExtractor*

#### Options {#branchfeature_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| correct | c | No | False | The converter calls the correct method on each neuron in the reconstruction
| selection | s | No | all | Branch subset selection. Accepted values: `all`, `terminal`, `preterminal`, `nonterminal`, `root`
| omitapical | - | No | false | If set, apical dendrite is not measured
| omitaxon | - | No | false | If set, axon is not measured
| omitdend | - | No | false | If set, dendrites are not measured

#### Output example {#branchfeature_example}

```json
[
    {
        "branch": "1",
        "measures": {
            "N_descs": 2.0,
            "N_nodes": 3.0,
            "box_volume": 0.0,
            "burker_taper_rate": 0.0,
            "centrifugal_order": 0.0,
            "child_diam_ratio": 0.0,
            "fractal_dimension": 0.632963,
            "length": 3.0,
            "local_bifurcation_angle": 1.570796,
            "local_tilt_angle": 0.785398,
            "local_torque_angle": 0.0,
            "partition_asymmetry": 0.632963,
            "remote_bifurcation_angle": 1.570796,
            "remote_tilt_angle": 0.785398,
            "remote_torque_angle": 0.0,
            "surface": 0.0,
            "tortuosity": 1.0,
            "volume": 0.0
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    },
    {
        "branch": "1-1",
        "measures": {
            "N_descs": 0.0,
            "N_nodes": 1.0,
            "box_volume": 0.0,
            "burker_taper_rate": 0.0,
            "centrifugal_order": 1.0,
            "fractal_dimension": 0.908842,
            "length": 1.414214,
            "surface": 0.0,
            "tortuosity": 1.0,
            "volume": 0.0
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    },
    {
        "branch": "1-2",
        "measures": {
            "N_descs": 2.0,
            "N_nodes": 1.0,
            "box_volume": 0.0,
            "burker_taper_rate": 0.0,
            "centrifugal_order": 1.0,
            "child_diam_ratio": 0.0,
            "fractal_dimension": 0.908842,
            "length": 1.414214,
            "local_bifurcation_angle": 3.141593,
            "local_tilt_angle": 1.570796,
            "local_torque_angle": 0.0,
            "partition_asymmetry": 0.908842,
            "remote_bifurcation_angle": 3.141593,
            "remote_tilt_angle": 1.570796,
            "remote_torque_angle": 0.0,
            "surface": 0.0,
            "tortuosity": 1.0,
            "volume": 0.0
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    },
    {
        "branch": "1-2-1",
        "measures": {
            "N_descs": 0.0,
            "N_nodes": 1.0,
            "box_volume": 0.0,
            "burker_taper_rate": 0.0,
            "centrifugal_order": 2.0,
            "fractal_dimension": 1.019436,
            "length": 1.0,
            "surface": 0.0,
            "tortuosity": 1.0,
            "volume": 0.0
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    },
    {
        "branch": "1-2-2",
        "measures": {
            "N_descs": 0.0,
            "N_nodes": 1.0,
            "box_volume": 0.0,
            "burker_taper_rate": 0.0,
            "centrifugal_order": 2.0,
            "fractal_dimension": 1.019436,
            "length": 1.0,
            "surface": 0.0,
            "tortuosity": 1.0,
            "volume": 0.0
        },
        "neurite": 1,
        "neurite_type": "Dendrite",
        "neuron": "simple_tree"
    }
]
```

#### Help message {#branchfeature_help}

```bash
Allowed options:
  -h [ --help ]                 Produce help message
  -i [ --input ] arg            Neuron reconstruction file
  -c [ --correct ]              Try to correct the errors in the reconstruction
  -s [ --selection ] arg (=all) Branch subset: all, terminal, nonterminal,
                                preterminal or root
  --omitapical                  Ignore the apical dendrite
  --omitaxon                    Ignore the axon
  --omitdend                    Ignore the non-apical dendrites

Example: BranchFeatureExtractor -i test.swc
```

#### Measures {#branchfeature_example}

| Measure key | Description | Value type | Details
|:--|:--|:--:|--:
| `N_descs` | Daughter branches count | Integer| |
| `N_nodes` | Node count | Single integer | |
| `tortuosity` | Branch tortuosity | Single integer | |
| `hill_taper_rate` | Branch Hillman taper rate |Float| |
| `burker_taper_rate` | Branch Burker taper rate | Float | |
| `centrifugal_order` | Branch centrifugal order | Integer | |
| `length` | Branch length | Float | |
| `volume` | Branch total volume | Float | Assumes truncated cone compartments
| `surface` | Branch total surface | Float | Assumes truncated cone compartments
| `box_volume` | Branch non axis aligned box volume | Float | |
| `branch_fractal_dimension` | Branch fractal dimension | Float  | |
| `local_bifurcation_angle` | Bifurcation amplitude from local vectors | Float vector | Only for non-terminal branches
| `local_tilt_angle` | Bifurcation tilt from local vectors | Float  | Only for non-terminal branches
| `local_torque_angle` | Bifurcation torque from local vectors | Float  | Only for non-terminal branches
| `remote_bifurcation_angle` | Bifurcation amplitude from remote vectors | Float  | Only for non-terminal branches
| `remote_tilt_angle` | Bifurcation tilt from remote vectors | Float  | Only for non-terminal branches
| `remote_torque_angle` | Bifurcation torque from remote vectors | Float  | Only for non-terminal branches
| `child_diam_ratio` | Bifurcation child diameter ratio | Float  | Only for non-terminal branches
| `partition_asymmetry` | Partition asymmetry at the bifurcation node | Float | Only for non-terminal branches

---

## Neuron Validator {#validator}

The neuron validator runs a test battery to detect possible errors in the reconstruction. It outputs a summary output in JSON format that, for each test, contains the test result and failing nodes. The validation results point out **possible** errors (again, **POSSIBLE**), so don't interpret them as the ground truth. Outliers do exist.

The default tests are:

- Neurite is attached to soma
- Neuron has soma
- Planar neurite reconstruction
- Abnormal dendrite count
- Abnormal apical count
- Abnormal axon count
- Trifrucation nodes detection
- Linear branches
- Zero-length compartments
- Intersecting node spheres
- Increasing diameters
- Branch collision
- Extreme bifurcation/elongation angles


**Executable name:** *Validator*

#### Options {#validator_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| exhaustive | e | No | False | Include every test result, not only failures
| attached | A | No | True | Enable neurite attached to soma validation
| noattached | a | No | False | Disable neurite attached to soma validation
| soma | S | No | True | Enable neuron has soma check
| nosoma | s | No | False | Disable neuron has soma check
| planar | P | No | True | Enable planar neurite test
| noplanar | p | No | False | Disable planar neurite test
| dendcnt | D | No | True | Enable abnormal dendrite count test
| nodendcnt | d | No | False | Disable abnormal dendrite count test
| apical | C | No | True | Enable neuron has apical check
| noapical | c | No | False | Disable neuron has apical check
| axon | X | No | True | Enable neuron has axon check
| noaxon | x | No | False | Disable neuron has axon check
| trifurcation | T | No | True | Enable trifurcation nodes test
| notrifurcation | t | No | False | Disable trifurcation nodes test
| linear | L | No | True | Enable linear branches test
| nolinear | l | No | False | Disable linear branches test
| zero | Z | No | True | Enable zero-length compartment test
| nozero | z | No | False | Disable zero-length compartment test
| intersect | I| No | True | Enable intersecting node spheres test
| nointersect | i | No | False | Disable intersecting node spheres test
| decrease | R| No | True | Enable increasing diameters test
| nodecrease | r | No | False | Disable increasing diameters test
| segcoll | V| No | False | Enable segment collision test
| nosegcoll | v | No | True | Disable segment collision test
| branchcoll | B| No | True | Enable branch collision test
| nobranchcoll | b | No | False | Disable branch collision test
| extremeang | M| No | True | Enable extreme bifurcation/elongation angles test
| noextremeang | m | No | False | Disable extreme bifurcation/elongation angles test
| nostrict | - | No | False | No strict mode. Apical and axon counts only fail if there are more than one element defined
| nodiameters | - | No | False | Disables tests that use diameter information
| is2D | - | No | False | Disables tests that assume a 3D reconstruction
| omitapical | - | No | false | If set, apical dendrite is not validated
| omitaxon | - | No | false | If set, axon is not validated
| omitdend | - | No | false | If set, dendrites are not validated
| planarth | - | No | 1.01 | Planar reconstruction test threshold
| linearth | - | No | 1.01 | Linear branche test threshold
| mindend | - | No | 2 | Minimum number of dendrites for the test (included)
| maxdend | - | No | 13 | Minimum number of dendrites for the test (excluded)

#### Output example {#validator_example}

```json
[
    {
        "description": "Fails if neurites are not attached to the soma",
        "name": "Neurites are attached to soma",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Pass if the neuron has at least one soma node",
        "name": "Neuron has soma",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails if the non-axis aligned box volume of the neurite is lower than prebuilt threshold",
        "name": "Planar neurite validation",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Pass if the dendrite count is greater or equal than 2 and less than 13",
        "name": "Basal dendrite count",
        "neuron_id": "simple_tree",
        "pass": false,
        "results": [
            {
                "id": {
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Neuron",
                "value": 1
            }
        ]
    },
    {
        "description": "Pass if and only if there is one apical dendrite",
        "name": "Strict apical dendrite count",
        "neuron_id": "simple_tree",
        "pass": false,
        "results": [
            {
                "id": {
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Neuron",
                "value": 0
            }
        ]
    },
    {
        "description": "Pass if and only if there is one axon",
        "name": "Strict axon count",
        "neuron_id": "simple_tree",
        "pass": false,
        "results": [
            {
                "id": {
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Neuron",
                "value": 0
            }
        ]
    },
    {
        "description": "Fails on those nodes with more than two descendants",
        "name": "Trifurcation validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails when the branch tortuosity falls below 1.010000",
        "name": "Linear branch validator",
        "neuron_id": "simple_tree",
        "pass": false,
        "results": [
            {
                "id": {
                    "branch": "1",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
            },
            {
                "id": {
                    "branch": "1-1",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
            },
            {
                "id": {
                    "branch": "1-2",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
            },
            {
                "id": {
                    "branch": "1-2-1",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
            },
            {
                "id": {
                    "branch": "1-2-2",
                    "neurite": 1,
                    "neuron": "simple_tree"
                },
                "pass": false,
                "type": "Branch",
                "value": 1.0
            }
        ]
    },
    {
        "description": "Fails when a segment length is close to zero",
        "name": "Zero length segments validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails when two consecutive node spheres intersection is not empty",
        "name": "Length smaller than radius validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails when diameter increases between two consecutive nodes",
        "name": "Non-decreasing diameter validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails when the distance between any two branches is zero",
        "name": "Branch collision validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    },
    {
        "description": "Fails when either elongation or bifurcation angles are too high to be plausible",
        "name": "Extreme angles validator",
        "neuron_id": "simple_tree",
        "pass": true,
        "results": []
    }
]
```

#### Help message {#validator_help}

```bash
Allowed options:
  --help                       Produce help message
  --input arg                  Neuron reconstruction file
  -e [ --exhaustive ]          Exhaustive report. Include all validation items,
                               not only failures
  -A [ --attached ]            Enable neurites attached to soma validation
  -a [ --noattached ]          Disable neurites attached to soma validation
  -S [ --soma ]                Enable soma validation
  -s [ --nosoma ]              Disable soma validation
  -P [ --planar ]              Enable planar reconstruction validation
  -p [ --noplanar ]            Disable planar reconstruction validation
  -D [ --dendcnt ]             Enable dendrite count validation
  -d [ --nodendcnt ]           Disable dendrite count validation
  -C [ --apical ]              Enable apical count validation
  -c [ --noapical ]            Disable apical count validation
  -X [ --axon ]                Enable axon count validation
  -x [ --noaxon ]              Disable axon count validation
  -T [ --trifurcation ]        Enable trifurcation validation
  -t [ --notrifurcation ]      Disable trifurcation validation
  -L [ --linear ]              Enable linear branches validation
  -l [ --nolinear ]            Disable linear branches validation
  -Z [ --zero ]                Enable zero length segments validation
  -z [ --nozero ]              Disable zero length segments validation
  -I [ --intersect ]           Enable intersecting nodes validation
  -i [ --nointersect ]         Disable intersecting nodes validation
  -R [ --decrease ]            Enable non-decrasing radius validation
  -r [ --nodecrease ]          Disable non-decrasing radius validation
  -V [ --segcoll ]             Enable segment collision validation
  -v [ --nosegcoll ]           Disable segment collision validation
  -B [ --branchcoll ]          Enable branch collision validation
  -b [ --nobranchcoll ]        Disable branch collision validation
  -M [ --extremeang ]          Enable extreme angles validation
  -m [ --noextremeang ]        Disable extreme angles validation
  --nostrict                   No strict mode
  --nodiameters                Disables diameter-based nodes
  --is2D                       Disables validations that assume a 3D
                               reconstruction
  --neuron                     Validates the entire neuron
  --omitapical                 Ignore the apical dendrite
  --omitaxon                   Ignore the axon
  --omitdend                   Ignore the non-apical dendrites
  --omitsoma                   Disable soma tests
  --planarth arg (=1.00999999) Planar reconstruction threshold
  --linearth arg (=1.00999999) Linear branch threshold
  --mindend arg (=2)           Number of dendrites minimum (in)
  --maxdend arg (=13)          Number of dendrites maximum (out)

Example: validator -i test.swc -e
```
---

## Scholl analysis {#scholl}

Performs a simple linear [Scholl analysis](https://en.wikipedia.org/wiki/Sholl_analysis) over the neurons in the given reconstruction. The executable outputs a three-column CSV file over the standard output with neuron, distance and branch count (intersections).

**Executable name:** *Scholl*

#### Options {#scholl_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| correct | c | No | False | The converter calls the correct method on each neuron in the reconstruction
| omitapical | - | No | false | If set, apical dendrite is ignored
| omitaxon | - | No | false | If set, axon is ignored
| omitdend | - | No | false | If set, dendrites are ignored

#### Output example {#scholl_example}

```csv
Neuron,Distance,Branch_Count
"test", 0.000000, 7
"test", 5.791105, 8
"test", 10.142367, 9
"test", 10.871992, 10
"test", 11.452746, 11
"test", 14.642872, 12
"test", 15.113467, 11
"test", 15.681764, 12
"test", 15.775044, 13
"test", 19.586906, 14
"test", 20.254789, 15
"test", 20.606409, 16
"test", 23.650518, 15
"test", 26.021965, 14
"test", 27.452669, 13
"test", 29.967087, 14
"test", 31.035795, 15
"test", 33.701023, 16
"test", 35.049515, 17
"test", 36.404655, 18
"test", 38.575405, 19
"test", 39.636028, 20
"test", 40.954132, 21
"test", 41.333488, 22
"test", 41.665516, 21
"test", 42.522957, 20
"test", 43.694332, 21
"test", 43.852596, 22
"test", 44.253582, 23
"test", 44.349628, 24
"test", 44.898899, 23
"test", 45.466465, 24
"test", 45.657787, 23
"test", 46.378159, 24
"test", 46.378372, 25
"test", 46.407532, 26
"test", 46.868195, 25
"test", 47.220634, 24
"test", 47.478245, 25
"test", 47.529491, 26
...
```

#### Help message {#scholl_help}

```bash
Allowed options:
  -h [ --help ]         Produce help message
  -i [ --input ] arg    Neuron reconstruction file
  -c [ --correct ]      Try to correct the errors in the reconstruction
  --omitapical          Ignore the apical dendrite
  --omitaxon            Ignore the axon
  --omitdend            Ignore the non-apical dendrites

Example: Scholl -i test.swc
```

---

## Box Cutter {#boxcut}

The neuron box cutter creates a virtual axis-aligned box with given min and max corners and uses it to "cut" the neuron. That is, it creates virtual nodes at the intersection of the box with the neuron, adds an empty property with key "cut" to all branches and nodes that lie outside the reconstruction. It also adds two properties to the neuron "cutbox_min" and "cutbox_max", the box min and max corner points. If no argument is given for certain corner x,y,z value, it takes the neuron min/max value for that axis.

The output is always a reconstruction in JSON format, since no other output format can store properties at node/branch level.

You can use this to select (and measure) nodes and branches outside/inside the box with the property_exists selector.

**Executable name:** *BoxCutter*

#### Options {#boxcut_options}

| Option | Short | Required | Default value | Description
|:--|:--:|:--:|:--:|:-|
| help | h | No | - | Produces help message
| input | i | Yes | - | Input reconstruction file ([swc](io/format.html#SWC), [dat](io/format.html#DAT), [asc](io/format.html#ASC) or [json](io/format.html#JSON) ). File format is guessed from the file extension
| input | o | Yes | - | The JSON output file
| minx | - | No | Neuron min x value | Cut box min x corner value
| miny | - | No | Neuron min y value | Cut box min y corner value
| minz | - | No | Neuron min z value | Cut box min z corner value
| maxx | - | No | Neuron max x value | Cut box min y corner value
| maxy | - | No | Neuron max y value | Cut box max y corner value
| maxz | - | No | Neuron max z value | Cut box max z corner value

#### Output example {#boxcut_example}

Command:

```bash
./BoxCutter -i simple_tree.swc -o simple_tree_out.json --maxx 3.0

```

Output:

```json
{
    "neurons": [
        {
            "id": "simple_tree",
            "neurites": [
                {
                    "id": 1,
                    "tree": {
                        "children": [
                            {
                                "nodes": [
                                    {
                                        "id": 8,
                                        "properties": {
                                            "cut": []
                                        },
                                        "r": 0.0,
                                        "x": 4.0,
                                        "y": -1.0,
                                        "z": 0.0
                                    }
                                ],
                                "root": {
                                    "id": 4,
                                    "r": 0.0,
                                    "x": 3.0,
                                    "y": 0.0,
                                    "z": 0.0
                                }
                            },
                            {
                                "children": [
                                    {
                                        "nodes": [
                                            {
                                                "id": 6,
                                                "properties": {
                                                    "cut": []
                                                },
                                                "r": 0.0,
                                                "x": 4.0,
                                                "y": 1.0,
                                                "z": 1.0
                                            }
                                        ],
                                        "properties": {
                                            "cut": []
                                        },
                                        "root": {
                                            "id": 5,
                                            "properties": {
                                                "cut": []
                                            },
                                            "r": 0.0,
                                            "x": 4.0,
                                            "y": 1.0,
                                            "z": 0.0
                                        }
                                    },
                                    {
                                        "nodes": [
                                            {
                                                "id": 7,
                                                "properties": {
                                                    "cut": []
                                                },
                                                "r": 0.0,
                                                "x": 4.0,
                                                "y": 1.0,
                                                "z": -1.0
                                            }
                                        ],
                                        "properties": {
                                            "cut": []
                                        },
                                        "root": {
                                            "id": 5,
                                            "properties": {
                                                "cut": []
                                            },
                                            "r": 0.0,
                                            "x": 4.0,
                                            "y": 1.0,
                                            "z": 0.0
                                        }
                                    }
                                ],
                                "nodes": [
                                    {
                                        "id": 5,
                                        "properties": {
                                            "cut": []
                                        },
                                        "r": 0.0,
                                        "x": 4.0,
                                        "y": 1.0,
                                        "z": 0.0
                                    }
                                ],
                                "root": {
                                    "id": 4,
                                    "r": 0.0,
                                    "x": 3.0,
                                    "y": 0.0,
                                    "z": 0.0
                                }
                            }
                        ],
                        "nodes": [
                            {
                                "id": 2,
                                "r": 0.0,
                                "x": 1.0,
                                "y": 0.0,
                                "z": 0.0
                            },
                            {
                                "id": 3,
                                "r": 0.0,
                                "x": 2.0,
                                "y": 0.0,
                                "z": 0.0
                            },
                            {
                                "id": 4,
                                "r": 0.0,
                                "x": 3.0,
                                "y": 0.0,
                                "z": 0.0
                            }
                        ],
                        "root": {
                            "id": 1,
                            "r": 0.0,
                            "x": 0.0,
                            "y": 0.0,
                            "z": 0.0
                        }
                    },
                    "type": 3
                }
            ],
            "properties": {
                "cutbox_max": {
                    "x": 3.0,
                    "y": 1.0,
                    "z": 1.0
                },
                "cutbox_min": {
                    "x": 0.0,
                    "y": -1.0,
                    "z": -1.0
                }
            },
            "soma": {
                "nodes": [
                    {
                        "id": 1,
                        "r": 0.0,
                        "x": 0.0,
                        "y": 0.0,
                        "z": 0.0
                    }
                ]
            }
        }
    ]
}
```

#### Help message {#boxcut_help}

```bash
Allowed options:
  -h [ --help ]         Produce help message
  -i [ --input ] arg    Neuron reconstruction file
  -c [ --correct ]      Try to correct the errors in the reconstruction
  --omitapical          Ignore the apical dendrite
  --omitaxon            Ignore the axon
  --omitdend            Ignore the non-apical dendrites

Example: Scholl -i test.swc
```


---
