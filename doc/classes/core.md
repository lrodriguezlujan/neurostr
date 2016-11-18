---
currentSection: class
currentSubsection: core
currentItem:
---
# Core classes

---

# class `Branch` {#class_branch}

```
class Branch
  : public neurostr::WithProperties
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  Branch()` | Default constructor.
`public  Branch(const id_type & id,int order)` | Creates a branch with given id and order.
`public  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root)` | Creates a branch with given id,order and root.
`public  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root,const std::vector< `[`Node`](#class_node)` > & nodes)` | Creates a branch with given id,order, root and nodes.
`public template<typename Iter>`  <br/>`inline  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root,const Iter & b,const Iter & e)` | Creates a branch with given id,order, root and nodes.
`public inline  ~Branch()` | Empty destructor.
`public  Branch(const `[`Branch`](#class_branch)` & b) = delete` | Copy constructor is not allowed.
`public `[`Branch`](#class_branch)` & operator=(const `[`Branch`](#class_branch)` & b) = delete` | Copy assign is not allowed.
`public  Branch(`[`Branch`](#class_branch)` && b) = default` | Default move constructor.
`public `[`Branch`](#class_branch)` & operator=(`[`Branch`](#class_branch)` && b) = default` | Defaul move assign.
`public inline int order() const` | Centrifugal order accessor.
`public inline const id_type & id() const` | ID accessor.
`public std::string idString() const` | Returns [Branch](#class_branch) ID as a string.
`public inline bool valid_neurite() const` | [Branch](#class_branch) neurite reference validity check.
`public const `[`Neurite`](#class_neurite)` & neurite() const` | [Branch](#class_branch) parent neurite.
`public `[`Neurite`](#class_neurite)` & neurite()` | [Branch](#class_branch) parent neurite.
`public `[`Branch`](#class_branch)` & id(const id_type & id)` | Set branch id.
`public `[`Branch`](#class_branch)` & order(int o)` | Set branch centrifugal order.
`public `[`Branch`](#class_branch)` & neurite(`[`Neurite`](#class_neurite)` * n)` | Set branch parent neurite.
`public inline void root(const `[`Node`](#class_node)` & n)` | Copy a node as new root.
`public inline void remove_root()` | Removes the current root.
`public inline void root(`[`Node`](#class_node)` && n)` | Move a node as new root.
`public inline bool operator==(const `[`Branch`](#class_branch)` & b) const` | Compares two branches by their ID.
`public inline bool operator!=(const `[`Branch`](#class_branch)` & b) const` | Compares two branches by their ID.
`public inline size_type size() const` | Number of nodes in the b.
`public inline bool has_root() const` | [Branch](#class_branch) root validity check.
`public const `[`Node`](#class_node)` & root() const` | Get root node reference.
`public `[`Node`](#class_node)` & root()` | Get root node reference.
`public const `[`Node`](#class_node)` & first() const` | Returns branch first node.
`public const `[`Node`](#class_node)` & last() const` | Returns branch last node.
`public `[`Node`](#class_node)` & first()` | Returns branch first node.
`public `[`Node`](#class_node)` & last()` | Returns branch last node.
`public point_type director_vector() const` | Returns vector from the first node of the branch to the last.
`public template<typename T>`  <br/>`inline auto add_property(const std::string & key,T value,bool recursive)` | Adds a property to the branch and optionally to its nodes.
`public inline auto add_property(const std::string & key,bool recursive)` | Adds an empty property to the branch and optionally to its nodes.
`public inline iterator begin()` | Begin node iterator (indirect iterator)
`public inline iterator end()` | End node iterator (indirect iterator)
`public inline reverse_iterator rbegin()` | Reverse begin node iterator (indirect iterator)
`public inline reverse_iterator rend()` | Reverse end node iterator (indirect iterator)
`public inline const_iterator begin() const` | Begin node iterator (indirect iterator)
`public inline const_iterator end() const` | End node iterator (indirect iterator)
`public inline const_reverse_iterator rbegin() const` | Reverse begin node iterator (indirect iterator)
`public inline const_reverse_iterator rend() const` | Reverse end node iterator (indirect iterator)
`public inline const_iterator cbegin() const` | Begin const node iterator (indirect iterator)
`public inline const_iterator cend() const` | End const node iterator (indirect iterator)
`public void push_back(const `[`Node`](#class_node)` & n)` | Copy a node to the end of the branch.
`public void push_back(`[`Node`](#class_node)` && n)` | Move a node to the end of the branch.
`public iterator insert(iterator pos,const `[`Node`](#class_node)` & n)` | Copies the given node at the position.
`public template<typename Iter>`  <br/>`inline void insert(iterator pos,Iter b,Iter e)` | Copies a range of nodes into the branch.
`public iterator erase(const iterator & pos)` | Deletes a node in the branch.
`public iterator erase(const iterator & first,const iterator & last)` | Deletes a range of nodes in the branch.
`public inline void clear()` | Deletes all nodes in the brnach.
`public `[`Branch`](#class_branch)` split(const iterator & pos)` | Divides the branch at given position and creates a new branch.
`public void simplify(float eps)` | Applies RDF simplification to the branch nodes.
`public void scale(float r)` | Scales the branch wrt root by r (>1 bigger, <1 smaller)
`public void normalize()` | Scales the branch so its length is equal to 1.
`public void scale(float rx,float ry,float rz)` | Scales branch (including root)
`public float length() const` | Computes branch path length.
`public void traslate(const point_type & p)` | Moves the branch (root included) by the vector p.
`public void rotate(const Eigen::Quaternionf & q)` | Rotates the branch (Root included) aplying the quaternion q.
`public void remove_null_segments()` | Removes zero-length segments in the branch.
`public float discrete_frechet(const `[`Branch`](#class_branch)` & other) const` | Computes the frechet distance between two branche s.
`public float distance(const `[`Branch`](#class_branch)` & other,bool ignore_radius) const` | Computes the distance between both branches.
`public void set_nodes_branch()` | Updates branch memeber in all nodes.
`public box_type boundingBox() const` | Gets bounding box.

## Members

### `public  Branch()` {#class_branch_1aa0b320c5e78c951252ede4e8be08504e}

Default constructor.

creates a branch with order -1 and empty id
#### Returns
[Branch](#class_branch)

---

### `public  Branch(const id_type & id,int order)` {#class_branch_1a46c3ebbf1e01047196af0062d62719a0}

Creates a branch with given id and order.

#### Parameters
* `id` [Branch](#class_branch) id


* `order` [Branch](#class_branch) order





#### Returns
[Branch](#class_branch)

---

### `public  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root)` {#class_branch_1adbd7f94f44e4887262cc67306dc6ba03}

Creates a branch with given id,order and root.

#### Parameters
* `id` [Branch](#class_branch) id


* `order` Centrifugal order


* `root` [Branch](#class_branch) root node





#### Returns
[Branch](#class_branch)

---

### `public  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root,const std::vector< `[`Node`](#class_node)` > & nodes)` {#class_branch_1a6b4d036568d1a7d6e367a7d61e4c391d}

Creates a branch with given id,order, root and nodes.

#### Parameters
* `id` [Branch](#class_branch) id


* `order` Centrifugal order


* `root` [Branch](#class_branch) root node


* `nodes` [Branch](#class_branch) nodes





#### Returns
[Branch](#class_branch)

---

### `public template<typename Iter>`  <br/>`inline  Branch(const id_type & id,int order,const `[`Node`](#class_node)` & root,const Iter & b,const Iter & e)` {#class_branch_1a136194adc4838b87416ce12f57ac457f}

Creates a branch with given id,order, root and nodes.

#### Parameters
* `id` [Branch](#class_branch) id


* `order` Centrifugal order


* `root` [Branch](#class_branch) root node


* `b` [Node](#class_node) begin iterator


* `e` [Node](#class_node) end iterator





#### Returns
[Branch](#class_branch)

---

### `public inline  ~Branch()` {#class_branch_1aaf14b7e060421c5fa1008779dd32f674}

Empty destructor.



---

### `public  Branch(const `[`Branch`](#class_branch)` & b) = delete` {#class_branch_1a1137aff329a5779c9e224a17e6247712}

Copy not allowed.

**DELETED**

---

### `public `[`Branch`](#class_branch)` & operator=(const `[`Branch`](#class_branch)` & b) = delete` {#class_branch_1a6d6845c914e6d3f9f7b16e2edd6e8d66}

Copy not allowed.

**DELETED**

---

### `public  Branch(`[`Branch`](#class_branch)` && b) = default` {#class_branch_1aeeb0df66cbcd2c1489b50fa1f19088dd}

Default move constructor.



---

### `public `[`Branch`](#class_branch)` & operator=(`[`Branch`](#class_branch)` && b) = default` {#class_branch_1a514d825a62be35df18b6b595978f5dae}

Defaul move assign.



---

### `public inline int order() const` {#class_branch_1af0e7e06c6b7d50951d5e0fb95dac36b6}

Centrifugal order accessor.

#### Returns
Centrifugal order

---

### `public inline const id_type & id() const` {#class_branch_1a11cabaa338d18fb7492926b9468c432e}

Returns the [Branch](#class_branch) ID as a vector of integers.

#### Returns
[Branch](#class_branch) Id

---

### `public std::string idString() const` {#class_branch_1aeb8511e2eaa637d88cc101834cd281a2}

Returns [Branch](#class_branch) ID as a string.

#### Returns
ID as string

---

### `public inline bool valid_neurite() const` {#class_branch_1afccafb5312d8ffea0ad707af64d79746}

[Branch](#class_branch) neurite reference validity check.

#### Returns
True if the [Neurite](#class_neurite) reference is valid

---

### `public const `[`Neurite`](#class_neurite)` & neurite() const` {#class_branch_1a28f7d24538f640d7e06aed62f03cd3d1}

[Branch](#class_branch) parent neurite.

#### Returns
Parent [Neurite](#class_neurite) reference

---

### `public `[`Neurite`](#class_neurite)` & neurite()` {#class_branch_1adc4b492f1c2ef06e53afcf37b64c06a0}

[Branch](#class_branch) parent neurite.

#### Returns
Parent neurite reference

---

### `public `[`Branch`](#class_branch)` & id(const id_type & id)` {#class_branch_1a0f08d3931ca09bbe8e4e661d8ef65493}

Set branch id.

#### Parameters
* `id` new id





#### Returns
Updated branch reference

---

### `public `[`Branch`](#class_branch)` & order(int o)` {#class_branch_1a3be74daf6c31a93e6d56ba397be745dc}

Set branch centrifugal order.

#### Parameters
* `o` new centrifugal order





#### Returns
Update branch reference

---

### `public `[`Branch`](#class_branch)` & neurite(`[`Neurite`](#class_neurite)` * n)` {#class_branch_1ac73afc2942a475e19db06472c26c792e}

Set branch parent neurite.

#### Parameters
* `n` [Neurite](#class_neurite) pointer





#### Returns
Update branch reference

---

### `public inline void root(const `[`Node`](#class_node)` & n)` {#class_branch_1a30ef19268a3d8d82f11aa84756932177}

Copy a node as new root.

#### Parameters
* `n` node to copy

---

### `public inline void remove_root()` {#class_branch_1acb0a8e7c50db6b1a65cdb88e585fb6b6}

Removes the current root.



---

### `public inline void root(`[`Node`](#class_node)` && n)` {#class_branch_1a11f6365be493046c7bd311daea1cdc61}

Move a node as new root.

#### Parameters
* `n` node to move

---

### `public inline bool operator==(const `[`Branch`](#class_branch)` & b) const` {#class_branch_1acd05258406942a6e88cb21b791c3e05f}

Compares two branches by their ID.

#### Parameters
* `b` [Branch](#class_branch)





#### Returns
True if two ids are equal

---

### `public inline bool operator!=(const `[`Branch`](#class_branch)` & b) const` {#class_branch_1a4293f0e0be34abfb2fff756cac7f49aa}

Compares two branches by their ID.

#### Parameters
* `b` [Branch](#class_branch)





#### Returns
True if two ids are NOT equal

---

### `public inline size_type size() const` {#class_branch_1a9f4228989204d5e9cd8d0605efcaac32}

Number of nodes in the b.

#### Returns
[Branch](#class_branch) size

---

### `public inline bool has_root() const` {#class_branch_1a6b4d6f5c02a3aa29b94c397ad9596784}

[Branch](#class_branch) root validity check.

#### Returns
True/False

---

### `public const `[`Node`](#class_node)` & root() const` {#class_branch_1afa19d56be3a754ba48b5968476b0b51d}

Get root node reference.

#### Throws
* `runtime_error` Attempt to access nullptr reference

#### Returns
Root node reference

---

### `public `[`Node`](#class_node)` & root()` {#class_branch_1a4b61255c68dbd659702132308f417c92}

Get root node reference.

#### Throws
* `runtime_error` Attempt to access nullptr reference

#### Returns
Root node reference

---

### `public const `[`Node`](#class_node)` & first() const` {#class_branch_1a9a85d3a1cad2260ef80fcc869be8b0bf}

Returns branch first node.

#### Throws
* `runtime_error` Attempt to access empty branch

#### Returns
[Node](#class_node) reference

---

### `public const `[`Node`](#class_node)` & last() const` {#class_branch_1a080cc50c1d359f731c6a25cb47fdf9a4}

Returns branch last node.

#### Throws
* `runtime_error` Attempt to access empty branch

#### Returns
[Node](#class_node) reference

---

### `public `[`Node`](#class_node)` & first()` {#class_branch_1a18efe57b0cee114d84161ce0992c19d5}

Returns branch first node.

#### Throws
* `runtime_error` Attempt to access empty branch

#### Returns
[Node](#class_node) reference

---

### `public `[`Node`](#class_node)` & last()` {#class_branch_1ab572b6757b84335171a57316006fadc9}

Returns branch last node.

#### Throws
* `runtime_error` Attempt to access empty branch

#### Returns
[Node](#class_node) reference

---

### `public point_type director_vector() const` {#class_branch_1a4b658a7e97c72f9c7cff2295e3ee10f4}

Returns vector from the first node of the branch to the last.

#### Returns
Vector

---

### `public template<typename T>`  <br/>`inline auto add_property(const std::string & key,T value,bool recursive)` {#class_branch_1ab5f628b002d50a6bb3bce6dbc768c642}

Adds a property to the branch and optionally to its nodes.

#### Parameters
* `key` Property name


* `value` Property value


* `recursive` If true, property is also added to branch nodes

#### Returns
Iterator to added property

---

### `public inline auto add_property(const std::string & key,bool recursive)` {#class_branch_1a301b484cb4239af143463e5ad80ce4d4}

Adds an empty property to the branch and optionally to its nodes.

#### Parameters
* `key` Property name


* `recursive` If true, property is also added to branch nodes


#### Returns
Iterator to added property

---

### `public inline iterator begin()` {#class_branch_1a24ecb6e31e508f05ffb76c7cafe102d9}

Begin node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline iterator end()` {#class_branch_1a89b7514bbc9eb233c2bf4beade1932f3}

End node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline reverse_iterator rbegin()` {#class_branch_1aa4985e2559e40ca6efcaaf6cc8fecd09}

Reverse begin node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline reverse_iterator rend()` {#class_branch_1a2626c1632fc79fab41ce8781ea95859a}

Reverse end node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_iterator begin() const` {#class_branch_1aeea5bcdf9726525db6a115683329cd5b}

Begin node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_iterator end() const` {#class_branch_1a2bb0fc46bb5db4efdfc6ffaa75936d4f}

End node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_reverse_iterator rbegin() const` {#class_branch_1ac4e3363782ed436f20a6df3613006047}

Reverse begin node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_reverse_iterator rend() const` {#class_branch_1a9b2b1a5b35bdfd6200681d91d5b3a1ae}

Reverse end node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_iterator cbegin() const` {#class_branch_1a2f1b2889358e7cb06fd7e9c4bc26babc}

Begin const node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public inline const_iterator cend() const` {#class_branch_1a3922132f47d6896ff9cfc47baa0dc0db}

End const node iterator (indirect iterator)

#### Returns
Indirect iterator

---

### `public void push_back(const `[`Node`](#class_node)` & n)` {#class_branch_1a078773ec08af93ae96f50e6c38783236}

Copy a node to the end of the branch.

#### Parameters
* `n` [Node](#class_node) to copy

---

### `public void push_back(`[`Node`](#class_node)` && n)` {#class_branch_1ab5b1d5bced85cba8b6721d36d73021bb}

Move a node to the end of the branch.

#### Parameters
* `n` [Node](#class_node) to move

---

### `public iterator insert(iterator pos,const `[`Node`](#class_node)` & n)` {#class_branch_1a46649bdb79415c5e79c8e1c44460e3e3}

Copies the given node at the position.

#### Parameters
* `pos` Position to insert


* `n` [Node](#class_node)





#### Returns
Updated iterator

---

### `public template<typename Iter>`  <br/>`inline void insert(iterator pos,Iter b,Iter e)` {#class_branch_1a194d46bbd5918605e2b15217cb1fe519}

Copies a range of nodes into the branch.

#### Parameters
* `pos` Insert position


* `b` Range begin iterator


* `e` Range end iterator

---

### `public iterator erase(const iterator & pos)` {#class_branch_1a813689cff6010890bd93273964a91b3f}

Deletes a node in the branch.

#### Parameters
* `pos` Position to delete





#### Returns
Updated iterator

---

### `public iterator erase(const iterator & first,const iterator & last)` {#class_branch_1a8a2f61537826d15a4d3a86293012f026}

Deletes a range of nodes in the branch.

#### Parameters
* `first` first position to delete


* `last` last position to delete





#### Returns
Updated iterator

---

### `public inline void clear()` {#class_branch_1a7f84824171b7187a4bc0a5717fb13f16}

Deletes all nodes in the branch.



---

### `public `[`Branch`](#class_branch)` split(const iterator & pos)` {#class_branch_1a5de6f0e15af4e7e7a6377ba950f2113a}

Divides the branch at given position and creates a new branch.

#### Parameters
* `pos` Split position





#### Returns
Split branch

---

### `public void simplify(float eps)` {#class_branch_1aa81b77aef56277031a531d22134e576a}

Applies RDF simplification to the branch nodes.

Root and last are always keeped
#### Parameters
* `eps` RDF algorithm epsilon parameter (tolerance). If eps is <0 is used as a relative tolerance to the node radius

---

### `public void scale(float r)` {#class_branch_1ad42431857e17e3f226b27b3398813af7}

Scales the branch wrt root by r (>1 bigger, <1 smaller)

#### Parameters
* `r` Scale rate

---

### `public void normalize()` {#class_branch_1ab7a18a51e2a8f47e34bc4e9e256b0b31}

Scales the branch so its length is equal to 1.



---

### `public void scale(float rx,float ry,float rz)` {#class_branch_1ad38b6ea74db9d8d99d6d46933220ed9f}

Scales branch (including root)

#### Parameters
* `rx` x-axis scale


* `ry` y-axis scale


* `rz` z-axis scale

---

### `public float length() const` {#class_branch_1a7b6cb383f3353013a69664c504f6a6f6}

Computes branch path length.

#### Returns
branch length

---

### `public void traslate(const point_type & p)` {#class_branch_1aa1edc843a383392fcd74cb13cc021b18}

Moves the branch (root included) by the vector p.

#### Parameters
* `p` Translation vector

---

### `public void rotate(const Eigen::Quaternionf & q)` {#class_branch_1af9f1684cd7106d56f38d397ff8ce8cec}

Rotates the branch (Root included) aplying the quaternion q.

#### Parameters
* `q` rotation quaternion

---

### `public void remove_null_segments()` {#class_branch_1aa7507c972e0b16067028bdb217995563}

Removes zero-length segments in the branch.



---

### `public float discrete_frechet(const `[`Branch`](#class_branch)` & other) const` {#class_branch_1adc4bbce7209ca615402bd9b6bdd8d0c4}

Computes the Discrete Frechet distance between two branches.

#### Parameters
* `other` [Branch](#class_branch)





#### Returns
Discrete frechet distance

---

### `public float distance(const `[`Branch`](#class_branch)` & other,bool ignore_radius) const` {#class_branch_1a156befe9e6fe58e49c3721b3f3329e49}

Computes the distance between both branches.

Ignores nodes shared by both branches
#### Parameters
* `other`





#### Returns
euclidean distance

---

### `public void set_nodes_branch()` {#class_branch_1a0ca6b621dd9c1a3847c75159c359353f}

Updates branch memeber in all nodes.



---

### `public box_type boundingBox() const` {#class_branch_1ada85b301fadb90c433bae05374fb25da}

Gets bounding box.




---

# class `Neurite` {#class_neurite}

```
class Neurite
  : public neurostr::WithProperties
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``const_node_iterator``](#class_neurite_const__node__iterator)        |
`class `[``node_iterator``](#class_neurite_node__iterator)        |
`class `[``stem_iterator``](#class_neurite_stem__iterator)        |
`public  Neurite()` | Empty neurite constructor.
`public  Neurite(int id)` | Create a neurite with given id and type undefined.
`public  Neurite(int id,const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & t)` | Create a neurite with given id and type.
`public  Neurite(const `[`Neurite`](#class_neurite)` & n) = default` | Default copy constructor.
`public  Neurite(`[`Neurite`](#class_neurite)` && n) = default` | Default move constructor.
`public `[`Neurite`](#class_neurite)` & operator=(const `[`Neurite`](#class_neurite)` & n) = default` | Default copy assign.
`public `[`Neurite`](#class_neurite)` & operator=(`[`Neurite`](#class_neurite)` && n) = default` | Default move assign.
`public inline  ~Neurite()` | Empty destructor (Default)
`public inline bool operator==(const `[`Neurite`](#class_neurite)` & n) const` | Compares two neurites by ID.
`public inline bool operator!=(const `[`Neurite`](#class_neurite)` & n) const` | Compares two neurites by ID.
`public inline const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & type() const` | Return neurite type.
`public inline const int id() const` | Returns neurite id.
`public inline bool root_is_soma() const` | Checks if root is soma.
`public inline `[`Neuron`](#class_neuron)` & neuron() const` | Return neurite parent neuron reference.
`public inline void type(const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & t)` | Set neurite type.
`public inline void id(int id)` | Set neurite ID.
`public inline void neuron(`[`Neuron`](#class_neuron)` *const n)` | Set neurite parent neuron pointer.
`public inline bool has_root() const` | Checks if the root branch of the neurite has root.
`public inline const `[`Node`](#class_node)` & root() const` | Get root reference.
`public void set_root()` | Sets an empt branch as the root branch without root node.
`public void set_root(const `[`Node`](#class_node)` & node)` | Creates an empty branch with node as root as root branch.
`public int max_centrifugal_order() const` | Get neurite max c.order.
`public inline int size() const` | [Neurite](#class_neurite) size (branch count)
`public int node_count() const` | [Neurite](#class_neurite) node count.
`public template<typename T>`  <br/>`inline auto add_property(const std::string & key,T v,bool recursive)` | Adds a property to the neurite and optionally to its branches.
`public inline auto add_property(const std::string & key,bool recursive)` | Adds an empty property to the neurite and optionally to its branches.
`public inline branch_iterator begin_branch() const` | Begin DFS branch iterator.
`public inline branch_iterator end_branch() const` | End DFS branch iterator.
`public inline branch_iterator begin_branch_subtree(const typename tree_type::iterator_base & other) const` | Creates a branch DFS iterator over the subtree of the branch pointed by €{other}.
`public branch_iterator end_branch_subtree(const typename tree_type::iterator_base & other) const` | Creates a branch DFS iterator over the subtree of the branch pointed by €{other}.

## Members

### `public  Neurite()` {#class_neurite_1a70b31382f151a1f7bf1ad21fa3cc88d7}

Empty neurite constructor.

Id -1 and type undefined
#### Returns
[Neurite](#class_neurite)

---

### `public  Neurite(int id)` {#class_neurite_1a2a677f05ad1c1409aafb0af4b1263bef}

Create a neurite with given id and type undefined.

#### Parameters
* `id` [Neurite](#class_neurite) id


#### Returns
[Neurite](#class_neurite)

---

### `public  Neurite(int id,const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & t)` {#class_neurite_1a1294c4fbf3f75b66cebeea1398519d95}

Create a neurite with given id and type.

#### Parameters
* `id` [Neurite](#class_neurite) id


* `t` [Neurite](#class_neurite) type





#### Returns
[Neurite](#class_neurite)

---

### `public  Neurite(const `[`Neurite`](#class_neurite)` & n) = default` {#class_neurite_1a0a1241d18fc286f358ffe5cf02699bde}

Default copy constructor.



---

### `public  Neurite(`[`Neurite`](#class_neurite)` && n) = default` {#class_neurite_1ab67cfab486fd55d0117f89812541f80a}

Default move constructor.



---

### `public `[`Neurite`](#class_neurite)` & operator=(const `[`Neurite`](#class_neurite)` & n) = default` {#class_neurite_1a24367013101636c139a5f64e53528091}

Default copy assign.



---

### `public `[`Neurite`](#class_neurite)` & operator=(`[`Neurite`](#class_neurite)` && n) = default` {#class_neurite_1aef76dbfc01e24464dd4cdad2b719cfd8}

Default move assign.



---

### `public inline  ~Neurite()` {#class_neurite_1ad25533d3089434fa779a8508302345a9}

Empty destructor (Default)



---

### `public inline bool operator==(const `[`Neurite`](#class_neurite)` & n) const` {#class_neurite_1a812aa3d916432e3126ce74ab3c246234}

Compares two neurites by ID.

#### Parameters
* `n` Other neurite





#### Returns
True if ids match

---

### `public inline bool operator!=(const `[`Neurite`](#class_neurite)` & n) const` {#class_neurite_1a3855817e45a82ae1128f1432be77b041}

Compares two neurites by ID.

#### Parameters
* `n` Other neurite


#### Returns
True if ids dont match

---

### `public inline const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & type() const` {#class_neurite_1a3a176cc109a831671afc2386f0c89ac3}

Return neurite type.

#### Returns
NeuriteType

---

### `public inline const int id() const` {#class_neurite_1ac24539f00c41e4ec4b1dda3e1fdbfb47}

Returns neurite id.

#### Returns
[Neurite](#class_neurite) ID

---

### `public inline bool root_is_soma() const` {#class_neurite_1aa3638b4160cb23294cfaa808bff4f966}

Checks if root is soma.

#### Returns
True if neurite root is soma

---

### `public inline `[`Neuron`](#class_neuron)` & neuron() const` {#class_neurite_1a9c2d455971e91a6d0c4b99382d107d61}

Return neurite parent neuron reference.

#### Returns
[Neuron](#class_neuron) reference

---

### `public inline void type(const `[`NeuriteType`](#namespace_1ac140abc732e29f73bf77fa7c480bc0a4)` & t)` {#class_neurite_1a14ca8371f112873e1b08e1b4f5272c26}

Set neurite type.

#### Parameters
* `t` New neurite type

---

### `public inline void id(int id)` {#class_neurite_1a2b6a1619fdf62536e411af547185969a}

Set neurite ID.

#### Parameters
* `id` New neurite ID

---

### `public inline void neuron(`[`Neuron`](#class_neuron)` *const n)` {#class_neurite_1a8f5c95ae579fbecb3d90ce0c0e7542a6}

Set neurite parent neuron pointer.

#### Parameters
* `n` Nueron pointer

---

### `public inline bool has_root() const` {#class_neurite_1a9a5cdefe94976c5c4d70107328745904}

Checks if the root branch of the neurite has root.

#### Returns
True if the neurite is rooted (i.e. attached to soma)

---

### `public inline const `[`Node`](#class_node)` & root() const` {#class_neurite_1a61d474df8a4547803759811c13ca88b8}

Get root reference.

#### Returns
Root reference

---

### `public void set_root()` {#class_neurite_1aefb57b25e8fb6d1785ad279f97b8f2f4}

Sets an empt branch as the root branch without root node.



---

### `public void set_root(const `[`Node`](#class_node)` & node)` {#class_neurite_1a5ae3bf5ee265b4368668a7622af08f24}

Creates an empty branch with node as root as root branch.

#### Parameters
* `node` Root node

---

### `public int max_centrifugal_order() const` {#class_neurite_1aee53307ab7b52074066b1b31fc37a2e9}

Get neurite max c.order.

#### Returns
Centrifugal order

---

### `public inline int size() const` {#class_neurite_1a82ea71e2e74624d6d4bc4b675d6a2e21}

[Neurite](#class_neurite) size (branch count)

#### Returns
Number of branches in the neurite

---

### `public int node_count() const` {#class_neurite_1aa42ed09f3591dcaf5ba3e17773eccb74}

[Neurite](#class_neurite) node count.

#### Returns
Number of distinct node ins the neurite (roots excluded)

---

### `public template<typename T>`  <br/>`inline auto add_property(const std::string & key,T v,bool recursive)` {#class_neurite_1a970625d7aba75f047161ae71bb19b955}

Adds a property to the neurite and optionally to its branches.

#### Parameters
* `key` Property key


* `v` Property value


* `recursive` If true, property is also added to braches and nodes

---

### `public inline auto add_property(const std::string & key,bool recursive)` {#class_neurite_1a71d836cb06374b8442f927c4d01c9a10}

Adds an empty property to the neurite and optionally to its branches.

#### Parameters
* `key` Property key


* `recursive` If true, property is also added to braches and nodes

---

### `public inline branch_iterator begin_branch() const` {#class_neurite_1aab9f08dd48a1d94f9ca84e9fd98b3efb}

Begin DFS branch iterator.

#### Returns
branch_iterator

---

### `public inline branch_iterator end_branch() const` {#class_neurite_1a3f122629f0b5c9d59d4096d01f567f20}

End DFS branch iterator.

#### Returns
branch_iterator

---

### `public inline branch_iterator begin_branch_subtree(const typename tree_type::iterator_base & other) const` {#class_neurite_1ae68a2a3570c403a4fd59458bcf172b5e}

Creates a branch DFS iterator over the subtree of the branch pointed by €{other}.

#### Parameters
* `other` [Branch](#class_branch) iterator





#### Returns
DFS branch iterator

---

### `public branch_iterator end_branch_subtree(const typename tree_type::iterator_base & other) const` {#class_neurite_1a24a27da8eeb5a54f316c492853b7aa73}

Creates a branch DFS iterator over the subtree of the branch pointed by €{other}.

#### Parameters
* `other` [Branch](#class_branch) iterator





#### Returns
DFS branch iterator


---

# class `node_iterator` {#class_neurite_node__iterator}

```
class node_iterator
  : public boost::iterator_facade< node_iterator< iter >, Node, std::iterator_traits< iter >::iterator_category >
```  

Template iterator that references directly to the nodes in the tree. The template parameter Iter, a branch iterator, determines  tree-visitor strategy.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  node_iterator()` | Empty constructor.
`public  node_iterator(const iter & b,const iter & e)` | Creates a node iterator that starts at the first node of b and ends at the first node of e.
`public  node_iterator(const iter & b,const iter & e,const iter & c)` | Creates a node iterator that starts at the first node of b and ends at the first node of e.
`public  node_iterator(const iter & b,const iter & e,const iter & c,const typename Branch::iterator & nodeit)` | Creates a node iterator that starts at the first node of b and ends at the first node of e.
`public  node_iterator(const `[`node_iterator`](#class_neurite_node__iterator)`< iter > &) = default` | Default copy constructor.
`public `[`node_iterator`](#class_neurite_node__iterator)` & operator=(const `[`node_iterator`](#class_neurite_node__iterator)`< iter > &) = default` | Default copy assign.
`public  node_iterator(`[`node_iterator`](#class_neurite_node__iterator)`< iter > &&) = default` | Default move constructor.
`public `[`node_iterator`](#class_neurite_node__iterator)` & operator=(`[`node_iterator`](#class_neurite_node__iterator)`< iter > &&) = default` | Default move assign.
`public iter begin() const` | Get iterator first branch.
`public iter end() const` | Get iterator last branch.
`public iter current() const` | Get iterator current branch.
`public iter branch() const` | Get iterator current branch.
`public Branch::iterator node() const` | Get iterator current noe.
`public `[`Neurite`](#class_neurite)` & neurite() const` | Get current branch neurite.
`public `[`Neuron`](#class_neuron)` & neuron() const` | Get current branch neuron.
`public `[`node_iterator`](#class_neurite_node__iterator)`< iter > last() const` | Get an iterator to the end node.
`public `[`node_iterator`](#class_neurite_node__iterator)`< iter > first() const` | Get an iterator to the first node.

## Members


### `public  node_iterator()` {#class_neurite_node__iterator_1a66419a0b06e9db3bbebcbbfceb9fcbbc}

Empty constructor.

#### Returns
[Node](#class_node) iterator

---

### `public  node_iterator(const iter & b,const iter & e)` {#class_neurite_node__iterator_1a5a64c917d858ce316e58e2101da113e6}

Creates a node iterator that starts at the first node of b and ends at the first node of e.

#### Parameters
* `b` First branch


* `e` Last branch





#### Returns
[Node](#class_node) iterator

---

### `public  node_iterator(const iter & b,const iter & e,const iter & c)` {#class_neurite_node__iterator_1a91f50a7999dbcf49e16500159e1e1bd5}

Creates a node iterator that starts at the first node of b and ends at the first node of e.

Current node is the first node of c.
#### Parameters
* `b` First branch


* `e` Last branch


* `c` Current branch





#### Returns
[Node](#class_node) iterator

---

### `public  node_iterator(const iter & b,const iter & e,const iter & c,const typename Branch::iterator & nodeit)` {#class_neurite_node__iterator_1a0e56efae1adab796071cfec772b919e9}

Creates a node iterator that starts at the first node of b and ends at the first node of e.

Current node is the nodeit node of c.
#### Parameters
* `b` First branch


* `e` Last branch


* `c` Current branch


* `nodeit` Current node





#### Returns
[Node](#class_node) iterator

---

### `public  node_iterator(const `[`node_iterator`](#class_neurite_node__iterator)`< iter > &) = default` {#class_neurite_node__iterator_1a7e1a5915fcb2fd57fd358a15e146456a}

Default copy constructor.



---

### `public `[`node_iterator`](#class_neurite_node__iterator)` & operator=(const `[`node_iterator`](#class_neurite_node__iterator)`< iter > &) = default` {#class_neurite_node__iterator_1a70bfb7d0caa7d8194e7e035cfa05ce28}

Default copy assign.



---

### `public  node_iterator(`[`node_iterator`](#class_neurite_node__iterator)`< iter > &&) = default` {#class_neurite_node__iterator_1a569568b8b346806027b39300094f5006}

Default move constructor.



---

### `public `[`node_iterator`](#class_neurite_node__iterator)` & operator=(`[`node_iterator`](#class_neurite_node__iterator)`< iter > &&) = default` {#class_neurite_node__iterator_1af5f6a5385e858dcad2b71f187e3bb511}

Default move assign.



---

### `public iter begin() const` {#class_neurite_node__iterator_1ad5586207b0e67f7cb5b5c76334d3df35}

Get iterator first branch.

#### Returns
First branch

---

### `public iter end() const` {#class_neurite_node__iterator_1a80e578a455127c48827cbf030bad22c0}

Get iterator last branch.

#### Returns
Last branch

---

### `public iter current() const` {#class_neurite_node__iterator_1a16221aeff3fbbbef0b20fdf8e9afd0bf}

Get iterator current branch.

#### Returns
Current branch

---

### `public iter branch() const` {#class_neurite_node__iterator_1af8bb3f863a844c1ec0fa76b0af78c229}

Get iterator current branch.

#### Returns
Current branch

---

### `public Branch::iterator node() const` {#class_neurite_node__iterator_1acdfdca8aca742c8359d1cadd01902245}

Get iterator current noe.

#### Returns
Current node

---

### `public `[`Neurite`](#class_neurite)` & neurite() const` {#class_neurite_node__iterator_1a47f5ac0f31f3bc2e1014035b0b3695b0}

Get current branch neurite.

#### Returns
[Neurite](#class_neurite) reference

---

### `public `[`Neuron`](#class_neuron)` & neuron() const` {#class_neurite_node__iterator_1a88f92f31aea01561290cff6e8b844c03}

Get current branch neuron.

#### Returns
[Neuron](#class_neuron) reference

---

### `public `[`node_iterator`](#class_neurite_node__iterator)`< iter > last() const` {#class_neurite_node__iterator_1a49d7f38b76ac784f48b520960b4b8e68}

Get an iterator to the end node.

#### Returns
End node iterator

---

### `public `[`node_iterator`](#class_neurite_node__iterator)`< iter > first() const` {#class_neurite_node__iterator_1af68cd71c0040200c5b944cef3df7cb12}

Get an iterator to the first node.

#### Returns
First node iterator


---

# class `stem_iterator` {#class_neurite_stem__iterator}

```
class stem_iterator
  : public iterator_base
```  
Tree iterator (Actually a forward iterator) that ascends from the given tree node to the root.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  stem_iterator()` | Empty constructor.
`public  stem_iterator(tree_node * tn)` | Creates an stem iterator that points to tn.
`public  stem_iterator(const typename tree_type::iterator_base & other)` | Copies the given iterator as stem iterator.
`public bool operator==(const `[`stem_iterator`](#class_neurite_stem__iterator)` & other) const` | Equality operator (compares two iterators)
`public bool operator!=(const `[`stem_iterator`](#class_neurite_stem__iterator)` & other) const` | Inequality operator (compares two iterators)
`public `[`stem_iterator`](#class_neurite_stem__iterator)` & operator++()` | Stem iterator single step - ascend one branch.
`public `[`stem_iterator`](#class_neurite_stem__iterator)` operator++(int)` | Stem iterator single step - ascend one branch.
`public `[`stem_iterator`](#class_neurite_stem__iterator)` & operator+=(unsigned int num)` | Stem iterator multi step - ascend num branches.

## Members


### `public  stem_iterator()` {#class_neurite_stem__iterator_1a2b4e07e724b9c3d9308137afd6c287c5}

Empty constructor.

#### Returns
Default iterator (actually, useless)

---

### `public  stem_iterator(tree_node * tn)` {#class_neurite_stem__iterator_1a2b9adcb826902fa48966014eb3362e92}

Creates an stem iterator that points to tn.

#### Parameters
* `tn` Tree node pointer





#### Returns
Stem iterator

---

### `public  stem_iterator(const typename tree_type::iterator_base & other)` {#class_neurite_stem__iterator_1acfdaac57f98bed9fcfd8c241b752325c}

Copies the given iterator as stem iterator.

#### Parameters
* `other` Iterator





#### Returns
Copied stem iterator

---

### `public bool operator==(const `[`stem_iterator`](#class_neurite_stem__iterator)` & other) const` {#class_neurite_stem__iterator_1a8011f3911250d56104c5580b4f4a5dc4}

Equality operator (compares two iterators)

#### Parameters
* `other` The other stem iterator





#### Returns
True if they both point to the same node

---

### `public bool operator!=(const `[`stem_iterator`](#class_neurite_stem__iterator)` & other) const` {#class_neurite_stem__iterator_1a6f265b692a05563766beeb08ee45aeb2}

Inequality operator (compares two iterators)

#### Parameters
* `other` The other stem iterator





#### Returns
True if they both dont point to the same node

---

### `public `[`stem_iterator`](#class_neurite_stem__iterator)` & operator++()` {#class_neurite_stem__iterator_1a74941d427d529a68b165c98a16ed6b0f}

Stem iterator single step - ascend one branch.

#### Returns
Updated iterator

---

### `public `[`stem_iterator`](#class_neurite_stem__iterator)` operator++(int)` {#class_neurite_stem__iterator_1a5462d8d28069592f768fbbf2221e5b65}

Stem iterator single step - ascend one branch.

#### Returns
new updated iterator

---

### `public `[`stem_iterator`](#class_neurite_stem__iterator)` & operator+=(unsigned int num)` {#class_neurite_stem__iterator_1ab4351d5f533d4dfad021c1f4d2ebfd21}

Stem iterator multi step - ascend num branches.

#### Returns
Updated iterator


---

# class `Contour` {#class_contour}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  Contour()` | [Contour](#class_contour) empty constructor.
`public  Contour(const std::vector< point_type > & v)` | Creates a contour from a point vector.
`public  Contour(const `[`Contour`](#class_contour)` &) = default` | Copy constructor.
`public `[`Contour`](#class_contour)` & operator=(const `[`Contour`](#class_contour)` &) = default` | Copy assign.
`public  Contour(`[`Contour`](#class_contour)` &&) = default` | Move constructor.
`public `[`Contour`](#class_contour)` & operator=(`[`Contour`](#class_contour)` &&) = default` | Move assign.
`public iterator begin()` | Returns an iterator to the first point in the contour.
`public const_iterator begin() const` | Returns an iterator to the first point in the contour.
`public iterator end()` | Returns an iterator to the next position after the last point in the contour.
`public const_iterator end() const` | Returns an iterator to the next position after the last point in the contour.
`public std::size_t size() const` | [Contour](#class_contour) size.
`public float length() const` | Computes the length of the contour.
`public float area(int component) const` | [Contour](#class_contour) planar area as 2D projection in the given component.
`public const std::string & name() const` | Returns contour name.
`public void name(const std::string & n)` | Set contour name.
`public const std::string & face_color() const` | Returns contour face color.
`public const std::string & back_color() const` | Returns contour back color.
`public void face_color(const std::string & s)` | Set contour face color.
`public void back_color(const std::string & s)` | Set contour back color.
`public float fill_density() const` | Return contour fill density (alpha channel)
`public void fill_density(float f)` | Set fill density value.
`public float resolution() const` | [Contour](#class_contour) resolution (im not sure what this actually is..like a ratio?)
`public void resolution(float f)` | Set resolution value.
`public bool is_closed() const` | True if the contour is defined as closed.
`public void properties_from_map(const `[`PropertyMap`](#class_property_map)` & p)` | Set all contour properties getting them from a p.
`public float closing_gap() const` | Distance between the last and the first point in the contour.
`public void close()` | Mark the contour as closed (add a segment bw the last and the first)
`public int planar_axis() const` | Cehcks if the contour is planar for some axis.
`public std::pair< float, float > range(int component) const` | Computes min and max values for the given component (0,1,2 x,y,z)
`public std::vector< `[`geometry::planar_point`](geometry.html#namespace_geometry_1a8fe2c5b0b8714c17379d950a39935052)` > planar_projection(int component) const` | Returns the contour points removing the ith component.
`public bool clockwise_oriented(int i) const` | Checks if the contour points are clockwise ordered (shoelace formula applied)
`public void reverse()` | Reverses the contour point order.
`public void rotate(iterator new_first)` | Rotates the contour (if it is closed) so the point pointed by new_first becomes the new first point.
`public point_type barycenter() const` | Computes contour barycenter.

## Members


### `public  Contour()` {#class_contour_1abc19b95f159c8c329bc5a2b146f58480}

[Contour](#class_contour) empty constructor.

Initializes all members to its default value and leaves the contour as empty

---

### `public  Contour(const std::vector< point_type > & v)` {#class_contour_1a4fb386c2bddeb93d477e72955af0a62a}

Creates a contour from a point vector.

#### Parameters
* `v` [Contour](#class_contour) point vector

---

### `public  Contour(const `[`Contour`](#class_contour)` &) = default` {#class_contour_1ad270c3f186e05d02317796bff4c9bf7c}

Copy constructor.



---

### `public `[`Contour`](#class_contour)` & operator=(const `[`Contour`](#class_contour)` &) = default` {#class_contour_1a190654c45e1cab3c6058a8a67ffe0d56}

Copy assign.



---

### `public  Contour(`[`Contour`](#class_contour)` &&) = default` {#class_contour_1a2067ee02499ad671aa276ccbcf31219c}

Move constructor.



---

### `public `[`Contour`](#class_contour)` & operator=(`[`Contour`](#class_contour)` &&) = default` {#class_contour_1a3f35c1843e45bb489c80a97923c4e253}

Move assign.



---

### `public iterator begin()` {#class_contour_1ae0f262ac7f97da4231745e98a12b8981}

Returns an iterator to the first point in the contour.

#### Returns
point iterator

---

### `public const_iterator begin() const` {#class_contour_1ab5a551017c8246d20138dc2a70daae90}

Returns an iterator to the first point in the contour.

#### Returns
const point iterator

---

### `public iterator end()` {#class_contour_1aaa4d717b77cce485ac1b180561ef1851}

Returns an iterator to the next position after the last point in the contour.

#### Returns
point iterator

---

### `public const_iterator end() const` {#class_contour_1a0cffcab078fa1c91371c149556d459a3}

Returns an iterator to the next position after the last point in the contour.

#### Returns
const point iterator

---

### `public std::size_t size() const` {#class_contour_1a90a56fe4ef5f8fe9a806ee58222e72cb}

[Contour](#class_contour) size.

#### Returns
number of points that describe the contour

---

### `public float length() const` {#class_contour_1a3b68508d6630157f72b353a4ce746798}

Computes the length of the contour.

#### Returns
[Contour](#class_contour) length

---

### `public float area(int component) const` {#class_contour_1ad67c7118e3940a4b82b4ebc8846d498d}

[Contour](#class_contour) planar area as 2D projection in the given component.

#### Parameters
* `component` Component that is ignored to compute the area





#### Returns
[Contour](#class_contour) planar area

---

### `public const std::string & name() const` {#class_contour_1ae824cbe1e883dd6090b0a4af396d78c7}

Returns contour name.

#### Returns
[Contour](#class_contour) name as string

---

### `public void name(const std::string & n)` {#class_contour_1acc2ea9cee81730487f5e2bb29ff53841}

Set contour name.

#### Parameters
* `n` The new contour name

---

### `public const std::string & face_color() const` {#class_contour_1a20974705fb268846bfd3eb9e04ccd631}

Returns contour face color.

#### Returns
Color as hex string #RRGGBB

---

### `public const std::string & back_color() const` {#class_contour_1a4a0c5368d5989e4263f7b4836ee70012}

Returns contour back color.

#### Returns
Color as hex string #RRGGBB

---

### `public void face_color(const std::string & s)` {#class_contour_1aec535071aa39ad88cd35820492da2b5d}

Set contour face color.

#### Parameters
* `s` Hex-string color. e.g. #FFFFFF

---

### `public void back_color(const std::string & s)` {#class_contour_1a0f7c13db18455f83aa7af43b70f11b63}

Set contour back color.

#### Parameters
* `s` Hex-string color. e.g. #FFFFFF

---

### `public float fill_density() const` {#class_contour_1a3ba38d3ee7605a5376404357140e920a}

Return contour fill density (alpha channel)

#### Returns
Alpha (opacity) value

---

### `public void fill_density(float f)` {#class_contour_1af13ec3464710db708b43ae775f2af357}

Set fill density value.

#### Parameters
* `f` [Contour](#class_contour) fill opacity. Between 0 and 1.

---

### `public float resolution() const` {#class_contour_1a0341b0d854c0131d4d5d76d9c2a65f48}

[Contour](#class_contour) resolution (im not sure what this actually is..like a ratio?)

#### Returns
Resolution as float

---

### `public void resolution(float f)` {#class_contour_1a927f4f8f530e7512a6cac05eacee99c0}

Set resolution value.

#### Parameters
* `f` resolution value. Actual meaning is unknown.

---

### `public bool is_closed() const` {#class_contour_1ac6f92da23aaac9dd3000806904899ee3}

True if the contour is defined as closed.

#### Returns
boolean flag

---

### `public void properties_from_map(const `[`PropertyMap`](#class_property_map)` & p)` {#class_contour_1a8318431aeca715e20a07d41c83804b3b}

Set all contour properties getting them from a p.

map
#### Parameters
* `p` input Property map

---

### `public float closing_gap() const` {#class_contour_1ae0ff90e6e38e8e57bac2ebd4566650e0}

Distance between the last and the first point in the contour.

#### Returns
Closing gap distance

---

### `public void close()` {#class_contour_1aa0b59e0bc426568a42fa4c22dda0cdb9}

Mark the contour as closed (add a segment bw the last and the first)



---

### `public int planar_axis() const` {#class_contour_1a674a451949d5424cf2954e5383d01467}

Cehcks if the contour is planar for some axis.

#### Returns
-1 is not planar, 0,1,2 x,y,z are constant respectively

---

### `public std::pair< float, float > range(int component) const` {#class_contour_1a84c2863d756e0239ff55d9d2c18d2baf}

Computes min and max values for the given component (0,1,2 x,y,z)

#### Parameters
* `component` [Contour](#class_contour) component index (0,1,2 <-> x,y,z)





#### Returns
Pair (min,max)

---

### `public std::vector< `[`geometry::planar_point`](geometry.html#namespace_geometry_1a8fe2c5b0b8714c17379d950a39935052)` > planar_projection(int component) const` {#class_contour_1ace74694b2171c18ad103610649de1aaf}

Returns the contour points removing the ith component.

#### Parameters
* `component` Index of component to remove





#### Returns
Planar points

---

### `public bool clockwise_oriented(int i) const` {#class_contour_1a42e11abd18c76202e262af2ee059a89c}

Checks if the contour points are clockwise ordered (shoelace formula applied)

#### Parameters
* `i` component index (0,1,2 <-> x,y,z) that is ignored to compute the orientation





#### Returns
True if clockwise ordered

---

### `public void reverse()` {#class_contour_1a06d15206046a20091f420b77d5111f05}

Reverses the contour point order.



---

### `public void rotate(iterator new_first)` {#class_contour_1a1b178dd119aedad3b6d75a4181244a43}

Rotates the contour (if it is closed) so the point pointed by new_first becomes the new first point.

#### Parameters
* `new_first` Point to become the first point

---

### `public point_type barycenter() const` {#class_contour_1a2dc5bfbcceeb2cdacd7cc15f4dd9cc30}

Computes contour barycenter.

#### Returns
Barycenter


---

# class `Neuron` {#class_neuron}

```
class Neuron
  : public neurostr::WithProperties
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  Neuron()` | Empty constructor.
`public  Neuron(const std::string & id)` | Create a neuron with given id, and no neurites nor soma.
`public  Neuron(const std::string & id,const std::vector< `[`Node`](#class_node)` > & soma)` | Creates a neuron with given id and soma nodes.
`public inline  ~Neuron()` | Default destructor.
`public  Neuron(const `[`Neuron`](#class_neuron)` &) = delete` | Deleted.
`public `[`Neuron`](#class_neuron)` & operator=(const `[`Neuron`](#class_neuron)` &) = delete` | Deleted.
`public  Neuron(`[`Neuron`](#class_neuron)` &&) = default` | Default implementation.
`public `[`Neuron`](#class_neuron)` & operator=(`[`Neuron`](#class_neuron)` &&) = default` | Default implementation.
`public inline const std::string & id() const` | Get neuron id string.
`public inline const point_type & up() const` | Get neuron Up vector.
`public void up(const point_type & up)` | Set neuron up vector.
`public inline int size() const` | Count number of neurites.
`public int node_count() const` | Number of different nodes in the neuron.
`public neurite_iterator add_neurite(`[`Neurite`](#class_neurite)` *const n)` | Add new neurite to the neuron.
`public void add_soma(const std::vector< `[`Node`](#class_node)` > & v)` | Add node set to soma.
`public inline void add_soma(const `[`Node`](#class_node)` & n)` | Add single node to soma.
`public template<typename T>`  <br/>`inline auto add_property(const std::string & key,const T & v,bool recursive)` | Adds a proprety to the neuron and, optionally, to its neurites.
`public inline auto add_property(const std::string & key,bool recursive)` | Adds an empty proprety to the neuron and, optionally, to its neurites.
`public inline neurite_iterator begin_neurite()` | Creates neurite iterator.
`public inline neurite_iterator end_neurite()` | Creates neurite iterator.
`public inline const_neurite_iterator begin_neurite() const` | Creates neurite iterator.
`public inline const_neurite_iterator end_neurite() const` | Creates neurite iterator.
`public inline soma_iterator begin_soma()` | Iterator over soma nodes.
`public inline soma_iterator end_soma()` | Iterator over soma nodes.
`public inline const_soma_iterator begin_soma() const` | Iterator over soma nodes.
`public inline const_soma_iterator end_soma() const` | Iterator over soma nodes.
`public inline auto begin_axon()` | Iterator over axon.
`public inline auto end_axon()` | Iterator over axon.
`public inline auto begin_apical()` | Iterator over apical.
`public inline auto end_apical()` | Iterator over apical.
`public inline auto begin_dendrite()` | Iterator over basal dendrites.
`public inline auto end_dendrite()` | Iterator over basal dendrites.
`public inline auto begin_axon() const` | Iterator over axon.
`public inline auto end_axon() const` | Iterator over axon.
`public inline auto begin_apical() const` | Iterator over apical.
`public inline auto end_apical() const` | Iterator over apical.
`public inline auto begin_dendrites() const` | Iterator over basal dendrites.
`public inline auto end_dendrites() const` | Iterator over basal dendrites.
`public inline int axon_count() const` | Counts number of axon neuritesin the neuron.
`public inline int apical_count() const` | Counts number of apical neurites in the neuron.
`public inline int dendrite_count() const` | Counts number of basal dendrites in the neuron.
`public inline bool has_soma() const` | Checks if the neuron soma is not empty.
`public `[`Neurite::base_node_iterator`](#class_neurite_node__iterator)` find(const `[`Node`](#class_node)` & n)` | Finds a node in the neuron.
`public inline `[`Neurite::base_node_iterator`](#class_neurite_node__iterator)` find(Node::id_type id)` | Finds a node in the neuron that matches the id.
`public soma_iterator find_soma(const `[`Node`](#class_node)` & n)` | Finds a node in the soma.
`public inline soma_iterator find_soma(Node::id_type id)` | Finds a node in the soma by id.
`public bool point_in_soma(const point_type & p) const` | Checks if the given point is within the soma.
`public void correct()` | Correct function calls the correct function over each.
`public void remove_null_segments()` | Removes zero-length segements in all neurites.
`public point_type soma_barycenter() const` | Computes soma barycenter.
`public void scale(float r)` | Scales all nodes in the neuron by r.
`public void scale(float rx,float ry,float rz)` | Scales all nodes in the neuron by (rx,ry,rz)
`public void traslate(const point_type & p)` | Moves all nodes in the neuron by p.
`public void rotate(const Eigen::Quaternionf & q)` | rotates all nodes in the neuron
`public void center()` | Traslates the neuron so the soma barycenter lies at 0,0,0.
`public neurite_iterator erase(const neurite_iterator & n)` | Removes a neurite from the neuron.
`public void erase_axon()` | Removes all axon neurites from the neuron.
`public void erase_apical()` | Removes all apical dendrties from the neuron.
`public void erase_dendrites()` | Removes all non-apical dendrties from the neuron.
`public void set_apical_up()` | Rotates the neuron so the apical towards "up" direction.
`public void set_basal_roots_xz()` | Rotates the neuron so the basal plane is close to the z=0 plane.
`public box_type boundingBox()` | Computes the axis-aligned bounding box of the neuron.
`public float somaArea() const` | Computes soma area.
`public void order()` | Order all neurites.
`public void simplify(float eps)` | Applies RDP simplification to all branches in the neruon.

## Members


### `public  Neuron()` {#class_neuron_1a4cb78f544c3edf455d8ee9bc8fa31303}

Empty constructor.

Create a neuron with no id, neurites nor soma. up vector is set to default value (0,0,1)
#### Returns
[Neuron](#class_neuron)

---

### `public  Neuron(const std::string & id)` {#class_neuron_1a06b90c889c843eea29338d07666a3d0b}

Create a neuron with given id, and no neurites nor soma.

up vector is set to default value (0,0,1)
#### Parameters
* `id` [Neuron](#class_neuron) id





#### Returns
[Neuron](#class_neuron)

---

### `public  Neuron(const std::string & id,const std::vector< `[`Node`](#class_node)` > & soma)` {#class_neuron_1aa250137a5beda068324aebd61451d946}

Creates a neuron with given id and soma nodes.

up vector is set to default value (0,0,1)
#### Parameters
* `id` [Neuron](#class_neuron) id


* `soma` Soma nodes





#### Returns
[Neuron](#class_neuron)

---

### `public inline  ~Neuron()` {#class_neuron_1a7cf9035e3ed9a3d8c15a7611edb362fe}

Default destructor.



---

### `public  Neuron(const `[`Neuron`](#class_neuron)` &) = delete` {#class_neuron_1ad5505ec842a0d5f7a2812864a50e2a1c}

**DELETED**

---

### `public `[`Neuron`](#class_neuron)` & operator=(const `[`Neuron`](#class_neuron)` &) = delete` {#class_neuron_1a3c7b0c2ac410274ae52eed0f658c9127}

**DELETED**

---

### `public  Neuron(`[`Neuron`](#class_neuron)` &&) = default` {#class_neuron_1a57145c88ee75505af19b0b8b84b7b071}

Default implementation.

---

### `public `[`Neuron`](#class_neuron)` & operator=(`[`Neuron`](#class_neuron)` &&) = default` {#class_neuron_1a4caa68aee2e9288d8b285ae90ca0ef62}

Default implementation.

---

### `public inline const std::string & id() const` {#class_neuron_1a1f62f3e27e77a8b4f154907a14ac41be}

Get neuron id string.

#### Returns
[Neuron](#class_neuron) id string

---

### `public inline const point_type & up() const` {#class_neuron_1aa3be111d2a6ccbf262421a26bb03ca07}

Get neuron Up vector.

Up vector allows us to orient angles in 3D space
#### Returns
Point

---

### `public void up(const point_type & up)` {#class_neuron_1a99f5256783a58549d6ad7d0b8a2c624d}

Set neuron up vector.

Given vector is normalized
#### Parameters
* `up` New up vector

---

### `public inline int size() const` {#class_neuron_1a6b60feef77393c8728ac7d70a56b2b23}

Count number of neurites.

#### Returns
[Neurite](#class_neurite) count

---

### `public int node_count() const` {#class_neuron_1ac5ab3227e2cbe4db96636144ad534c3a}

Number of different nodes in the neuron.

#### Returns
[Node](#class_node) count

---

### `public neurite_iterator add_neurite(`[`Neurite`](#class_neurite)` *const n)` {#class_neuron_1ac51fc36355768cc9e29bf78207b94588}

Add new neurite to the neuron.

#### Parameters
* `n` [Neurite](#class_neurite) pointer to be added





#### Returns
Insert point

---

### `public void add_soma(const std::vector< `[`Node`](#class_node)` > & v)` {#class_neuron_1a3ad6997abc8f289caf67a2cd89e93f72}

Add node set to soma.

#### Parameters
* `v` Vector of nodes to add to the soma

---

### `public inline void add_soma(const `[`Node`](#class_node)` & n)` {#class_neuron_1ab908caaa582fc44bbeef4cdb4527be71}

Add single node to soma.

#### Parameters
* `n` [Node](#class_node) to add

---

### `public template<typename T>`  <br/>`inline auto add_property(const std::string & key,const T & v,bool recursive)` {#class_neuron_1ae75abe07acf0b2156722ea6fa8ff482a}

Adds a proprety to the neuron and, optionally, to its neurites.

#### Parameters
* `key` Property key


* `v` Property value


* `recursive` If true, property is also added to neuron neurites.

---

### `public inline auto add_property(const std::string & key,bool recursive)` {#class_neuron_1a074026c442f144bb55b8f7f545a7aa9a}

Adds an empty proprety to the neuron and, optionally, to its neurites.

#### Parameters
* `key` Property key


* `recursive` If true, property is also added to neuron neurites.

---

### `public inline neurite_iterator begin_neurite()` {#class_neuron_1ac4654f2183cb7ef41286fe3b9047372d}

Creates neurite iterator.

#### Returns
Begin neurite iterator

---

### `public inline neurite_iterator end_neurite()` {#class_neuron_1aebc7afcab95c0a289853e20192bce006}

Creates neurite iterator.

#### Returns
End neurite iterator

---

### `public inline const_neurite_iterator begin_neurite() const` {#class_neuron_1a87271d00eaaead94ce70545601f92b5d}

Creates neurite iterator.

#### Returns
Begin neurite iterator

---

### `public inline const_neurite_iterator end_neurite() const` {#class_neuron_1a9d6be9d970b6c5bf6dbc1318c09eb6e9}

Creates neurite iterator.

#### Returns
End neurite iterator

---

### `public inline soma_iterator begin_soma()` {#class_neuron_1a47a8a880c43de71cc47de07ea6ed262b}

Iterator over soma nodes.

#### Returns
Begin soma iterator

---

### `public inline soma_iterator end_soma()` {#class_neuron_1a892e03fbc1415d25dd84ec8164c665f8}

Iterator over soma nodes.

#### Returns
End soma iterator

---

### `public inline const_soma_iterator begin_soma() const` {#class_neuron_1a5e96e48702c8fc28b36af23c30af9943}

Iterator over soma nodes.

#### Returns
Begin soma iterator

---

### `public inline const_soma_iterator end_soma() const` {#class_neuron_1a5a6c9237fc900e4917b39cf2f9782f32}

Iterator over soma nodes.

#### Returns
End soma iterator

---

### `public inline auto begin_axon()` {#class_neuron_1a9b2d28f4f3f95b971952882c6639de09}

Iterator over axon.

Axon is supposed to be unique...
#### Returns
Begin axon iterator

---

### `public inline auto end_axon()` {#class_neuron_1acbbbfc46ef28c2915b117e86aacf31c2}

Iterator over axon.

Axon is supposed to be unique...
#### Returns
End axon iterator

---

### `public inline auto begin_apical()` {#class_neuron_1a90cfaacf0a5fb0301ca9186efc48b651}

Iterator over apical.

Apical is supposed to be unique...
#### Returns
Begin apical iterator

---

### `public inline auto end_apical()` {#class_neuron_1a77ea3ddf3db5e5d64780c356b9b95148}

Iterator over apical.

Apical is supposed to be unique...
#### Returns
End apical iterator

---

### `public inline auto begin_dendrite()` {#class_neuron_1a2da72392655061683e1ef256f171096a}

Iterator over basal dendrites.

#### Returns
Begin basal dendrites iterator

---

### `public inline auto end_dendrite()` {#class_neuron_1a402188c0735cae7798f61f73df8e987f}

Iterator over basal dendrites.

#### Returns
End basal dendrites iterator

---

### `public inline auto begin_axon() const` {#class_neuron_1a678cceb136fb7aae07d40b5357d024cf}

Iterator over axon.

Axon is supposed to be unique...
#### Returns
Begin axon iterator

---

### `public inline auto end_axon() const` {#class_neuron_1a67beb8d944c75e3f973ea962f31d1556}

Iterator over axon.

Axon is supposed to be unique...
#### Returns
End axon iterator

---

### `public inline auto begin_apical() const` {#class_neuron_1a464ec6d22ebd9373a82e63c032ca8f96}

Iterator over apical.

Apical is supposed to be unique...
#### Returns
Begin apical iterator

---

### `public inline auto end_apical() const` {#class_neuron_1afa96757fc79f311186101b1fb0d310de}

Iterator over apical.

Apical is supposed to be unique...
#### Returns
End apical iterator

---

### `public inline auto begin_dendrites() const` {#class_neuron_1af572ad6f184db84a51884c2e614f82b4}

Iterator over basal dendrites.

#### Returns
Begin basal dendrites iterator

---

### `public inline auto end_dendrites() const` {#class_neuron_1ae11bece2309a0b88b7dc14f894717634}

Iterator over basal dendrites.

#### Returns
End basal dendrites iterator

---

### `public inline int axon_count() const` {#class_neuron_1a8eddcc8c98e97d36b9f6daeb2abdfae6}

Counts number of axon neuritesin the neuron.

#### Returns
Number of axon

---

### `public inline int apical_count() const` {#class_neuron_1a4a7454c4f18fdba44f0a87f05c5c697b}

Counts number of apical neurites in the neuron.

#### Returns
Number of apical

---

### `public inline int dendrite_count() const` {#class_neuron_1a1e6f0416cbf85e09d9aa88bc70dc927b}

Counts number of basal dendrites in the neuron.

#### Returns
Number of apical

---

### `public inline bool has_soma() const` {#class_neuron_1aa550bc6f37beede23fbab2b2ae95f02f}

Checks if the neuron soma is not empty.

#### Returns
True if soma is not empty

---

### `public `[`Neurite::base_node_iterator`](#class_neurite_node__iterator)` find(const `[`Node`](#class_node)` & n)` {#class_neuron_1a4f374cee5c129f4443ecc67d80deb377}

Finds a node in the neuron.

doesnt search in soma nodes
#### Parameters
* `n` [Node](#class_node) to be found





#### Returns
[Node](#class_node) iterator. IF node is not found returns the iterator created by the empty constructor

---

### `public inline `[`Neurite::base_node_iterator`](#class_neurite_node__iterator)` find(Node::id_type id)` {#class_neuron_1ac7c9b8c2c2e83483fd17851d40be9901}

Finds a node in the neuron that matches the id.

doesnt search in soma nodes
#### Parameters
* `id` [Node](#class_node) Id





#### Returns
[Node](#class_node) iterator. IF node is not found returns the iterator created by the empty constructor

---

### `public soma_iterator find_soma(const `[`Node`](#class_node)` & n)` {#class_neuron_1af2601f1bae87181db8871e9056e6b042}

Finds a node in the soma.

#### Parameters
* `n` [Node](#class_node) to be found





#### Returns
Iterator to the node. end_soma otherwise

---

### `public inline soma_iterator find_soma(Node::id_type id)` {#class_neuron_1a0043278c084deb7504825092a00bd363}

Finds a node in the soma by id.

#### Parameters
* `id` ID of the node to be found





#### Returns
Iterator to the node. end_soma otherwise

---

### `public bool point_in_soma(const point_type & p) const` {#class_neuron_1aef2fbe40f3187792ee29d4c93c9ed119}

Checks if the given point is within the soma.

The condition is that the given point should be closer to the soma barycenter than at least one point in the soma
#### Parameters
* `p` Point





#### Returns
True if point is considered to be in the soma

---

### `public void correct()` {#class_neuron_1aa65b61bddc548b8b529dc907eb70cb4f}

Correct function calls the correct function over each.

Additionaly checks if the neurite root is part of the soma and set is as such if necessary.

---

### `public void remove_null_segments()` {#class_neuron_1ab02f8aacd0e38b357d988d84b300ad66}

Removes zero-length segements in all neurites.



---

### `public point_type soma_barycenter() const` {#class_neuron_1a252b0c622d5f8a48d344adba3f0346bb}

Computes soma barycenter.

#### Returns
soma barycenter

---

### `public void scale(float r)` {#class_neuron_1a2424f863b6f7eb9698fea40e3d5767c8}

Scales all nodes in the neuron by r.

#### Parameters
* `r` scale rate

---

### `public void scale(float rx,float ry,float rz)` {#class_neuron_1aa38f94006d720cb82fae4aed1090e9b4}

Scales all nodes in the neuron by (rx,ry,rz)

#### Parameters
* `rx` x-axis scale


* `ry` y-axis scale


* `rz` z-axis scale

---

### `public void traslate(const point_type & p)` {#class_neuron_1add49550d961c36e2e776bfa8803e0ad3}

Moves all nodes in the neuron by p.

#### Parameters
* `p` Traslation vector

---

### `public void rotate(const Eigen::Quaternionf & q)` {#class_neuron_1a68d646856577afdcf779fad6cacbb9e0}

rotates all nodes in the neuron

#### Parameters
* `q` rotation quaternion

---

### `public void center()` {#class_neuron_1a87f065861e7277cb1e94d7c46a873697}

Traslates the neuron so the soma barycenter lies at 0,0,0.



---

### `public neurite_iterator erase(const neurite_iterator & n)` {#class_neuron_1a1591b28a927ebc1e3740f44308cac119}

Removes a neurite from the neuron.

#### Parameters
* `n` [Neurite](#class_neurite) iterator





#### Returns
updated iterator

---

### `public void erase_axon()` {#class_neuron_1a3fbb3202cfba9dd22a64e52bea7c52a0}

Removes all axon neurites from the neuron.



---

### `public void erase_apical()` {#class_neuron_1a467472950549aca38c3b9070fec5731a}

Removes all apical dendrties from the neuron.



---

### `public void erase_dendrites()` {#class_neuron_1acd2659624e87cdf7ea5e93afa71f1ad9}

Removes all non-apical dendrties from the neuron.



---

### `public void set_apical_up()` {#class_neuron_1a0a4c7344fa13ca08264f85c0a2d40bc7}

Rotates the neuron so the apical towards "up" direction.



---

### `public void set_basal_roots_xz()` {#class_neuron_1a80fbfd144fbd8091b6cdbbdb7414233d}

Rotates the neuron so the basal plane is close to the z=0 plane.



---

### `public box_type boundingBox()` {#class_neuron_1af81cb2e5ba2c474a69003033cc5ffdcf}

Computes the axis-aligned bounding box of the neuron.

#### Returns
bounding box

---

### `public float somaArea() const` {#class_neuron_1a67de045d57bfb2d5f3537f792a945ea5}

Computes soma area.

#### Returns
Soma area

---

### `public void order()` {#class_neuron_1ab4b9b2e6e2122abd367da0482c4f9283}

Order all neurites.



---

### `public void simplify(float eps)` {#class_neuron_1a1ac32b2b6fe5dc8cfb14af1ac1bc9bd7}

Applies RDP simplification to all branches in the neruon.

#### Parameters
* `eps` Tolerance


---

# class `Node` {#class_node}

```
class Node
  : public neurostr::WithProperties
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  Node()` | Empty constructor, creates a node with ID -1 at 0,0,0 with radius 0.
`public  Node(int id)` | Creates a node with ID id at 0,0,0 with radius 0.
`public  Node(int id,const point_type & p,double r)` | Creates a node with ID id at position p with radius r.
`public  Node(int id,double x,double y,double z,double r)` | Creates a node with ID id at position (x,y,z) with radius r
`public  Node(const `[`Node`](#class_node)` & n) = default` | Default.
`public  Node(`[`Node`](#class_node)` && n) = default` | Default.
`public `[`Node`](#class_node)` & operator=(const `[`Node`](#class_node)` & n) = default` | Default.
`public `[`Node`](#class_node)` & operator=(`[`Node`](#class_node)` && n) = default` | Default.
`public inline  ~Node()` | Empty destructor.
`public inline bool operator==(const `[`Node`](#class_node)` & n) const` | Compare two nodes by ID.
`public inline bool operator!=(const `[`Node`](#class_node)` & n) const` | Compare two nodes by ID.
`public inline float radius() const` | Returns node radius.
`public inline const id_type id() const` | Returns node id.
`public inline const point_type & position() const` | Return node position.
`public inline float x() const` | Returns node X coordinate.
`public inline float y() const` | Returns node Y coordinate.
`public inline float z() const` | Returns node Z coordinate.
`public inline bool valid_branch() const` | Checks wether the parent branch referece is valid.
`public `[`Branch`](#class_branch)` & branch()` | Returns parent branch.
`public const `[`Branch`](#class_branch)` & branch() const` | Returns parent branch.
`public `[`Node`](#class_node)` & position(const point_type & p)` | Changes node position for.

## Members


### `public  Node()` {#class_node_1a465465a95fd1d8e27c09cefca2f82f68}

Empty constructor, creates a node with ID -1 at 0,0,0 with radius 0.

#### Returns
[Node](#class_node)

---

### `public  Node(int id)` {#class_node_1a330ed6f136f818b7c8ee3453696f3725}

Creates a node with ID id at 0,0,0 with radius 0

#### Parameters
* `id` The Node ID

---

### `public  Node(int id,const point_type & p,double r)` {#class_node_1a17d1d33dd2efb05ddba6db7d51aaa0a7}

Creates a node with ID id at position p with radius r

#### Parameters
* `id` The Node ID
* `p` Node position (3D point)
* `r` Node radius


---

### `public  Node(int id,double x,double y,double z,double r)` {#class_node_1a226ccc6591cf05fb860540a51d3ac864}

Creates a node with ID id at position (x,y,z) with radius r

#### Parameters
* `id` The Node ID
* `x` Node x coord.
* `y` Node y coord.
* `z` Node z coord.
* `r` Node radius

---

### `public  Node(const `[`Node`](#class_node)` & n) = default` {#class_node_1af92b6c5ed90ea97735f785d99102c3e0}

Default.



---

### `public  Node(`[`Node`](#class_node)` && n) = default` {#class_node_1ad309afad87a6a4d8f971b97f21fb7b55}

Default.



---

### `public `[`Node`](#class_node)` & operator=(const `[`Node`](#class_node)` & n) = default` {#class_node_1a3944a0afe29dc4192f3b2783161ebb42}

Default.



---

### `public `[`Node`](#class_node)` & operator=(`[`Node`](#class_node)` && n) = default` {#class_node_1a89a149c9f8e1060d99067b1bbe8d3d36}

Default.



---

### `public inline  ~Node()` {#class_node_1a69b8325cb8878558506bbb97fe6627a0}

Empty destructor.

#### Returns

---

### `public inline bool operator==(const `[`Node`](#class_node)` & n) const` {#class_node_1aea92d6877c75a8c4bccaaf0318b2283e}

Compare two nodes by ID.

#### Parameters
* `n` The other node





#### Returns
True if both ids are equal

---

### `public inline bool operator!=(const `[`Node`](#class_node)` & n) const` {#class_node_1a32c7aaa50711110db04ca273020ae54c}

Compare two nodes by ID.

#### Parameters
* `n` The other node





#### Returns
True if both ids are different

---

### `public inline float radius() const` {#class_node_1a8f2c8006725301776d70e9c71d6ad471}

Returns node radius.

#### Returns
Radius

---

### `public inline const id_type id() const` {#class_node_1afaf58d5ff5aafc0db0aced5b80e107e6}

Returns node id.

#### Returns
ID

---

### `public inline const point_type & position() const` {#class_node_1a68da2f77aa8904f04e62462e6fe26fb4}

Return node position.

#### Returns
Position

---

### `public inline float x() const` {#class_node_1a6236f8be0dc65cef40dc70fee011b8f3}

Returns node X coordinate.

#### Returns
X coord

---

### `public inline float y() const` {#class_node_1ad123b2b3fb814ba99b72df0e1214850b}

Returns node Y coordinate.

#### Returns
Y coord

---

### `public inline float z() const` {#class_node_1a9e54426de216dbce57b1c39ab3f0f2dc}

Returns node Z coordinate.

#### Returns
Z coordinate

---

### `public inline bool valid_branch() const` {#class_node_1aca9a62ca42e21d4fc116d28a17053ee3}

Checks whether the parent branch reference is valid.

#### Returns
True if the reference is valid

---

### `public `[`Branch`](#class_branch)` & branch()` {#class_node_1ae7da2f57d6be848affef69a8d5e60292}

Returns parent branch.

#### Throws
* `runtime_exception` If we attempt to access null branch





#### Returns
Parent branch reference

---

### `public const `[`Branch`](#class_branch)` & branch() const` {#class_node_1a1b2c193a1f148d00dcfa701316f5001c}

Returns parent branch.

#### Parameters
* `runtime_exception` If attempt to access null branch





#### Returns
Parent branch const reference

---

### `public `[`Node`](#class_node)` & position(const point_type & p)` {#class_node_1a3bc4ae95a8e8c1f7888b0500e4006767}

Changes node position for.

#### Parameters
*


---

# class `PropertyMap` {#class_property_map}






## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  PropertyMap()` | Initializes an empty property map.
`public template<typename Iter>`  <br/>`inline  PropertyMap(const Iter & begin,const Iter & end)` | Initializes a property map with the content in the range.
`public const_iterator find(const std::string & k) const` | Returns the property with key k.
`public  PropertyMap(const `[`PropertyMap`](#class_property_map)` &) = default` | Default.
`public `[`PropertyMap`](#class_property_map)` & operator=(const `[`PropertyMap`](#class_property_map)` &) = default` | Default.
`public  PropertyMap(`[`PropertyMap`](#class_property_map)` &&) = default` | Default.
`public `[`PropertyMap`](#class_property_map)` & operator=(`[`PropertyMap`](#class_property_map)` &&) = default` | Default.
`public template<typename T>`  <br/>`inline T get(const std::string & k) const` | Returns the value of the poperty with key k.
`public std::pair< iterator, bool > set(const property_type & p)` | Adds a new property to the map.
`public std::pair< iterator, bool > set(const std::string & k)` | Adds an empty property to the map.
`public std::pair< iterator, bool > set(const std::string & k,int v)` | Adds a new int valued property to the map.
`public std::pair< iterator, bool > set(const std::string & k,bool v)` | Adds a new bool valued property to the map.
`public std::pair< iterator, bool > set(const std::string & k,float v)` | Adds a new float valued property to the map.
`public std::pair< iterator, bool > set(const std::string & k,const std::string v)` | Adds a new string valued property to the map.
`public std::pair< iterator, bool > set(const std::string & k,const point_type v)` | Adds a new point valued property to the map.
`public std::pair< iterator, bool > set(const std::string & k,boost::any v)` | Adds a property to the map.
`public bool exists(const std::string & k) const` | Property exists.
`public void remove(const std::string & k)` | Deletes a property.
`public void remove(const iterator & i)` | Deletes a property.
`public map_type::size_type size() const` | Property map size.
`public const_iterator begin() const` | Property begin iterator.
`public iterator begin()` | Property begin iterator.
`public const_iterator end() const` | Property end iterator.
`public iterator end()` | Property end iterator.

## Members


### `public  PropertyMap()` {#class_property_map_1ad9767f940dc5b0a71650943a4e3b9e2d}

Initializes an empty property map.



---

### `public template<typename Iter>`  <br/>`inline  PropertyMap(const Iter & begin,const Iter & end)` {#class_property_map_1a9fa080171fd784ea443ba7e19e7de017}

Initializes a property map with the content in the range.

#### Parameters
* `begin` property begin iterator


* `end` property end iterator

---

### `public const_iterator find(const std::string & k) const` {#class_property_map_1a6a3df4bbe5d587549751a23bcc2e0e6e}

Returns the property with key k.

#### Parameters
* `k` Property key





#### Returns
Const iterator. End() if no property with key k exists

---

### `public  PropertyMap(const `[`PropertyMap`](#class_property_map)` &) = default` {#class_property_map_1a01bf1c75a052ea47c59bec6113d3c885}

Default.



---

### `public `[`PropertyMap`](#class_property_map)` & operator=(const `[`PropertyMap`](#class_property_map)` &) = default` {#class_property_map_1a6c0d2becb5fd99e39f71875653e31491}

Default.



---

### `public  PropertyMap(`[`PropertyMap`](#class_property_map)` &&) = default` {#class_property_map_1a917410a81744d4b59a11d75084f0ea52}

Default.



---

### `public `[`PropertyMap`](#class_property_map)` & operator=(`[`PropertyMap`](#class_property_map)` &&) = default` {#class_property_map_1a46614ab41b6d2a53bab275fb1873e64d}

Default.



---

### `public template<typename T>`  <br/>`inline T get(const std::string & k) const` {#class_property_map_1a12db4ea1e97b61a38d0d8495a242c93a}

Returns the value of the poperty with key k.

#### Parameters
* `k` Key





#### Returns
Property value

---

### `public std::pair< iterator, bool > set(const property_type & p)` {#class_property_map_1ade5b967866609097b5f13eafff1d57c2}

Adds a new property to the map.

#### Parameters
* `p` Property to add





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k)` {#class_property_map_1a8952608446ee2e4efd4621cefe0d3175}

Adds an empty property to the map.

#### Parameters
* `k` Property key





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,int v)` {#class_property_map_1aa6032c9580537937340ead90e84f10af}

Adds a new int valued property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,bool v)` {#class_property_map_1a5d6b6da98358fc9bb5bb320e72073340}

Adds a new bool valued property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,float v)` {#class_property_map_1a34f2993bc75b0b3ec6929703473233e6}

Adds a new float valued property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,const std::string v)` {#class_property_map_1af4dc03dddea1f5b736a692a343c62592}

Adds a new string valued property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,const point_type v)` {#class_property_map_1ab41659abd27463c54c9354944a7fef65}

Adds a new point valued property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public std::pair< iterator, bool > set(const std::string & k,boost::any v)` {#class_property_map_1ad7b6298a0a65cb58ddab8e8d597f5634}

Adds a property to the map.

#### Parameters
* `k` Property key


* `v` Property value





#### Returns
pair(iterator, T/F property added)

---

### `public bool exists(const std::string & k) const` {#class_property_map_1a8bdf31839a617eb97e34b4ea2d1cf88c}

Property exists.

#### Parameters
* `k` Property name





#### Returns
True if the property exists

---

### `public void remove(const std::string & k)` {#class_property_map_1a18a5de6825153f495b45f8425abc0aa0}

Deletes a property.

#### Parameters
* `k` Poperty key

---

### `public void remove(const iterator & i)` {#class_property_map_1a495cf2173c7256702be59cfe3061613d}

Deletes a property.

#### Parameters
* `i` property iterator

---

### `public map_type::size_type size() const` {#class_property_map_1a4790c802c1382c599162386a904f5333}

Property map size.

#### Returns
Number of properties in the map

---

### `public const_iterator begin() const` {#class_property_map_1a826c73d2f9e3add3e4cc417600f25beb}

Property begin iterator.

#### Returns
const iterator

---

### `public iterator begin()` {#class_property_map_1a23e37b429c21fa9fb49385c481bce001}

Property begin iterator.

#### Returns
iterator

---

### `public const_iterator end() const` {#class_property_map_1ac6e66207650ff30a515f01f1f30130df}

Property end iterator.

#### Returns
const iterator

---

### `public iterator end()` {#class_property_map_1a286cb5e85e0eb38e1f8f2d96d4cf665d}

Property end iterator.

#### Returns
iterator


---

# class `Reconstruction` {#class_reconstruction}

```
class Reconstruction
  : public neurostr::WithProperties
```  





## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  Reconstruction()` | Creates a reconsturction with no id, neurons nor contour.
`public  Reconstruction(const std::string & id)` | Creates an empty reconstruction with given id.
`public inline  ~Reconstruction()` | Default.
`public  Reconstruction(const `[`Reconstruction`](#class_reconstruction)` &) = delete` | Not allowed.
`public `[`Reconstruction`](#class_reconstruction)` & operator=(const `[`Reconstruction`](#class_reconstruction)` &) = delete` | Not allowed.
`public  Reconstruction(`[`Reconstruction`](#class_reconstruction)` &&) = default` | Default.
`public `[`Reconstruction`](#class_reconstruction)` & operator=(`[`Reconstruction`](#class_reconstruction)` &&) = default` | Default.
`public inline void addNeuron(`[`Neuron`](#class_neuron)` *const n)` | Adds a neuron to the reconstruction.
`public void addContour(const `[`contour_type`](#class_contour)` & v)` | Sets a vector of points as reconstruction contour.
`public inline std::vector< `[`contour_type`](#class_contour)` >::const_iterator contour_begin() const` | Get reconstruction contour as polygon.
`public inline std::vector< `[`contour_type`](#class_contour)` >::const_iterator contour_end() const` |
`public inline const std::string & id() const` | Get reconstruction ID.
`public inline std::size_t n_contours() const` | Checks whether the contour is empty.
`public inline int size() const` | Counts number of neurons in the reconstruction.
`public int node_count() const` | Counts number of different nodes in the reconstruction.
`public neuron_iterator closest_soma(const point_type & p)` | Finds the neuron whose soma is the closest one to a given point.
`public neuron_iterator add_neurite_to_closest_soma(`[`Neurite`](#class_neurite)` * n)` | Adds a neurite to the neuron whose soma is the closest one to the neurite root.
`public inline neuron_iterator begin()` | [Neuron](#class_neuron) iterator.
`public inline neuron_iterator end()` | [Neuron](#class_neuron) iterator.
`public inline const_neuron_iterator begin() const` | [Neuron](#class_neuron) iterator.
`public inline const_neuron_iterator end() const` | [Neuron](#class_neuron) iterator.

## Members


### `public  Reconstruction()` {#class_reconstruction_1af5862853032770793fcbba2c5d9bb8db}

Creates a reconsturction with no id, neurons nor contour.



---

### `public  Reconstruction(const std::string & id)` {#class_reconstruction_1ae025a7fd0b8bf672adb69859ba822770}

Creates an empty reconstruction with given id.

#### Parameters
* `id` [Reconstruction](#class_reconstruction) ID

---

### `public inline  ~Reconstruction()` {#class_reconstruction_1a2e8bd9cf1a1330131d2336573c798278}

Default.



---

### `public  Reconstruction(const `[`Reconstruction`](#class_reconstruction)` &) = delete` {#class_reconstruction_1aa179fbea5f67df3807a1bdb00e4c6b4c}

Not allowed.

**DELETED**

---

### `public `[`Reconstruction`](#class_reconstruction)` & operator=(const `[`Reconstruction`](#class_reconstruction)` &) = delete` {#class_reconstruction_1acd214bb9c9a7a9c335c4306605a6c72d}

Not allowed.

**DELETED**

---

### `public  Reconstruction(`[`Reconstruction`](#class_reconstruction)` &&) = default` {#class_reconstruction_1a5fca77aeaa07c103c3379a7bd3ca76ab}

Default.



---

### `public `[`Reconstruction`](#class_reconstruction)` & operator=(`[`Reconstruction`](#class_reconstruction)` &&) = default` {#class_reconstruction_1a2ad388a736f184cb8ee78fb80725f1ed}

Default.



---

### `public inline void addNeuron(`[`Neuron`](#class_neuron)` *const n)` {#class_reconstruction_1a88f7aef15fb664ff1afc999613fd0024}

Adds a neuron to the reconstruction.

#### Parameters
* `n` [Neuron](#class_neuron) pointer

---

### `public void addContour(const `[`contour_type`](#class_contour)` & v)` {#class_reconstruction_1a15a6c62c1bf6794fa36547a708cb186f}

Sets a vector of points as reconstruction contour.

#### Parameters
* `v` Point vector

---

### `public inline std::vector< `[`contour_type`](#class_contour)` >::const_iterator contour_begin() const` {#class_reconstruction_1aec969bb73083317d55f5ba38c92dde91}

Get reconstruction contour as polygon.

#### Returns
[Reconstruction](#class_reconstruction) contour

---

### `public inline std::vector< `[`contour_type`](#class_contour)` >::const_iterator contour_end() const` {#class_reconstruction_1a61dbbb9cc98e33dc8228c0fb564b3c1d}





---

### `public inline const std::string & id() const` {#class_reconstruction_1ad8f01d826047b2d3e4e1fd37dd24ce3e}

Get reconstruction ID.

#### Returns
ID

---

### `public inline std::size_t n_contours() const` {#class_reconstruction_1a6e24c463b54fcfcf2bfd3fd22d210eae}

Checks whether the contour is empty.

#### Returns
True if contour is not empty

---

### `public inline int size() const` {#class_reconstruction_1acc41df688957e610ccfc98fe2b92e4af}

Counts number of neurons in the reconstruction.

#### Returns
[Neuron](#class_neuron) count

---

### `public int node_count() const` {#class_reconstruction_1abf9caf634f30b804a8c7d13ecd733a8a}

Counts number of different nodes in the reconstruction.

#### Returns
[Node](#class_node) count

---

### `public neuron_iterator closest_soma(const point_type & p)` {#class_reconstruction_1ac5fd6ed3fa56a399a8a8c342ac2a55fa}

Finds the neuron whose soma is the closest one to a given point.

#### Parameters
* `p` Point





#### Returns
[Neuron](#class_neuron) iterator

---

### `public neuron_iterator add_neurite_to_closest_soma(`[`Neurite`](#class_neurite)` * n)` {#class_reconstruction_1ab2ee6017bd833f30b0b7520377508ca9}

Adds a neurite to the neuron whose soma is the closest one to the neurite root.

#### Parameters
* `n` [Neurite](#class_neurite) pointer





#### Returns
[Neuron](#class_neuron) iterator (insertion point)

---

### `public inline neuron_iterator begin()` {#class_reconstruction_1a43faf0e08d4c2a27d2fb91555372b4fd}

[Neuron](#class_neuron) iterator.

#### Returns
begin neuron interator

---

### `public inline neuron_iterator end()` {#class_reconstruction_1af53522823c64659a3eb4070e3585ab44}

[Neuron](#class_neuron) iterator.

#### Returns
end neuron interator

---

### `public inline const_neuron_iterator begin() const` {#class_reconstruction_1ac7a8f1eb48d09f3b7ec629ab988f5a96}

[Neuron](#class_neuron) iterator.

#### Returns
begin neuron interator

---

### `public inline const_neuron_iterator end() const` {#class_reconstruction_1ae731f46b922911e920d3c68fb271d8c9}

[Neuron](#class_neuron) iterator.

#### Returns
end neuron interator


---

# class `WithProperties` {#class_with_properties}


## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`PropertyMap`](#class_property_map)` properties` |
`public  WithProperties()` | create an empty property map
`public  WithProperties(const `[`WithProperties`](#class_with_properties)` & other) = default` | Default.
`public `[`WithProperties`](#class_with_properties)` & operator=(const `[`WithProperties`](#class_with_properties)` & b) = default` | Default.
`public  WithProperties(`[`WithProperties`](#class_with_properties)` && b) = default` | Default.
`public `[`WithProperties`](#class_with_properties)` & operator=(`[`WithProperties`](#class_with_properties)` && b) = default` | Default.
`public inline auto begin_properties() const` | Proprerty begin iterator.
`public inline auto end_properties() const` | Property end iterator.
`public template<typename T>`  <br/>`inline auto add_property(const std::string & key,const T & v)` | Adds a property.
`public std::pair< PropertyMap::iterator, bool > add_property(const std::string & key)` | Adds an empty property.
`public std::pair< PropertyMap::iterator, bool > add_property(const std::pair< std::string, boost::any > & v)` | Adds a property.
`public PropertyMap::const_iterator get_property(const std::string & key) const` | Get property.

## Members


### `public `[`PropertyMap`](#class_property_map)` properties` {#class_with_properties_1acaefcaaa5a5621434cc6d9838f2c8304}





---

### `public  WithProperties()` {#class_with_properties_1a5974021dd4df42b6fb591b2103b35ace}

create an empty property map



---

### `public  WithProperties(const `[`WithProperties`](#class_with_properties)` & other) = default` {#class_with_properties_1a06a596c731cb5bf78c44e71dc591ef1f}

Default.



---

### `public `[`WithProperties`](#class_with_properties)` & operator=(const `[`WithProperties`](#class_with_properties)` & b) = default` {#class_with_properties_1ae999b598459bcf715798bb35af3e5911}

Default.



---

### `public  WithProperties(`[`WithProperties`](#class_with_properties)` && b) = default` {#class_with_properties_1a779f75b4306be463ce8f9ada017711eb}

Default.



---

### `public `[`WithProperties`](#class_with_properties)` & operator=(`[`WithProperties`](#class_with_properties)` && b) = default` {#class_with_properties_1ac5067f16b110988c13f6f05103935d65}

Default.



---

### `public inline auto begin_properties() const` {#class_with_properties_1a471b2630dfebc67c2c8603661ebf7b28}

Proprerty begin iterator.

#### Returns
property iterator

---

### `public inline auto end_properties() const` {#class_with_properties_1a9641bc080ab1ab1de3e82fbaa1629a2f}

Property end iterator.

#### Returns
property iterator

---

### `public template<typename T>`  <br/>`inline auto add_property(const std::string & key,const T & v)` {#class_with_properties_1a6477eebefb65182bc6dafb1cf54b46c7}

Adds a property.

#### Parameters
* `key` Property key


* `v` Property value





#### Returns
property iterator

---

### `public std::pair< PropertyMap::iterator, bool > add_property(const std::string & key)` {#class_with_properties_1ada99fd4b17acd29c9b3b63c299e5dfbb}

Adds an empty property.

#### Parameters
* `key` Property key





#### Returns
property iterator

---

### `public std::pair< PropertyMap::iterator, bool > add_property(const std::pair< std::string, boost::any > & v)` {#class_with_properties_1ab5843547922860167cf9633ff7eda694}

Adds a property.

#### Parameters
* `v` Propery





#### Returns
property iterator

---

### `public PropertyMap::const_iterator get_property(const std::string & key) const` {#class_with_properties_1a4d5800d7d6108d6fdc383da4b4df5f4c}

Get property.

#### Parameters
* `key` Property key





#### Returns
property iterator
