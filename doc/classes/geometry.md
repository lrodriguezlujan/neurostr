---
currentSection: class
currentSubsection: geometry
currentItem:
---
# namespace `geometry` {#namespace_geometry}

Geometry namespace hides geometry specific implementation details from the rest of the library.


## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``DiscreteFrechet``](#class_geometry__discrete_frechet)        |
`class `[``RDPSimplifier``](#class_geometry__r_d_p_simplifier)        |
`class `[``TriangleMesh``](#class_geometry__triangle_mesh)        |
`public template<int I>`  <br/>`inline float get(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets the ith component from a point.
`public template<int I>`  <br/>`inline float get(const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & p)` | Gets the ith component from a 2D point.
`public inline float getx(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets point x coordinate.
`public inline float gety(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | gets pòint y coordinate
`public inline float getz(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets point z coordinate.
`public inline float get(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int coord)` | Gets the ith component from a point.
`public template<int I>`  <br/>[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Removes the ith component from P.
`public `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int i)` | Dynamic planar projection.
`public float distance(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Euclidean distance between a and b.
`public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` vectorFromTo(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & from,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & to)` | Vector with origin in from and end in to.
`public void traslate(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v)` | Adds v to p.
`public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ref)` | Modifies the point p scaling it by scale wrt ref so its norm is multiplied by scale.
`public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float rx,float ry,float rz)` | Modifies the point p scaling it by (rx,ry,rz)
`public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale)` | Modifies p multiplying its norm by scale.
`public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` cross_product(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q)` | Computes the 3D cross product p ^ q.
`public float norm(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Returns de 2-norm of p as vector.
`public inline bool equal(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Checks whether two point a and b are equal.
`public inline bool equal(const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & a,const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & b)` | Checks whether two point a and b are equal.
`public std::array< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > get_basis(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & vx,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & up)` | Retunrs a orthonormal right-oriented basis where vx is the first vector.
`public float segment_segment_distance(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q1)` | Computes the distance between two line-segments p and q.
`public Eigen::Quaternionf align_vectors(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & u,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` | Returns the quaternion to transform v into u (both unitary)
`public bool segment_box_intersection(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,const `[`segment_type`](#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & inter)` | Computes the box-segment intersection of b and s.
`public template<typename G1,typename G2>`  <br/>`inline bool covered_by(const G1 & g1,const G2 & g2)` | Checks if first geometry is covered by the second.
`public template<int I,typename Point>`  <br/>`inline bool segment_cross_plane(const `[`segment_type`](#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,const Point & v,Point & inter)` | Segment-axis plane intersection.
`public template<int I,typename Point>`  <br/>`inline void min_component(const Point & p,Point & res)` | Set the ith component in res to the minimim betweeen the ith components in p and res.
`public template<int I,typename Point>`  <br/>`inline void max_component(const Point & p,Point & res)` | Set the ith component in res to the maximum betweeen the ith components in p and res.
`public template<typename Point>`  <br/>`inline void max_by_component(const Point & p,Point & res)` | Computes the component-wise maximum between p and res and stores it in res.
`public template<typename Point>`  <br/>`inline void min_by_component(const Point & p,Point & res)` | Computes the component-wise minimum between p and res and stores it in res.
`public template<`[`Axis`](#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`float axisLength(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Return box axis length.
`public template<`[`Axis`](#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`void setAxis(`[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,float v)` | Set box axis to given value.
`public `[`polygon_type`](#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` as_planar_polygon(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` |
`public template<typename G>`  <br/>`inline std::size_t num_points(const G & geom)` | Number of points in the geometry.
`public float polygon_area(const `[`polygon_type`](#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` & p)` | Computes the pclosed polygon area.
`public template<typename Iter>`  <br/>`inline float polygon_area(const Iter & begin,const Iter & end)` | Computes the closed polygon area.
`public void negate(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Multiplies every component by -1.
`public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` barycenter(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Computes the barycenter of a pointset.
`public void normalize(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Modifies p so its norm is equal to 1.
`public float vector_vector_angle(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Computes the planar vector-vector shortest angle.
`public bool box_box_intersection(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & a,const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Checks if box a intersects with box b (axis aligned)
`public std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > box_corners(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Returns 8 corner points in a axis-aligned box.
`public float lineseg_dist(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & u,const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Euclidean distance between two line-segments.
`public `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` bounding_box(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Computes the bounding box of a node set.
`public float vector_vector_directed_angle(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` | Computes the planar angle from a to b.
`public std::pair< float, float > local_orientation(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const std::array< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > & basis)` | Computes the local orientation (Azimuth and elevation) of p wrt basis.
`public bool in_triangle_border(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if p is in the border of the triangle t.
`public bool is_triangle_vertex(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if P is one of the vertices of T.
`public bool within_triangle(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if p is inside the triangle t.
`public bool triangle_ray_intersection(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_o,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_v,`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & intersection)` | Computes Triangle-ray intersection with the moller-trumbore algorithm.
`public float tetrahedron_volume(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p2,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p3)` | Returns the volume of the tetrahedron.
`public float triangle_area(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t)` | Compute the triangle area.

## Members


### `public template<int I>`  <br/>`inline float get(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a5c9dd191b8139a29ce36d56164661cd2}

Gets the ith component from a point.

#### Parameters
* `p` Point

#### Returns
Ith component (float)

---

### `public template<int I>`  <br/>`inline float get(const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & p)` {#class_geometry_1a000b76bdf48b2b60337c68cdb004f724}

Gets the ith component from a 2D point.

#### Parameters
* `p` 2D Point





#### Returns
I-th component (float)

---

### `public inline float getx(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a3edf50991dd6e40d5a71c96adc381d54}

Gets point x coordinate.

#### Parameters
* `p`





#### Returns

---

### `public inline float gety(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1add3f1347fce6f4160581d2ff977209f9}

gets pòint y coordinate

#### Parameters
* `p`





#### Returns

---

### `public inline float getz(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a38d7aebfd527fd2ad5eaa50635353901}

Gets point z coordinate.

#### Parameters
* `p`





#### Returns

---

### `public inline float get(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int coord)` {#class_geometry_1a5953a1ba26ac8c38205bfd7f7c2f327e}

Gets the ith component from a point.

#### Parameters
* `p` Point


* `coord` coordinate





#### Returns
Ith component (float)

---

### `public template<int I>`  <br/>[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1aa46043e30d626a7b62911b3cf07ee3cb}

Removes the ith component from P.

#### Parameters
* `p` Point to project





#### Returns
projected point

---

### `public `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int i)` {#class_geometry_1a4106fe68a377bf3601c3d7ef9a3fc9ce}

Dynamic planar projection.

#### Parameters
* `p` Point to project





#### Returns
projected point

---

### `public float distance(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` {#class_geometry_1a425f07466c99261739829ce216660984}

Euclidean distance between a and b.

#### Parameters
* `a` First point


* `b` Second point





#### Returns
Eculidean distance (Float)

---

### `public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` vectorFromTo(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & from,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & to)` {#class_geometry_1a758a7f209d7d71571aaca90afecca528}

Vector with origin in from and end in to.

#### Parameters
* `from` Vector origin


* `to` Vector end





#### Returns
Vector (point type)

---

### `public void traslate(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v)` {#class_geometry_1acfc56fc2debf57c21b655206b63ae820}

Adds v to p.

#### Parameters
* `p` point to be modified


* `v` traslation vector

---

### `public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ref)` {#class_geometry_1a0c1f837fc4512ecba0019b9cc3bdbd53}

Modifies the point p scaling it by scale wrt ref so its norm is multiplied by scale.

#### Parameters
* `p` Point to be modified


* `scale` Scale


* `ref` Referecne point

---

### `public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float rx,float ry,float rz)` {#class_geometry_1a9ea6a3c252e07bd7a4816b9ba410884c}

Modifies the point p scaling it by (rx,ry,rz)

#### Parameters
* `p` Point to be modified


* `rx` X scale


* `ry` Y Scale


* `rz` Z scale

---

### `public void scale(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale)` {#class_geometry_1ad54b17f6012e19b1d5cff90435822a90}

Modifies p multiplying its norm by scale.

#### Parameters
* `p` Point to be modified


* `scale` Scale factor

---

### `public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` cross_product(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q)` {#class_geometry_1a7c4804c8f5ffeb40b2a7bb5cd4f2e2d5}

Computes the 3D cross product p ^ q.

#### Parameters
* `p` First 3D vector


* `q` Second 3D Vector





#### Returns
Cross product p^q

---

### `public float norm(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a763424be476267a7b481b7923bea152b}

Returns de 2-norm of p as vector.

#### Parameters
* `p` 3D Vector





#### Returns
P 2-Norm

---

### `public inline bool equal(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` {#class_geometry_1a0c3175466cc0855117f68d2fb031c1b9}

Checks whether two point a and b are equal.

#### Parameters
* `a` First point


* `b` Second point





#### Returns
True if every component in a is equal to b

---

### `public inline bool equal(const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & a,const `[`planar_point`](#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & b)` {#class_geometry_1a71f47a7b8f3958eeda4f875735afe686}

Checks whether two point a and b are equal.

#### Parameters
* `a` First point


* `b` Second point





#### Returns
True if every component in a is equal to b

---

### `public std::array< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > get_basis(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & vx,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & up)` {#class_geometry_1aef7646de6023672dd1297e4037bb4041}

Retunrs a orthonormal right-oriented basis where vx is the first vector.

#### Parameters
* `vx` First vector in the basis


* `up` Up reference position (to be z)

---

### `public float segment_segment_distance(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q1)` {#class_geometry_1add05db8394b6c1f50cee76454e5a7081}

Computes the distance between two line-segments p and q.

#### Parameters
* `p0` P start point


* `p1` P end point


* `q0` Q start point


* `q1` Q end point





#### Returns
Distance between p and q

---

### `public Eigen::Quaternionf align_vectors(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & u,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` {#class_geometry_1ac668e00659be395573d83d77a3c6be80}

Returns the quaternion to transform v into u (both unitary)

#### Parameters
* `v` Unitary vector


* `u` Unitary vector


* `up` Reference vector to determine sign in 3D angles





#### Returns
Quaternion

---

### `public bool segment_box_intersection(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,const `[`segment_type`](#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & inter)` {#class_geometry_1a6a174cbb708d30e36efde47ed335bc5e}

Computes the box-segment intersection of b and s.

#### Parameters
* `b` Box


* `s` Segment


* `inter` (Return) Intersection point





#### Returns
True if b intersects with s

---

### `public template<typename G1,typename G2>`  <br/>`inline bool covered_by(const G1 & g1,const G2 & g2)` {#class_geometry_1a856c7aefc6cf96b8d9bf32780a52c312}

Checks if first geometry is covered by the second.

#### Parameters
* `g1` First geometry


* `g2` Second geometry





#### Returns
True if g1 is covered by g2

---

### `public template<int I,typename Point>`  <br/>`inline bool segment_cross_plane(const `[`segment_type`](#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,const Point & v,Point & inter)` {#class_geometry_1ad4c775966434b0ab02419c8c79428102}

Segment-axis plane intersection.

#### Parameters
* `s` Segment


* `v` Point that marks the Ith plane position


* `inter` Intersection point





#### Returns
True if they intersect

---

### `public template<int I,typename Point>`  <br/>`inline void min_component(const Point & p,Point & res)` {#class_geometry_1a539630ef30926e9db9c11b643ad5e4e8}

Set the ith component in res to the minimim betweeen the ith components in p and res.

#### Parameters
* `p` Base point. unmodified


* `res` Point to be modified

---

### `public template<int I,typename Point>`  <br/>`inline void max_component(const Point & p,Point & res)` {#class_geometry_1a0d88840770c3a1d4c29c5c369928f36d}

Set the ith component in res to the maximum betweeen the ith components in p and res.

#### Parameters
* `p` Base point. unmodified


* `res` Point to be modified

---

### `public template<typename Point>`  <br/>`inline void max_by_component(const Point & p,Point & res)` {#class_geometry_1a810d8b548213869ad4cde3394e537d19}

Computes the component-wise maximum between p and res and stores it in res.

#### Parameters
* `p` Base point


* `res` Return point

---

### `public template<typename Point>`  <br/>`inline void min_by_component(const Point & p,Point & res)` {#class_geometry_1afd47ecb0bcbfa1ef6814a01cf90adacf}

Computes the component-wise minimum between p and res and stores it in res.

#### Parameters
* `p` Base point


* `res` Return point

---

### `public template<`[`Axis`](#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`float axisLength(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` {#class_geometry_1a055aad21d75f9c388ad7ab0fbb3135b5}

Return box axis length.

#### Parameters
* `box`





#### Returns
Axis length (value)

---

### `public template<`[`Axis`](#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`void setAxis(`[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,float v)` {#class_geometry_1a8030806c1704b568e0d2d2b456d3eb4c}

Set box axis to given value.

#### Parameters
* `b` Box


* `v` Value

---

### `public `[`polygon_type`](#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` as_planar_polygon(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` {#class_geometry_1a49117c56f2b2ad0db93f64b0d37186bf}





---

### `public template<typename G>`  <br/>`inline std::size_t num_points(const G & geom)` {#class_geometry_1adb2025754d346acc91a87794ef33a7b6}

Number of points in the geometry.

#### Parameters
* `geom` Geoemtry object





#### Returns
Number of point

---

### `public float polygon_area(const `[`polygon_type`](#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` & p)` {#class_geometry_1a15469947e00ae6e594c59b790fae229c}

Computes the pclosed polygon area.

#### Parameters
* `p` Polygon object





#### Returns
Area

---

### `public template<typename Iter>`  <br/>`inline float polygon_area(const Iter & begin,const Iter & end)` {#class_geometry_1a3f0feb2d89c9919db89e3c1a90817cfa}

Computes the closed polygon area.

#### Parameters
* `begin`


* `end`





#### Returns
Area

---

### `public void negate(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1ad7068ed3422fe5f7055e167ec3a83ac8}

Multiplies every component by -1.

#### Parameters
* `p` Point to negate

---

### `public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` barycenter(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` {#class_geometry_1aa2773e6094e625fd13bccf34068d6025}

Computes the barycenter of a pointset.

#### Parameters
* `v` Vector of points





#### Returns
Barycenter

---

### `public void normalize(`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1ac4fb11cf9cd69ec69ce30d7c09698685}

Modifies p so its norm is equal to 1.

#### Parameters
* `p` Point to normalize

---

### `public float vector_vector_angle(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` {#class_geometry_1a6fd68bd6b871bd0844495b55a1b04c3b}

Computes the planar vector-vector shortest angle.

#### Parameters
* `a` First vector


* `b` Second vector





#### Returns
Angle between a and b [0,pi]

---

### `public bool box_box_intersection(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & a,const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` {#class_geometry_1a9fa16a1974220e5952a2a6110e532bce}

Checks if box a intersects with box b (axis aligned)

#### Parameters
* `a`


* `b`





#### Returns
True if they intersect

---

### `public std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > box_corners(const `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` {#class_geometry_1a6e54ab08140b5c0a6fb192efd02f6a00}

Returns 8 corner points in a axis-aligned box.

#### Parameters
* `a`





#### Returns
Corner points

---

### `public float lineseg_dist(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & u,const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` {#class_geometry_1a250678f8728d101c8e8a93d54985fa78}

Euclidean distance between two line-segments.

#### Parameters
* `u`


* `v`





#### Returns
euclidean distance

---

### `public `[`box_type`](#class_geometry_1a67f4955807b967aad3b839d637ee7657)` bounding_box(const std::vector< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` {#class_geometry_1a7eb12026135a4b6e7ad8334d2cad94f6}

Computes the bounding box of a node set.

#### Parameters
* `v` node set





#### Returns
box

---

### `public float vector_vector_directed_angle(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` {#class_geometry_1af1063d7641369b4475a6407dc834c5c7}

Computes the planar angle from a to b.

#### Parameters
* `a` First vector


* `b` Second vector


* `up` Reference vector to determine sign in 3D angles





#### Returns
Angle from a to b [0,wpi)

---

### `public std::pair< float, float > local_orientation(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const std::array< `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > & basis)` {#class_geometry_1a08a3df2d6f0d1b201bf7c9c4a65b79b6}

Computes the local orientation (Azimuth and elevation) of p wrt basis.

#### Parameters
* `p` Point


* `basis` local basis





#### Returns
pair (azimuth, elevation)

---

### `public bool in_triangle_border(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a06d3ecbced989835f8033c2932c1ac2a}

Verifies if p is in the border of the triangle t.

#### Parameters
* `t` Triangle


* `p` Point





#### Returns
True if p lies in the border of t

---

### `public bool is_triangle_vertex(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1ab51f7b1fdadc94a491d6975168dca49b}

Verifies if P is one of the vertices of T.

#### Parameters
* `t` Triangle


* `p` Point





#### Returns
True if p is a vertex of t

---

### `public bool within_triangle(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry_1a2275f60e542ee0f195cc245c0b6da7ef}

Verifies if p is inside the triangle t.

#### Parameters
* `t` Triangle


* `p` Point





#### Returns
True if p is inside t

---

### `public bool triangle_ray_intersection(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_o,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_v,`[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & intersection)` {#class_geometry_1afe2e75728ed9c4249ad12c46f0dc9735}

Computes Triangle-ray intersection with the moller-trumbore algorithm.

#### Parameters
* `t` Triangle


* `ray_o` Ray origin


* `ray_v` Ray direction


* `intersection` Output: intersection point





#### Returns
True if the ray intersects the triangle

---

### `public float tetrahedron_volume(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p2,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p3)` {#class_geometry_1a1095d93da892dfbe8affd95c89a99c81}

Returns the volume of the tetrahedron.

#### Parameters
* `p0` vertex


* `p1` vertex


* `p2` vertex


* `p3` vertex





#### Returns
Tetrahedron voulme

---

### `public float triangle_area(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t)` {#class_geometry_1ad0fe13d86c4971b48ae637402cfe78b1}

Compute the triangle area.

#### Returns
Triangle area

---

---

# class `DiscreteFrechet` {#class_geometry__discrete_frechet}


## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  DiscreteFrechet(IterA ini_a,IterA end_a,IterB ini_b,IterB end_b)` | Base constructor.
`public inline double value()` | Computes de discrete frechet distance recursively.

## Members


### `public inline  DiscreteFrechet(IterA ini_a,IterA end_a,IterB ini_b,IterB end_b)` {#class_geometry__discrete_frechet_1a8717c0d6b6c96be62ea368798548f7f8}

Base constructor.

Initializes the class with the tow line-segment
#### Parameters
* `ini_a` First branch line-segment begin iterator


* `end_a` First branch line-segment end iterator


* `ini_b` Second branch line-segment begin iterator


* `end_b` Secondbranch line-segment end iterator





#### Returns
[DiscreteFrechet](#class_geometry__discrete_frechet) class

---

### `public inline double value()` {#class_geometry__discrete_frechet_1af18f8cd3a240be7f4432068e1b29a0cb}

Computes de discrete frechet distance recursively.

#### Returns
Discrete frechet distance


---

# class `RDPSimplifier` {#class_geometry__r_d_p_simplifier}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  RDPSimplifier(float eps,std::vector< Node > & v)` | Base constructor, sets toleracne and the line-segment.
`public inline void simplify()` | Applies the simplification to the line-segment.

## Members

### `public inline  RDPSimplifier(float eps,std::vector< Node > & v)` {#class_geometry__r_d_p_simplifier_1ad6e66bac56315350bbc973682f3746d4}

Base constructor, sets toleracne and the line-segment.

#### Parameters
* `eps` Tolerance


* `v` Node set (vector)

---

### `public inline void simplify()` {#class_geometry__r_d_p_simplifier_1a13251746e72851e5047bbeae0ba506e9}

Applies the simplification to the line-segment.




---

# class `TriangleMesh` {#class_geometry__triangle_mesh}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  TriangleMesh()` | Creates an empty (no vertex no faces) mesh.
`public  TriangleMesh(const `[`face_storage`](#class_geometry__triangle_mesh_1a7e90f358c0167e1f17463c7ee3e3291a)` & faces)` | Creates a mesh with given faces.
`public  ~TriangleMesh()` | Default destructor.
`public  TriangleMesh(const `[`TriangleMesh`](#class_geometry__triangle_mesh)` &) = delete` |
`public `[`TriangleMesh`](#class_geometry__triangle_mesh)` & operator=(const `[`TriangleMesh`](#class_geometry__triangle_mesh)` &) = delete` |
`public  TriangleMesh(`[`TriangleMesh`](#class_geometry__triangle_mesh)` &&) = default` |
`public `[`TriangleMesh`](#class_geometry__triangle_mesh)` & operator=(`[`TriangleMesh`](#class_geometry__triangle_mesh)` &&) = default` |
`public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` add(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Adds a vertex to the mesh (if it doesnt exist already)
`public template<typename Iter>`  <br/>`inline void add(const Iter & b,const Iter & e)` | Copies a range of vertices to the mesh.
`public void remove(const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & it)` | Removes the vertex and all its faces from the mesh.
`public void remove(const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & b,const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & e)` | Removes a range of vertices and their faces from the mesh.
`public void clear()` | Removes all vertices and faces.
`public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` begin_vertex()` | Creates an iterator to the first vertex in the mesh.
`public `[`const_vertex_iterator`](#class_geometry__triangle_mesh_1aae2cbf2520f3c3a99730e550bb93e285)` begin_vertex() const` | Creates an iterator to the first vertex in the mesh.
`public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` end_vertex()` | Creates an iterator to one-past position of the last vertex in the mesh.
`public `[`const_vertex_iterator`](#class_geometry__triangle_mesh_1aae2cbf2520f3c3a99730e550bb93e285)` end_vertex() const` | Creates an iterator to one-past position of the last vertex in the mesh.
`public std::size_t vertex_count() const` | Number of vertices in the mesh.
`public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` add(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v2)` | Adds a new triangular face to the mesh.
`public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` add(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t)` | Adds a new triangular face to the mesh.
`public void remove(const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & it)` | Removes a face from the mesh.
`public void remove(const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & b,const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & e)` | Removes a set of faces from the mesh.
`public void clear_faces()` | Removes all faces (but not the vertices)
`public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` begin_face()` | Returns an iterator to the first face in the mesh.
`public `[`const_face_iterator`](#class_geometry__triangle_mesh_1a37ecd5335b26115f2f73810616ddd08a)` begin_face() const` | Returns an iterator to the first face in the mesh.
`public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` end_face()` | Returns an iterator to one-past the last face in the mesh.
`public `[`const_face_iterator`](#class_geometry__triangle_mesh_1a37ecd5335b26115f2f73810616ddd08a)` end_face() const` | Returns an iterator to one-past the last face in the mesh.
`public std::size_t face_count() const` | Number of faces in the mesh.
`public bool point_inside(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_direction) const` | Using ray-tracing method computes if the point p is Inside the triangular mesh assuming that it is closed.
`public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` ray_intersection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_direction) const` |

## Members

### `public  TriangleMesh()` {#class_geometry__triangle_mesh_1a8aa5a4c1b0309e19e9e92517c14c960c}

Creates an empty (no vertex no faces) mesh.



---

### `public  TriangleMesh(const `[`face_storage`](#class_geometry__triangle_mesh_1a7e90f358c0167e1f17463c7ee3e3291a)` & faces)` {#class_geometry__triangle_mesh_1a14fb195a7ffa66ba305943b369eacbd6}

Creates a mesh with given faces.

Vertices are added automatically

---

### `public  ~TriangleMesh()` {#class_geometry__triangle_mesh_1a6dad4bf2288f7365cb2d4475eeac58c6}

Default destructor.

Nothign special to do

---

### `public  TriangleMesh(const `[`TriangleMesh`](#class_geometry__triangle_mesh)` &) = delete` {#class_geometry__triangle_mesh_1a83d41af7f2ee3279425f242d8601e10c}





---

### `public `[`TriangleMesh`](#class_geometry__triangle_mesh)` & operator=(const `[`TriangleMesh`](#class_geometry__triangle_mesh)` &) = delete` {#class_geometry__triangle_mesh_1aa89f8859f770385605668fef7095b14f}





---

### `public  TriangleMesh(`[`TriangleMesh`](#class_geometry__triangle_mesh)` &&) = default` {#class_geometry__triangle_mesh_1ae52c6947674d6f3df370e571a291d194}





---

### `public `[`TriangleMesh`](#class_geometry__triangle_mesh)` & operator=(`[`TriangleMesh`](#class_geometry__triangle_mesh)` &&) = default` {#class_geometry__triangle_mesh_1ac32047a0380e2dd3dffcdb02cad59378}





---

### `public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` add(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` {#class_geometry__triangle_mesh_1abc058abeae38218015fc3c312c677bce}

Adds a vertex to the mesh (if it doesnt exist already)

#### Parameters
* `p` Vertex to add.

---

### `public template<typename Iter>`  <br/>`inline void add(const Iter & b,const Iter & e)` {#class_geometry__triangle_mesh_1acef238219d90f04901547e29ce260f48}

Copies a range of vertices to the mesh.

#### Parameters
* `b` Range begin iterator


* `e` Range end iterator

---

### `public void remove(const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & it)` {#class_geometry__triangle_mesh_1a9b9bc41134f7849ea02b8c9e074fc7de}

Removes the vertex and all its faces from the mesh.

#### Parameters
* `it` Vertex iterator

---

### `public void remove(const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & b,const `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` & e)` {#class_geometry__triangle_mesh_1a931c4a01a5dc9e69118dc8fbcce1d8be}

Removes a range of vertices and their faces from the mesh.

#### Parameters
* `b` Range begin


* `e` Range end

---

### `public void clear()` {#class_geometry__triangle_mesh_1abda4696d6b0054a7cccb20a1016b504f}

Removes all vertices and faces.



---

### `public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` begin_vertex()` {#class_geometry__triangle_mesh_1a85cdc2ccd504fa1b30d4f44320521c68}

Creates an iterator to the first vertex in the mesh.

#### Returns
Begin iterator

---

### `public `[`const_vertex_iterator`](#class_geometry__triangle_mesh_1aae2cbf2520f3c3a99730e550bb93e285)` begin_vertex() const` {#class_geometry__triangle_mesh_1a1b4910f1830a4bbf2b52b541578bacfe}

Creates an iterator to the first vertex in the mesh.

#### Returns
Begin iterator

---

### `public `[`vertex_iterator`](#class_geometry__triangle_mesh_1aeb55dfc74ba99d733cc50c18db03cb1c)` end_vertex()` {#class_geometry__triangle_mesh_1a0fec27ba2d8b20c9b7d0b9ee91d301a8}

Creates an iterator to one-past position of the last vertex in the mesh.

#### Returns
End iterator

---

### `public `[`const_vertex_iterator`](#class_geometry__triangle_mesh_1aae2cbf2520f3c3a99730e550bb93e285)` end_vertex() const` {#class_geometry__triangle_mesh_1afeb89f464e92e27b809e80a7fdfa8392}

Creates an iterator to one-past position of the last vertex in the mesh.

#### Returns
End iterator

---

### `public std::size_t vertex_count() const` {#class_geometry__triangle_mesh_1a0a56d84d88c038db4bce31751074e34a}

Number of vertices in the mesh.



---

### `public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` add(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v0,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v1,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v2)` {#class_geometry__triangle_mesh_1a1859b1ef3d0163851b4590cffa4f398b}

Adds a new triangular face to the mesh.

Inserts the vertices if necessary
#### Parameters
* `v0` First vertex


* `v1` Second vertex


* `v2` Third vertex





#### Returns
Iterator to the inserted face

---

### `public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` add(const `[`triangle_type`](#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t)` {#class_geometry__triangle_mesh_1adec299b7a8cb182114305e15417e6104}

Adds a new triangular face to the mesh.

Inserts the vertices if necessary
#### Parameters
* `t` face triangle





#### Returns
Iterator to the inserted face

---

### `public void remove(const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & it)` {#class_geometry__triangle_mesh_1a258853e64662d75fe1822c3901520e0e}

Removes a face from the mesh.

#### Parameters
* `it` Face iterator

---

### `public void remove(const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & b,const `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` & e)` {#class_geometry__triangle_mesh_1ad1f4e15a135aa4d2f54acc075148d6f5}

Removes a set of faces from the mesh.

#### Parameters
* `b` Begin iterator


* `e` End iterator

---

### `public void clear_faces()` {#class_geometry__triangle_mesh_1a214a55072e5395ce4d7061eafb9f2f2e}

Removes all faces (but not the vertices)



---

### `public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` begin_face()` {#class_geometry__triangle_mesh_1a0e0fe5e7abe494b0499fa43e51f1273c}

Returns an iterator to the first face in the mesh.

#### Returns
Begin iterator

---

### `public `[`const_face_iterator`](#class_geometry__triangle_mesh_1a37ecd5335b26115f2f73810616ddd08a)` begin_face() const` {#class_geometry__triangle_mesh_1a80888c4042622b02fd302baa4c5a4f5e}

Returns an iterator to the first face in the mesh.

#### Returns
Begin iterator

---

### `public `[`face_iterator`](#class_geometry__triangle_mesh_1a6a46624a4c4e8f4fb2ef0f7281cebf34)` end_face()` {#class_geometry__triangle_mesh_1aa734b2afefcf5dbbf6bfebff21ee1556}

Returns an iterator to one-past the last face in the mesh.

#### Returns
End iterator

---

### `public `[`const_face_iterator`](#class_geometry__triangle_mesh_1a37ecd5335b26115f2f73810616ddd08a)` end_face() const` {#class_geometry__triangle_mesh_1a3e8214fb83067990b3a588398bb08d95}

Returns an iterator to one-past the last face in the mesh.

#### Returns
End iterator

---

### `public std::size_t face_count() const` {#class_geometry__triangle_mesh_1a41aef587c0242cb42a647ac4d5b7d177}

Number of faces in the mesh.



---

### `public bool point_inside(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_direction) const` {#class_geometry__triangle_mesh_1a573ec14f9b4602e0d975a6380bc52cfc}

Using ray-tracing method computes if the point p is Inside the triangular mesh assuming that it is closed.

#### Parameters
* `p` Point





#### Returns
True if the point is within the mesh

---

### `public `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` ray_intersection(const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_direction) const` {#class_geometry__triangle_mesh_1a0bbd6a2f50150d2ef4e12c6f41666fa6}



#### Parameters
* `p`


* `ray_direction`


#### Returns
