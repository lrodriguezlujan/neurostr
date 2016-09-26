#ifndef NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_
#define NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_

#include "selector/selector.h"

#include "measure/measure.h"
#include "measure/neurite_measure.h"
#include "measure/branch_measure.h"
#include "measure/neuron_measure.h"

#include "validator/checks.h"
#include "validator/validator.h"

namespace neurostr {
namespace validator {

namespace ns = neurostr::selector;
namespace nm = neurostr::measure;
namespace nv = neurostr::validator;

// Checks that neurites are attached to soma
const auto neurites_attached_to_soma =
    nv::create_validator(nm::root_is_soma,
                         nv::is_true);

// Checks that neuron has soma
const auto neuron_has_soma =
    nv::create_validator(nm::has_soma,
                         nv::is_true);


// Checks that neurite reconstructions are not planar (box volume under the threshold
auto planar_reconstruction_validator_factory(float min) {
  return nv::create_validator( 
                              nm::selectorMeasureCompose(ns::neurite_node_selector, nm::box_volume),
                              nv::range_check_factory(min));
}

auto dendrite_count_validator_factory(unsigned int min, unsigned int max) {
  return nv::create_validator(
                              nm::neuron_dendrite_counter,
                              nv::range_check_factory<unsigned int>(min, max));
} 

auto apical_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(1,2));
  } else {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(0,2));
  } 
}

auto axon_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(1,2));
  } else {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(0,2));
  } 
}

const auto no_trifurcations_validator = nv::create_validator(
                              nm::desc_count,
                              nv::range_check_factory<unsigned int>(0,3)); // Check that each node has a number of descs < 3


auto linear_branches_validator_factory(float min = 1.01) {
    return nv::create_validator(
                         nm::tortuosity,
                         nv::range_check_factory<float>(min));
}

const auto zero_length_segments_validator =
  nv::create_validator(nm::node_length_to_parent,
                       nv::range_check_factory<float>(1E-6));
  
const auto increasing_radius_validator =
  nv::create_validator(nm::node_segment_taper_rate_hillman,
                       nv::range_check_factory<float>(0)) ;


const auto segment_collision_validator =
  nv::create_validator(  nm::segment_distance_to_closest,
                         nv::range_check_factory<float>(0.01));


const auto extreme_angles_validator  =
    nv::create_validator(nm::extreme_angle,
                         nv::is_false);

}  // Validation
}  // Neurostr
#endif
