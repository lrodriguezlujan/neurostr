/**
 * Read neurolucida DAT format
 *
 * Specs from http://www.neuronland.org/NLMorphologyConverter/MorphologyFormats/NeurolucidaDAT/Spec.html Not official so
 *it can vary
 *
 * @author Luis Rodriguez
 *
 */

#include "io/DATParser.h"
#include "io/basen.hpp"

#include <stdexcept>
#include <cstring>

namespace neurostr {
namespace io {

const std::uint8_t DATParser::header[DATParser::header_size] = {
    0x04, 0x56, 0x33, 0x20, 0x44, 0x41, 0x54, 0x20, 0x66, 0x69, 0x6C, 0x65, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,   0, 0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0, 0, 0, 0, 0,    0,   0, 0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 0, 0, 0, 0, 0, 0, 0, 0x2B, 0xAD};
const std::uint32_t DATParser::footer = 0xAABBCCDD;

/***** PUBLIC METHODS **/
std::unique_ptr<Reconstruction> DATParser::read(const std::string &name) {
  // Check header
  if (!valid_header()) throw std::runtime_error("Stream header is not valid");

  node_count_ = 0;
  reset_errors();

  // Root block
  Reconstruction *r = new Reconstruction(name);
  try{
    while (read_next_block_() > 0) {
      process_block_(*r);
    }
  } catch (std::exception e){
    // Any error at this point is critical
    NSTR_LOG_(critical, e.what());
    // Mark as such
    critical_error = true;
    ++error_count;
  }
  
  // Reset header check
  checked_header_ = false;
  valid_header_ = false;
  
    // Correct neuron
  /*for (auto it = r->begin(); it != r->end(); ++it) {
    it->correct();
    //for (auto neur_it = (*it)->begin_neurite(); neur_it != (*it)->end_neurite(); ++neur_it)
    //  (*neur_it)->correct();
  }*/
  
  if(error_count > 0){
    NSTR_LOG_(warn, std::to_string(error_count) + " errors were detected while processing the file. Please, send us an email with the conflicting file attached to solve the issue ASAP.")
  }

  return std::unique_ptr<Reconstruction>(r);
}

bool DATParser::valid_header() {
  if (!checked_header_)
    return check_header_();
  else
    return valid_header_;
}

/***** PROTECTED METHODS ***/

// PROCESS STRING BLOCK
std::string DATParser::process_string(std::size_t len) {
  std::string s;
  s.assign((char *)(buffer_head_), len);
  buffer_head_ += len;
  return s;
}

// PROCESS SAMPLE BLOCK
Node DATParser::process_sample() {
  // Create node with addecuate id
  Node n(node_count_++);

  // Set position
  point_type p(((float *)buffer_head_)[0], ((float *)buffer_head_)[1], ((float *)buffer_head_)[2]);
  n.position(p);

  // Set diameter/rad
  n.radius(((float *)buffer_head_)[3] / 2.);

  // Advance buffer head
  buffer_head_ += sizeof(float) * 4;

  // Skip section
  buffer_head_ += sizeof(std::uint16_t);

  // C++11 ensures that this is efficient. is moved not copied =)
  return n;
}

marker_type DATParser::process_markerset() {
  
  marker_type m;
  size_t len;

  // Process header and get property name
  if(ensure_buffer_size_(block_header_size)){
    NSTR_LOG_(warn,"Expanding buffer in markerset name header");
    ++warn_count;
  }
  len = process_block_header_();
  if(ensure_buffer_size_(len)){
    NSTR_LOG_(warn,"Expanding buffer in markerset block name");
    ++warn_count;
  }

  if (type_in_buffer_ != block_type::STRING){
    throw std::logic_error("Malformed markerset block - Missing name block");  
  }
  
  m.name = process_string(len);
  std::transform(m.name.begin(), m.name.end(), m.name.begin(), ::tolower);  // Keys are lowecase always
  
  // Copy color values (RGBA)
  for(int i = 0; i < 4 ; ++i){
    m.color[i] = buffer_head_[i];
  }
  buffer_head_ += 4;
  
  // Process proplist
  if(empty()){
    NSTR_LOG_(warn,"Reading header after block end in markerset block");
    ++warn_count;
    ensure_buffer_size_(block_header_size);
  }
    
  len = process_block_header_();
  if(ensure_buffer_size_(len)){
    NSTR_LOG_(warn, "Expanding buffer in markerset block property list ");
    ++warn_count;
  }
  
  if (type_in_buffer_ != block_type::PROPERTY_LIST) {
    throw std::logic_error("Malformed markerset block - Expected property list block");  
  }
  m.properties = process_proplist_();
  
  // Process sample list
  if(empty()){
    NSTR_LOG_(warn,"Reading block after block end in markerset block");
    ++warn_count;
    ensure_buffer_size_(block_header_size);
  }
    
  len = process_block_header_();
  if(ensure_buffer_size_(len)){
    NSTR_LOG_(warn, "Expanding buffer in markerset block sample list ");
    ++warn_count;
  }
  
  if (type_in_buffer_ != block_type::SAMPLE_LIST){
    throw std::logic_error("Malformed markerset block - Expected sample list block");  
  }
  
  try{
    m.samples = process_samplelist_();
  } catch(std::logic_error e){
    process_error(e);
    skip_block();
  }
    
  return m;
}

// PROCESS PROPERTY
PropertyMap::property_type DATParser::process_property() {

  std::string key;
  size_t len;

  // Process header and get property name
  if(ensure_buffer_size_(block_header_size)){
    NSTR_LOG_(warn, "Expanding buffer in property name header");
    ++warn_count;
  }
  len = process_block_header_();
  
  if(ensure_buffer_size_(len)){
    NSTR_LOG_(warn, "Expanding buffer in markerset name ");
    ++warn_count;
  }
  
  if (type_in_buffer_ != block_type::STRING){
    throw std::logic_error("Malformed property block - Missing name block");
  }
  
  key = process_string(len);
  std::transform(key.begin(), key.end(), key.begin(), ::tolower);  // Keys are lowecase always

  // Read intermediate numbers
  bool has_value = static_cast<bool>(((std::uint16_t *)(buffer_head_))[0]);
  buffer_head_ += sizeof(std::uint16_t);

  if (empty() || !has_value) {
    return PropertyMap::property_type(key, boost::any());
  }

  bool is_string = static_cast<bool>(((std::uint16_t *)(buffer_head_))[0]);
  buffer_head_ += sizeof(std::uint16_t);

  // String property
  if (is_string) {
    // Read property value
    
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn, "Expanding buffer in property value header");
      ++warn_count;
    }
    len = process_block_header_();
    if(ensure_buffer_size_(len)){
      NSTR_LOG_(warn, "Expanding buffer in property value ");
      ++warn_count;
    }

