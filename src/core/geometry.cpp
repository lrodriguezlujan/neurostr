#include <neurostr/core/geometry.h>

namespace neurostr {
namespace geometry {
  
  template <>
  planar_point planar_projection<0>(const point_type& p){
    return planar_point(bg::get<1>(p),bg::get<2>(p));
  }
  
  template <>
  planar_point planar_projection<1>(const point_type& p){
    return planar_point(bg::get<0>(p),bg::get<2>(p));
  }
  
  template <>
  planar_point planar_projection<2>(const point_type& p){
    return planar_point(bg::get<0>(p),bg::get<1>(p));
  }
  
  planar_point planar_projection(const point_type& p, int i){
    switch(i){
      case 0: return planar_projection<0>(p);
      case 1: return planar_projection<1>(p);
      case 2: return planar_projection<2>(p);
      default: return planar_point(NAN,NAN);
    }
  }
  
  float distance(const point_type& a, const point_type& b){ 
    return bg::distance(a,b);
  }
  
  point_type vectorFromTo(const point_type& from, const point_type& to){
    point_type ret = to;
    bg::subtract_point(ret,from);
    return ret;
  }
  
  void traslate(point_type& p, const point_type& v ){ 
    bg::add_point(p,v); 
  }
  
  void scale(point_type& p, float r, const point_type&  ref){
    auto tmp = p ; 
    bg::subtract_point(tmp, ref); // tmp is our "vector to scale"
    scale(tmp,r);
    bg::add_point(tmp, ref);
    p = tmp;
  }
  
  void scale(point_type& p, float rx, float ry, float rz){
    bg::multiply_point(p, point_type(rx,ry,rz));
  }
  
  void scale(point_type& p, float r){
    
    if(r == 1) return;
    
    float factor = r * norm(p);
    normalize(p);
    bg::multiply_value(p, factor);
  }
  
  point_type cross_product(const point_type& p, const point_type& q) {
    point_type r;
    bg::set<0>(r, bg::get<1>(p) * bg::get<2>(q) - bg::get<2>(p) * bg::get<1>(q));
    bg::set<1>(r, bg::get<2>(p) * bg::get<0>(q) - bg::get<0>(p) * bg::get<2>(q));
    bg::set<2>(r, bg::get<0>(p) * bg::get<1>(q) - bg::get<1>(p) * bg::get<0>(q));
    
    return r;
  }
  
  float norm(const point_type& p) {
    return bg::distance(p, point_type(0,0,0));
  }

