#ifndef NEUROSTR_CORE_GEOMETRY_H_
#define NEUROSTR_CORE_GEOMETRY_H_

#include <math.h>
#include <array>
#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace neurostr
{
  
/**
* @brief Geometry namespace hides geometry specific implementation details
* from the rest of the library.
* 
*/
namespace geometry
{
  
  namespace bg =        boost::geometry;
  
  // 3D Types
  
  /**
  * @brief 3D point definition
  **/
  using point_type =    bg::model::point<float, 3, bg::cs::cartesian>;
  
  
  using box_type =      bg::model::box<point_type>;
  using segment_type =  bg::model::segment<point_type>;
  using triangle_type = std::array< point_type,3>;
  
  // 2D Types
  
  /**
  * @brief 2D point definition
  **/
  using planar_point = bg::model::point<float, 2, bg::cs::cartesian>;
  using polygon_type =  bg::model::polygon<planar_point>;
  using ring_type    = bg::model::ring<planar_point>;
  
  
  /**
  * Axis enum
  */
  enum class Axis: int {
      X_POS = 0,
      X_NEG,
      Y_POS,
      Y_NEG,
      Z_POS,
      Z_NEG
  };  
  
  /**
   * @brief Gets the ith component from a point
   * @param p Point
   * @return Ith component (float)
   */
  template <int I>
  inline float get(const point_type& p){
    return bg::get<I>(p);
  }
  
  /**
   * @brief Gets the ith component from a 2D point
   * @param p 2D Point
   * @return I-th component (float)
   */
  template <int I>
  inline float get(const planar_point& p){
    return bg::get<I>(p);
  }
  
  /**
   * @brief Gets point x coordinate
   * @param p
   * @return 
   */
  inline float getx(const point_type& p){
    return get<0>(p);
  }
  
  /**
   * @brief gets pòint y coordinate
   * @param p
   * @return 
   */
  inline float gety(const point_type& p){
    return get<1>(p);
  }
  
  /**
   * @brief Gets point z coordinate
   * @param p
   * @return 
   */
  inline float getz(const point_type& p){
    return get<2>(p);
  }

  /**
   * @brief Gets the ith component from a point
   * @param p Point
   * @param coord coordinate
   * @return Ith component (float)
   */  
  inline float get(const point_type& p, int coord){
    switch(coord){
      case 0: return getx(p);
      case 1: return gety(p);
      case 2: return getz(p);
      default: return NAN;
    }
  }
  
  /**
   * @brief Removes the ith component from P
   * @param p Point to project
   * @return projected point
   */
  template <int I>
  planar_point planar_projection(const point_type& p);
  
  /**
   * @brief Dynamic planar projection
   * @param p Point to project
   * @return projected point
   */
   planar_point planar_projection(const point_type& p, int i);
  
  /**
   * @brief Euclidean distance between a and b
   * @param a First point
   * @param b Second point
   * @return  Eculidean distance (Float)
   */
  float distance(const point_type& a, const point_type& b);
  
  /**
   * @brief Vector with origin in from and end in to
   * @param from Vector origin
   * @param to Vector end
   * @return Vector (point type)
   */
  point_type vectorFromTo(const point_type& from, const point_type& to);
  
  /**
   * @brief Adds v to p
   * @param p point to be modified
   * @param v traslation vector
   */
  void traslate(point_type& p, const point_type& v );
  
  /**
   * @brief Modifies the point p scaling it by scale wrt ref so its norm 
   * is multiplied by scale
   * @param p Point to be modified
   * @param scale Scale
   * @param ref Referecne point
   */
  void scale(point_type& p, float scale, const point_type&  ref);
  
  /**
   * @brief  Modifies the point p scaling it by (rx,ry,rz)
   * @param p Point to be modified
   * @param rx X scale
   * @param ry Y Scale
   * @param rz Z scale
   */
  void scale(point_type& p, float rx, float ry, float rz);
  
  /**
   * @brief Modifies p multiplying its norm by scale
   * @param p Point to be modified
   * @param scale Scale factor
   */
  void scale(point_type& p, float scale);
  
  /**
   * @brief Computes the 3D cross product p ^ q
   * 
   * @param p First 3D vector
   * @param q Second 3D Vector
   * @return Cross product p^q
   */
  point_type cross_product(const point_type& p, const point_type& q);

  /**
   * @brief Returns de 2-norm of p as vector
   * @param p 3D Vector
   * @return P 2-Norm
   */
  float norm(const point_type& p);
  
  /**
   * @brief Checks whether two point a and b are equal
   * @param a First point
   * @param b Second point
   * @return  True if every component in a is equal to b
   */
  inline bool equal(const point_type& a, const point_type& b){
    return ( bg::get<0>(a) == bg::get<0>(b)) &&
           ( bg::get<1>(a) == bg::get<1>(b)) &&
           ( bg::get<2>(a) == bg::get<2>(b));
  }
  
  /**
   * @brief Checks whether two point a and b are equal
   * @param a First point
   * @param b Second point
   * @return  True if every component in a is equal to b
   */
  inline bool equal(const planar_point& a, const planar_point& b){
    return ( bg::get<0>(a) == bg::get<0>(b)) &&
           ( bg::get<1>(a) == bg::get<1>(b));
  }

  /**
   * @brief Retunrs a orthonormal right-oriented basis where vx is 
   * the first vector
   * @param vx First vector in the basis
   * @param up Up reference position (to be z)
   */
  std::array<point_type, 3> get_basis(const point_type& vx, 
                                      const point_type& up);
  
  /**
   * @brief Computes the distance between two line-segments p and q
   * @param p0 P start point
   * @param p1 P end point
   * @param q0 Q start point
   * @param q1 Q end point
   * @return Distance between p and q
   */
  float segment_segment_distance(const point_type& p0, const point_type& p1, 
                                 const point_type& q0, const point_type& q1);

  /**
   * @brief Returns the quaternion to transform v into u (both unitary)
   * @param v Unitary vector
   * @param u Unitary vector
   * @param up Reference vector to determine sign in 3D angles
   * @return Quaternion
   */
  Eigen::Quaternionf align_vectors(const point_type& v, const point_type& u, const point_type up = point_type(0,0,1));


  /**
   * @brief Computes the box-segment intersection of b and s
   * @param b Box
   * @param s Segment
   * @param inter (Return) Intersection point
   * @return True if b intersects with s
   */
  bool segment_box_intersection( const box_type&      b, 
                                 const segment_type&  s, 
                                 point_type&          inter);

  /**
   * @brief Checks if first geometry is covered by the second
   * @param g1 First geometry
   * @param g2 Second geometry
   * @return True if g1 is covered by g2
   */
  template <typename G1, typename G2>
  bool covered_by(const G1& g1, const G2& g2){
    return bg::covered_by(g1,g2);
  }
  
  /**
   * @brief Segment-axis plane intersection
   * @param s Segment
   * @param v Point that marks the Ith plane position
   * @param inter Intersection point
   * @return True if they intersect
   */
  template<int I, typename Point>
  bool segment_cross_plane(const segment_type& s, 
                           const Point&        v, 
                           Point&              inter){
    
    // Segment crosses axis plane
    if ( (bg::get<I>(s.first)-bg::get<I>(v) ) *
         (bg::get<I>(s.second)-bg::get<I>(v)) <= 0 ) {
        
      if((bg::get<I>(s.first)-bg::get<I>(v) ) == 0){
          inter = s.first;
          return true;
      } else if((bg::get<I>(s.second)-bg::get<I>(v) ) == 0){
          inter = s.second;
          return true;
      }
      
      // Compute intersection point
      point_type vec_s = s.second;
      bg::subtract_point(vec_s,s.first); // This is the vector for s
      
      float lambda = (bg::get<I>(v) - bg::get<I>(s.first)) / bg::get<I>(vec_s) ;
      
      bg::multiply_value(vec_s, lambda);
      bg::add_point(vec_s,s.first);
      
      inter = vec_s;
      
      return true;
    } else {
      return false;
    }
  }

  /**
   * @brief Set the ith component in res to the minimim betweeen the ith components
   * in p and res
   * @param p Base point. unmodified
   * @param res Point to be modified
   */
  template<int I, typename Point>
  void min_component(const Point& p, Point& res){
      if(bg::get<I>(p) < bg::get<I>(res) ) 
        bg::set<I>(res, bg::get<I>(p) );
  };

  /**
   * @brief Set the ith component in res to the maximum betweeen the ith components
   * in p and res
   * @param p Base point. unmodified
   * @param res Point to be modified
   */
  template<int I, typename Point>
  void max_component(const Point& p, Point& res){
      if(bg::get<I>(p) > bg::get<I>(res) ) 
        bg::set<I>(res, bg::get<I>(p) );
  };

  /**
   * @brief Computes the component-wise maximum between p and res and stores it in res
   * @param p Base point
   * @param res Return point
   */
  template<typename Point>
  void max_by_component(const Point& p, Point& res){
    max_component<0>(p,res);
    max_component<1>(p,res);
    max_component<2>(p,res);
  };

  /**
   * @brief Computes the component-wise minimum between p and res and stores it in res
   * @param p Base point
   * @param res Return point
   */
  template<typename Point>
  void min_by_component(const Point& p, Point& res){
    min_component<0>(p,res);
    min_component<1>(p,res);
    min_component<2>(p,res);
  };


  /**
   * @brief Return box axis length
   * @param box
   * @return Axis length (value)
   */
  template <Axis axis>
  float axisLength(const box_type& b);


  /**
   * @brief Set box axis to given value
   * @param b Box
   * @param v Value
   */
  template <Axis axis>
  void setAxis(box_type& b, float v);
  
  polygon_type as_planar_polygon( const std::vector<point_type>& v);
  
  /**
   * @brief Number of points in the geometry
   * @param geom Geoemtry object
   * @return Number of point
   */
  template<typename G>
  std::size_t num_points(const G& geom){
    return bg::num_points(geom);
  }
  
  /**
   * @brief Computes the pclosed polygon area
   * @param p Polygon object
   * @return Area
   */
  float polygon_area(const polygon_type& p);
  
  
  /**
   * @brief Computes the closed polygon area
   * @param begin
   * @param end
   * @return Area
   */
   template<typename Iter>
   float polygon_area(const Iter& begin, const Iter& end){
     // Create ring
     ring_type r(begin,end);
     
     // Correct
     bg::correct(r);
     
     // Return area
     return bg::area(r);
   };
  
  /**
   * @brief Multiplies every component by -1
   * @param p Point to negate
   */
  void negate(point_type &p);
  
  /**
   * @brief Computes the barycenter of a pointset
   * @param v Vector of points
   * @return Barycenter
   */
  point_type barycenter(const std::vector<point_type>& v);
  
  /**
   * @brief Modifies p so its norm is equal to 1
   * @param p Point to normalize
   */
  void normalize(point_type& p);
  
  /**
   * @brief Computes the planar vector-vector shortest angle 
   * @param a First vector
   * @param b Second vector
   * @return Angle between a and b  [0,pi]
   */
  float vector_vector_angle(const point_type&a ,const point_type &b);
  
  /**
   * @brief Checks if box a intersects with box b (axis aligned)
   * @param a 
   * @param b
   * @return True if they intersect
   */
  bool box_box_intersection(const box_type&a ,const box_type&b);
  
  /**
   * @brief Returns 8 corner points in a axis-aligned box
   * @param a 
   * @return Corner points
   */
  std::vector<point_type> box_corners(const box_type &b);
  
  /**
   * @brief Euclidean distance between two line-segments
   * @param u
   * @param v
   * @return euclidean distance
   */
  float lineseg_dist(const std::vector<point_type>& u,
                     const std::vector<point_type>& v);
  
  
  /**
   * @brief Computes the bounding box of a node set
   * @param v node set
   * @return box
   */
  box_type bounding_box(const std::vector<point_type>& v);
  
  /**
   * @brief Computes the planar angle from a to b
   * @param a First vector
   * @param b Second vector
   * @param up Reference vector to determine sign in 3D angles
   * @return Angle from a to b  [0,wpi)
   */
  float vector_vector_directed_angle(const point_type&a ,const point_type &b, const point_type up = point_type(0,0,1));
  
  /**
   * @brief Computes the local orientation (Azimuth and elevation) of p wrt basis
   * @param p Point
   * @param basis local basis
   * @return pair (azimuth, elevation)
   */
  std::pair<float,float> local_orientation(const point_type& p, const std::array<point_type,3>& basis);
  
  // Triangle methods
  
  /**
   * @brief Verifies if p is in the border of the triangle t
   * @param t Triangle
   * @param p Point
   * @return  True if p lies in the border of t
   */
  bool in_triangle_border(const triangle_type& t, const point_type& p);
  
  /**
   * @brief Verifies if P is one of the vertices of T
   * @param t Triangle
   * @param p Point
   * @return True if p is a vertex of t
   */
  bool is_triangle_vertex(const triangle_type& t, const point_type& p);
  
  /**
   * @brief Verifies if p is inside the triangle t
   * @param t Triangle
   * @param p Point 
   * @return True if p is inside t
   */
  bool within_triangle(const triangle_type& t, const point_type& p);
  
  
  /**
   * @brief Computes Triangle-ray intersection with the moller-trumbore algorithm
   * @param t Triangle
   * @param ray_o Ray origin
   * @param ray_v Ray direction
   * @param intersection Output: intersection point
   * @return True if the ray intersects the triangle
   */
  bool triangle_ray_intersection( const triangle_type& t,
                                  const point_type& ray_o,
                                  const point_type& ray_v,
                                  point_type& intersection );
  
  /**
   * @brief Returns the volume of the tetrahedron
   * @param p0 vertex
   * @param p1 vertex 
   * @param p2 vertex
   * @param p3 vertex
   * @return Tetrahedron voulme
   */
  float tetrahedron_volume( const point_type& p0, 
                            const point_type& p1,
                            const point_type& p2,
                            const point_type& p3);
  
  
  /**
   * @brief Compute the triangle area
   * @return Triangle area
   */
  float triangle_area( const triangle_type& t);
                            
  /**
   * @class RDPSimplifier
   * @author luis
   * @date 28/09/16
   * @file geometry.h
   * @brief Auxiliar class that applies RDP simplification to a line-segment
   */
  template <typename Node>
  class RDPSimplifier{
    
    private:
      float eps;
      std::vector<Node>& v;
      
    public:
      /**
       * @brief Base constructor, sets toleracne and the line-segment
       * @param eps Tolerance
       * @param v Node set (vector)
       */
      RDPSimplifier(float eps, std::vector<Node>& v) : eps(eps), v(v) {};
      
      /**
       * @brief Applies the simplification to the line-segment
       */
      void simplify(){
        simplify_recursive(v.begin(), v.end() );
      }
      
    private:
      /**
       * @brief Auxiliar function to recursively simplify the line-segment
       * @param end
       */
      void simplify_recursive(const typename std::vector<Node>::iterator ini, 
                              const typename std::vector<Node>::iterator end){
        
        // Stop condition
        if(std::distance(ini,end) < 2 ) return ;
        
        segment_type segm(ini->position(),end->position());
        float maxd = 0.;
        float tmp;
        
        typename std::vector<Node>::iterator m;
        
        //Check distance bw every node and the line ini->end
        for(auto it = (ini+1); it != end ; ++it){
          tmp = bg::distance(segm, it->position() );
          if( tmp > maxd ) {
            maxd = tmp;
            m = it;
          }
        }
        
        // Check if we shoud keep m and simplify recursively
        if (maxd > eps) {
          simplify_recursive(ini,m);
          simplify_recursive(m,end);
        }
        else{
          // DELETE intermediate nodes
          v.erase(ini+1,end);
        }
      }
  }; // RDP simplifier
  
  /**
   * @class DiscreteFrechet
   * @author luis
   * @date 28/09/16
   * @file geometry.h
   * @brief Class to compute the discrete frechet distance in a line-segment
   */
  template< typename IterA, typename IterB >
  class DiscreteFrechet {
    
    private:
      
      // ITerators
      IterA ini_a;
      IterA end_a;
      IterB ini_b;
      IterB end_b;
      
      // a and b sizes
      int p;
      int q;
      
      // Axuiliar DP matrix
      Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> buffer;
      
    public:
      /**
       * @brief Base constructor. Initializes the class with the tow line-segment
       * @param ini_a First branch line-segment begin iterator
       * @param end_a First branch line-segment end iterator
       * @param ini_b Second branch line-segment begin iterator
       * @param end_b Secondbranch line-segment end iterator
       * @return DiscreteFrechet class
       */
      DiscreteFrechet(IterA ini_a, IterA end_a, IterB ini_b, IterB end_b)
        : ini_a(ini_a)
        , end_a(end_a)
        , ini_b(ini_b)
        , end_b(end_b)
        , p(std::distance(ini_a,end_a))
        , q(std::distance(ini_b,end_b))
        , buffer( p, q) {
          buffer.fill(-1.0); // Fill buffer 
      }
    
      /**
       * @brief Computes de discrete frechet distance recursively
       * @return Discrete frechet distance
       */
      double value(){        
        return recursive_value(p-1,q-1);
      };
    
    private:
      
      /**
       * @brief Internal function. Computes the value i,j of the DP matrix
       * @param i Row
       * @param j Column
       * @return  i-j value in DP matrix
       */
      double recursive_value(int i, int j){
        // Computed already
        if (buffer(i,j) < 0) {  
          if ( i == 0 ) {
            // I = 0 CASE
            if ( j == 0) {
              // Base case (first step)
              buffer(0,0) =  boost::geometry::distance(*ini_a,*ini_b);
            } else {
              buffer(0,j) = std::max(recursive_value(0,j-1), boost::geometry::distance(*ini_a,*(ini_b+j)) );
            }
          } else {
            // I != 0
            if ( j == 0) {
              buffer(i,0) = std::max(recursive_value(i-1,0),boost::geometry::distance(*(ini_a+i),*ini_b) );
            } else {
              // Both are not 0
              buffer(i,j) = std::max(
                std::min({ recursive_value(i-1,j),recursive_value(i,j-1), recursive_value(i-1,j-1)}),
                boost::geometry::distance(*(ini_a+i),*(ini_b+j)) );
            }
          }
        }
        return buffer(i,j);
      };
  }; // Discrete frechet class template

/**
 * @class TriangleMesh
 * @author luis
 * @date 24/10/16
 * @file geometry.h
 * @brief Simple class for a 3D mesh with triangular faces
 */
  class TriangleMesh {
    
    public:
    
    using vertex_type = point_type;
    using vertex_storage = std::vector<point_type>;
    using vertex_iterator = vertex_storage::iterator;
    using const_vertex_iterator = vertex_storage::const_iterator;
    
    
    using face_type = triangle_type;
    using face_storage = std::vector<face_type>;
    using face_iterator = face_storage::iterator;
    using const_face_iterator = face_storage::const_iterator;
    
    private:
      
      vertex_storage vertices_;
      face_storage faces_;
    
    public:
      
      /**
       * @brief Creates an empty (no vertex no faces) mesh
       */
      TriangleMesh();
      
      /**
       * @brief Creates a mesh with given faces. Vertices are added automatically
       */
      TriangleMesh(const face_storage& faces);
      
      /**
       * @brief Default destructor. Nothign special to do
       */
      ~TriangleMesh();
      
      // Copy not allowed (we store iterators...)
      TriangleMesh(const TriangleMesh&) = delete;
      TriangleMesh& operator=(const TriangleMesh&) = delete;
      
      // Move
      TriangleMesh(TriangleMesh&&) = default;
      TriangleMesh& operator=(TriangleMesh&&) = default;
      
      // VERTICES
      
      // Add
      
      /**
       * @brief Adds a vertex to the mesh (if it doesnt exist already)
       * @param p Vertex to add.
       */
      vertex_iterator add(const point_type& p);
      
      /**
       * @brief Copies a range of vertices to the mesh
       * @param b Range begin iterator
       * @param e Range end iterator
       */
      template <typename Iter>
      void add(const Iter& b, const Iter& e){
        for(auto it = b; it != e ; ++it){
          add(*it);
        }
      }
      
      /**
       * @brief Removes the vertex and all its faces from the mesh
       * @param it Vertex iterator
       */
      void remove(const vertex_iterator& it);
      
      /**
       * @brief Removes a range of vertices and their faces from the mesh
       * @param b Range begin
       * @param e Range end
       */
      void remove(const vertex_iterator& b, const vertex_iterator& e);
      
      /**
       * @brief Removes all vertices and faces
       */
      void clear();
      
      /**
       * @brief Creates an iterator to the first vertex in the mesh
       * @return Begin iterator
       */
      vertex_iterator begin_vertex();
      
      /**
       * @brief Creates an iterator to the first vertex in the mesh
       * @return Begin iterator
       */
      const_vertex_iterator begin_vertex() const;
      
      /**
       * @brief Creates an iterator to one-past position of the last vertex in the mesh
       * @return End iterator
       */
      vertex_iterator end_vertex();
      
      /**
       * @brief Creates an iterator to one-past position of the last vertex in the mesh
       * @return End iterator
       */
      const_vertex_iterator end_vertex() const;
      
      /**
       * @brief Number of vertices in the mesh
       */
      std::size_t vertex_count() const;
      
      // FACES
      
      /**
       * @brief Adds a new triangular face to the mesh. Inserts the vertices
       * if necessary
       * @param v0 First vertex
       * @param v1 Second vertex
       * @param v2 Third vertex
       * 
       * @return Iterator to the inserted face
       */         
      face_iterator add(const point_type& v0,
               const point_type& v1,
               const point_type& v2);
      
      /**
       * @brief Adds a new triangular face to the mesh. Inserts the vertices
       * if necessary
       * @param t face triangle
       * 
       * @return Iterator to the inserted face
       */                  
      face_iterator add(const triangle_type& t);
        
      /**
       * @brief Removes a face from the mesh
       * @param it Face iterator
       */
      void remove(const face_iterator& it);
      
      /**
       * @brief Removes a set of faces from the mesh
       * @param b Begin iterator
       * @param e End iterator
       */
      void remove(const face_iterator& b, const face_iterator& e);
      
      /**
       * @brief Removes all faces (but not the vertices)
       */
      void clear_faces();

      // Face iterator
      
      /**
       * @brief Returns an iterator to the first face in the mesh
       * @return Begin iterator
       */
      face_iterator begin_face();
      /**
       * @brief Returns an iterator to the first face in the mesh
       * @return Begin iterator
       */
      const_face_iterator begin_face() const;
      
      /**
       * @brief Returns an iterator to one-past the last face in the mesh
       * @return End iterator
       */
      face_iterator end_face();
      
      /**
       * @brief Returns an iterator to one-past the last face in the mesh
       * @return End iterator
       */
      const_face_iterator end_face() const;
      
      /**
       * @brief Number of faces in the mesh
       */
      std::size_t face_count() const;
      
      
      /**
       * @brief Using ray-tracing method computes if the point p is Inside the
       * triangular mesh assuming that it is closed
       * @param p Point
       * @return  True if the point is within the mesh
       */
      bool point_inside(const point_type& p, const point_type& ray_direction = point_type(1,0,0)) const;
      
      /**
       * @brief 
       * @param p
       * @param ray_direction
       * @return 
       */
      point_type ray_intersection(const point_type& p, const point_type& ray_direction = point_type(1,0,0)) const;
      
    private:
      
      /**
       * @brief Checks if v is a vertex of f
       * @param v Vertex
       * @param f face
       * @return 
       */
      static bool vertex_of_face(const vertex_type& v, const face_type& f);
      
  };//Triangle mesh

} // namespace geometry

  // Expose geometry types in the neurostr namespace
  using point_type =    geometry::point_type;
  using box_type =      geometry::box_type;
  using segment_type =  geometry::segment_type;
  using polygon_type =  geometry::polygon_type;
  using triangle_type =  geometry::triangle_type;
  using triMesh_type = geometry::TriangleMesh;
  
  
  
} // namespace neurostr

// Trimesh output
  std::ostream& operator<<(std::ostream&,  const neurostr::geometry::TriangleMesh&);

#endif
