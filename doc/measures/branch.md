---
currentSection: measures
currentSubsection: predef
currentItem: branch
---
# Branch measures
text

### Hillman taper rate<a id="hillman"> </a>

**Function:** `taper_rate_hillman = [](const Branch& b) -> float`

**Description:** Computes the Hillman taper rate for the given [Branch]

**Output:** real number. Hillman taper rate.

**Details:** The Hillman taper rate defined as the ratio of the difference between first and last node diameters and the first node diameter. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an
exception for a [Branch] with no nodes.

`(first.diameter - last.diameter) / first.diameter`

ADD IMAGE

---

### Burker taper rate <a id="burker"> </a>

**Function:** `taper_rate_burker = [](const Branch& b) -> float`

**Description:** Computes the Burker taper rate for the given [Branch]

**Output:** real number. Burker taper rate.

**Details:** The Burker taper rate defined as the ratio of the difference between the first and last node diameters and the euclidean distance between these two same nodes. If the branch's root exists, it is taken as the first node. If we assume non-decreasing diameters, the hillman taper rate should be non-negative. Note that it will throw an exception for a [Branch] with no nodes.

`(first.diameter - last.diameter) / distance(first,last)`

ADD IMAGE

---

### Tortuosity <a id="tortuosity"> </a>

**Function:** `tortuosity = [](const Branch& b) -> float`

**Description:** Computes the branch tortuosity value.

**Output:** Non-negative real number. Greater or equal than 1.

**Details:** The tortuosity value is defined as the ratio of the total length of the branch and  the euclidean distance between the first and the last nodes. If the branch's root exists, it is taken as the first node.

`branch.length / distance(first,last)`

ADD IMAGE

---

### Node count <a id="size"> </a>

**Function:** `branch_size = [](const Branch &b) -> int`

**Description:** Returns the number of nodes in the [Branch].

**Output:** Non-negative integer

**Details:** This returns the number of nodes that are part of the Branch excluding the root. In our data model, the branch's root node belongs to the parent branch (or to the soma) and not to the branch itself.

ADD IMAGE

---

### Branch index <a id="index"> </a>

**Function:** `branch_index = [](const Branch &b) -> unsigned int`

**Description:** Returns the index of the given branch as daughter of the parent branch.

**Output:** Non-negative integer

**Details:** This returns 0 for the first branch, 1 for the second and so on. If the [Neurite] has been sorted, the first and last branches are ordered by they azimuth, in other words the rightmost and leftmost branches correspond to the first and last position respectively.

ADD IMAGE

---

### Centrifugal order <a id="order"> </a>

**Function:** `branch_order = [](const Branch &b) -> int`

**Description:** Returns the centrifugal order of the given [Branch]

**Output:** Non-negative integer

**Details:** Branch orders counts the number of bifurcations in the path from the given [Branch] to the root of the [Neurite]. That is, the root [Branch] has a centrifugal order of 0, it's daughters have a centrifugal order of 1, and so on.

ADD IMAGE

---

### Child diameter ratio <a id="childdimratio"> </a>

**Function:** `child_diam_ratio = [](const Branch& b) -> float`

