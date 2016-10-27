#ifndef NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_
#define NEUROSTR_VALIDATION_PREDEFINED_VALIDATORS_H_

#include <string>

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
                         nv::is_true,
                         "Neurites are attached to soma",
                         "Fails if neurites are not attached to the soma");

// Checks that neuron has soma
const auto neuron_has_soma =
    nv::create_validator(nm::has_soma,
                         nv::is_true,
                         "Neuron has soma",
                         "Pass if the neuron has at least one soma node" );


// Checks that neurite reconstructions are not planar (box volume under the threshold
auto planar_reconstruction_validator_factory(float min) {
  return nv::create_validator( 
                              nm::selectorMeasureCompose(ns::neurite_node_selector, nm::box_volume),
                              nv::range_check_factory(min),
                              "Planar neurite validation",
                              "Fails if the non-axis aligned box volume of the neurite is lower than predefined threshold");
}

auto dendrite_count_validator_factory(unsigned int min, unsigned int max) {
  return nv::create_validator(
                              nm::neuron_dendrite_counter,
                              nv::range_check_factory<unsigned int>(min, max),
                              "Basal dendrite count",
                              "Pass if the dendrite count is greater or equal than " + std::to_string(min) + " and less than " + std::to_string(max));
} 

auto apical_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(1,2),
                              "Strict apical dendrite count",
                              "Pass if and only if there is one apical dendrite");
  } else {
    return nv::create_validator(
                              nm::neuron_apical_counter,
                              nv::range_check_factory<unsigned int>(0,2),
                              "Tolerant apical dendrite count",
                              "Fails if there are two or more apical dendrites");
  } 
}

auto axon_count_validator_factory(bool strict = false) {
  if(strict) {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(1,2),
                              "Strict axon count",
                              "Pass if and only if there is one axon");
  } else {
    return nv::create_validator(
                              nm::neuron_axon_counter,
                              nv::range_check_factory<unsigned int>(0,2),
                              "Tolerant axon count",
                              "Fails if there are two or more axons");
  } 
}

const auto no_trifurcations_validator = nv::create_validator(
                              nm::desc_count,
                              nv::range_check_factory<unsigned int>(0,3),
                              "Trifurcation validator",
                              "Fails on those nodes with more than two descendants"); // Check that each node has a number of descs < 3


auto linear_branches_validator_factory(float min = 1.01) {
    return nv::create_validator(
                         nm::tortuosity,
                         nv::range_check_factory<float>(min),
                         "Linear branch validator",
                         "Fails when the branch tortuosity falls below " + std::to_string(min) );
}

const auto zero_length_segments_validator =
  nv::create_validator(nm::node_length_to_parent,
                       nv::range_check_factory<float>(1E-6),
                       "Zero length segments validator",
                       "Fails when a segment length is close to zero");
                       
const auto radius_length_segments_validator =
  nv::create_validator(nm::node_length_to_parent_border,
                       nv::range_check_factory<float>(1E-6),
                       "Length smaller than radius validator",
                       "Fails when two consecutive node spheres intersection is not empty");
                       
  
const auto increasing_radius_validator =
  nv::create_validator(nm::node_segment_taper_rate_hillman,
                       nv::range_check_factory<float>(0),
                       "Non-decreasing diameter validator",
                       "Fails when diameter increases between two consecutive nodes") ;


const auto segment_collision_validator =
  nv::create_validator(  nm::segment_distance_to_closest,
                         nv::range_check_factory<float>(0.01),
                         "Segment collision validator",
                         "Fails when the distance between any two segments is too close to zero");


auto branch_collision_validator_factory(bool ignore_diams=false){
  return nv::create_validator(  nm::branch_intersects_factory(ignore_diams),
                         nv::empty_string,
                         "Branch collision validator",
                         "Fails when the distance between any two branches is zero");
}

const auto extreme_angles_validator  =
    nv::create_validator(nm::extreme_angle,
                         nv::is_false,
                         "Extreme angles validator",
                         "Fails when either elongation or bifurcation angles are too high to be plausible");

}  // Validation
}  // Neurostr
#endif
