#ifndef NEUROSTR_METHODS_TRICONTOUR_H_
#define NEUROSTR_METHODS_TRICONTOUR_H_

#include "core/log.h"
#include "core/neuron.h"
#include "core/contour.h"
#include "core/geometry.h"


namespace neurostr{
namespace methods{
  
  /**
   * @brief Given two contours, reorients them in counter clockwise order. 
   * Also applies a rotation to ensure that the two first nodes are the closest ones.
   * @param a First contour
   * @param b Second contour
  */
  void align_contours( Contour& a, Contour& b, int component);
  
  /**
   * @brief Closes the contour 
   * @param a Contour
   * @return Set of triangules to close the contour
   */
  std::vector<triangle_type> close_contour(const Contour& a);
  
  
  
  /**
   * @brief Auxiliar function. Computes nu_a volume
   * @param ob B contour barycenter
   * @return 
   */
  template <typename IterA, typename IterB>
  float triangulation_va_volume( std::size_t i, std::size_t j,
                        const IterA& b_a, const IterB& b_b, const point_type& ob){
    return geometry::tetrahedron_volume( *std::next(b_a,i), *std::next(b_a,i+1),
                                         *std::next(b_b,j), ob);
  
  }
  
  /**
   * @brief Auxiliar function. Computes nu_b volume
   * @param oa A contour barycenter
   * @return 
   */
  template <typename IterA, typename IterB>
  float triangulation_vb_volume( std::size_t i, std::size_t j,
                        const IterA& b_a, const IterB& b_b, const point_type& oa){
    return geometry::tetrahedron_volume( *std::next(b_b,j), *std::next(b_b,j+1),
                                         *std::next(b_a,i), oa);
    
  }
  
  /**
   * @brief Auxiliar function. Computes nu_a area
   * @return 
   */
  template <typename IterA, typename IterB>
  float triangulation_va_area( std::size_t i, std::size_t j,
                        const IterA& b_a, const IterB& b_b){
    return geometry::triangle_area( {*std::next(b_a,i), *std::next(b_a,i+1),
                                          *std::next(b_b,j)});
  
  }
  
  /**
   * @brief Auxiliar function. Computes nu_b area
   * @return 
   */
  template <typename IterA, typename IterB>
  float triangulation_vb_area( std::size_t i, std::size_t j,
                        const IterA& b_a, const IterB& b_b){
    return geometry::triangle_area( {*std::next(b_b,j), *std::next(b_b,j+1),
                                     *std::next(b_a,i)} );
    
  }
  
