#include "core/neurite_type.h"

namespace neurostr{
  
std::ostream& operator<<(std::ostream& os, const neurostr::NeuriteType& t) {
  switch (t) {
  case neurostr::NeuriteType::kUndefined:
    os << "undefined";
    break;
  case neurostr::NeuriteType::kSoma:
    os << "soma";
    break;
  case neurostr::NeuriteType::kAxon:
    os << "axon";
    break;
  case neurostr::NeuriteType::kDendrite:
    os << "dendrite";
    break;
  case neurostr::NeuriteType::kApical:
    os << "apical";
    break;
  case neurostr::NeuriteType::kOther:
    os << "other";
    break;
  }
  return os;
}

}
