---
currentSection: class
currentSubsection:
currentItem:
---
# namespace `neurostr`

Neurostr namespace contains all other namespaces in the library as well as the data model classes.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[``log``](classes/log.html#namespace_log)    | Log namespace contains logger functions.
`namespace `[``io``](classes/io.html#namespace_io)    | IO namespace contains write/read functionality for most common file formats.
`namespace `[``traits``](classes/traits.html#namespace_traits)    | Core template traits
`namespace `[``geometry``](classes/geometry.html#namespace_geometry)    | Geometry namespace hides geometry specific implementation details from the rest of the library.
`class `[``Branch``](classes/core.html#class_branch)    | Representation of a single branch in a reconstruction. Conceptually is an ordered sequence of nodes.
`class `[``Neurite``](classes/core.html#class_neurite)    | Represents a single neurite (dendrite, apical dend. or axon)
`class `[``Contour``](classes/core.html#class_contour)    | 3D contour in the reconstruction. It is an ordered sequence of 3D points (not nodes). Contours are usually closed but it is not  mandatory.
`class `[``Neuron``](classes/core.html#class_neuron)    | Represents a single neuron, its soma and neurites
`class `[``Node``](classes/core.html#class_node)    | Node concept class. stores a numeric ID, x,y,z coordinates and radius. Also stores references to its branch and parent node if they exist and implements basic operations.
`class `[``PropertyMap``](classes/core.html#class_property_map)    | Auxiliar class. Stores key-value properties
`class `[``Reconstruction``](classes/core.html#class_reconstruction)    | Stores several neuron as well as common contours
`class `[``WithProperties``](classes/core.html#class_with_properties)    | Base class for neuron , neurite ... that have a property map

---

# namespace [`geometry`](classes/geometry.html) {#namespace_geometry}

Geometry namespace hides geometry specific implementation details from the rest of the library.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``DiscreteFrechet``](classes/geometry.html#class_geometry__discrete_frechet)        | |
`class `[``RDPSimplifier``](classes/geometry.html#class_geometry__r_d_p_simplifier)        | |
`class `[``TriangleMesh``](classes/geometry.html#class_geometry__triangle_mesh)        | |
`public template<int I>`  <br/>`inline float get(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets the ith component from a point.
`public template<int I>`  <br/>`inline float get(const `[`planar_point`](classes/geometry.html#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & p)` | Gets the ith component from a 2D point.
`public inline float getx(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets point x coordinate.
`public inline float gety(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | gets pòint y coordinate
`public inline float getz(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Gets point z coordinate.
`public inline float get(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int coord)` | Gets the ith component from a point.
`public template<int I>`  <br/>[`planar_point`](classes/geometry.html#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Removes the ith component from P.
`public `[`planar_point`](classes/geometry.html#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` planar_projection(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,int i)` | Dynamic planar projection.
`public float distance(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Euclidean distance between a and b.
`public `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` vectorFromTo(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & from,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & to)` | Vector with origin in from and end in to.
`public void traslate(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v)` | Adds v to p.
`public void scale(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ref)` | Modifies the point p scaling it by scale wrt ref so its norm is multiplied by scale.
`public void scale(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float rx,float ry,float rz)` | Modifies the point p scaling it by (rx,ry,rz)
`public void scale(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,float scale)` | Modifies p multiplying its norm by scale.
`public `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` cross_product(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q)` | Computes the 3D cross product p ^ q.
`public float norm(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Returns de 2-norm of p as vector.
`public inline bool equal(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Checks whether two point a and b are equal.
`public inline bool equal(const `[`planar_point`](classes/geometry.html#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & a,const `[`planar_point`](classes/geometry.html#class_geometry_1a0be2bd3dfe9e29d27900d58c051ec20a)` & b)` | Checks whether two point a and b are equal.
`public std::array< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > get_basis(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & vx,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & up)` | Retunrs a orthonormal right-oriented basis where vx is the first vector.
`public float segment_segment_distance(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q0,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & q1)` | Computes the distance between two line-segments p and q.
`public Eigen::Quaternionf align_vectors(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & v,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & u,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` | Returns the quaternion to transform v into u (both unitary)
`public bool segment_box_intersection(const `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,const `[`segment_type`](classes/geometry.html#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & inter)` | Computes the box-segment intersection of b and s.
`public template<typename G1,typename G2>`  <br/>`inline bool covered_by(const G1 & g1,const G2 & g2)` | Checks if first geometry is covered by the second.
`public template<int I,typename Point>`  <br/>`inline bool segment_cross_plane(const `[`segment_type`](classes/geometry.html#class_geometry_1a1155e1ecb90affb2cdd8464f4692d342)` & s,const Point & v,Point & inter)` | Segment-axis plane intersection.
`public template<int I,typename Point>`  <br/>`inline void min_component(const Point & p,Point & res)` | Set the ith component in res to the minimim betweeen the ith components in p and res.
`public template<int I,typename Point>`  <br/>`inline void max_component(const Point & p,Point & res)` | Set the ith component in res to the maximum betweeen the ith components in p and res.
`public template<typename Point>`  <br/>`inline void max_by_component(const Point & p,Point & res)` | Computes the component-wise maximum between p and res and stores it in res.
`public template<typename Point>`  <br/>`inline void min_by_component(const Point & p,Point & res)` | Computes the component-wise minimum between p and res and stores it in res.
`public template<`[`Axis`](classes/geometry.html#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`float axisLength(const `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Return box axis length.
`public template<`[`Axis`](classes/geometry.html#class_geometry_1a19daa71ce572e7c06c78b8872dbac4b9)` axis>`  <br/>`void setAxis(`[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b,float v)` | Set box axis to given value.
`public `[`polygon_type`](classes/geometry.html#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` as_planar_polygon(const std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` |
`public template<typename G>`  <br/>`inline std::size_t num_points(const G & geom)` | Number of points in the geometry.
`public float polygon_area(const `[`polygon_type`](classes/geometry.html#class_geometry_1acc0ab5374c64759f77fcf4e7291b25fb)` & p)` | Computes the pclosed polygon area.
`public template<typename Iter>`  <br/>`inline float polygon_area(const Iter & begin,const Iter & end)` | Computes the closed polygon area.
`public void negate(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Multiplies every component by -1.
`public `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` barycenter(const std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Computes the barycenter of a pointset.
`public void normalize(`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Modifies p so its norm is equal to 1.
`public float vector_vector_angle(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b)` | Computes the planar vector-vector shortest angle.
`public bool box_box_intersection(const `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & a,const `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Checks if box a intersects with box b (axis aligned)
`public std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > box_corners(const `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` & b)` | Returns 8 corner points in a axis-aligned box.
`public float lineseg_dist(const std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & u,const std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Euclidean distance between two line-segments.
`public `[`box_type`](classes/geometry.html#class_geometry_1a67f4955807b967aad3b839d637ee7657)` bounding_box(const std::vector< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` > & v)` | Computes the bounding box of a node set.
`public float vector_vector_directed_angle(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & a,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & b,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` up)` | Computes the planar angle from a to b.
`public std::pair< float, float > local_orientation(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p,const std::array< `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)`, 3 > & basis)` | Computes the local orientation (Azimuth and elevation) of p wrt basis.
`public bool in_triangle_border(const `[`triangle_type`](classes/geometry.html#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if p is in the border of the triangle t.
`public bool is_triangle_vertex(const `[`triangle_type`](classes/geometry.html#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if P is one of the vertices of T.
`public bool within_triangle(const `[`triangle_type`](classes/geometry.html#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p)` | Verifies if p is inside the triangle t.
`public bool triangle_ray_intersection(const `[`triangle_type`](classes/geometry.html#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_o,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & ray_v,`[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & intersection)` | Computes Triangle-ray intersection with the moller-trumbore algorithm.
`public float tetrahedron_volume(const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p0,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p1,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p2,const `[`point_type`](classes/geometry.html#class_geometry_1ae5d33f53c10261df2871104fa1c76c8e)` & p3)` | Returns the volume of the tetrahedron.
`public float triangle_area(const `[`triangle_type`](classes/geometry.html#class_geometry_1a8af5bb35f5a90c3474257df24c3e8b74)` & t)` | Compute the triangle area.

# namespace [`traits`](classes/traits.html) {#namespace_traits}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`Trait `[``function_traits``](classes/traits.html#struct_traits_function__traits)    | Extract basic information from a fuctor like out type, arg type, arity...
`Trait `[``is_vector``](classes/traits.html#struct_traits_is__vector)    | Base false trait is vector.
`Trait `[``is_base_of_template``](#struct_traits_is_base_of_template)    | Is base of template base trait.

---


# namespace [`log`](classes/log.html) {#namespace_log}

Log namespace contains logger functions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``_logger_storage``](classes/log.html#class_log___logger__storage)        | |
`public `[`_logger_storage`](classes/log.html#class_log___logger__storage)` _nstr_logger_` | |
`public void init_log_file(const std::string & path)` | Inits file logger.
`public void init_log_cout()` | Initializes the logger using the standard output stream.
`public void init_log_cerr()` | Initializes the logger using the standard error stream.
`public void disable_log()` | Disables the log.
`public void enable_log()` | Enables the log.
`public void set_format(const std::string & s)` | Changes current log format.
`public void set_level(`[`severity_level`](classes/log.html#class_log_1a10acfc5ebf7a1e159905211f5b89d5df)` l)` | Changes current logger severity threshold.

---

# namespace [`io`](classes/io.html) {#namespace_io}

IO namespace contains write/read functionality for most common file formats.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``ASCParser``](classes/io.html#class_io__a_s_c_parser)    | |
`class `[``DATParser``](classes/io.html#class_io__d_a_t_parser)    | |
`class `[``JSONParser``](classes/io.html#class_io__j_s_o_n_parser)    | |
`class `[``JSONWriter``](classes/io.html#class_io__j_s_o_n_writer)    | |
`class `[``Parser``](classes/io.html#class_io__parser)    | |
`class `[``SWCParser``](classes/io.html#class_io__s_w_c_parser)    | |
`class `[``SWCWriter``](classes/io.html#class_io__s_w_c_writer)    | |
`struct `[``contour_info``](classes/io.html#struct_io_contour__info)    | [Contour](classes/core.html#class__contour) header in DAT files.
`struct `[``marker_type``](classes/io.html#struct_io_marker__type)    | Markerset structure for NL files.
`struct `[``subtree_info``](classes/io.html#struct_io_subtree__info)    | SubTree header in DAT files.
`struct `[``tree_info``](classes/io.html#struct_io_tree__info)    | Tree header in DAT files.


---
# namespace [`selector`](classes/selector.html#namespace_selector) {#namespace_selector}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[``selector_func_traits``](classes/selectors.html#struct_selector__func__traits)        | Selector function traits.
`struct `[``type_chooser``](classes/selectors.html#struct_type__chooser)        | Trait that extracts the selector i/o type.
`struct `[``type_chooser< true, T >``](classes/selectors.html#struct_type__chooser_3_01true_00_01_t_01_4)        | |
`public template<typename F1,typename F2,typename... Funcs,std::enable_if_t< sizeof...(Funcs)==0 > *>`  <br/>`inline constexpr auto compose_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector composition.
`public template<typename F,std::enable_if_t< `[`selector_func_traits`](classes/selectors.html#struct_selector__func__traits)`< F >::out_set > *>`  <br/>`inline constexpr auto selector_out_single_to_set(const F & f)` | Converts a selector with single output in one with set output Case: Output is already set.
`public template<typename F,std::enable_if_t< `[`selector_func_traits`](classes/selectors.html#struct_selector__func__traits)`< F >::in_set > *>`  <br/>`inline constexpr auto selector_in_single_to_set(const F & f)` | Converts a selector with single output in one with set output Case: Output is already set.
`public template<typename F1,typename F2,std::enable_if_t< `[`selector_func_traits`](classes/selectors.html#struct_selector__func__traits)`< F1 >::in_set > *,std::enable_if_t< `[`selector_func_traits`](classes/selectors.html#struct_selector__func__traits)`< F2 >::out_set > *>`  <br/>`inline constexpr auto selector_foreach(const F1 & f1,const F2 & f2)` | Creates a new selector that applies the selector f2 to each selected element of f1.
`public template<typename F1,typename F2,typename... Funcs,std::enable_if_t< sizeof...(Funcs)==0 > *>`  <br/>`inline constexpr auto union_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector union.
`public template<typename F1,typename F2,typename... Funcs,std::enable_if_t< sizeof...(Funcs)==0 > *>`  <br/>`inline constexpr auto intersection_selector(const F1 & f1,const F2 & f2,Funcs... fns)` | Recursive template for selector intersection.
`public template<typename F1,typename F2,std::enable_if_t<!`[`selector_func_traits`](classes/selectors.html#struct_selector__func__traits)`< F1 >::in_set > *>`  <br/>`inline constexpr auto diff_selector_factory(const F1 & f_1,const F2 & f_2)` | Assymetric difference.


# namespace [`measure`](classes/measure.html#namespace_measure) {#namespace_measure}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[``aggregate``](classes/measure.html#namespace_aggregate)    | Namespace that contains aggregate-related functions and traits
`template <typename Fn> auto measureEach(const Fn& f)` | Converts a single-input measure into a set measure that applies the original measure to each element of the input set
`template <typename Fn, typename Aggr> auto measureEachAggregate(const Fn& f, const Aggr& aggr)` | Converts a single-input measure into a set measure that applies the original measure to each element of the input set and then aggregates the  output.
`template <typename S, typename M> auto selectorMeasureCompose(const S& selector, const M& measure)` | Creates a new measure as result of the composition of the selector and the measure (M o S). Types and arity must match
`template <typename... Measures> auto createMeasureTuple(const Measures&... measures )` | Creates a measure that applies several measures to the same input and returns their result in a tuple
`template <typename F> struct measure_func_traits` |Measure function traits. Extracts input type, input arity and output type.


# namespace [`validator`](classes/validator.html#namespace_validator) {#namespace_validator}

Validator namespace contains the validator template class and the predefined validators and check functions.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[``Validator``](classes/validator.html#class_validator)    | |
`class `[``ValidatorItem``](classes/validator.html#class_validator_item)    | |
`class `[``check_func_traits``](classes/validator.html#struct_check__func__traits)        | |
`public const auto is_true` | Dummy. Checks that a given boolean is true
`public const auto is_false` | Dummy. Checks that a given boolean is false
`public const auto empty_string` | Dummy. Checks that a given string is empty
`public template<typename T>`  <br/>`inline auto range_check_factory(T min,T max)` | Range check factory. Checks that a given value is in the range [min, max)
`public const auto neurites_attached_to_soma` | Neurite validator. Checks that neurites are attached to the soma
`public const auto neuron_has_soma` | Neuron validator. Checks that neuron soma is defined
`public const auto no_trifurcations_validator` | Node validator. Checks that the number of descendants of a node is at most 2.
`public const auto zero_length_segments_validator` | Node validator. Checks that the length of the compartment associated to each node is not zero.
`public const auto radius_length_segments_validator` | Node validator. Check that the distance between two consecutive nodes is greater than the sum of their radii.
`public const auto increasing_radius_validator` | Node validator. Checks that the node radius is not increasing.
`public const auto segment_collision_validator` | Node validator. Check that the node compartment don't collide with any other compartment in the reconstruction
`public const auto extreme_angles_validator` | Node validator. Check that the elongation/bifurcation angle are not too high to be plausible
`public inline auto planar_reconstruction_validator_factory(float min)` | Neurite validator. Verifies that neurite reconstruction is not planar by checking that its non-axis aligned box volume is over the minimum value (close to 0)
`public inline auto dendrite_count_validator_factory(unsigned int min,unsigned int max)` | Neuron validator. Checks that the number of dendrites in the neuron is in the range [min,max)
`public inline auto apical_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of apical dendrites in the neuron is not greater than 2
`public inline auto axon_count_validator_factory(bool strict)` | Neuron validator. Checks that the number of axons in the neuron is not greater than 2
`public inline auto linear_branches_validator_factory(float min)` | Branch validator. Verifies that the branch reconstruction is not a prefect straight line by checking that its tortuosity value is not equal to 1
`public inline auto branch_collision_validator_factory(bool ignore_diams)` | Branch validator. Check that the Branch dont collide with any other branch in the neuron
