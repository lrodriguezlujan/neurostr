---
currentSection: measures
currentSubsection: predef
currentItem: lmeasure
---
# L-measure measures {#lmeasure}

### Soma surface <a id="lmeasure_somasurface"> </a>

**Function:** `soma_surface`

**Description:** Computes the soma surface area under spherical shape assumption.

**Output:** Non-negative real number. Soma surface area. Zero if the neuron don't have soma points.

**Details:** If there are several soma points, the computed area is the surface of the sphere centered at the soma barycenter with radius the average distance from the barycenter to the external border of the sphere. See [soma_surface](neuron.html#soma_surface) measure.

ADD IMAGE HERE

---

### Number of stems <a id="lmeasure_nstems"> </a>

**Function:** `n_stems`

**Description:** Returns the number of stems (what we call neurites) in the neuron.

**Output:** Non-negative integer. Number of stems/neurites.

**Details:**  See [neuron_neurite_count](neuron.html#neurite_count) measure.

---

### Number of bifurcations <a id="lmeasure_nbifs"> </a>

**Function:** `n_bifs`

**Description:** Returns the number of bifurcation points in the neuron.

**Output:** Non-negative integer. Number of bifurcations.

---

### Number of branches <a id="lmeasure_nbranches"> </a>

**Function:** `n_branch`

**Description:** Counts the number of branches in the neuron.

**Output:** Non-negative integer. Number of branches.

---

### Number of terminal tips <a id="lmeasure_nterminals"> </a>

**Function:** `n_tips`

**Description:** Counts the number of terminal tips in the neuron.

**Output:** Non-negative integer. Terminal tips count.

---

### Width, Height and Depth <a id="lmeasure_width"> </a>

**Function:** `width`, `height`, `depth`

**Description:** Computes the neuron [range length](../measures.html#range) for the x,y and z axis respectively.

**Output:** Non-negative real number.

ADD IMAGE HERE

---

### Diameter <a id="lmeasure_diameter"> </a>

**Function:** `diameter`

**Description:** Computes the [Summary] statistics for the [Node] diameter value.

**Output:** Diameter [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node diameter](node.html#diameter) measure.

---

### Diameter power <a id="lmeasure_diameterpow"> </a>

**Function:** `diameter_pow`

**Description:** Computes the [Summary] statistics for the [Node] diameter value power to 1.5.

**Output:** Diameter power [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node diameter pow](node.html#diameterpow) measure.

---

### Length <a id="lmeasure_length"> </a>

**Function:** `length`

**Description:** Computes the [Summary] statistics for compartment lengths.

**Output:** Compartment length [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node length to parent](node.html#length) measure.

ADD IMAGE HERE

---

### Branch length <a id="lmeasure_branchlength"> </a>

**Function:** `branch_pathlength`

**Description:** Computes the [Summary] statistics for branch lengths.

**Output:** Branch length [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch length](branch.html#length) measure.

ADD IMAGE HERE

---

### Surface <a id="lmeasure_surface"> </a>

**Function:** `surface`

**Description:** Computes the [Summary] statistics for compartment surface area.

**Output:** Compartment surface [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment surface](node.html#surface) measure.

ADD IMAGE HERE

---

### Branch surface <a id="lmeasure_branchsurface"> </a>

**Function:** `branch_surface`

**Description:** Computes the [Summary] statistics for branch surface area.

**Output:** Branch surface area [Summary] stats (sum, max, min, median, mean and sd).

**Details:** Branch surface is computed as the sum of compartment surfaces. See [Node compartment surface](node.html#surface) measure.

ADD IMAGE HERE

---

### Compartment section area <a id="lmeasure_section_area"> </a>

**Function:** `section_area`

**Description:** Computes the [Summary] statistics for compartment section area.

**Output:** Compartment section area [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment section area](node.html#section_area) measure.

ADD IMAGE HERE

---


### Compartment volume <a id="lmeasure_volume"> </a>

**Function:** `volume`

**Description:** Computes the [Summary] statistics for compartment volume.

**Output:** Compartment volume [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node compartment volume](node.html#volume) measure.

ADD IMAGE HERE

---

### Branch Volume <a id="lmeasure_branch_volume"> </a>

**Function:** `branch_volume`

**Description:** Computes the [Summary] statistics for branch compartment volume.

**Output:** Branch volume [Summary] stats (sum, max, min, median, mean and sd).

**Details:** Branch volume is computed as the sum of compartment surfaces. See [Node compartment volume](node.html#volume) measure.

ADD IMAGE HERE

---

### Distance to root <a id="lmeasure_rootdist"> </a>

**Function:** `euc_distance`

**Description:** Computes the [Summary] statistics for the euclidean distance of each [Node] to the [Neurite] root.

**Output:** Distance [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node root distance](node.html#rootdist) measure.

ADD IMAGE HERE

---

### Path length to root <a id="lmeasure_rootpath"> </a>

**Function:** `path_distance`

**Description:** Computes the [Summary] statistics for the path distance of each [Node] to the [Neurite] root.

**Output:** Distance [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Node path distance](node.html#rootpath) measure.

ADD IMAGE HERE

---

### Branch centrifugal order <a id="lmeasure_branchorder"> </a>

**Function:** `branch_order`

**Description:** Computes the [Summary] statistics for the branch centrifugal order of each [Branch] in the neuron.

**Output:** Centrifugal order [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch centrifugal order](branch.html#order) measure.

ADD IMAGE HERE

---

### Node Terminal degree <a id="lmeasure_terminaldegree"> </a>

**Function:** `terminal_degree`

**Description:** Computes the [Summary] statistics for the terminal degree centrifugal order of each [Node] in the neuron. The terminal degree is the number of terminal tips in the subtree of the given [Node].

**Output:** Terminal degree [Summary] stats (sum, max, min, median, mean and sd).

ADD IMAGE HERE

---

### Branch Terminal degree <a id="lmeasure_branch_terminaldegree"> </a>

**Function:** `branch_terminal_degree`

**Description:** Computes the [Summary] statistics for the terminal degree centrifugal order of each [Branch] in the neuron. The terminal degree is the number of terminal tips in the subtree of the given [Branch].

**Output:** Terminal degree [Summary] stats (sum, max, min, median, mean and sd).

ADD IMAGE HERE

---


### Taper 1: Burker taper rate <a id="lmeasure_burker"> </a>

**Function:** `taper_1`

**Description:** Computes the [Summary] statistics for the branch Burker taper rate [Branch] in the neuron for every [Branch] in the [Neuron].

**Output:** Taper rate [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Burker taper rate](branch.html#burker) measure.

ADD IMAGE HERE

---

### Taper 2: Hillman taper rate <a id="lmeasure_hillman"> </a>

**Function:** `taper_2`

**Description:** Computes the [Summary] statistics for the branch Hillman taper rate [Branch] in the neuron for every [Branch] in the [Neuron].

**Output:** Taper rate [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Hillman taper rate](branch.html#hillman) measure.

ADD IMAGE HERE

---

### Contraction <a id="lmeasure_contraction"> </a>

**Function:** `contraction`

**Description:** Computes the [Summary] statistics for the [Branch] contraction, i.e. its tortuosity for every [Branch] in the [Neuron].

**Output:** Contraction [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Tortuosity](branch.html#tortuosity) measure.

ADD IMAGE HERE

---

### Fragmentation <a id="lmeasure_fragmentation"> </a>

**Function:** `fragmentation`

**Description:** Computes the [Summary] statistics for the [Branch] fragmentation, i.e. its number of nodes for every [Branch] in the [Neuron].

**Output:** Fragmentation [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Branch size](branch.html#size) measure.

ADD IMAGE HERE

---

### Daughter ratio <a id="lmeasure_daughter_ratio"> </a>

**Function:** `daughter_ratio`

**Description:** Computes the [Summary] statistics for the [Branch] daughter ratio, i.e. the ratio of the diameters of its daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Daughter ratio [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Child diameter ratio](branch.html#chid_diam) measure.

ADD IMAGE HERE

---

### Partition asymmetry <a id="lmeasure_partition_asymmetry"> </a>

**Function:** `partition_asymmetry`

**Description:** Computes the [Summary] statistics for the [Branch] partition asymmetry value, i.e. the ratio between the number of terminals in the left-subtree and the right-subtree , for every non-terminal [Branch] in the [Neuron].

**Output:** Partition asymmetry [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Partition asymmetry](branch.html#partition_asymmetry) measure.

ADD IMAGE HERE

---

### Rall's power <a id="lmeasure_rall"> </a>

**Function:** `rall_power`

**Description:** Computes the [Summary] statistics for the Rall's power fitted value for every non-terminal [Branch] in the [Neuron].

**Output:** Rall's power fitted value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Rall's power fit ](branch.html#rall) measure.

ADD IMAGE HERE

---

### Pk fitted value <a id="lmeasure_pkfit"> </a>

**Function:** `pk`

**Description:** Computes the [Summary] statistics for the Pk with factor given by the fitted value returned by the [Rall's power fit ](branch.html#rall) measure for every non-terminal [Branch] in the [Neuron].

**Output:** Pk value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Rall's power fit ](branch.html#rall) and [Pk factory](branch.html#pk) measures.

ADD IMAGE HERE

---

### Pk classic and squared <a id="lmeasure_pkclassic"> </a>

**Function:** `pk_classic`, `pk2`

**Description:** Computes the [Summary] statistics for the Pk with factors 1.5 and 2 respectively for every non-terminal [Branch] in the [Neuron].

**Output:** Pk value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Pk factory](branch.html#pk) measure.

ADD IMAGE HERE

---

### Local bifurcation amplitude <a id="lmeasure_local_bif"> </a>

**Function:** `bif_ampl_local`

**Description:** Computes the [Summary] statistics for the bifurcation angle computed w.r.t. the  firs node in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation amplitude (angle in radians) [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local bifurcation angle](branch.html#local_bif) measure.

ADD IMAGE HERE

---

### Remote bifurcation amplitude <a id="lmeasure_remote_bif"> </a>

**Function:** `bif_ampl_remote`

**Description:** Computes the [Summary] statistics for the bifurcation angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation amplitude (angle in radians) [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote bifurcation angle](branch.html#remote_bif) measure.

ADD IMAGE HERE

---

### Local bifurcation tilt <a id="lmeasure_local_tilt"> </a>

**Function:** `bif_tilt_local`

**Description:** Computes the [Summary] statistics for the bifurcation tilt angle computed w.r.t. the first nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Tilt angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local tilt angle](branch.html#local_tilt) measure.

ADD IMAGE HERE

---

### Remote bifurcation tilt <a id="lmeasure_remote_tilt"> </a>

**Function:** `bif_tilt_remote`

**Description:** Computes the [Summary] statistics for the bifurcation tilt angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation tilt angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote tilt angle](branch.html#remote_tilt) measure.

ADD IMAGE HERE

---

### Local bifurcation torque <a id="lmeasure_local_torque"> </a>

**Function:** `bif_torque_local`

**Description:** Computes the [Summary] statistics for the bifurcation torque angle computed w.r.t. the first nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Torque angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Local torque angle](branch.html#local_torque) measure.

ADD IMAGE HERE

---

### Remote bifurcation tilt <a id="lmeasure_remote_torque"> </a>

**Function:** `bif_torque_remote`

**Description:** Computes the [Summary] statistics for the bifurcation torque angle computed w.r.t. the last nodes in the daughter branches for every non-terminal [Branch] in the [Neuron].

**Output:** Bifurcation torque angle in radians [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Remote torque angle](branch.html#remote_torque) measure.

ADD IMAGE HERE

---

### Terminal bifurcation diameter <a id="lmeasure_terminaldiam"> </a>

**Function:** `last_parent_diam`

**Description:** Computes the [Summary] statistics for the diameter of every terminal bifurcation (see [Terminal bifurcation selector](../selectors/neurite.html#terminal_bif)) [Node] in the [Neuron].

**Output:** [Node] diameter [Summary] stats (sum, max, min, median, mean and sd).

ADD IMAGE HERE

---

### Hillman threshold <a id="lmeasure_hillman_threshold"> </a>

**Function:** `hillman_threshold`

**Description:** Computes the [Summary] statistics for the Hillman threshold value (see [Hillman threshold measure](branch.html#hillman_threshold)) for every pre-terminal [Branch] in the [Neuron].

**Output:** Hillman threshold value [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Hillman threshold](branch.html#hillman_threshold) measure.

ADD IMAGE HERE

---

### Fractal dimension <a id="lmeasure_fractal_dimension"> </a>

**Function:** `fractal_dim`

**Description:** Computes the [Summary] statistics for the Fractal dimension of every [Branch] in the [Neuron].

**Output:** Fractal dimension [Summary] stats (sum, max, min, median, mean and sd).

**Details:** See [Fractal dimension](node.html#fractal_dimension) measure.

ADD IMAGE HERE

---

[Node]: ../goals_architecture.html#node
[Branch]: ../goals_architecture.html#branch
[Neurite]: ../goals_architecture.html#neurite
[Neuron]: ../goals_architecture.html#neuron
[Summary]: (../measures.html#summary)
