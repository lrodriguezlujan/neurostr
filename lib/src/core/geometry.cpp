#include "core/geometry.h"

namespace neurostr {
namespace geometry {
  
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
  
  void scale(point_type& p, float scale, const point_type&  ref){
    auto tmp = p ; 
    bg::subtract_point(tmp, ref); // tmp is our "vector to scale"
    bg::multiply_value(tmp, scale);
    bg::add_point(tmp, ref);
    p = tmp;
  }
  
  void scale(point_type& p, float rx, float ry, float rz){
    bg::multiply_point(p, point_type(rx,ry,rz));
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
Eigen::Quaternionf align_vectors(const point_type& from, const point_type& to){
  
  namespace bg = boost::geometry;
    
    // Already aligned
    if( geometry::equal(from,to) ) return  Eigen::Quaternionf::Identity();
    
    // Rotation axis (normalized)
    auto axis = geometry::cross_product(from, to);
    
    float angle;
    
    if(geometry::norm(axis) == 0){
        // 180 rotation
        angle = M_PI;
        //axis (any orthogonal vector)
        axis = point_type(-bg::get<1>(from),bg::get<0>(from),0);
    } else {
      normalize(axis);
      // Angle bw dir and to
      angle = geometry::vector_vector_directed_angle(from,to);
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
  else return std::acos(boost::geometry::dot_product(a,b)/(norm(a)*norm(b)));
}

float vector_vector_directed_angle(const point_type&v0 ,const point_type &v1){
  point_type norm_v0 = v0;
  point_type norm_v1 = v1;
  normalize(norm_v0);
  normalize(norm_v1);
  return std::atan2(geometry::norm(geometry::cross_product(norm_v0, norm_v1)), boost::geometry::dot_product(norm_v0, norm_v1));
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

}  // namespace geoutils
}  // namespace neurostr
