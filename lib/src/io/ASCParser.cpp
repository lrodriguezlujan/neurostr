/**
 * Neurolucida ASC (ASCII) files parser
 *
 * @author Luis Rodriguez
 *
 */

#include "io/ASCParser.h"


namespace neurostr {
namespace io {

// Consts
const std::string ASCParser::marker = "doublecircle";

// Static
bool ASCParser::is_stopper(std::string& s, char next) {
  if (next == EOF) {
    return true;
  } else if (s.size() > 0 && s[0] == string_escape) {
    return next == string_escape;
  } else {
    return isspace(next) || next == block_start || next == block_end || next == branch_start || next == spine_start ||
           next == spine_end;
  }
}

bool ASCParser::skip_comment() {
  // Skip until endline or eof
  if (stream_.peek() == comment) {
    stream_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  } else
    return false;
}

bool ASCParser::skip_spaces_eol() {
  bool ret = false;
  int c = stream_.peek();
  while ((isspace(c) || c == '\n') && !stream_.eof()) {
    stream_.get();
    c = stream_.peek();
    ret = true;
  }
  return ret;
}

int ASCParser::skip_to_stopper() {
  // Skip spaces and everything
  while (skip_spaces_eol() || skip_comment())
    ;
  return stream_.peek();
}

int ASCParser::get_value() {
  std::string line;

  // Skip and get line until next stopper
  skip_to_stopper();
  while (!is_stopper(line, stream_.peek())) {
    line.push_back(stream_.get());
  }

  if (line.size() == 0) {
    val_ = boost::any();  // Return empty container
  } else {
    // Is numeric?
    char* endptr;
    float v;

    v = strtof(line.c_str(), &endptr);
    // c_str is invalidated if we modify the string
    // Dont do this at home
    if (endptr == line.c_str()) {
      // Conversion failed. IS a string
      if (line[0] == string_escape) line += stream_.get();  // Complete escape
      val_ = boost::any(line);
    } else {
      // IS real
      val_ = boost::any(v);
    }
  }
  return stream_.peek();
}

bool ASCParser::pass_block_end() {

  // End block
  if (stream_.peek() != block_end)
    if (skip_to_stopper() != block_end) return false;
  stream_.get();

  return true;
}

PropertyMap::property_type ASCParser::process_color() {
  std::array<uint8_t, 3> rgb;
  char tmp[8];

  // RED
  get_value();

  // Check that value is not empty, float and the stopper is a space
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    rgb[0] = floor(boost::any_cast<float>(val_));
  else{
    throw std::logic_error("Malformed color block (RED) - Expected int value");
  }

  // GREEN
  get_value();
  // Check that value is not empty, float and the stopper is a space
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    rgb[1] = floor(boost::any_cast<float>(val_));
  else{
    throw std::logic_error("Malformed color block (GREEN) - Expected int value");
  }

  // BLUE
  get_value();
  // Check that value is not empty, float
  if (!val_.empty() && val_.type() == typeid(float))
    rgb[2] = floor(boost::any_cast<float>(val_));
  else{
    throw std::logic_error("Malformed color block (BLUE) - Expected int value");
  }

  // Print HEX COLOR CHAIN
  sprintf(tmp, "#%02x%02x%02x", rgb[0], rgb[1], rgb[2]);
  if (pass_block_end() == false){
    throw std::logic_error( std::string("Malformed color block - Wrong termination - Expected: ") + 
                            std::to_string(block_end) + 
                            ", got: " + 
                            std::to_string(stream_.peek()) );
  }
  return property_type("color", std::string(tmp) );
}

// Auxiliar: Read property block
PropertyMap::property_type ASCParser::process_property() {

  std::string name = boost::any_cast<std::string>(val_);
  PropertyMap::property_type p;

  // Name to lower
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);

  // If stopchar is already ")" dont try to read
  if (stream_.peek() == block_end) {
    stream_.get();  // Pass block end
    return PropertyMap::property_type(name, boost::any());
  }

  // Try to read value
  get_value();
  p = PropertyMap::property_type(name, val_);

