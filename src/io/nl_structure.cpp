/**
 * Neurolucida internal structure
 *
 * @author Luis Rodriguez
 *
 */
#include <neurostr/io/nl_structure.h>

namespace neurostr {
namespace io {

std::string tree_type_tostr(const tree_type_cd& t){
  switch (t) {
    case tree_type_cd::AXON:
      return "axon";
    case tree_type_cd::DENDRITE:
      return "dendrite";
    case tree_type_cd::APICAL:
      return "apical";
    case tree_type_cd::SOMA:
      return "soma";
    case tree_type_cd::NONE:
      return "none";
    case tree_type_cd::SAMPLE_CONTOUR:
      return "sample_contour";
    case tree_type_cd::UNKNOWN:
      return "unknown";
    default:
      return "unknown";
  }
}
  
std::ostream& operator<<(std::ostream& os, const tree_type_cd& t) {
  os << tree_type_tostr(t);
  return os;
}

NeuriteType set_neurite_type_by_nlproperties(Neurite& n) {
    auto it = n.properties.find(std::string("type"));
    if (it != n.properties.end()) {
      tree_type_cd tt = boost::any_cast<tree_type_cd>(it->second);
      switch (tt) {
      case tree_type_cd::APICAL:
        n.type(NeuriteType::kApical);
        break;
      case tree_type_cd::AXON:
        n.type(NeuriteType::kAxon);
        break;
      case tree_type_cd::DENDRITE:
        n.type(NeuriteType::kDendrite);
        break;
      default:
        throw std::runtime_error("unexpected tree type code");
      }
    } else {
      // Check keywords
      if (n.properties.exists(std::string("axon"))) {
        n.type(NeuriteType::kAxon);
      } else if (n.properties.exists(std::string("dendrite"))) {
        n.type(NeuriteType::kDendrite);
      } else if (n.properties.exists(std::string("apical"))) {
        n.type(NeuriteType::kApical);
      }
    }
    return n.type();
}


}  // Namespace io
}  // Namespace neurostr