    // Read value string
    if (type_in_buffer_ != block_type::STRING){
      throw std::logic_error("Malformed property block - Missing value string");
    }

    return PropertyMap::property_type(key, process_string(len));
  }
  // Float property
  else {
    boost::any value = boost::any(((float *)(buffer_head_))[0]);
    buffer_head_ += sizeof(float);
    return PropertyMap::property_type(key, value);
  }
}

// List processing

std::vector<Node> DATParser::process_samplelist_() {
  std::vector<Node> v;
  std::uint16_t nsamples;

  // Read number of samples
  nsamples = ((std::uint16_t *)buffer_head_)[0];
  buffer_head_ += sizeof(std::uint16_t);
  v.reserve(nsamples);

  // Read samples
  for (int i = 0; i < nsamples; i++) {
    // Read header
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn, "Expanding buffer in process samplelist header");
      ++warn_count;
    }
    if(ensure_buffer_size_(process_block_header_())){
      NSTR_LOG_(warn, "Expanding buffer in process samplelist sample");
      ++warn_count;
    }
    
    // Read sample
    if (type_in_buffer_ != block_type::SAMPLE) {
      throw std::logic_error("Unexpected non-sample block inside a sample list");    } else {
      v.push_back(process_sample());
    }
  }
  if (v.size() != nsamples){
    throw std::logic_error("Malformed sample list block - Expected " + 
                           std::to_string(nsamples) + 
                           " samples, got " + std::to_string(v.size()) );
  }
  return v;
}