  if (!val_.empty()) {
    // String
    if (val_.type() != typeid(float)) {

      std::string s = boost::any_cast<std::string>(val_);
      if (s == "RGB") {
        while (stream_.get() != block_start && !stream_.eof());
        
        if (stream_.eof()){
          throw std::runtime_error("Missing block inside a RGB block - EOF reached");
        }
        
        try{
          p = process_color();
        } catch(std::logic_error e){
          process_error(e); // Process parser error
          recover_from_error();
        }
      }
    }
  }

  // End block
  if (pass_block_end() == false){
    throw std::logic_error( std::string("Malformed color block - Wrong termination - Expected: ") + 
                            std::to_string(block_end) + 
                            ", got: " + 
                            std::to_string(stream_.peek()) );
  }
  return p;
}

Node ASCParser::process_sample() {

  float x, y, z, d;

  // This value is what determined that the block is a sample
  x = boost::any_cast<float>(val_);

  // Y
  get_value();
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    y = boost::any_cast<float>(val_);
  else {
    throw std::logic_error("Malformed sample block (Y-value) - Expected float value");
  }

  get_value();
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    z = boost::any_cast<float>(val_);
  else {
    throw std::logic_error("Malformed sample block (Z-value) - Expected float value");
  }

  get_value();
  if (!val_.empty() && val_.type() == typeid(float))
    d = boost::any_cast<float>(val_);
  else {
    throw std::logic_error("Malformed sample block (diameter value) - Expected float value");
  }

  // End block
  if (pass_block_end() == false){
    throw std::logic_error( std::string("Malformed sample block - Wrong termination - Expected: ") + 
                            std::to_string(block_end) + 
                            ", got: " + 
                            std::to_string(stream_.peek()) );
  }

  return Node(++node_count_, x, y, z, d / 2);
}

marker_type ASCParser::process_marker(){
  
  marker_type m;
  m.name  = boost::any_cast<std::string>(val_);

  // Name to lower
  std::transform(m.name.begin(), m.name.end(), m.name.begin(), ::tolower);
  
  skip_to_stopper();
  // Process subblocks
  while (stream_.peek() != block_end && stream_.peek() != EOF) {
  
    if (stream_.peek() == block_start) {
      stream_.get();
      // Inside the block
      block_type btype = next_block_type(true);
      if (btype == block_type::SAMPLE) {
        m.samples.push_back(process_sample());
      } else if (btype == block_type::PROPERTY) {
        m.properties.push_back(process_property());
      } else {
        throw std::logic_error("Malformed marker block - Unexpected inner block type");
      }
    } else {
        throw std::logic_error( std::string("Malformed marker block - Expected: ") + 
                                std::to_string(block_start) + 
                                ", got: " + 
                                std::to_string(stream_.peek()) );
    }
    skip_to_stopper();    
  }
  
  // IF PEEK EOF - Malformed block
  if (pass_block_end() == false) {
    throw std::logic_error( std::string("Malformed marker block - Wrong termination - Expected: ") + 
                            std::to_string(block_end) + 
                            ", got: " + 
                            std::to_string(stream_.peek()) );
  }
  
  // Return marker
  return(m);
}

void ASCParser::process_spine() {

  // Spine is "like" a sample
  get_value();
  try{
    process_sample();
  } catch(std::logic_error e){
    process_error(e);
    recover_from_error();
  }
  
  if (stream_.peek() != spine_end){
    throw std::logic_error( std::string("Malformed spine block - Expected: ") + 
                            std::to_string(spine_end) + 
                            ", got: " + 
                            std::to_string(stream_.peek()) );
  }
  
  // Skip spine end
  stream_.get();
}

block_type ASCParser::next_block_type(bool inBlock) {

  // Try to read a value
  get_value();

  // Empty value
  if (val_.empty() || val_.type() == typeid(void)) {
    // our type depends on our parents type (if no string / value is given)
    if (!inBlock)
      return block_type::TREE;
    else
      return block_type::SUB_TREE;
  } else if (val_.type() == typeid(float)) {
    // FLOAT!
    return block_type::SAMPLE;
  } else {
    // STRING
    std::string tmp = boost::any_cast<std::string>(val_);
    std::transform(tmp.begin(),tmp.end(),tmp.begin(),::tolower);
    
    if (tmp[0] == string_escape)
      return block_type::CONTOUR;
    else if (tmp == marker)
      return block_type::MARKERSET;
    else
      return block_type::PROPERTY;
  }
}

void ASCParser::process_(Reconstruction & r) {

  block_type btype;

  // Advance to the next stopper
  skip_to_stopper();
  
  // Branches are not allowd here we should stop only at file end
  while (stream_.peek() != EOF) {

    // Only blocks allowed at this level
    if (stream_.peek() != block_start){
      process_error(std::logic_error( std::string("Malformed block - Expected: ") + 
                                      std::to_string(block_start) + 
                                      ", got: " + 
                                      std::to_string(stream_.peek()) ));
      // Try to reach block start
      while( stream_.get() != block_start && !stream_.eof());
      if(stream_.eof()){
        throw std::runtime_error("EOF Reached while recovering form the error");
      }
    }
    else  // Step into
      stream_.get();

    // Guess block type
    btype = next_block_type(false);

    // Now, call by guessed type
    switch (btype) {
    case block_type::CONTOUR: {
      // Auxiliar neurite structure for reading purposes
      // Should be a single-node tree
      Neurite aux;
      aux.set_root();
      
      // Add contour name
      aux.add_property("name", val_);

      // Process container
      try{
        process_container_(aux.begin_branch());
      } catch(std::logic_error e){
        process_error(e);
        recover_from_error();
      }

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
        // ITS A SOMA! - new neuron
        
        // Create neuron
        Neuron* n = new Neuron(r.id() + std::string("_") + std::to_string(r.size() + 1),
                               std::vector<Node>(aux.begin_node(), aux.end_node()));
        // Invalidate all branches and parent int soma nodes!
        for(auto it = n->begin_soma(); it != n->end_soma(); ++it){
          it->parent(nullptr);
          it->branch(nullptr);
        }
        
        r.addNeuron(n);
      }

      break;
    }
    // No subtrees here
    case block_type::TREE: {
      Neurite* n = new Neurite();
      
      // Create root branch
      // Branch b{n, std::vector<int>{1}, 0};
      // n->set_head(b);
      n->set_root();
      
      // Process container
      try{
        process_container_(n->begin_branch());
      } catch(std::logic_error e){
        process_error(e);
        recover_from_error();
      }

      set_neurite_type_by_nlproperties(*n);

      // And check to which neuron it corresponds if any.
      // Somas are required to be defined before neurites
      if(r.size() == 0){
        
        // We need to create the neuron before
        Neuron* neuro = new Neuron(r.id() + std::string("_1"));
        r.addNeuron(neuro);
      }
      
      r.add_neurite_to_closest_soma(n);  
      

      break;
    }
    // Skip block
    case block_type::PROPERTY:
      try{
        r.add_property(process_property());
      } catch(std::logic_error e){
        process_error(e);
        recover_from_error();
      }
      break;
    case block_type::MARKERSET:
      // We process and ignore it
      try{
        process_marker();
      } catch(std::logic_error e){
        process_error(e);
        recover_from_error();
      }
      break;
    // Default just skip
    default:
      skip_block();
      break;
    } // End switch
    skip_to_stopper();
  }
  return;
}

