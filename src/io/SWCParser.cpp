#include <stdexcept>
#include <neurostr/io/SWCParser.h>
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

  reset_errors();
  neuron_ = new Neuron(name);

  while (getline(stream_, line)) {
    process_line_(line);
  }
  
  // Correct neurites (and neuron)
  neuron_->correct();

  // Create reconstruction
  Reconstruction *rec = new Reconstruction(name);
  rec->addNeuron(neuron_) ;
  
  if(error_count > 0){
    NSTR_LOG_(warn, std::to_string(error_count) + 
    " errors were detected while processing the file. Please, check the file and correct the errors.")
  }
  
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
  else{
    try{
      process_data_(s);
    } catch(std::logic_error e){
      process_error(e);
      // Just ignore the line
    }
  }
    
}

void SWCParser::process_header_(const std::string& s) {
  // Remove content till first comment character
  size_t comment_pos = s.find_first_of(comment_char);
  // Extract tokens after comment start
  tokenizer tok{s.begin() + comment_pos + 1, s.end(), sep_};

  if ((tok.begin() != tok.end())) {
    auto it = tok.begin();
    //  skip empty tokens
    while (it != tok.end() && it->size() == 0) ++it;
    // Check if the first token is key
    if (it != tok.end() && is_key(*it)) {
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
  
  std::size_t num_chars;

  // Skip initial empty fields
  while (it->size() == 0) ++it;

  // Read every field
  if (it == tok.end()) 
    throw std::logic_error("Missing fields in line " + s);
  try{
    id = std::stoi(*it,&num_chars);
    if(num_chars != it->size() || id < 0 )
      throw std::logic_error("Id is not a non-negative integer in line "+ s +". Type: " + *it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Id is not numeric in line "+ s +". ID: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    type = std::stoi(*it,&num_chars);
    if(num_chars != it->size() )
      throw std::logic_error("Type is not integer in line "+ s +". Type: " + *it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Type is not numeric in line "+ s +". Type: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    x = std::stof(*it);
  } catch(std::invalid_argument e){
    throw std::logic_error("X value is not numeric in line "+ s +". X: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    y = std::stof(*it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Y value is not numeric in line "+ s +". Y: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    z = std::stof(*it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Z value is not numeric in line "+ s +". Z: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    d = std::stof(*it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Diameter is not numeric in line "+ s +". Diameter: " + *it);
  }
  
  if(d<0){
    throw std::logic_error("Negative diameter value " + std::to_string(d));
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  if (it == tok.end()){
    throw std::logic_error("Missing fields in line " + s);
  }
  try{
    parent = std::stoi(*it,&num_chars);
    if(num_chars != it->size() )
      throw std::logic_error("Type is not integer in line "+ s +". Type: " + *it);
  } catch(std::invalid_argument e){
    throw std::logic_error("Parent is not numeric in line "+ s +". Parent: " + *it);
  }
  
  // Skip empty fields
  while ( (++it)!=tok.end() && it->size() == 0 );
  // Warn if there are extra fields
  if(it != tok.end()){
    ++warn_count;
    NSTR_LOG_(warn,std::string("Extra fields in line ") + s);
  }

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
      last_node_pos_ = neurite->insert_node( neurite->begin_branch(), node);
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
        throw std::logic_error("Oprhan node "+ std::to_string(id) + "- Can't find parent node " + std::to_string(parent) );
      } else {
        // Set branch
        last_node_pos_ = pos.neurite().insert_node(pos, node);
      }
    }
    
  } else {
    // New neurite with root not soma
    Neurite* neurite = new Neurite(neuron_->size() + 1, NeuriteType(type));
    neurite->set_root(); // No root
    last_node_pos_ = neurite->insert_node(neurite->begin_node(), node); // Add node
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
