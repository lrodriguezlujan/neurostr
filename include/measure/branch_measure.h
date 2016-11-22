#ifndef NEUROSTR_MEASURE_BRANCH_MEASURE_H_
#define NEUROSTR_MEASURE_BRANCH_MEASURE_H_

// Function minimization
#include <boost/math/tools/minima.hpp>

#include "core/log.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

#include "measure/measure_operations.h"
#include "measure/node_measure.h"

#include "selector/selector.h"
#include "selector/node_selector.h"
#include "selector/neurite_selector.h"

namespace neurostr {
  
namespace measure {
  

const auto taper_rate_hillman = [](const Branch& b) -> float {
  
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  if(b.has_root())
    return (b.root().radius() - b.last().radius())/b.root().radius();
  else 
    return (b.first().radius() - b.last().radius())/b.first().radius();
};

const auto taper_rate_burker = [](const Branch& b) -> float {
  
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  float dist ;
  if(b.has_root()){
    
    dist = b.root().distance(b.last());
    if(dist == 0.0) return 0;
    else return 2*(b.root().radius() - b.last().radius())/dist;
    
  } else {
    
    dist = b.first().distance(b.last());
    if(dist == 0.0) return 0;
    else return 2*(b.first().radius() - b.last().radius())/b.first().distance(b.last());
  }
};

const auto tortuosity = [](const Branch& b) -> float {
  
  // Check empty branch
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  float total_length = 0;

  // Compute length
  
  // Add distance to root if it exists
  if (b.has_root()) total_length += b.begin()->distance(b.root());
  
  // Branch length
  for (auto it = ++(b.begin()); it != b.end(); ++it) {
    total_length+=(it->distance(*(it - 1)));
  }

  // divided by the shortest length
  float d;
  if (b.has_root()){
    d = b.last().distance(b.root());
  } else {
    d =  b.first().distance(b.last());
  }
  
  if(d == 0) return 1.;
  else return total_length / d;
};

const auto branch_azimuth = [](const Branch& b) -> float {
  
  return 0.0; // TODO  
};

const auto branch_size = [](const Branch &b) -> int {
  return b.size();
};

const auto branch_director_vector = [](const Branch& b) -> point_type {
  // TODO
  return point_type();
};

const auto branch_index = [](const Branch& b) -> unsigned int {
    auto it = b.neurite().find(b);
    return b.neurite().index(Neurite::sibling_iterator(it));
};

const auto branch_order = [](const Branch &b) -> int {
  return b.order();
};

const auto child_diam_ratio = [](const Branch& b) -> float {
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  auto it = b.neurite().find(b);
  
  if(it.number_of_children() < 2){
    return 0;
  } else {
    auto cit = b.neurite().begin_children(it);
    float r1 = cit->first().radius();
    ++it;
    if(r1 == 0.0 && cit->first().radius() == 0.0)
      return 0.0;
    return r1/cit->first().radius();
  }
};

const auto parent_child_diam_ratio = [](const Branch& b) -> std::pair<float,float> {
  auto it = b.neurite().find(b);
  
  if(it.number_of_children() < 2){
    return std::pair<float,float>(0,0);
  } else {
    auto cit = b.neurite().begin_children(it);
    float r1 = cit->first().radius()/b.last().radius();
    ++it;
    return std::pair<float,float>( r1 , cit->first().radius()/b.last().radius() );
  }
};

const auto partition_asymmetry = [](const Branch& b) -> float {
  
  auto it = b.neurite().find(b);
  
  if(it.number_of_children() < 2){
    return -1;
  } else {
    auto cit = b.neurite().begin_children(it);
    auto n1 = std::distance(b.neurite().begin_leaf(cit),b.neurite().end_leaf(cit));
    ++cit;
    auto n2 = std::distance(b.neurite().begin_leaf(cit),b.neurite().end_leaf(cit));
   
   if(n1 == 0) n1 = 1;
   if(n2 == 0) n2 = 1;
    
    if(n1 == n2) return 0;
    else return std::abs(n1 - n2) / (n1 + n2 - 2);
  }
};

static inline auto rall_power_fit_factory(float min = 0 , float max = 5){
  return [min_ = min, max_ = max](const Branch &b) -> float {
    
     auto it = b.neurite().find(b);
    if(it.number_of_children() < 2){
      return -1;
    } else {
      
      // Get diams
      float dp = b.last().radius()*2;
      auto cit = b.neurite().begin_children(it);
      float da = cit->first().radius()*2;
      float db = (++cit)->first().radius()*2;
      
      // Number of bits to work with
      int bits = std::numeric_limits<float>::digits;
      
      // Create function to minimize
      auto aux_fun = [p_ = dp, a_ = da, b_ = db](float r) -> float {
        return std::pow(std::pow(p_,r) - std::pow(a_,r) - std::pow(b_,r) ,2);
      };
      
      // Call minimizer
      std::pair<float,float> ret = boost::math::tools::brent_find_minima(aux_fun, 
                                                                         min_, 
                                                                         max_, 
                                                                         bits);
      return ret.first;
    }
  };
};

static inline auto pk_factory(float r){
  return [r_ = r](const Branch &b) -> float {
    auto it = b.neurite().find(b);
    if(it.number_of_children() < 2){
      return -1;
    } else {
      
      // Get diams
      float dp = b.last().radius()*2;
      auto cit = b.neurite().begin_children(it);
      float da = cit->first().radius()*2;
      float db = (++cit)->first().radius()*2;
      
      return (std::pow(da,r_) + std::pow(db,r_))/std::pow(dp,r_);
    }
  };
};

static inline auto pk_fit_factory(float min = 0 , float max = 5){
  return [min_ = min, max_ = max](const Branch &b) -> float {
    float r = rall_power_fit_factory(min_,max_)(b);
    auto it = b.neurite().find(b);
    if(it.number_of_children() < 2){
      return -1;
    } else {
      
      // Get diams
      float dp = b.last().radius()*2;
      auto cit = b.neurite().begin_children(it);
      float da = cit->first().radius()*2;
      float db = (++cit)->first().radius()*2;
      
      return (std::pow(da,r) + std::pow(db,r))/std::pow(dp,r);
    }
  };
};

const auto hillman_threshold = [](const Branch &b) -> float {

  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    
    auto cit_a = b.neurite().begin_children(it);
    auto cit_b = cit_a; 
    ++cit_b;
    
    // Not a terminal branch
    if(cit_a.number_of_children() != 0 && cit_b.number_of_children() != 0 ){
      return -1;
    } else {
      // 50% of father rad + 25% of daught. radius
      return b.last().radius() + (cit_a->first().radius() + cit_b->first().radius())/2.;
    }
  }
};

const auto local_bifurcation_angle = [](const Branch &b) -> float {
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    auto cit_a = b.neurite().begin_children(it);
    auto cit_b = cit_a; 
    ++cit_b;
    
    auto ret = geometry::vector_vector_angle(b.last().vectorTo(cit_a->first()), 
                                         b.last().vectorTo(cit_b->first()));
    if (std::isnan(ret)){
      geometry::vector_vector_angle(b.last().vectorTo(cit_a->first()), 
                                         b.last().vectorTo(cit_b->first()));
    }
    return ret;
  }
};