void ASCParser::skip_block(){
   // Skip block
      int depth = 1;
      // We need to skip () until count reaches 0
      while (depth > 0 && stream_.peek() != EOF) {
        if (stream_.get() == block_start)
          ++depth;
        else if (stream_.get() == block_start)
          --depth;
      }
}

Neurite::branch_iterator ASCParser::process_container_(
    const Neurite::branch_iterator& pos) {

  auto current_pos = pos;

  skip_to_stopper();
  // Process subblocks
  while (stream_.peek() != block_end && stream_.peek() != branch_start && stream_.peek() != EOF) {
    // Process spine
    if (stream_.peek() == spine_start) {
      stream_.get();  // get < char
      if (stream_.get() != block_start) {
        process_error(std::logic_error( std::string("Malformed spine block - Expected: ") + 
                                        std::to_string(block_start) + 
                                        ", got: " + 
                                        std::to_string(stream_.peek()) ));
        recover_from_error();
      } else {
        process_spine();
      }
    }
    // Process any other block
    else if (stream_.peek() == block_start) {
      stream_.get();
      // Inside the block
      block_type btype = next_block_type(true);
      if (btype == block_type::SAMPLE) {
        try{
          current_pos->neurite().insert_node(current_pos, process_sample());
        } catch(std::logic_error e){
          process_error(e);
          recover_from_error();
        }
      } else if (btype == block_type::PROPERTY) {
        try{
          current_pos->neurite().properties.set(process_property());
        } catch(std::logic_error e){
          process_error(e);
          recover_from_error();
        }
      } else if (btype == block_type::SUB_TREE) {
        // Create branch
        std::vector<int> id = current_pos->id();
        id.push_back(current_pos.number_of_children()+1);
        
        
        // Insert branch at current posititon with last node as root
        Neurite::branch_iterator inserted = current_pos->neurite()
          .append_branch(current_pos,
          Branch(id, current_pos->order()+1, current_pos->last() ));
        
        try{
          process_container_(inserted);
        } catch(std::logic_error e){
          process_error(e);
          recover_from_error();
        }
        
      } else {
        throw std::logic_error("Malformed block - Unexpected block type inside a generic block");
      }
    } else {
      throw std::logic_error( std::string("Malformed block - Expected: ") + 
                              std::to_string(block_start) + 
                              ", got: " + 
                              std::to_string(stream_.peek()) );
    }

    // Look for any word like.. incomplete or normal...that we ignore it
    get_value();
    if (!val_.empty()) {
      if ( val_.type() != typeid(float) ) {
        // String value (we do not ignore numbers...
        if (stream_.peek() != branch_start && stream_.peek() != block_end) {
          get_value();  // Move fwd - lazy
          if (!val_.empty()){
            throw std::logic_error("Malformed block - Expected non empty ending");
          }
        }
      }
    }
  }

  if (stream_.peek() == branch_start) {
    // Replace by )(
    stream_.get();
    stream_.putback(block_start);
  } else {
    skip_to_stopper();
    // End block
    if (stream_.peek() != EOF && pass_block_end() == false){
      std::logic_error( std::string("Malformed block - Expected: ") + 
                        std::to_string(block_end) + 
                        ", got: " + 
                        std::to_string(stream_.peek()) );
    }
  }

  return current_pos;
}

void ASCParser::recover_from_error(){
  while (stream_.get() != block_end && !stream_.eof());
  if(stream_.eof()){
    throw std::runtime_error("EOF Reached while recovering form the error");
  }
}

// Main function
 std::unique_ptr<Reconstruction> ASCParser::read(const std::string& name) {

  Reconstruction* r = new Reconstruction(name);

  node_count_ = 0;
  try{
    process_(*r);
  } catch (std::exception e){
    // Any error at this point is critical
    NSTR_LOG_(critical, e.what());
    // Mark as such
    critical_error = true;
    ++error_count;
  }
  
  // Correct neurites
  for (auto it = r->begin(); it != r->end(); ++it) {
    it->correct();
    //for (auto neur_it = (*it)->begin_neurite(); neur_it != (*it)->end_neurite(); ++neur_it)
    //  (*neur_it)->correct();
  }

  // root->tree_type_by_properties();
  // root->block_color_by_properties();
  
  if(error_count > 0){
    NSTR_LOG_(warn, std::to_string(error_count) + " were detected while processing the file. Please, send us an email with the conflicting file attached to solve the issue ASAP.")
  }

  return std::unique_ptr<Reconstruction>(r);
}

}  // Namespace io
}  // Namespace neurostr
