#ifndef NEUROSTR_METHODS_TRICONTOUR_H_
#define NEUROSTR_METHODS_TRICONTOUR_H_

#include "core/contour.h"
#include "core/geometry.h"


namespace neurostr{
namespace methods{
  
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
      align_contours(*std::prev(it,1),*it);
      
      // Copy contours and close them
      std::vector<point_type> contour_a(std::prev(it,1)->begin(),std::prev(it,1)->end());
      std::vector<point_type> contour_b(it->begin(),it->end());
      contour_a.push_back(*(std::prev(it,1)->begin()));
      contour_b.push_back(*(it->begin()));
      
      // Compute triangulation
      std::vector<triangle_type> t = triangulate_contours(
                                      contour_a.begin(), 
                                      contour_a.end(),
                                      contour_b.begin(),
                                      contour_b.end(),
                                      std::prev(it,1)->barycenter(),
                                      it->barycenter());
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
   * @brief Given two contours, joins them to create a triangular-faced mesh
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
                        const IterB& b_b, const IterB& e_b,
                        const point_type& oa, const point_type& ob){
    
    // Get number of nodes in each contour                      
    std::size_t m = std::distance(b_a,e_a);
    std::size_t n = std::distance(b_b,e_b);
    
    // Matrices w and p as vectors (row-first)
    std::vector<float> w(m*n); // Allocate an n*m vector
    std::vector<bool> p(m*n);// 
    
    std::size_t c;
    
    // Initialize w0,1 and w,1,0
    w[ (0*m) + 1 ] = triangulation_va_volume(0, 1, b_a, b_b, ob);
    w[ (1*m) + 0 ] = triangulation_vb_volume(1, 0, b_a, b_b, oa);
    
    float v_a,v_b;
    
    // For increments of c..
    for(std::size_t c = 2; c <= (m-1)+(n-1); ++c){
      // Get index i
      for(std::size_t i = 0 ; i <= c && i < m ; ++i ){
        // Get index j
        std::size_t j = c-i; // J is fully determined by c and i
        v_a = w[ ((i-1)*m) + j ] + triangulation_va_volume(i-1, j, b_a, b_b, ob);
        v_b = w[ (i*m) + (j-1) ] + triangulation_vb_volume(i, j-1, b_a, b_b, oa);
        
        // Maximize and set p and w
        if ( v_a >= v_b) {
          p[(i*m) + j ] = true;
          w[(i*m) + j ] = v_a;
        } else {
          p[(i*m) + j ] = false;
          w[(i*m) + j ] = v_b;
        }
      } // End for I
    } // End for C
    
    // At this point we should have stopped at m,n and onle need to go backwards
    // to get the triangulation
    std::vector<triangle_type> triangles;
    
    std::size_t i,j;
    i = m-1;
    j = n-1;
    while( i != 0 && j != 0){
      // Add triangles while we can
      if( p[(i*m) + j ] ){
        // The triangulation is  (A(i-1), A(i), B(j))
        triangles.emplace_back( *std::next(b_a,i-1), *std::next(b_a,i), *std::next(b_b,j));
      } else {
        // The triangulation is  (A(i), B(j-1), B(j))
        triangles.emplace_back( *std::next(b_a,i), *std::next(b_b,j-1), *std::next(b_b,j));
      }
    } // end while
    
    return triangles;
    
  }// End triangulate contours

} // End namespace methods  
} // End namespace neurostr

#endif