const auto remote_bifurcation_angle = [](const Branch &b) -> float {
  
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    auto cit_a = b.neurite().begin_children(it);
    auto cit_b = cit_a; 
    ++cit_b;
    
    return geometry::vector_vector_angle(b.last().vectorTo(cit_a->last()), 
                                         b.last().vectorTo(cit_b->last()));
  }
};

const auto local_tilt_angle = [](const Branch &b) -> float {
  
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    
    point_type v = b.director_vector();

    auto cit_a = b.neurite().begin_children(it);
    auto cit_b = cit_a; 
    ++cit_b;
    
    float v_a = geometry::vector_vector_angle(v, b.last().vectorTo(cit_a->first()));
    float v_b = geometry::vector_vector_angle(v, b.last().vectorTo(cit_b->first()));
    
    return (v_a<v_b)? v_a : v_b;
  }
};

const auto remote_tilt_angle = [](const Branch &b) -> float {
  
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return 0;
  } else {
    point_type v;
    if(b.has_root())
      v=b.root().vectorTo(b.last());
    else
      v = b.first().vectorTo(b.last());
      
    auto cit_a = b.neurite().begin_children(it);
    auto cit_b = cit_a; 
    ++cit_b;
    
    float v_a = geometry::vector_vector_angle(v, b.last().vectorTo(cit_a->last()));
    float v_b = geometry::vector_vector_angle(v, b.last().vectorTo(cit_b->last()));
    return (v_a<v_b)? v_a : v_b;
  }
};

