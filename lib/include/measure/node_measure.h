#ifndef NEUROSTR_MEASURE_NODE_MEASURE_H_
#define NEUROSTR_MEASURE_NODE_MEASURE_H_

#include <Eigen/Dense>
#include <Eigen/SVD>

#include "core/node.h"

#include "measure/measure_operations.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/neuron_selector.h"

namespace neurostr {
namespace measure {

  using node_iterator = typename std::vector<selector::node_reference>::iterator;
  using const_node_iterator = typename std::vector<selector::const_node_reference>::iterator;
/** Get node properties */  

const auto node_x = [](const Node& n) -> float {
  return n.x();
};

const auto node_y = [](const Node& n) -> float {
  return n.y();
};

const auto node_z = [](const Node& n) -> float {
  return n.z();
};

const auto node_radius = [](const Node& n) -> float {
  return n.radius();
};

const auto node_diameter = [](const Node& n) -> float {
  return n.radius()*2;
};

const auto node_diameter_pow = [](const Node& n) -> float {
  return std::pow(n.radius()*2,1.5);
};

const auto node_order = [](const Node& n) -> int {
  return n.branch().order();
};

/* Parent-related measures */

// Get node length to parent
const auto node_length_to_parent = [](const Node& n) -> float {
  const Node& parent = selector::node_parent(n);
  //if( parent == n ) return NAN;
  return n.distance(parent);
};

const auto node_length_to_parent_border = [](const Node& n) -> float {
  const Node& parent = selector::node_parent(n);
  //if( parent == n ) return NAN;
  return n.distance(parent) - (parent.radius() + n.radius());
};

// Node compartment volume
const auto node_volume = [](const Node& n) -> float {
  const float pi = boost::math::constants::pi<float>();
  const Node& parent = selector::node_parent(n);
  
  float pr = parent.radius();
  float nr = n.radius();
  
  // Truncated cone volume
  return pi/3. * (pr*pr + pr*nr + nr*nr) * n.distance(parent) ;
};

// Hillman tapper rate
const auto node_segment_taper_rate_hillman = [](const Node &n) -> float {
  const Node& parent = selector::node_parent(n);
  if(parent.radius() == 0){
    if(n.radius() == 0) return 0;
    else return std::numeric_limits<float>::min();
  } else {
    return (parent.radius() - n.radius())/parent.radius();
  }
};

// Burker taper rate
const auto node_segment_taper_rate_burker = [](const Node &n) -> float {
  const Node& parent = selector::node_parent(n);
  return (parent.radius() - n.radius())/ n.distance(parent);
};

const auto node_compartment_surface = [](const Node &n) -> float {
  const Node& parent = selector::node_parent(n);
  // Lat. length
  float s = std::sqrt( 
              std::pow(n.distance(parent),2) + 
              std::pow((parent.radius()-n.radius()),2));
              
  return M_PI * (parent.radius()+n.radius()) * s;
};

// Average section area
const auto node_compartment_section_area = [](const Node &n) -> float {
  const Node& parent = selector::node_parent(n);
  return M_PI * std::pow( ((parent.radius()+n.radius())/2.),2);
};

// Get distance to root
const auto node_distance_to_root = [](const Node& n) -> float {
  if(n.branch().neurite().has_root())
    return n.distance(n.branch().neurite().root());
  else 
    return n.distance(*(n.branch().neurite().begin_node()));
};

const auto node_distance_to_soma = [](const Node& n) -> float {
  
  Neuron& neuron = n.branch().neurite().neuron();
  
  if (!(neuron.has_soma())) return n.distance(point_type(0, 0, 0));

  float mindist = std::numeric_limits<float>::max();
  float aux;

  for (auto it = neuron.begin_soma(); it != neuron.end_soma(); ++it) {
    aux = n.distance(*it);
    if (aux < mindist) mindist = aux;
  }
  return mindist;
};

// Get path to root
const auto node_path_to_root = [](const Node& n) -> float {
  
  // Select all nodes in the path to the root
  auto sel = selector::node_stem_selector(n);
  float dist = 0;
  
  for (auto it = (sel.begin()+1); it != sel.end(); ++it) {
    dist += it->get().distance( (it-1)->get() );
  }
  return dist;
};

// number of descends.
const auto desc_count = [](const Node& n) -> unsigned int {
  return selector::node_descendants(n).size();
};

// Minimum box volume
const auto box_volume = [](const const_node_iterator& b,
                           const const_node_iterator& e) -> double {

  // Create nx3 matrix
  Eigen::Matrix<double, Eigen::Dynamic, 3> m;
  auto n = std::distance(b, e);
  m.resize(n, 3);

  int i = 0;
  for (auto it = b; it != e; ++it, ++i) {
    m(i, 0) = node_x(it->get());
    m(i, 1) = node_y(it->get());
    m(i, 2) = node_z(it->get());
  }

  // Then perform jacobisvd
  Eigen::JacobiSVD<decltype(m)> svd(m, Eigen::ComputeFullV);

  Eigen::Matrix<double, Eigen::Dynamic, 3> aux = m * svd.matrixV();

  // Eigen allocates matrices in column-major
  double vol = 1;
  auto data = aux.data();
  for (int i = 0; i < 3; ++i) {
    double minv = std::numeric_limits<double>::max();
    double maxv = std::numeric_limits<double>::min();
    int tmp = n * i;
    for (int j = 0; j < n; ++j) {
      if (data[tmp + j] > maxv) maxv = data[tmp + j];
      if (data[tmp + j] < minv) minv = data[tmp + j];
    }
    // Add to volume
    vol *= (maxv - minv);
  }
  return vol;
};

const auto node_parent_vector = [](const Node& n) -> point_type {
  
  const Node& parent = selector::node_parent(n);
  auto v = n.vectorTo(parent);
  
  geometry::normalize(v); 

  return v;
};

// Bifurcation angle
 const auto node_local_bifurcation_angle = [](const Node& n) -> float {
  auto descs = selector::node_descendants(n);
  if (descs.size() < 2)
    return 0;
  else {
    point_type v1 = descs[0].get().position();
    point_type v2 = descs[1].get().position();

    return geometry::vector_vector_angle(n.vectorTo(v1), n.vectorTo(v2));
  }
};

// Elongation angle
const auto node_local_elongation_angle = [](const Node& n) -> float {

  auto descs = selector::node_descendants(n);
  if (descs.size() != 1) return 0;

  const Node& parent = selector::node_parent(n);
  if (parent == n) return 0;

  auto v0 = parent.vectorTo(n);
  auto v1 = n.vectorTo(descs[0].get());

  return geometry::vector_vector_directed_angle(v0,v1, n.branch().neurite().neuron().up());
};

// Extreme angle
const auto extreme_angle = [](const Node& n) -> bool {

  auto descs = selector::node_descendants(n);
  if (descs.size() == 0) return false;

  const Node& parent = selector::node_parent(n);
  if (parent == n) return false;

  auto v0 = parent.vectorTo(n);
  auto l0 = parent.distance(n);
  
  float angle, length;
  for (auto desc = descs.begin(); desc != descs.end(); ++desc) {
    auto v1 = n.vectorTo(desc->get().position());
    auto l1 = n.distance(desc->get().position());
    
    angle = geometry::vector_vector_directed_angle(v0,v1);
    length = l0 + l1;
    
    if (std::abs(angle) > (2 * std::sqrt(length * 1E-6) / 4.732E-4)) return true;
  }
  return false;
};

// Orientation
const auto node_local_orientation = [](const Node& n) -> std::pair<float, float> {
  const Node& parent = selector::node_parent(n);
  if (parent == n)
    return std::pair<float, float>(0, 0);
  else {
    // Get parent local basis
    auto basis = parent.local_basis(selector::node_parent(parent), n.branch().neurite().neuron().up());

    // Our vector
    auto pos = parent.vectorTo(n);

    return geometry::local_orientation(pos, basis);
  }
};

const auto node_in_terminal_segment = [](const Node& n) -> bool {
  auto it = n.branch().neurite().find(n.branch());
  return it.number_of_children() == 0;
};

//FIXME
/*static inline auto nodeset_avg_orientation(const point_type& ref){
 return [=](const std::vector<node_reference>::iterator& b, const std::vector<node_reference>::iterator& e) -> point_type {
  point_type tmp;
  point_type acum(0,0,0);
  
  for(auto it = b; it != e ; ++it){
    tmp = (*it)->position();
    boost::geometry::subtract_point(tmp,ref);
    boost::geometry::divide_value(tmp,geometry::norm(tmp)); // Normalize
    boost::geometry::add_point(acum,tmp);
    boost::geometry::divide_value(acum,geometry::norm(acum)); // Normalize
  }
  
  return acum;
 };
}
*/


const auto segment_distance_to_closest = [](const Node& n) -> float {
  
  // Get parent and create the segmnet
  auto parent = selector::node_parent(n);

  float mindist = std::numeric_limits<float>::max();
  float aux;

  if (n == parent)
    return std::numeric_limits<float>::max();
  else {
    // Select every node in the neuron
    auto sel = selector::neuron_node_selector(n.branch().neurite().neuron());
    for (auto noderef_it = sel.begin(); noderef_it != sel.end(); ++noderef_it) {
      // Get noderef parent node
      auto node_parent = selector::node_parent(noderef_it->get());
      // This is: nd has parent, nd is not i or his parent, and i is not the parent of nd
      if ( (noderef_it->get()) != n && (noderef_it->get()) != parent && (noderef_it->get()) != node_parent  && node_parent != n ){
        // Same parent -> return 0 if same position
        if( node_parent == parent ) {
            if (noderef_it->get().distance(n) == 0 )
              return 0;
        } else {
          
          aux = geometry::segment_segment_distance(parent.position(), n.position(), node_parent.position(), noderef_it->get().position());
          
          // Real distance is ....
          aux = std::max( 0.0 , aux - (parent.radius() + n.radius() + (noderef_it->get()).radius() + node_parent.radius())/2.0 );
          
          if(aux == 0) return 0;
          else if(aux < mindist) mindist = aux;
        }
      }
    }
    return mindist;
  }
};

const auto node_set_fractal_dim = [](const const_node_iterator& b, 
                                     const const_node_iterator& e) -> float{
  
  float euc,path;
  float top_sum = 0;
  float bot_sum = 0;
  
  for(auto it = b ; it != e ; ++it){
    euc = node_distance_to_root(it->get());
    path = node_path_to_root(it->get());
    top_sum += std::log(1+euc)*std::log(1+path);
    bot_sum += std::pow(std::log(1+euc),2);
  }
  
  if(top_sum == bot_sum) return 1.0;
  else return top_sum/bot_sum;
                                       
};

} // Measure ns
} // Neurostr ns

#endif