**Description:** Returns the child-diameter ratio of the daughters of the given [[Branch], the ratio of the daughter branches first node's diameters.

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always return 0.

` branch.child[0].first.diameter /  branch.child[1].first.diameter `

ADD IMAGE

---

### Parent-Child diameter ratio <a id="childdimratio"> </a>

**Function:** `parent_child_diam_ratio = [](const Branch& b) -> std::pair<float,float>`

**Description:** Returns the ratio between the diameter of the last node of the given branch and the first nodes of the daughter branches.

**Output:** Real number pair

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always return the pair (0,0).

` (branch.child[0].first.diameter/branch.last.diameter, branch.child[1].first.diameter/branch.last.diameter) `


ADD IMAGE

---

### Partition asymmetry <a id="partition"> </a>

**Function:** `partition_asymmetry = [](const Branch& b) -> float`

**Description:** The partition asymmetry first computes the number of terminal points in the left/right subtrees, *n1* and *n2* respectively. Then computes the following quantity as the partition asymmetry value:

` |n1-n2| / (n1 + n2 - 2)|`

**Output:** Non negative real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.

ADD IMAGE

---

### Rall's power fit <a id="rall"> </a>

**Factory function:** `auto rall_power_fit_factory(float min = 0 , float max = 5)`

**Function:** `(const Branch &b) -> float `

**Description:** Computes the best value for the parameter *r* in the range [*min*,*max*] that minimizes the following quantity:

`(branch.diameter^r - branch.child[0].diameter^r - branch.child[1].diameter^r)^2`

**Output:** Real number - best fit value

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.

ADD IMAGE

---

### Pk measure <a id="pk"> </a>

**Factory function:** `auto pk_factory(float r)`

**Function:** `(const Branch &b) -> float`

**Description:** Given the parameter *r*, computes the quantity:

`(branch.child[0].diameter^r - branch.child[1].diameter^r)/branch.diameter^r`

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2, the measure always returns -1.

**Note:** `pk_fit_factory(float min = 0 , float max = 5)` just applies this same measure where *r* is computed using [Rall's power fit](#rall).

ADD IMAGE

---

### Hillman threshold <a id="hillman_threshold"> </a>

**Function:** `hillman_threshold = [](const Branch &b) -> float`

**Description:** Computes the Hillman threshold value for the given [Branch] bifurcation. The Hillman threshold is the weighted sum of parent and daugther diameters (0.5,0.25,0.25). Hillman threshold only applies to pre-terminal branches (i.e to terminal bifurcation nodes).

`0.25*(branch.child[0].diameter + branch.child[1].diameter) + 0.5*branch.diameter`

**Output:** Real number

**Details:** If the number of descendants of the given [Branch] is not equal to 2 or it is not a pre-terminal branch the measure returns -1.

ADD IMAGE

---

### Local bifurcation angle <a id="localbif"> </a>

**Function:** `local_bifurcation_angle = [](const Branch &b) -> float`

**Description:** Computes the bifurcation amplitude, measured as the shortest planar angle between the vectors from the bifurcation node (the last node of the given branch) to the first nodes of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.

ADD IMAGE

---

### Remote bifurcation angle <a id="remotebif"> </a>

**Function:** `remote_bifurcation_angle = [](const Branch &b) -> float`

**Description:** Computes the bifurcation amplitude, measured as the shortest planar angle between the vectors from the bifurcation node (the last node of the given branch) to the last nodes of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.

ADD IMAGE

---

### Local tilt angle <a id="localtilt"> </a>

**Function:** `local_tilt_angle = [](const Branch &b) -> float`

**Description:** Computes the tilt angle at the last node bifurcation point. Tilt angle is the smallest angle between the branch director vector and the vectors form the bifurcation point to the first node of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.

ADD IMAGE

---

### Remote tilt angle <a id="remotetilt"> </a>

**Function:** `remote_tilt_angle = [](const Branch &b) -> float`

**Description:** Computes the tilt angle at the last node bifurcation point. Tilt angle is the smallest angle between the branch director vector and the vectors form the bifurcation point to the last node of the daughter branches.

**Output:** Real number. Angle in radians [0,pi]

**Details:** If the number of descendants of the given [Branch] is not equal to 2 it returns -1. NAN values might appear if null segments are present.

ADD IMAGE

---

### Local plane vector <a id="localplane"> </a>

**Function:** `local_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the normal vector to the plane defined by the vectors from the root to the first node of the daughter branches.

**Output:** Plane normal vector

**Details:** If the branch don't have a sibling branch, it returns the null vector.

ADD IMAGE

---

### Remote plane vector <a id="remoteplane"> </a>

**Function:** `remote_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the normal vector to the plane defined by the vectors from the branch root and the last node of the daughter branches.

**Output:** Plane normal vector

**Details:** If the branch don't have a sibling branch, it returns the null vector.

ADD IMAGE

---

### Local torque angle <a id="localtoruqe"> </a>

TODO CONTINUE HERE!

**Function:** `local_plane_vector = [](const Branch &b) -> point_type `

**Description:** Computes the normal vector to the plane defined by the vectors from the root to the first node of the daughter branches.

**Output:** Plane normal vector

**Details:** If the branch don't have a sibling branch, it returns the null vector.

ADD IMAGE

---

- [Local tilt angle](measures/branch.html#localtilt)
- [Remote tilt angle](measures/branch.html#remotetilt)
- [Local torque angle](measures/branch.html#localtoruqe)
- [Remote torque angle](measures/branch.html#remotetorque)
- [Length](measures/branch.html#length)
- [Intersects](measures/branch.html#intersects)


[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
[Soma]: ../goals_architecture.html#soma