const auto local_plane_vector = [](const Branch &b) -> point_type {
    
    if(b.size() == 0 ){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return point_type();
    } else if (!b.has_root()){
      NSTR_LOG_(warn, std::string("Unrooted branch ") + b.idString() );
      return point_type();
    }
  
    auto it = b.neurite().find(b);
    
    // Our vector
    auto v = b.root().vectorTo(b.first());
  
    // Check if we have siblings
    if(it.node->prev_sibling == nullptr){
      if(it.node->next_sibling == nullptr){
        return point_type();
      } else {
        
        if( !it.node->next_sibling->data.has_root() ){
          NSTR_LOG_(warn, std::string("Unrooted sibling branch ") + b.idString() );
          return point_type();
        } else if (it.node->next_sibling->data.size() == 0){
          NSTR_LOG_(warn, std::string("Empty sibling branch ") + b.idString() );
          return point_type();
        }
        
        return geometry::cross_product(v,
        it.node->next_sibling->data.root().vectorTo(it.node->next_sibling->data.first()));
      }
    } else {
      
      if( !it.node->prev_sibling->data.has_root() ){
          NSTR_LOG_(warn, std::string("Unrooted sibling branch ") + b.idString() );
          return point_type();
      } else if (it.node->prev_sibling->data.size() == 0){
          NSTR_LOG_(warn, std::string("Empty sibling branch ") + b.idString() );
          return point_type();
      }
      
      return geometry::cross_product(v,
        it.node->prev_sibling->data.root().vectorTo(it.node->prev_sibling->data.first()));
    }
};

const auto remote_plane_vector = [](const Branch &b) -> point_type {
    if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return point_type();
    } else if (!b.has_root()){
      NSTR_LOG_(warn, std::string("Unrooted branch ") + b.idString() );
      return point_type();
    }
  
    auto it = b.neurite().find(b);
    
    // Our vector
    auto v = b.root().vectorTo(b.last());
  
    // Check if we have siblings
    if(it.node->prev_sibling == nullptr){
      if(it.node->next_sibling == nullptr){
        return point_type();
      } else {
        
        if( !it.node->next_sibling->data.has_root() ){
          NSTR_LOG_(warn, std::string("Unrooted sibling branch ") + b.idString() );
          return point_type();
        } else if (it.node->next_sibling->data.size() == 0){
          NSTR_LOG_(warn, std::string("Empty sibling branch ") + b.idString() );
          return point_type();
        }
        
        return geometry::cross_product(v,
        it.node->next_sibling->data.root().vectorTo(it.node->next_sibling->data.last()));
      }
    } else {
      
      if( !it.node->prev_sibling->data.has_root() ){
          NSTR_LOG_(warn, std::string("Unrooted sibling branch ") + b.idString() );
          return point_type();
        } else if (it.node->prev_sibling->data.size() == 0){
          NSTR_LOG_(warn, std::string("Empty sibling branch ") + b.idString() );
          return point_type();
        }
      
      return geometry::cross_product(v,
        it.node->prev_sibling->data.root().vectorTo(it.node->prev_sibling->data.last()));
    }
};

const auto local_torque_angle = [](const Branch &b) -> float {
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  } else if(b.order() == 0){
    // Cannot be computed for the root branch
    NSTR_LOG_(info, "Torque angle cannot be computed for the root branch");
    return 0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    
    // Our vector
    auto b_n = local_plane_vector(b);
    
    // Child vector
    auto c_n = local_plane_vector(*(b.neurite().begin_children(it)) );
    
    return geometry::vector_vector_angle(b_n,c_n);
  }
};

const auto remote_torque_angle = [](const Branch &b) -> float {
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  } else if(b.order() == 0){
    NSTR_LOG_(info, "Torque angle cannot be computed for the root branch");
    return 0;
  }
  
  auto it = b.neurite().find(b);
  if(it.number_of_children() < 2){
    return -1;
  } else {
    
    // Our vector
    auto b_n = remote_plane_vector(b);
    
    // Child vector
    auto c_n = remote_plane_vector(*(b.neurite().begin_children(it)) );
    
    return geometry::vector_vector_angle(b_n,c_n);
  }
};

const auto branch_length = [](const Branch &b) -> float {
  if(b.size() == 0){
      NSTR_LOG_(warn, std::string("Empty branch measure ") + b.idString() );
      return 0.0;
  }
  
  float len = b.has_root()?b.first().distance(b.root()):0.;
  for(auto it = (b.begin()+1) ; it != b.end() ; ++it ){
    len += it->distance( *(it-1) );
  }
  return len;
};

static inline auto branch_intersects_factory(bool ignore_radius = false){
 
  return [_ign = ignore_radius](const Branch &b ) -> std::string {
 
    // First get neuron 
    if(b.valid_neurite() ){
      const Neuron& n = b.neurite().neuron();
      box_type bbox_b = b.boundingBox();
    
      for(auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
        for(auto bit = it->begin_branch(); bit != it->end_branch(); ++bit){

          // If their bounding boxes intersect
          if(*bit != b){
            if(geometry::box_box_intersection(bbox_b,bit->boundingBox()) ){
              if(b.distance(*bit,_ign) == 0.0){
                return bit->idString()+" @ Neurite: "+std::to_string(bit->neurite().id());
              }
            }
          }
        }
      }
    }
    return std::string();
  };
}// Factory

} // measure
} // neurostr

#endif
