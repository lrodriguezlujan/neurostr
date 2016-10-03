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
  else
    throw std::runtime_error("Malformed color block (Red channel)");

  // GREEN
  get_value();
  // Check that value is not empty, float and the stopper is a space
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    rgb[1] = floor(boost::any_cast<float>(val_));
  else
    throw std::runtime_error("Malformed color block (Green channel)");

  // BLUE
  get_value();
  // Check that value is not empty, float
  if (!val_.empty() && val_.type() == typeid(float))
    rgb[2] = floor(boost::any_cast<float>(val_));
  else
    throw std::runtime_error("Malformed color block (Blue channel)");

  // Print HEX COLOR CHAIN
  sprintf(tmp, "#%02x%02x%02x", rgb[0], rgb[1], rgb[2]);
  if (pass_block_end() == false){
    throw std::runtime_error("Malformed property block (Wrong termination)");
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
        while (stream_.get() != block_start && !stream_.eof())
          ;
        if (stream_.eof()) throw std::runtime_error("Missing block inside a RGB block");
        p = process_color();
      }
    }
  }

  // End block
  if (pass_block_end() == false){
    throw std::runtime_error("Malformed property block (Wrong termination)");
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
  else
    throw std::runtime_error("Malformed sample (y-value)");

  get_value();
  if (!val_.empty() && val_.type() == typeid(float)&&isspace(stream_.peek()))
    z = boost::any_cast<float>(val_);
  else
    throw std::runtime_error("Malformed sample (z-value)");

  get_value();
  if (!val_.empty() && val_.type() == typeid(float))
    d = boost::any_cast<float>(val_);
  else
    throw std::runtime_error("Malformed sample (d-value)");

  // End block
  if (pass_block_end() == false){
    throw std::runtime_error("Malformed sample block (Wrong termination)");
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
        throw std::runtime_error("Malformed marker block");
      }
    } else {
        throw std::runtime_error("Malformed marker block");
    }
    skip_to_stopper();    
  }
  
  // IF PEEK EOF - Malformed block
  if (pass_block_end() == false) {
    throw std::runtime_error("Malformed marker block (Wrong termination)");
  }
  
  // Return marker
  return(m);
}

void ASCParser::process_spine() {

  // Spine is "like" a sample
  get_value();
  process_sample();
  if (stream_.peek() != spine_end){
    throw std::runtime_error("Malformed spine");
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
    if (stream_.peek() != block_start)
      throw std::runtime_error("Malformed block");
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
      process_container_(aux.begin_node());

      // If soma -> add it to the reconstruction
      auto it = aux.properties.find("cellbody");
      if (it == aux.end_properties()) {
        // Is sample contour
        if (!r.has_contour()) {
          std::vector<point_type> p;
          p.reserve(aux.node_count());
          
          //std::transform(aux.begin_node(),aux.end_node(), p.end(), [](Node& n){return n.position();});
          for(auto it = aux.begin_node() ; it != aux.end_node() ; ++it){
            p.push_back(it->position());
          }
          
          r.addContour(p);
        } else {
          // Ignore? or throw
          throw std::runtime_error("Only one contour per reconstruction allowd");
        }
      } else {
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
      process_container_(n->begin_node());

      set_neurite_type_by_nlproperties(*n);

      // And check to which neuron it corresponds if any.
      // Somas are required to be defined before neurites
      r.add_neurite_to_closest_soma(n);

      break;
    }
    // Skip block
    case block_type::PROPERTY:
      r.add_property(process_property());
      break;
    case block_type::MARKERSET:
      // We process and ignore it
      process_marker();
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

Neurite::base_node_iterator ASCParser::process_container_(
    const Neurite::base_node_iterator& pos) {

  auto current_pos = pos;

  skip_to_stopper();
  // Process subblocks
  while (stream_.peek() != block_end && stream_.peek() != branch_start && stream_.peek() != EOF) {
    // Process spine
    if (stream_.peek() == spine_start) {
      stream_.get();  // get < char
      if (stream_.get() != block_start) {
        throw std::runtime_error("Malformed spine block");
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
        current_pos = current_pos.neurite().insert_node(current_pos, process_sample());
      } else if (btype == block_type::PROPERTY) {
        current_pos.neurite().properties.set(process_property());
      } else if (btype == block_type::SUB_TREE) {
        // Create branch
        std::vector<int> id = current_pos.branch()->id();
        id.push_back(current_pos.branch().number_of_children()+1);
        
        
        // Insert branch at current posititon with last node as root
        Neurite::branch_iterator inserted = current_pos.neurite()
          .append_branch(current_pos.branch(),
          Branch(id, current_pos.branch()->order()+1, *current_pos ));
        Neurite::base_node_iterator new_pos = 
        Neurite::base_node_iterator(current_pos.begin(),current_pos.end(),inserted);
        
        process_container_(new_pos);
        
      } else {
        throw std::runtime_error("Malformed block");
      }
    } else {
      throw std::runtime_error("Malformed block");
    }

    // Look for any word like.. incomplete...that we will ignore
    get_value();
    if (!val_.empty()) {
      if ((current_pos.begin() != current_pos.end())  && val_.type() != typeid(float)) {
        // String value
        if (stream_.peek() != branch_start && stream_.peek() != block_end) {
          get_value();  // Move fwd - lazy
          if (!val_.empty()) throw std::runtime_error("Malformed block");
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
      throw std::runtime_error("Malformed block (Wrong termination)");
    }
  }

  return current_pos;
}

// Main function
 std::unique_ptr<Reconstruction> ASCParser::read(const std::string& name) {

  Reconstruction* r = new Reconstruction(name);

  node_count_ = 0;
  process_(*r);
  
  // Correct neurites
  for (auto it = r->begin(); it != r->end(); ++it) {
    it->correct();
    //for (auto neur_it = (*it)->begin_neurite(); neur_it != (*it)->end_neurite(); ++neur_it)
    //  (*neur_it)->correct();
  }

  // root->tree_type_by_properties();
  // root->block_color_by_properties();

  return std::unique_ptr<Reconstruction>(r);
}

}  // Namespace io
}  // Namespace neurostr