std::vector<PropertyMap::property_type> DATParser::process_proplist_() {
  std::uint16_t nprops;
  std::vector<PropertyMap::property_type> v;

  nprops = ((std::uint16_t *)buffer_head_)[0];
  buffer_head_ += sizeof(std::uint16_t);
  if (nprops == 0) return v;

  // Read number of samples
  v.reserve(nprops);  // Ensure capacity

  // Read samples
  for (int i = 0; i < nprops; i++) {
    // Read header
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn, "Expanding buffer in process proplist header");
      ++warn_count;
    }
    if(ensure_buffer_size_(process_block_header_())){
      NSTR_LOG_(warn, "Expanding buffer in process proplist property");
      ++warn_count;
    }
    
    if (type_in_buffer_ != block_type::PROPERTY){ 
      throw std::logic_error("Unexpected non-property block inside a property list");
    } else {
      try{
        v.push_back(process_property());
      } catch(std::logic_error e){
        process_error(e);
        skip_block();
      }
    }
  }
  if (v.size() != nprops){
    throw std::logic_error("Malformed property list block - Expected " + 
                           std::to_string(nprops) + 
                           " samples, got " + std::to_string(v.size()) );
  }
  return v;
}

std::vector<marker_type> DATParser::process_markersetlist_(){
  std::uint16_t nmarkers;
  std::vector<marker_type> v;

  nmarkers = ((std::uint16_t *)buffer_head_)[0];
  buffer_head_ += sizeof(std::uint16_t);
  if (nmarkers == 0) return v;

  // Read number of samples
  v.reserve(nmarkers);  // Ensure capacity

  // Read samples
  //for (int i = 0; i < nmarkers && !empty(); i++) {
  // Markers are....ahrg.
  for (int i = 0; i < nmarkers ; i++) {
    
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn, "Expanding buffer in process markerset list header");
      ++warn_count;
    }
    if(ensure_buffer_size_(process_block_header_())){
      NSTR_LOG_(warn, "Expanding buffer in process markerset list marker");
      ++warn_count;
    }
    
    if (type_in_buffer_ != block_type::MARKERSET){ 
      throw std::logic_error("Unexpected non markerset block inside a markerset list");
    } else {
      v.push_back(process_markerset());
    }
  }
  if (v.size() != nmarkers){
    throw std::logic_error("Malformed markerset list block - Expected " + 
                           std::to_string(nmarkers) + 
                           " samples, got " + std::to_string(v.size()) );
  }
  return v;
}

