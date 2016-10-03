#include <stdexcept>
#include "io/SWCParser.h"
#include <algorithm>
#include <string>

namespace neurostr {
namespace io {


SWCParser::SWCParser(std::istream& s) 
  : Parser(s)
  , sep_('\0', ' ', '"')
  , neuron_(nullptr)
  ,last_node_pos_() {
  initialize_property_keys();
}

SWCParser::SWCParser(std::istream& s, const std::string& separators)
    : Parser(s), sep_("", separators, "\""), neuron_(nullptr),last_node_pos_() {
  initialize_property_keys();
};

SWCParser::~SWCParser() {};

// Main function
std::unique_ptr<Reconstruction> SWCParser::read(const std::string& name) {

  std::string line;

  neuron_ = new Neuron(name);

  while (getline(stream_, line)) {
    process_line_(line);
  }
  
  // Correct neurites (and neuron)
  neuron_->correct();

  // Create reconstruction
  Reconstruction *rec = new Reconstruction(name);
  rec->addNeuron(neuron_) ;
  
  // Transfer rec. ownership
  return std::unique_ptr<Reconstruction>(rec);
}

// Properties management
bool SWCParser::is_key(const std::string& s) const {
  std::string tmp = s;
  // to lower
  std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
  return property_keys_.find(tmp) != property_keys_.end();
}

void SWCParser::add_property_key(const std::string& s) {
  std::string tmp = s;
  // to lower
  std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
  property_keys_.insert(tmp);
}

void SWCParser::remove_property_key(const std::string& s) {
  std::string tmp = s;
  // to lower
  std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
  property_keys_.erase(tmp);
}

const std::set<std::string>& SWCParser::get_property_keys() const { return property_keys_; }

void SWCParser::initialize_property_keys() {
  property_keys_ = {"original_source",      "creature",       "region",       "field", "layer",  "field/layer",
                    "type",                 "contributor",    "reference",    "raw",   "extras", "soma_area",
                    "shrinkage_correction", "version_number", "version_date", "scale"};
}

void SWCParser::process_line_(const std::string& s) {
  // Decide bw header and data
  if (is_headerline(s))
    process_header_(s);
  else
    process_data_(s);
}

void SWCParser::process_header_(const std::string& s) {
  // Remove content till first comment character
  size_t comment_pos = s.find_first_of(comment_char);
  // Extract tokens after comment start
  tokenizer tok{s.begin() + comment_pos + 1, s.end(), sep_};

  if ((tok.begin() != tok.end())) {
    auto it = tok.begin();
    //  skip empty tokens
    while (it->size() == 0) ++it;
    // Check if the first token is key
    if (is_key(*it)) {
      std::string key = *it, val;
      while (++it != tok.end()) val += *it;
      neuron_->add_property(key, val);  // Add metadata :)
    }
  }
}

void SWCParser::process_data_(const std::string& s) {
  tokenizer tok{s, sep_};

  auto it = tok.begin();
  int id, type, parent;
  float x, y, z, d;

  // Skip initial empty fields
  while (it->size() == 0) ++it;

  // Read every field
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  id = std::stoi(*it);
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  type = std::stoi(*(++it));
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  x = std::stof(*(++it));
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  y = std::stof(*(++it));
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  z = std::stof(*(++it));
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  d = std::stof(*(++it));
  if (it == tok.end()) throw std::runtime_error("Missing data fields");
  parent = std::stoi(*(++it));

  // Create node
  Node node{id, x, y, z, d / 2.0};

  if (NeuriteType(type) == NeuriteType::kSoma) {
    neuron_->add_soma(node);
  } else if (parent != -1) {
    // Parent in soma
    auto soma_pos = neuron_->find_soma(parent);
    if (soma_pos != neuron_->end_soma()) {
      
      // Parent is soma -> new neurite with soma root
      Neurite* neurite(new Neurite(neuron_->size() + 1, NeuriteType(type)));
      // Create a branch with root given parent
      neurite->set_root(*soma_pos);
      last_node_pos_ = neurite->insert_node( neurite->begin_node(), node);
      neuron_->add_neurite(neurite);
      
    } else {
      Neurite::base_node_iterator pos;
      // Find parent node
      if(last_node_pos_->id() == parent){
        pos = last_node_pos_;
      } else{
        pos = neuron_->find(parent);
      }
      if (pos.begin() == pos.end()) {
        throw std::runtime_error("Oprhan node");
      } else {
        // Set branch
        last_node_pos_ = pos.neurite().insert_node(pos, node);
      }
    }
    
  } else {
    // New neurite with root not soma
    Neurite* neurite = new Neurite(neuron_->size() + 1, NeuriteType(type));
    neurite->set_root(); // No root
    last_node_pos_ = neurite->insert_node(-1, node); // Add node
    neuron_->add_neurite(neurite);
  }
}

bool SWCParser::is_headerline(const std::string& s) const {
  for (auto it = s.begin(); it != s.end(); it++) {
    if (!isspace(*it)) {
      if (*it == comment_char)
        return true;
      else
        return false;
    }
  }
  return true;
}

}  // Namespace io
}  // namespace neurostr
