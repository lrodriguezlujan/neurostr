---
currentSection: measures
currentSubsection: predef
currentItem: node
---
# Node measures {#node}
text

### X, Y, Z components<a id="node_component"> </a>

**Function:** `node_x, node_y, node_z = [](const Node& n) -> float`

**Description:** Returns the x, y, z component of the given [Node] position.

**Output:** Real number.

ADD IMAGE

---

### Radius, diameter<a id="node_radius"> </a>

**Function:** `node_radius,node_diameter = [](const Node& n) -> float`

**Description:** Returns the radius/diameter of the given [Node].

**Output:** Real number.

**Details:** The Hillman taper rate defined as the ratio of the difference between first and last node diameters and the first node diameter. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an
exception for a [Branch] with no nodes.

ADD IMAGE

---

### Centrifugal order<a id="node_order"> </a>

**Function:** `node_order = [](const Node& n) -> int`

**Description:** Returns the centrifugal order of the [Branch] that the [Node] belongs to.

**Output:** Integer. Centrifugal order

**Details:** See [Branch order](branch.html#order)

ADD IMAGE

---

### Distance to parent<a id="node_parent_length"> </a>

**Function:** `node_length_to_parent,node_length_to_parent_border = [](const Node& n) -> float`

**Description:** Returns the euclidean distance between the given [Node] and its parent. the *border* variant subtract the radius of both nodes to the distance.

**Output:** Real Number.

**Details:** Please note that the border variant might return negative values if the sum of radius is greater than the distance

ADD IMAGE

---

### Distance to root<a id="node_rootdist"> </a>

**Function:** `node_distance_to_root = [](const Node& n) -> float`

**Description:** Computes the euclidean distance between the given [Node] and the root of the [Neurite] that the node belongs to.

**Output:** Non negative real Number.

**Details:** If the [Neurite] doesn't have a root node, the distance is computed to its first [Node]

ADD IMAGE

---

### Distance to soma<a id="node_somadist"> </a>

**Function:** `node_distance_to_soma = [](const Node& n) -> float`

**Description:** Computes the euclidean distance between the given [Node] and the closest [Soma] point in the neuron.

**Output:** Non negative real Number.

**Details:** If the [Neuron] doesn't have a [Soma], the the method returns the distance between the given node and the point (0,0,0).

ADD IMAGE

---

### Path length to root<a id="node_rootpath"> </a>

**Function:** `node_path_to_root = [](const Node& n) -> float`

**Description:** Computes the length of the path from the given [Node] to the root of the [Neurite] that the node belongs to.

**Output:** Non negative real Number.

ADD IMAGE

---


### Compartment volume<a id="node_volume"> </a>

**Function:** `node_volume = [](const Node& n) -> float`

**Description:** Computes the volume of the truncated cone from the given [Node] to its parent.

**Output:** Non negative real Number.

**Details:** The aforementioned cone has the radius of the parent at one end and the radius of the given [Node] at the other. If the parent of the given [Node] cannot be determined, it returns 0.

ADD IMAGE

---

### Compartment surface<a id="node_surface"> </a>

**Function:** `node_compartment_surface = [](const Node& n) -> float`

**Description:** Computes the surface of the truncated open cone from the given [Node] to its parent.

**Output:** Non negative real Number.

**Details:** The aforementioned cone has the radius of the parent at one end and the radius of the given [Node] at the other. If the parent of the given [Node] cannot be determined, it returns 0.

ADD IMAGE

---

### Compartment section area<a id="node_section"> </a>

**Function:** `node_compartment_section_area = [](const Node& n) -> float`

**Description:** Computes section area as the area of the circle with radius the average of the given [Node] and its parent radius.

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the circle radius is just the given node radius.

ADD IMAGE

---

### Local Hillman taper rate<a id="node_hillman"> </a>

**Function:** `node_segment_taper_rate_hillman = [](const Node& n) -> float`

**Description:** Computes the Hillman taper rate between the given [Node] and its parent

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the taper rate is 0. The Hillman taper rate is given by:
`(parent.radius-node.radius)/parent.radius`

ADD IMAGE

---

### Local Burker taper rate<a id="node_burker"> </a>

**Function:** `node_segment_taper_rate_burker = [](const Node& n) -> float`

**Description:** Computes the Burker taper rate between the given [Node] and its parent

**Output:** Non negative real Number.

**Details:** If the parent of the given [Node] cannot be determined, the taper rate is 0. The Burker taper rate is given by:
`(parent.radius-node.radius)/distance(parent,node)`

ADD IMAGE

---

### Non axis aligned minimum box volume<a id="node_boxvol"> </a>

**Function:** `box_volume = [](const const_node_iterator& b,
                           const const_node_iterator& e) -> double`

**Description:** Computes the minimum box volume for the given [Node] set. The box is not restricted to be axis-aligned.

**Output:** Non negative real Number.

**Details:** The box volume is computed by applying a PCA over the position of the nodes, and then computing the axis-aligned box volume on the rotated positions.

ADD IMAGE

---

### Vector to parent<a id="node_parentvector"> </a>

**Function:** `node_parent_vector = [](const Node& n) -> point_type`

**Description:** Computes the vector from the given [Node] to its parent.

**Output:** 3D Vector

**Details:** If the parent of the given [Node] cannot be determined, the method returns the null vector.

ADD IMAGE

---

### Local bifurcation angle<a id="node_localbif"> </a>

**Function:** `node_local_bifurcation_angle = [](const Node& n) -> float`

**Description:** If the given node is a bifurcation, it returns the local bifurcation angle.

**Output:** Angle in radians [0,pi)

**Details:** If the node is not a bifurcation node it returns 0. See [Branch local bifurcation angle](branch.html#localbif)

ADD IMAGE

---

### Local elongation angle<a id="node_localelong"> </a>

**Function:** `node_local_elongation_angle = [](const Node& n) -> float`

**Description:** If the given [Node] is an elongation, i.e. it only has one descendant, returns the oriented angle between the vector form the parent to the given [Node] and the vector from the [Node] to its descendant.

**Output:** Angle in radians

**Details:** If the node is not an elongation node it returns 0. The reference vector for 3D angle orientation is the [Neuron] up vector (by default it is the (0,0,1) vector)

ADD IMAGE

---

### Local orientation<a id="node_localorientation"> </a>

**Function:** `node_local_orientation = [](const Node& n) -> std::pair<float, float>`

**Description:** It computes the values of azimuth and elevation for the given [Node] using the orthonormal basis span by the vector from the parent and the neuron up vector as reference.

**Output:** Pair of angles in radians (-pi,pi). Azimuth and elevation

ADD IMAGE

---

### In terminal branch<a id="node_interminalbranch"> </a>

**Function:** `node_in_terminal_segment = [](const Node& n) -> bool`

**Description:** Returns true if the [Branch] that the node belongs to is a terminal branch

**Output:** Boolean value. True if the node's branch is terminal.

ADD IMAGE

---

### Distance to closest segment<a id="node_distclosest"> </a>

**Function:** `segment_distance_to_closest = [](const Node& n) -> bool`

**Description:** Returns the minimum distance between the segment [parent,node] to any other segment in the neuron.

**Output:** Non negative value. If the parent of the given [Node] cannot be determined, the method returns the highest value representable in a float.

ADD IMAGE

---

### Distance to closest segment<a id="node_distclosest"> </a>

**Function:** `segment_distance_to_closest = [](const Node& n) -> bool`

**Description:** Returns the minimum distance between the segment [parent,node] to any other segment in the neuron.

**Output:** Non negative value. If the parent of the given [Node] cannot be determined, the method returns the highest value representable in a float.

ADD IMAGE

---

### Fractal dimension<a id="node_fractal"> </a>

**Function:** ` node_set_fractal_dim = [](const const_node_iterator& b,
                                     const const_node_iterator& e) -> float`

**Description:** Computes the fractal dimension of the given set of nodes (assuming that they are a sequence).


**Output:** Fractal dimension, real value between 1 (straight line) and 2 (random walk)

**Details:** See [L-measure fractal dimension documentation](http://cng.gmu.edu:8080/Lm/help/Fractal_Dim.htm).


ADD IMAGE

---

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
[Soma]: ../goals_architecture.html#soma