std::size_t DATParser::process_container_(
    const Neurite::branch_iterator &pos) {

  // Block name and properties
  std::string block_name;
  auto current_pos = pos;

  block_type type;

  // Alloc block
  size_t current_block_size = in_buffer_;
  size_t total_extended = 0;

  // Check for empty blocks
  if (empty()) return 0;

  // Get block type
  type = type_in_buffer_;

  // Read name (in any)
  if (named(type)) {
    // Read name block header
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn,"Expanding buffer in container name header");
      ++warn_count;
    }
    std::size_t len = process_block_header_();
    
    if(ensure_buffer_size_(len)){
      NSTR_LOG_(warn, "Expanding buffer in container name");
      ++warn_count;
    }
    
    if (type_in_buffer_ != block_type::STRING)
      throw std::logic_error("Malformed block - Missing block name");
    else {
      // Read name string
      block_name = process_string(len);
    }
  }

  // Process container info
  std::vector<PropertyMap::property_type> tmp = process_block_info_(type);
  for(auto it = tmp.begin(); it != tmp.end(); ++it ) pos->neurite().properties.set(*it);
  
  // Add name if not empty
  if (block_name.size() > 0) pos->neurite().properties.set(PropertyMap::property_type(std::string("name"), block_name));

  // Read child blocks
  while (!empty()) {

    // Read block header
    if(ensure_buffer_size_(block_header_size)){
      NSTR_LOG_(warn, "Expanding buffer in container subblock header");
      ++warn_count;
    }
    
    std::size_t inblock_size = process_block_header_();
    
    if(ensure_buffer_size_(inblock_size)){
      NSTR_LOG_(warn, "Expanding buffer in container sub-block");
      ++warn_count;
    }
    
    // Correct head displacement
    in_buffer_ = inblock_size + (buffer_head_ - buffer_);
    
    // Single sample or list
    try{
      if (type_in_buffer_ == block_type::SAMPLE) {
        Node n = process_sample();
        current_pos->neurite().insert_node(current_pos, n);
      } else if (type_in_buffer_ == block_type::SAMPLE_LIST) {
        // Sample list
        std::vector<Node> v = process_samplelist_();
        for (auto it = v.begin(); it != v.end(); it++) {
          current_pos->neurite().insert_node(current_pos, *it);
        }
      } else if (type_in_buffer_ == block_type::PROPERTY) {
        // Single property
        PropertyMap::property_type p = process_property();
        current_pos->neurite().properties.set(p);
      } else if (type_in_buffer_ == block_type::PROPERTY_LIST) {
        // Property list
        std::vector<PropertyMap::property_type> v = process_proplist_();
        for(auto it = v.begin(); it != v.end() ; ++it) 
          current_pos->neurite().properties.set(*it);

      } else if (type_in_buffer_ == block_type::SUB_TREE) {
        // Create branch
        std::vector<int> id = current_pos->id();
        id.push_back(current_pos.number_of_children()+1);      
        Neurite::branch_iterator inserted = current_pos->neurite()
          .append_branch(current_pos,
            Branch(id, current_pos->order()+1, current_pos->last()));
        
        // !!!!
        // If the sub container have extended read past the block end... this might be troublesome.
        // Some subblocks might be ignored.
        // How can we solve this..
        
        // Non vanilla blocks
        total_extended+=process_container_(inserted);
        
        
        
        
        
      } else if (type_in_buffer_ == block_type::MARKERSET_LIST ) {
        // Property list
        std::vector<marker_type> v = process_markersetlist_();
        //for(auto it = v.begin(); it != v.end() ; ++it) 
        //  for(auto p = it->properties.begin(); p != it->properties.end() ; ++p)
        //    pos.neurite()->add_property(*p);
        
      } else if (type_in_buffer_ == block_type::MARKERSET ) {
        // Property list
        marker_type m = process_markerset();
        //for(auto p = m.properties.begin(); p != m.properties.end() ; ++p)
        //  pos.neurite()->add_property(*p);
        
      } else {
          skip_block();
      }
      
      } catch (std::logic_error e){
        process_error(e);
        skip_block();
      }

    // Restore block size
    total_extended += extended_bytes_;
    in_buffer_ = current_block_size + total_extended;
    extended_bytes_ = 0;
  } // End while
  return total_extended;
}

void DATParser::skip_block() { buffer_head_ = buffer_ + in_buffer_; }