  std::array<point_type, 3> get_basis(const point_type& vx, 
                                      const point_type& up){

  std::array<point_type, 3> basis;

  point_type norm_vx = vx;
  point_type norm_up = up;
  point_type vy;

  // Normalize
  bg::divide_value(norm_vx, norm(vx));
  bg::divide_value(norm_up, norm(up));

  // Compute cross product
  vy = cross_product(norm_up, norm_vx);
  bg::divide_value(vy, norm(vy));

  // Save normvx and normvy
  basis[0] = norm_vx;
  basis[1] = vy;
  basis[2] = cross_product(norm_vx, vy);
  bg::divide_value(basis[2], norm(basis[2]));

  return basis;
}

float segment_segment_distance(const point_type& p0, const point_type& p1, 
                               const point_type& q0, const point_type& q1) {

  namespace bg = boost::geometry;

  // Vectors
  auto u = p1;
  bg::subtract_point(u, p0);
  auto v = q1;
  bg::subtract_point(v, q0);
  auto w = p0;
  bg::subtract_point(w, q0);

  // Auxiliar values
  float a = bg::dot_product(u, u);
  float b = bg::dot_product(u, v);
  float c = bg::dot_product(v, v);
  float d = bg::dot_product(u, w);
  float e = bg::dot_product(v, w);
  float D = a * c - b * b;
  float sD = D;
  float tD = D;

  float sN, tN;

  if (D < 1E-3) {
    sN = 0;
    sD = 1;
    tN = e;
    tD = c;
  } else {
    sN = (b * e - c * d);
    tN = (a * e - b * d);
    if (sN < 0) {
      sN = 0;
      tN = e;
      tD = c;
    } else if (sN > sD) {
      sN = sD;
      tN = e + b;
      tD = c;
    }
  }

  if (tN < 0) {
    tN = 0;
    if (d > 0) {
      sN = 0;
    } else if (-d > a) {
      sN = sD;
    } else {
      sN = -d;
      sD = a;
    }
  } else if (tN > tD) {
    tN = tD;
    if ((-d + b) < 0.0)
      sN = 0;
    else if ((-d + b) > a)
      sN = sD;
    else {
      sN = (-d + b);
      sD = a;
    }
  }

  float sc, tc;

  if (std::abs(sN) < 1E-3)
    sc = 0;
  else
    sc = sN / sD;

  if (std::abs(tN) < 1E-3)
    tc = 0;
  else
    tc = tN / tD;

  bg::multiply_value(u, sc);
  bg::multiply_value(v, tc);
  bg::subtract_point(u, v);
  bg::add_point(w, u);
  return norm(w);
}

// Computes the quaternion to transform v into u
Eigen::Quaternionf align_vectors(const point_type& from, const point_type& to, const point_type up){
  
  namespace bg = boost::geometry;
    
    if(norm(from) == 0 || norm(to) == 0)
      return  Eigen::Quaternionf::Identity();
    
    float angle = geometry::vector_vector_directed_angle(from,to,up);
    
    // Already aligned
    if( angle == 0 ) return  Eigen::Quaternionf::Identity();
    
    // Rotation axis (normalized)
    auto axis = geometry::cross_product(from, to);
    
    
    
    if(geometry::norm(axis) == 0){
        // 180 rotation
        angle = M_PI;
        //axis (any orthogonal vector)
        axis = point_type(-bg::get<1>(from),bg::get<0>(from),0);
    } else {
      normalize(axis);
      if(boost::geometry::dot_product(up,axis) < 0)
        angle *= -1;;
    }
    
    // Compute angle axis rotation and rotate.
    Eigen::AngleAxisf rotation( angle, 
                                Eigen::Vector3f(bg::get<0>(axis),
                                                bg::get<1>(axis),
                                                bg::get<2>(axis))
                              );
    Eigen::Quaternionf q(rotation);
    q.normalize(); // just in case. its supposed to be normalized already
  
  return q;
}

bool segment_box_intersection( const bg::model::box<point_type>& b, 
                               const bg::model::segment<point_type>& s, 
                              point_type& inter){
   
  // Croses min corner by x
  if(segment_cross_plane<0>(s,b.min_corner(),inter)){
    return true;
  } else if (segment_cross_plane<1>(s,b.min_corner(),inter)){
    return true;
  } else if (segment_cross_plane<2>(s,b.min_corner(),inter)){
    return true;
  } else if (segment_cross_plane<0>(s,b.max_corner(),inter)){
    return true;
  } else if (segment_cross_plane<1>(s,b.max_corner(),inter)){
    return true;
  } else if (segment_cross_plane<2>(s,b.max_corner(),inter)){
    return true;
  } else {
    return false;
  }
}

bool box_box_intersection(const box_type&a ,const box_type&b) {
  std::vector<point_type> corners = box_corners(b);
  
  for(auto it = corners.begin(); it != corners.end() ; ++it) {
    if(bg::covered_by(*it,a))
      return true;
  }
  return false;
}

float lineseg_dist(const std::vector<point_type>& u,
                     const std::vector<point_type>& v){
  
  float mindist =  std::numeric_limits<float>::max();
  float d;
  
  if(u.size() < 2 || v.size() < 2 ) return mindist;
                       
  for(auto uit = std::next(u.begin(),1); uit != u.end(); ++uit){
    for(auto vit = std::next(v.begin(),1); vit != v.end(); ++vit){
      d= segment_segment_distance(*std::prev(uit,1),*uit,
                                  *std::prev(vit,1),*vit);
      if(d<mindist) mindist = d;
    }
  }
  return mindist;
}

std::vector<point_type> box_corners(const box_type &b){
  
  point_type max_corner = b.max_corner();
  point_type min_corner = b.min_corner();
  
  std::vector<point_type> v;
  v.reserve(8);
  
  v.push_back(max_corner); // 1 1 1 
  v.push_back(min_corner); // 0 0 0
  bg::set<0>(min_corner, bg::get<0>(max_corner)); 
  v.push_back(min_corner); // 1 0 0
  bg::set<1>(min_corner, bg::get<1>(max_corner));
  v.push_back(min_corner); // 1 1 0
  bg::set<0>(min_corner, bg::get<0>(min_corner));
  v.push_back(min_corner); // 0 1 0
  bg::set<2>(min_corner, bg::get<2>(max_corner));
  v.push_back(min_corner); // 0 1 1
  bg::set<1>(min_corner, bg::get<1>(min_corner));
  v.push_back(min_corner); // 0 0 1
  bg::set<0>(min_corner, bg::get<0>(max_corner));
  v.push_back(min_corner); // 1 0 1

  return v;
}

box_type bounding_box(const std::vector<point_type>& v){
  
  if(v.size() == 0){
      return box_type(point_type(0,0,0),point_type(0,0,0));
  }
  
  point_type min_corner( std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max(), 
                           std::numeric_limits<float>::max());
    
  point_type max_corner( std::numeric_limits<float>::min(),
                           std::numeric_limits<float>::min(), 
                           std::numeric_limits<float>::min());
                           
  for( auto n_it = v.begin(); n_it != v.end(); ++n_it ) {
    geometry::max_by_component(*n_it,max_corner);
    geometry::min_by_component(*n_it,min_corner);
  }
  
  return box_type(min_corner,max_corner);
}

template <>
float axisLength<Axis::X_POS>( const bg::model::box<point_type>& b){
    return bg::get<0>(b.max_corner());
};

template <>
float axisLength<Axis::X_NEG>( const bg::model::box<point_type>& b){
    return bg::get<0>(b.min_corner());
};

template <>
float axisLength<Axis::Y_POS>( const bg::model::box<point_type>& b){
    return bg::get<1>(b.max_corner());
};

template <>
float axisLength<Axis::Y_NEG>( const bg::model::box<point_type>& b){
    return bg::get<1>(b.min_corner());
};

template <>
float axisLength<Axis::Z_POS>( const bg::model::box<point_type>& b){
    return bg::get<2>(b.max_corner());
};

template <>
float axisLength<Axis::Z_NEG>( const bg::model::box<point_type>& b){
    return bg::get<2>(b.min_corner());
};



// SET AXIS
template <>
void setAxis<Axis::X_POS>(bg::model::box<point_type>& b, float v){
    bg::set<0>(b.max_corner(),v);
};

template <>
void setAxis<Axis::X_NEG>(bg::model::box<point_type>& b, float v){
    bg::set<0>(b.min_corner(),v);
};

template <>
void setAxis<Axis::Y_POS>(bg::model::box<point_type>& b, float v){
    bg::set<1>(b.max_corner(),v);
};

template <>
void setAxis<Axis::Y_NEG>(bg::model::box<point_type>& b, float v){
    bg::set<1>(b.min_corner(),v);
};

template <>
void setAxis<Axis::Z_POS>(bg::model::box<point_type>& b, float v){
    bg::set<2>(b.max_corner(),v);
};

template <>
void setAxis<Axis::Z_NEG>(bg::model::box<point_type>& b, float v){
    bg::set<2>(b.min_corner(),v);
};

void normalize(point_type& p){
  if(norm(p) != 0){
    bg::divide_value(p,norm(p));
  }
}

float vector_vector_angle(const point_type&a ,const point_type &b){
  if(equal(a,b)) return 0.;
  
  if(norm(a) == 0 || norm(b) == 0 ) return 0;
  
  point_type norm_v0 = a;
  point_type norm_v1 = b;
  normalize(norm_v0);
  normalize(norm_v1);
  
  float angle = std::atan2(geometry::norm(geometry::cross_product(norm_v0, norm_v1)), boost::geometry::dot_product(norm_v0, norm_v1));
  if(std::isnan(angle)) return 0;
  else return angle;
}

float vector_vector_directed_angle(const point_type&v0 ,const point_type &v1, const point_type up){
  
  point_type norm_v0 = v0;
  point_type norm_v1 = v1;
  normalize(norm_v0);
  normalize(norm_v1);
  
  // They are in the same direction
  if(equal(norm_v0,norm_v1))
    return 0.0;
  
  // This is more precise than acos 
  float angle = std::atan2(geometry::norm(geometry::cross_product(norm_v0, norm_v1)), boost::geometry::dot_product(norm_v0, norm_v1));
  
  // Check sign
  if( boost::geometry::dot_product(up,geometry::cross_product(norm_v0, norm_v1)) < 0){
    return -angle;
  } else {
    return angle;
  }
  //return std::atan2(geometry::norm(geometry::cross_product(norm_v0, norm_v1)), boost::geometry::dot_product(norm_v0, norm_v1));
}
std::pair<float,float> local_orientation(const point_type& p, const std::array<point_type,3>& basis){
  point_type norm_p = p;
  normalize(norm_p);
  // Compute azimuth and incl
  float azimuth =
        std::atan2(boost::geometry::dot_product(norm_p, basis[1]), boost::geometry::dot_product(norm_p, basis[0]));
        
  float elevation =
        std::atan2(boost::geometry::dot_product(norm_p, basis[2]), boost::geometry::dot_product(norm_p, basis[0]));
        
  return std::pair<float, float>(azimuth, elevation);
}

polygon_type as_planar_polygon( const std::vector<point_type>& v){
  
    if(v.size() < 2) return polygon_type();
    
    // Create nx3 matrix
    Eigen::Matrix<float, Eigen::Dynamic, 3> m;
    auto n = v.size();
    m.resize(n, 3);
    

    decltype(n) i = 0;
    for (auto it = v.begin(); it != v.end(); ++it, ++i) {
        m(i, 0) = get<0>(*it);
        m(i, 1) = get<1>(*it);
        m(i, 2) = get<2>(*it);
    }

    // Then perform jacobisvd
    Eigen::JacobiSVD<decltype(m)> svd(m, Eigen::ComputeFullV);

    Eigen::Matrix<float, Eigen::Dynamic, 3> aux = m * svd.matrixV();

    // Eigen allocates matrices in column-major
    auto data = aux.data();
    
    // Create polygon
    polygon_type p;
    
    for (decltype(n) i = 0; i < n; ++i) {
        bg::append(p.outer(), planar_point(data[i], data[n + i]));
    }
    // Close
    bg::append(p.outer(), planar_point(data[0], data[n]));
    bg::correct(p);
    
    return p;
  }
  
float polygon_area(const polygon_type& p){
    return bg::area(p);
  }

void negate(point_type &p){
    bg::multiply_value(p,-1);
  }
  
point_type barycenter(const std::vector<point_type>& v){
    point_type res(0,0,0);
    
    if(v.size()>0){
      for (auto it = v.begin(); it != v.end(); ++it){ 
        bg::add_point(res,*it);
      }
      bg::divide_value(res,v.size());
    }
    return res;
}

// Auxiliar function Point in segment
bool point_in_segment(const point_type & p,const segment_type& s){
  point_type v = s.second;
  point_type w = p;
  
  bg::subtract_point(v,s.first);
  bg::subtract_point(w,s.first);
  
  // Same direction and shorter distance
  return (bg::dot_product(v,w) == (norm(v)*norm(w))) && 
         norm(v) >= norm(w);
}

bool in_triangle_border(const triangle_type& t, const point_type& p){
  segment_type aux;
  
  // Check every segment
  
  // BG::within is 2D ignores the third component!
  
  return (point_in_segment(p, segment_type(t[0],t[1])) ||
          point_in_segment(p, segment_type(t[0],t[2])) ||
          point_in_segment(p, segment_type(t[1],t[2])) ||
          equal(p,t[0]) || equal(p,t[1]) || equal(p,t[2]));
}
  
bool is_triangle_vertex(const triangle_type& t, const point_type& p){
  for(auto it = t.begin(); it != t.end(); ++it ){
    if(equal(p,*it)) return true;
  }
  return false;
}

bool within_triangle(const triangle_type& t, const point_type& p){
  // First: Check if the point lies within the same plane
  point_type u = t[1]; // u will be the vector t0-t1
  point_type v = t[2]; // v will be the vector t0-t2
  point_type w = p; // w is t0 - P
  
  bg::subtract_point(u,t[0]);
  //normalize(u);
  bg::subtract_point(v,t[0]);
  //normalize(v);
  bg::subtract_point(w,t[0]);
  
  // n is a normal vector
  point_type n = cross_product(u,v);
  float n_sqnorm = bg::dot_product(n,n);
  
  // If the dot product bw n and w is not 0 -> not in the same plane
  if(bg::dot_product(n,w) != 0) return false;
  else {
    // We are in the same plane - check that we are in the triangle
    // For that we will use barycentric coordinates 
    // Check http://math.stackexchange.com/questions/544946/determine-if-projection-of-3d-point-onto-plane-is-within-a-triangle 
    // for a detailed explanation
    float gamma = bg::dot_product( cross_product(u,w),n) / n_sqnorm;
    float beta = bg::dot_product( cross_product(w,v),n) / n_sqnorm;
    float alpha = 1 - gamma - beta;
    
    return (gamma >= 0 && gamma <= 1) &&
           (beta >= 0 && beta <= 1) &&
           (alpha >= 0 && alpha <= 1);
  }
  
}

/**
   * @brief Computes Triangle-ray intersection with the moller-trumbore algorithm
   * @param t Triangle
   * @param ray_o Ray origin
   * @param ray_v Ray direction (Normalized)
   * @param intersection Output: intersection point
   * @return True if the ray intersects the triangle
   */
  bool triangle_ray_intersection( const triangle_type& t,
                                  const point_type& ray_o,
                                  const point_type& ray_v,
                                  point_type& intersection ){
  point_type e1 = t[1]; // Vector t0-t1
  point_type e2 = t[2]; // vector t0-t2
  
  bg::subtract_point(e1,t[0]);
  bg::subtract_point(e2,t[0]);

  // Cross product bw ray vector and E2 (used to compute the determinant and the u param)
  point_type p = cross_product(ray_v,e2);
  // Determinat near 0 - ray is in the triangle or parallel
  float det = bg::dot_product(e1,p);
  if( det < 1E-6 && det > -(1E-6) ){
    return false;
  } else {
    float inv_det = 1.0/det;
    
    // Vector from V0 to Ray origin
    point_type vec_t = ray_o;
    bg::subtract_point(vec_t,t[0]);
    
    // U param
    float u = bg::dot_product(vec_t,p) * inv_det;
    
    // Intersection outside triangle
    if(u < 0. || u> 1.) return false;
    
    // V parameter
    point_type q = cross_product(vec_t,e1);
    float v = bg::dot_product(ray_v,q) * inv_det;
    
    // Intersection outside triangle
    if( v < 0. || (u+v) > 1.) return false;
    
    float g = bg::dot_product(e2,q) * inv_det;
    if(g > 1E-6){
      // g is the distance 
      intersection = ray_v;
      bg::multiply_value(intersection,g);
      bg::add_point(intersection,ray_o);
      return true;      
    }
    
    // No hit
    return false;
  }
}

// Heron's formula
float triangle_area( const triangle_type& t){
  point_type v0 = t[1];
  point_type v1 = t[2];
  point_type v2 = t[1];
  
  bg::subtract_point(v0, t[0]);
  bg::subtract_point(v1, t[0]);
  bg::subtract_point(v2, t[2]);
  
  // Norms
  float a = norm(v0);
  float b = norm(v1);
  float c = norm(v2);
  
  // Perimeter half 
  float s = (a+b+c) / 2.0;
  // Area (Heron's formula)
  return std::sqrt( s * (s-a) * (s-b) * (s-c));
}

float tetrahedron_volume( const point_type& p0, 
                          const point_type& p1,
                          const point_type& p2,
                          const point_type& p3){

  point_type v0 = p0;
  point_type v1 = p1;
  point_type v2 = p2;
  
  bg::subtract_point(v0,p3);
  bg::subtract_point(v1,p3);
  bg::subtract_point(v2,p3);
  
  return std::abs(bg::dot_product(cross_product(v0,v1),v2)/3.0);
}

// TriangleMesh


TriangleMesh::TriangleMesh()
    : vertices_()
    , faces_(){};


TriangleMesh::TriangleMesh(const face_storage& faces)
    : vertices_()
    , faces_(){
      
      // Add faces
      for(auto it = faces.begin(); it!= faces.end() ; ++it){
        add( (*it)[0],(*it)[1],(*it)[2] );
      }
}

TriangleMesh::~TriangleMesh(){};

TriangleMesh::vertex_iterator TriangleMesh::add(const point_type& p){
  vertex_iterator pos;
  for(pos = begin_vertex(); pos != end_vertex(); ++pos){
    if(distance(*pos,p)<1E-3) return pos;
  }
  
  vertices_.push_back(p);
  return std::prev(vertices_.end(),1);
}


void TriangleMesh::remove(const TriangleMesh::vertex_iterator& v_it){
  // First remove faces
  for(auto it = begin_face(); it != end_face(); ++it){
    if(vertex_of_face(*v_it,*it)){
      it = std::prev( faces_.erase(it), 1);
    }
  }
  // Then remove vertex
  vertices_.erase(v_it);
}


void TriangleMesh::remove(const TriangleMesh::vertex_iterator& b, const TriangleMesh::vertex_iterator& e){
  // FIXME: This can be way more efficient
  for(auto it = b; it != e ; ++it){
    remove(it);
  }
}

void TriangleMesh::clear(){
  faces_.clear();
  vertices_.clear();
}


TriangleMesh::vertex_iterator TriangleMesh::begin_vertex(){
  return vertices_.begin();
}


TriangleMesh::const_vertex_iterator TriangleMesh::begin_vertex() const{
  return vertices_.begin();
}

TriangleMesh::vertex_iterator TriangleMesh::end_vertex(){
  return vertices_.end();
}

TriangleMesh::const_vertex_iterator TriangleMesh::end_vertex() const{
  return vertices_.end();
}


std::size_t TriangleMesh::vertex_count() const{
  return vertices_.size();
}


TriangleMesh::face_iterator TriangleMesh::add(const point_type& v0, const point_type& v1, const point_type& v2){
  point_type v0_p = *add(v0);
  point_type v1_p = *add(v1);
  point_type v2_p = *add(v2);
  // This is a reminder: Adding a element to a vector MAY invalidate other iterators since
  // IT could BE REALLOCATED!!!!
  triangle_type t = {v0_p,v1_p,v2_p};
  faces_.push_back(t);
  return std::prev(faces_.end(),1);
}

TriangleMesh::face_iterator TriangleMesh::add(const triangle_type& t){
  return add(t[0],t[1],t[2]);
}

void TriangleMesh::remove(const TriangleMesh::face_iterator& it){
  faces_.erase(it);
}

void TriangleMesh::remove(const TriangleMesh::face_iterator& b, const TriangleMesh::face_iterator& e){
  for(auto it = b  ;it != e; ++it){
    remove(it);
  }
}

void TriangleMesh::clear_faces(){
  faces_.clear();
}

TriangleMesh::face_iterator TriangleMesh::begin_face(){
    return faces_.begin();
}

TriangleMesh::const_face_iterator TriangleMesh::begin_face() const{
    return faces_.begin();
}

TriangleMesh::face_iterator TriangleMesh::end_face(){
    return faces_.end();
}

TriangleMesh::const_face_iterator TriangleMesh::end_face() const {
    return faces_.end();
}

std::size_t TriangleMesh::face_count() const{
  return faces_.size();
}

/**
 * @brief Using ray-tracing method computes if the point p is Inside the
 * triangular mesh assuming that it is closed
 * @param p Point
 * @return  True if the point is within the mesh
 */
bool TriangleMesh::point_inside(const point_type& p, const point_type& ray_direction) const{
  
  /** Steps:
  *
  *  1. ray with source p and direction 1,0,0 
  *  2. Check intersections with all mesh faces
  *  3. Odd number of intersections - Its inside
  *  
  *  Special cases: 
  *   If the intersection is at the border or at a vertex
  *   of a triangle, only count it once. 
  *  Easy way to go: Count distinct intersection points instead.
  */
  
  // Intersection points
  std::vector<point_type> intersections;
  point_type i_point;
  bool new_point;
  
  for (auto it = begin_face(); it != end_face(); ++it) {
      if(triangle_ray_intersection(*it,
                                     p,
                                     ray_direction,
                                     i_point)){
        // Hit!
        new_point = true;
        
        // Its a new intersection point?
        for(auto ip_it = intersections.begin(); 
            new_point && ip_it != intersections.end(); ++ip_it){
          if( distance(i_point,*ip_it) < 1E-3 )
            new_point = false;
        }
        
        // Add new point
        if (new_point) {
          intersections.push_back(i_point);
        }
      }
  }
  // Return is even
  return (intersections.size() % 2 == 1);
}

point_type TriangleMesh::ray_intersection(const point_type& p, 
                                          const point_type& ray_direction) const {
  point_type i_point;
  for (auto it = begin_face(); it != end_face(); ++it) {
      if(triangle_ray_intersection(*it,
                                     p,
                                     ray_direction,
                                     i_point)){
        return i_point;
      }
  }
  return i_point;
}

/**
 * @brief Aux function that transforms a face to a triangle
 * @param p Face
 * @return Triangle
 */

bool TriangleMesh::vertex_of_face(const TriangleMesh::vertex_type& v, const TriangleMesh::face_type& f){
  return ( equal(v,(f[0])) || equal(v,(f[1])) || equal(v,(f[2])));
}



}  // namespace geoutils
}  // namespace neurostr

std::ostream& operator<<(std::ostream& os,const neurostr::geometry::TriangleMesh& m) {
  
  using namespace neurostr::geometry;
  
  os << "--Mesh--" << std::endl;
  
  os << "\tVertices: " << std::endl ;
  for(auto it = m.begin_vertex(); it != m.end_vertex(); ++it){
    os << "\t\t (" << getx(*it) << ", " << gety(*it) << ", " << getz(*it) << ")" << std::endl;
  }
  
  os << "\tFaces: " << std::endl ;
  for(auto it = m.begin_face(); it != m.end_face(); ++it){
    os << "\t\tFace: " << std::endl ;  
    os << "\t\t\t (" << getx( (*it)[0] ) << ", " << gety((*it)[0]) << ", " << getz((*it)[0]) << ")" << std::endl;
    os << "\t\t\t (" << getx( (*it)[1] ) << ", " << gety((*it)[1]) << ", " << getz((*it)[1]) << ")" << std::endl;
    os << "\t\t\t (" << getx( (*it)[2] ) << ", " << gety((*it)[2]) << ", " << getz((*it)[2]) << ")" << std::endl;
  }
  
  os << "--END Mesh--" << std::endl;
  return os;
}