  /**
   * @brief Given two contours, joins them to create a triangular-faced mesh
   * Actually this is like doing dijkstra from 0,0 to the last vertex.
   * @param b_a Contour A begin iterator
   * @param e_a Contour A end iterator
   * @param b_b Contour B begin iterator
   * @param e_b Contour B end iterator
   * @param oa Contour A barycenter
   * @param ob Contour B barycenter
   * @return Triangular faces
   */
  template <typename IterA, typename IterB>
  std::vector<triangle_type> 
  triangulate_contours( const IterA& b_a, const IterA& e_a,
                        const IterB& b_b, const IterB& e_b){
    
    // Get number of nodes in each contour                      
    std::size_t m = std::distance(b_a,e_a);
    std::size_t n = std::distance(b_b,e_b);
    
    NSTR_LOG_(debug, "Contour sizes: " + std::to_string(m) + ", " + std::to_string(n) );
    // Matrices w and p as vectors (row-first)
    std::vector<float> w(m*n); // Allocate an n*m vector (0)

    std::vector<bool> p(m*n);//  False
    
    w[0] = 0.0; // Initialize first position
    
    // Fill left border
    NSTR_LOG_(debug, "Filling left border");
    for(std::size_t i = 1; i < m ; ++i){
      w[ (i*n) + 0 ] = w[ ((i-1)*n) + 0 ] + triangulation_va_area(i-1, 0, b_a, b_b);  
      p[ (i*n) + 0 ] = true; // Left border always goes up (we cant go left)
    }
    
    // Fill top border
    NSTR_LOG_(debug, "Filling top border");
    for(std::size_t j = 1; j < n ; ++j){
      w[ j ] = w[ j-1 ] + triangulation_vb_area(0, j-1, b_a, b_b);  
      p[ j ] = false;  // Top border always goes left (we cant go up)
    }
    
    // Temp to choose path
    float v_a,v_b;
    
    // For increments of c..
    NSTR_LOG_(debug, "Filling");
    for(std::size_t c = 2; c <= (m-1)+(n-1); ++c){
      // Get index i (Always gt 0 - border case)
      for(std::size_t i = 1 ; i < c && i < m ; ++i ){
        // Get index j (Always gt 0 - border case)
        std::size_t j = c-i; // J is fully determined by c and i
        if(j < n){
        
          // V_a cost if we create a vertical segment - (Triangle P_i-1, P_i, Q_j)
          v_a = w[ ((i-1)*n) + j ] + triangulation_va_area(i-1, j, b_a, b_b);
          
          // V_b cost if we create a horizontal segment - (Triangle P_i, Q_j-1, Q_j)
          v_b = w[ (i*n) + (j-1) ] + triangulation_vb_area(i, j-1, b_a, b_b);
          
          // Maximize and set p and w
          if ( v_a < v_b) {
            p[(i*n) + j ] = true; // We choose the vertical option
            w[(i*n) + j ] = v_a; // Updated path cost at i,j
          } else {
            p[(i*n) + j ] = false; // We choose the hz option
            w[(i*n) + j ] = v_b; // Update path cost at i,j
          }
        }
      } // End for I
    } // End for C
    
    // At this point we should have stopped at m,n and onle need to go backwards
    // to get the triangulation
    NSTR_LOG_(debug, "Extracting triangulation");
    std::vector<triangle_type> triangles;
    triangles.reserve(m+n);
    
    std::size_t i,j;
    i = m-1;
    j = n-1;
    triangle_type t;
    while( i != 0 || j != 0){ // If we have done right the previous step this shouldnt fail
      // Add triangles while we can
      
      if( p[(i*n) + j ] ){
        // Vertical segment - Create (P_i-1,P_i,Q_j)
        t = {*std::next(b_a,i-1), *std::next(b_a,i), *std::next(b_b,j)};
        --i;
      } else {
        // Horizontal - The triangulation is  (P(i), Q(j-1), Q(j))
        t = {*std::next(b_a,i), *std::next(b_b,j-1), *std::next(b_b,j)};
        --j;
      }
      triangles.push_back(t);
    } // end while
    
    return triangles;
    
  }// End triangulate contours
  
  
  
  /**
   * @brief Given an ordered set of Contours, joins them and creates a
   * triangular-faced mesh
   * @param b Contour set begin
   * @param e Contour set end
   * @return Triangular faced mesh
   */
  template <typename Iter>
  triMesh_type create_triangular_contour(const Iter& b, const Iter& e,int component = 2){
    triMesh_type mesh; // Empty mesh
    for(auto it = std::next(b,1) ; it!= e; ++it){
      // Align contours (first - shortest distance & same orientation
      align_contours(*std::prev(it,1),*it,component);
      
      // Compute triangulation
      std::vector<triangle_type> t = triangulate_contours(
                                      std::prev(it,1)->begin(), 
                                      std::prev(it,1)->end(),
                                      it->begin(),
                                      it->end());
      // Add to the mesh
      for(auto t_it = t.begin(); t_it != t.end(); ++t_it){
        mesh.add(*t_it);
      }
    }
    
    //Close first and last contours
    std::vector<triangle_type> t = close_contour(*b);
    for(auto t_it = t.begin(); t_it != t.end(); ++t_it){
        mesh.add(*t_it);
    }
      
    t = close_contour(*std::prev(e,1));
    for(auto t_it = t.begin(); t_it != t.end(); ++t_it){
        mesh.add(*t_it);
    }
    
    return mesh;
  }
  
  /**
   * @brief 
   * @param r
   * @param name
   * @param component
   */
  void reconstructionContourProcess( Reconstruction& r, const std::string& name, int component = 2);
  
  /**
   * @brief 
   * @param n
   * @param name
   * @param contour
   */
  void neuronContourProcess( Neuron& n, const std::string& name, const triMesh_type& contour);
  
  /**
   * @brief 
   * @param n
   * @param name
   * @param contour
   */
  void neuriteContourProcess( Neurite& n, const std::string& name, const triMesh_type& contour);
  
  /**
   * @brief 
   * @param b
   * @param name
   * @param contour
   * @return 
   */
  void branchContourProcess( Branch& b, const std::string& name, const triMesh_type& contour);
  
  /**
   * @brief 
   * @param r
   */
  void removeContourVirtualNodes( Reconstruction& r );
  


} // End namespace methods  
} // End namespace neurostr

#endif