void DATParser::process_block_(Reconstruction &r) {

  if (type_in_buffer_ == block_type::TREE) {
    // Here we should create a neurite - we do not know its id, neuron or type yet
    Neurite *n = new Neurite();
    n->set_root();

    // Process
    process_container_(n->begin_branch());

    set_neurite_type_by_nlproperties(*n);
    
    // And check to which neuron it corresponds if any.
    // Somas are required to be defined before neurites
    if(r.size() == 0){
      // We need to create the neuron before
      Neuron* neuro = new Neuron(r.id() + std::string("_1"));
      r.addNeuron(neuro);
    }
    r.add_neurite_to_closest_soma(n);  

  } else if (type_in_buffer_ == block_type::CONTOUR) {
    // Auxiliar neurite structure for reading purposes
    // Should be a single-node tree
    Neurite aux;
    aux.set_root();

    // Read container
    process_container_(aux.begin_branch());

    // If soma -> add it to the reconstruction
    auto it = aux.properties.find("cellbody");
    if (it == aux.end_properties()) {
      
      // Not a soma - Some other contour - Create it
      std::vector<point_type> p;
      p.reserve(aux.node_count());
      for(auto it = aux.begin_node(); it != aux.end_node(); ++it){
        p.push_back(it->position());
      }
      
      Contour c(p);
      c.properties_from_map(aux.properties);
      r.addContour(c);
      
    } else {
      // Create neuron
      Neuron *n = new Neuron(r.id() + std::string("_") + std::to_string(r.size() + 1),
                             std::vector<Node>(aux.begin_node(), aux.end_node()));
      for(auto it = n->begin_soma(); it != n->end_soma(); ++it){
          it->parent(nullptr);
          it->branch(nullptr);
        }
        
      r.addNeuron(n);
    }
  /** Add properties to the whole reconstruction / neuron */
  }  else if (type_in_buffer_ == block_type::PROPERTY ){
    try{
      PropertyMap::property_type p = process_property();
      r.properties.set(p);
    } catch (std::logic_error e){
      process_error(e);
      skip_block();
    }
  } else if (type_in_buffer_ == block_type::PROPERTY_LIST ){
    try{
      std::vector<PropertyMap::property_type> v = process_proplist_();
      for(auto it = v.begin(); it != v.end() ; ++it) 
        r.properties.set(*it);
    } catch (std::logic_error e){
      process_error(e);
      skip_block();
    }
  } else if (type_in_buffer_ == block_type::IMAGE ){

    
    // Save it as a property
    // Vector of bytes
    std::vector<unsigned char> v;
    v.reserve(in_buffer_);
    while(!empty()){
      v.push_back(*buffer_head_);
      ++buffer_head_;
    }
    std::string s_enc;
    bn::encode_b64(v.begin(), v.end(), back_inserter(s_enc));
    r.properties.set("image",s_enc);

  }else {
    skip_block();
  }

  return;
}

/***** PRIVATE METHODS **/

std::streamsize DATParser::fill_buffer_(int n) {
  std::streamsize nbytes;
  in_buffer_ = n;
  in_buffer_real_ = n;
  
  stream_.read((char *)buffer_, n);
  buffer_head_ = buffer_;
  
  nbytes = stream_.gcount();
  read_bytes_+= nbytes;
  return nbytes;
}

std::streamsize DATParser::expand_buffer_(std::size_t nbytes){
  
  /*if( in_buffer_ + nbytes <= in_buffer_real_){
      // Just expand
      in_buffer_+=nbytes;
      extended_bytes_+=nbytes;
      return nbytes;
  } else {*/
  
    if ( (in_buffer_real_ + nbytes) > buffer_size) {
      throw std::runtime_error("Buffer size exceded. Something went wrong.");
    }
    
    // read
    char* last = (char*)(buffer_ + in_buffer_real_);
    stream_.read(last, nbytes);
    
    std::streamsize readbytes = stream_.gcount();
    
    in_buffer_ += readbytes;
    in_buffer_real_ += readbytes;
    read_bytes_+= readbytes;
    extended_bytes_+=readbytes;
    
    return readbytes;  
  //}
}


bool DATParser::ensure_buffer_size_(std::size_t min_size){
  
  int delta = (in_buffer_ - (buffer_head_ - buffer_)) - min_size;
  
  if( delta < 0 ){
    // We need to expand -delta
    if( std::abs(delta) != expand_buffer_(std::abs(delta)) ){
      throw std::runtime_error("Unexpected EOF");
    }
    return true;
  } else {
    return false;
  }
}

bool DATParser::empty() { return (in_buffer_ == 0 || ((buffer_ + in_buffer_) <= buffer_head_)); }

/* Check header */
bool DATParser::check_header_() {
  std::streamsize len;
  checked_header_ = true;

  len = fill_buffer_(header_size);

  buffer_head_ += header_size;
  if (len != header_size)
    return valid_header_ = false;
  else
    return valid_header_ = std::memcmp(buffer_, DATParser::header, header_size) == 0 ? true : false;
}

