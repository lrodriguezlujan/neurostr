#ifndef NEUROSTR_CORE_GEOMETRY_H_
#define NEUROSTR_CORE_GEOMETRY_H_

#include <math.h>
#include <array>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace neurostr
{
  
/**
* This namespace hides geometry implementation to the rest of the library
*/
namespace geometry
{
  
  namespace bg =        boost::geometry;
  using point_type =    bg::model::point<float, 3, bg::cs::cartesian>;
  using box_type =      bg::model::box<point_type>;
  using segment_type =  bg::model::segment<point_type>;
  
  using planar_point = bg::model::point<float, 2, bg::cs::cartesian>;
  using polygon_type =  bg::model::polygon<planar_point>;
  
  
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
   * @brief Euclidean distance between a and b
   * @param a First point
   * @param b Second point
   * @return  Eculidean distance (Float)
   */
  float distance(const point_type& a, const point_type& b);
  
  /**
   * @brief Vector with origin in \code{from} and end in \code{to}
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
   * @brief Modifies the point p scaling it by \code{scale} wrt ref
   * @param p Point to be modified
   * @param scale Scale
   * @param ref Referecne point
   */
  void scale(point_type& p, float scale, const point_type&  ref);
  
  /**
   * @brief  Modifies the point \code{p} scaling it by (rx,ry,rz)
   * @param p Point to be modified
   * @param rx X scale
   * @param ry Y Scale
   * @param rz Z scale
   */
  void scale(point_type& p, float rx, float ry, float rz);
  
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
   * @return Quaternion
   */
  Eigen::Quaternionf align_vectors(const point_type& v, const point_type& u);


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
   * @brief Computes the planar angle from a to b
   * @param a First vector
   * @param b Second vector
   * @return Angle from a to b  [0,wpi)
   */
  float vector_vector_directed_angle(const point_type&a ,const point_type &b);
  
  /**
   * @brief Computes the local orientation (Azimuth and elevation) of p wrt basis
   * @param p Point
   * @param basis local basis
   * @return pair (azimuth, elevation)
   */
  std::pair<float,float> local_orientation(const point_type& p, const std::array<point_type,3>& basis);
  
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
        for(auto it = (ini+1); it != (end-1) ; ++it){
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
          v.erase(ini+1,end-1);
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


} // namespace geometry

  // Expose geometry types in the neurostr namespace
  using point_type =    geometry::point_type;
  using box_type =      geometry::box_type;
  using segment_type =  geometry::segment_type;
  using polygon_type =  geometry::polygon_type;
  
} // namespace neurostr

#endif
