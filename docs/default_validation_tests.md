# Reconstruction Validation

## Predefined validations

### Definition

| Name | Description | Parameters | Can be fixed? |
| :--- | :--- | :--- | :--- | :---: |
| Neurites attached to soma | Checks if the root of the neurites is in the soma | None | Yes. Create a new node in the soma and set it as root |
| Neuron has soma | Checks if the neuron has at least one soma node | None | Yes. Create a soma node in (0,0,0) or any other logic position. |
| Planar reconstruction | Checks if the neurite reconstruction is planar by computing its non axis-aligned box volume | *float* **threshold**  (e.g. 1E-3) | No |
| Dendrite count | Checks that the number of dendrites in the neurons is withing a given range [a,b) | *float* **a,b** Interval values(e.g. [2,9) ) | No |
| Apical count | Checks that the number of apical dendrites is either 1 or 0 | *bool* **strict** if true, fails if no apical dendrite is present | TBD |
| Axon count | Checks that the number of axons is either 1 or 0 | *bool* **strict** if true, fails if no axon is present | TBD |
| No Trifurcations | Checks that every node has less than 3 descendants | None | TBD |
| Linear branches | Checks that the branch tortuosity is greater than a given value | *float* **threshold** (e.g. 1.01) | No |
| Zero length segments | Fails on those nodes on the same position as its parent | None | Yes. Remove duplicated node |
| Intersecting nodes | Fails when two consecutive node's spheres intersection is not empty | None | Yes. Remove one of the nodes |
| Non-decreasing diameters| Fails when diameter increases between two consecutive nodes | None | No|
| Segment collision (deprecated) | Fails whenever the distance between any two segments in the reconstruction is zero | None | No |
| Branch collision | Fails whenever the distance between any two branches in the reconstruction is zero | None | No |
| Extreme angles | Fails when the elongation or bifurcation angle at a given node is too high to be plausible | None | No|

### Executable

| Name | Flags (short) | Default | Default parameters |  Depends on diameter value? | 3D assumption
| :--- | :--- | :--- | :--- | :---: |
| Neurites attached to soma | attached(-A) noattached(-a)| Active |  | No | No
| Neuron has soma| soma(-S) noSoma(-s) | Active |  | No | No
| Planar reconstruction| planar(-P) noplanar(-p) | Active | **threshold** = 1.01 | No | Yes
| Dendrite count| dendrite(-D) nodendrite(-D)  | Active | **range** = [2,13) | No | No
| Apical count| apical(-C) noapical(-c)  | Active | **strict** = true | No | No
| Axon count| axon(-X) noaxon(-x)  | Active | **strict** = true | No | No
| No trifurcations| trifurcation(-T) notrifurcation(-t) | Active |  | No | No
| Linear branches| linear(-L) nolinear(-l) | Active |**threshold** = 1.01  | No | Yes (partially)
| Zero length segments| zero(-Z) nozero(-z) | Active | | No | No
| Intersecting nodes| intersect(-I) nointersect(-i)  | Active | | Yes | No
| Non-decreasing diameters| decrease(-D) nodecrease(-d)| Active | | Yes | No
| Segment collision| segcoll(-V) nosegcoll(-v)| Inactive (deprecated) | | No | Yes
| Branch collision| branchcoll(-B) nobranchcoll(-b)| Active | | No | Yes (mutable)
| Extreme angles| extremeang(-M) noextremeang(-m)| Active | | No | No

#### Additional flags:
- **--nodiameters** : disables/mutates all validations that depend on the diameter value
- **--is2D** : disables all validations that assume a 3D reconstruction

#### Notes:
- Activation has priority over deactivation



## Anomaly detection
TBD

## Novelty detection
TBD