// PROCESS HEADER
std::size_t DATParser::process_block_header_() {
  // Type to type in buffer
  type_in_buffer_ = static_cast<block_type>(((std::uint16_t *)buffer_head_)[0]);

  buffer_head_ += sizeof(std::uint16_t);

  // Return size
  size_t s = static_cast<std::size_t>(((std::uint32_t *)(buffer_head_))[0]);
  buffer_head_ += sizeof(std::uint32_t);
  return (s - block_header_size);  // size includes header
}

std::streamsize DATParser::read_next_block_() {

  // Check header
  if (!valid_header()) throw std::runtime_error("Stream header is not valid");

  fill_buffer_(block_header_size);

  // Check for footer (end)
  if (stream_.fail()) {
    return static_cast<std::streamsize>(0);
  } else if (stream_.eof() && (std::memcmp(buffer_head_, &DATParser::footer, sizeof(footer)) == 0)) {
    return static_cast<std::streamsize>(0);
  } else {
    // Process header
    in_buffer_ = process_block_header_();
    if (in_buffer_ > buffer_size){
      throw std::runtime_error("Buffer size excedeed");
    }

    // Read
    fill_buffer_(in_buffer_);

    if (static_cast<std::size_t>(stream_.gcount()) != in_buffer_) throw std::runtime_error("Malformed block");

    // Return number of bytes read
    return stream_.gcount();
  }
}

std::vector<PropertyMap::property_type> DATParser::process_block_info_(block_type &t) {
  std::vector<PropertyMap::property_type> props;

  switch (t) {
  case block_type::CONTOUR: {
    char tmp[8];

    // Set info
    props.push_back(
        PropertyMap::property_type(std::string("closed"), boost::any(static_cast<bool>(((std::uint16_t *)buffer_head_)[0]))));
    buffer_head_ += sizeof(std::uint16_t);
    // Get colors
    // FACE
    sprintf(tmp,"#%02x%02x%02x",((uint8_t *)buffer_head_)[0],((uint8_t *)buffer_head_)[1],((uint8_t *)buffer_head_)[2]);
    buffer_head_ += 3;
    props.push_back(PropertyMap::property_type(std::string("face_color"), boost::any(std::string(tmp))));
    // Back
    sprintf(tmp,"#%02x%02x%02x",((uint8_t *)buffer_head_)[0],((uint8_t *)buffer_head_)[1],((uint8_t *)buffer_head_)[2]);
    buffer_head_ += 3;
    props.push_back(PropertyMap::property_type(std::string("back_color"), boost::any(std::string(tmp))));
    return props;
  }
  case block_type::TREE: {
    char tmp[8];

    // Set info
    props.push_back(PropertyMap::property_type(
        std::string("type"), boost::any(tree_type_cd(static_cast<std::uint8_t>(((std::uint16_t *)buffer_head_)[0])))));
    props.push_back(PropertyMap::property_type(
        std::string("type_name"), boost::any(tree_type_tostr(tree_type_cd(static_cast<std::uint8_t>(((std::uint16_t *)buffer_head_)[0]))))));
    buffer_head_ += sizeof(std::uint16_t);

    // Get colors
    // FACE
    sprintf(tmp,"#%x%x%x",((uint8_t *)buffer_head_)[0],((uint8_t *)buffer_head_)[1],((uint8_t *)buffer_head_)[2]);
    buffer_head_ += 3;
    props.push_back(PropertyMap::property_type(std::string("face_color"), boost::any(std::string(tmp))));
    // Back
    sprintf(tmp,"#%x%x%x",((uint8_t *)buffer_head_)[0],((uint8_t *)buffer_head_)[1],((uint8_t *)buffer_head_)[2]);
    buffer_head_ += 3;
    props.push_back(PropertyMap::property_type(std::string("back_color"), boost::any(std::string(tmp))));
    return props;
  }
  case block_type::SUB_TREE: {
    // SKIP
    // b.info_.subtree.value1 = ((std::uint16_t*)buffer_head_)[0];
    // b.info_.subtree.value2 = ((std::uint16_t*)buffer_head_)[1];
    buffer_head_ += sizeof(std::uint16_t) * 2;

    return props;
  }
  default:
    return props;
  }
}

}  // Namespace io
}  // Namespace neurostr

//////////////////////////////////////////////////
