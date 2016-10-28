#include "io/JSONParser.h"
#include "rapidjson/error/en.h"
#include "core/log.h"

namespace neurostr {
namespace io {
  
  point_type JSONParser::parsePoint(const rapidjson::Value::ConstObject& v) {
    
    if( !v.HasMember("x") ){
      throw std::logic_error("Missing field 'x' in point");
    } else if( !v.HasMember("y") ){
      throw std::logic_error("Missing field 'y' in point");
    } else if( !v.HasMember("y") ){
      throw std::logic_error("Missing field 'y' in point");
    }
    
    // Check types
    if( !v["x"].IsNumber() ){
      throw std::logic_error("Point field 'x' is not numeric");
    } else if( !v["y"].IsNumber() ){
      throw std::logic_error("Point field 'y' is not numeric");
    } else if( !v["z"].IsNumber() ){
      throw std::logic_error("Point field 'z' is not numeric");
    }
    
    return point_type( v["x"].GetFloat(), 
                       v["y"].GetFloat(), 
                       v["z"].GetFloat());
  }
  
  PropertyMap::property_type JSONParser::parsePropertyValue(const rapidjson::Value::Member& m ){
    
    
    auto name = m.name.GetString();
    
    if(m.value.IsArray())
      return PropertyMap::property_type(name, boost::any() );
    else if (m.value.IsInt()) {
      return PropertyMap::property_type(name, boost::any(m.value.GetInt()));
    } else if (m.value.IsNumber()) {
      return PropertyMap::property_type(name, boost::any(m.value.GetFloat()));
    } else if (m.value.IsString()) {
      return PropertyMap::property_type(name, boost::any(std::string(m.value.GetString())));
    } else if (m.value.IsObject()) {
      return PropertyMap::property_type(name, boost::any(parsePoint(m.value.GetObject())));
    } else if (m.value.IsBool()) {
      return PropertyMap::property_type(name, boost::any(m.value.GetBool()));
    } else {
      NSTR_LOG_(warn, std::string("Unrecognized property type for ") + name);
      ++warn_count;
      return PropertyMap::property_type(name, boost::any() );
    }
  }
  
  PropertyMap JSONParser::parseProperties(const rapidjson::Value::ConstObject& v ) {
    // Check that props are object
    //assert(v.IsObject());
    
    PropertyMap p;
    
    for( auto it = v.MemberBegin(); it != v.MemberEnd(); ++it){
      p.set(parsePropertyValue(*it));
    }
    
    return p;
  }
  
  // Single parsers
  Node JSONParser::parseNode(const rapidjson::Value::ConstObject& v ){
    // Check node sanity
    //assert(v.HasMember("id") && v["id"].IsInt());
    //assert(v.HasMember("r") && v["r"].IsNumber());
    
    if(!v.HasMember("id")){
      throw std::logic_error("Missing node ID");
    } else if( !v["id"].IsInt() ){
      throw std::logic_error("Node ID is not an integer");
    }
    
    if(!v.HasMember("r")){
      throw std::logic_error("Missing node radius");
    } else if( !v["id"].IsNumber() ){
      throw std::logic_error("Node radius is not numeric");
    }
    
    // Parse
    
    // We Dont catch parse point error - Propagate them 
    Node n( v["id"].GetInt(), 
            parsePoint(v),
            v["r"].GetFloat());
    // Parse properties
    if(v.HasMember("properties")){
      if(!v["properties"].IsObject() ){
        NSTR_LOG_(warn,"Node properties field is not an object");
        ++warn_count;
      } else {
        n.properties = parseProperties(v["properties"].GetObject());
      }
    }
    return n;
    
  }
  

  
  
  //assert(v.HasValue("type") && v["type"].IsUint() ); 
  void JSONParser::parseBranch(const rapidjson::Value::ConstObject& v,
                     const Neurite::branch_iterator& pos){
                       
    //assert(v.HasMember["root"] && v["root"].IsObject());
    //assert(v.HasMember["nodes"] && v["nodes"].IsArray());
    
    // Branch has root
    if(!v.HasMember("root")){
      ++warn_count;
      NSTR_LOG_(warn, "Unrooted branch");
    } else {
      // Root (may throw error)
      try{
        pos->root( parseNode(v["root"].GetObject()) );  
      } catch( std::logic_error e){
        // We kjust ignore the root
        process_error(e);
        NSTR_LOG_(info, "Error while parsing branch root. Skipped.");  
        pos->remove_root();  
      }
    }
    
    if(!v.HasMember("nodes")){
      throw std::logic_error("Missing nodes field in branch");
    } else if(!v["nodes"].IsArray()){
      throw std::logic_error("Branch nodes field is not an array");
    }
    
    // nodes
    auto tmp = v["nodes"].GetArray();
    pos->clear();
    for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
      try{
        if(!it->IsObject()){
          throw std::logic_error("Unexpected non object node");
        }
        pos->push_back( parseNode(it->GetObject()));
      } catch( std::logic_error e){
        process_error(e);
        NSTR_LOG_(info, "Conflicting nodes will are omitted");  
      }
    }
    
    // Properties
     if(v.HasMember("properties")){
      if(!v["properties"].IsObject() ){
        NSTR_LOG_(warn,"Branch properties field is not an object - Ignoring");
        ++warn_count;
      } else {
        pos->properties = parseProperties(v["properties"].GetObject());
      }
    }
    
    // Children
     if(v.HasMember("children")){
      if(!v["nodes"].IsArray()){
          throw std::logic_error("Branch children field is not an array");
      }
       //assert(v["children"].IsArray());
       auto tmp = v["children"].GetArray();
       for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
         
         // Add temporal branch
         auto newpos = pos->neurite()
                        .append_branch(pos,Branch()); // This copies neurite in b.
         newpos->order(pos->order()+1);
         
         // Parse recursive
         try{
          if(!it->IsObject()){
            throw std::logic_error("Unexpected non object branch");
          }
          parseBranch(it->GetObject(), newpos);
         } catch(std::logic_error e){
           process_error(e);
           NSTR_LOG_(info, "Ignoring conflicting branch");  
         }
       }
     }                  
  }
  
  
  Neurite* JSONParser::parseNeurite(const rapidjson::Value::ConstObject& v ){
    //assert(v.HasValue("id") && v["id"].IsUint() );
    //assert(v.HasValue("type") && v["type"].IsUint()) );
    //assert(v.HasValue("tree") && v["tree"].IsObject()) );
    if(!v.HasMember("id")){
      throw std::logic_error("Missing neurite id field");
    } else if ( !v["id"].IsUint()){
      throw std::logic_error("Neurite id field is not an unsigned integer");
    }
    
    if(!v.HasMember("type")){
      throw std::logic_error("Missing neurite type field");
    } else if ( !v["type"].IsUint()){
      throw std::logic_error("Neurite type field is not an unsigned integer");
    }
    
    if(!v.HasMember("tree")){
      throw std::logic_error("Missing neurite tree field");
    } else if ( !v["tree"].IsObject()){
      throw std::logic_error("Neurite tree field is not an object");
    }
    
    // Create neurite
    Neurite * n = new Neurite(v["id"].GetUint(), NeuriteType(v["type"].GetUint()) );
    
    // Properties..
    if(v.HasMember("properties")){
      if(!v["properties"].IsObject() ){
        NSTR_LOG_(warn,"Neurite properties field is not an object - Ignoring");
        ++warn_count;
      } else {
        n->properties = parseProperties(v["properties"].GetObject());
      }
    }
    
    // Tree
    n->set_root(); // Create empty root
    n->begin_branch()->order(0);
    parseBranch(v["tree"].GetObject(), n->begin_branch());
    
    return n;
  }
  
  Neuron* JSONParser::parseNeuron(const rapidjson::Value::ConstObject& v ){
    //assert(v.HasValue("id") && v["id"].IsString() );
    //assert(v.HasValue("neurites") && v["neurites"].IsArray()) );
    
    if(!v.HasMember("id")){
      throw std::logic_error("Missing neuron id field");
    } else if ( !v["id"].IsString()){
      throw std::logic_error("Neuron id field is not a string");
    }
    
    Neuron* n = new Neuron(v["id"].GetString());
    
    // If has soma
    if(v.HasMember("soma")){
      //assert(v["soma"].IsObject());
      //assert(v["soma"].HasValue("nodes"));
      
      if(!v["soma"].IsObject()){
        NSTR_LOG_(warn,"Neuron soma is not an object - Skipping");
        ++warn_count;
      } else if (!v["soma"].HasMember("nodes")) {
        NSTR_LOG_(warn,"Missing nodes field in soma - Skipping");
        ++warn_count;
      } else if ( !v["soma"]["nodes"].IsArray() ){
        NSTR_LOG_(warn,"Soma nodes is not an array - Skipping");
        ++warn_count;
      } else {
        // Get soma nodes
        auto tmp = v["soma"]["nodes"].GetArray();

        std::vector<Node> soma(tmp.Size());
        
        // Parse each node
        for( auto it = tmp.begin(); it != tmp.end() ; ++it){
          try{
            if(!it->IsObject()){
              throw std::logic_error("Unexpected non object node");
            }
            soma.push_back(parseNode(it->GetObject()));
          } catch (std::logic_error e){
            process_error(e);
            NSTR_LOG_(info, "Conflicting soma nodes will be ignored");
          }
        }
        n->add_soma(soma);
      }
    }
    
    // Properties..
    if(v.HasMember("properties")){
      if(!v["properties"].IsObject() ){
        NSTR_LOG_(warn,"Neuron properties field is not an object - Ignoring");
        ++warn_count;
      } else {
        n->properties = parseProperties(v["properties"].GetObject());
      }
    }
    
    if(!v.HasMember("neurites")){
      throw std::logic_error("Missing neurites field in Neuron");
    } else if ( !v["neurites"].IsArray()){
      throw std::logic_error("Neuron neurites field is not an array");
    }
    
    // Tree
    auto tmp = v["neurites"].GetArray();
    for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
      try{
        if(!it->IsObject()){
          throw std::logic_error("Unexpected non object neurite");
        }
        n->add_neurite(parseNeurite(it->GetObject()));
      } catch (std::logic_error e){
        process_error(e);
        NSTR_LOG_(info, "Conflicting neurites are ignored");
      }
    }
    
    return n;
  }
  
  Contour JSONParser::parseContour(const rapidjson::Value::ConstObject& v){
    
    std::vector<point_type> points;
    
    
    if(!v.HasMember("name")){
      throw std::logic_error("Missing contour name");
    } else if(!v["name"].IsString()){
      throw std::logic_error("Contour name is not a string");
    }
    
    
    if(!v.HasMember("face_color")){
      throw std::logic_error("Missing contour face_color");
    } else if(!v["face_color"].IsString()){
      throw std::logic_error("Contour face_color is not a string");
    }
    
    
    if(!v.HasMember("back_color")){
      throw std::logic_error("Missing contour back_color");
    } else if(!v["back_color"].IsString()){
      throw std::logic_error("Contour back_color is not a string");
    }
    
    
    if(!v.HasMember("closed")){
      throw std::logic_error("Missing contour closed field");
    } else if(!v["closed"].IsBool()){
      throw std::logic_error("Contour closed is not boolean");
    }
    
    
    if(!v.HasMember("fill")){
      throw std::logic_error("Missing contour fill field");
    } else if(!v["fill"].IsNumber()){
      throw std::logic_error("Contour fill is not numeric");
    }
    
    
    if(!v.HasMember("resolution")){
      throw std::logic_error("Missing contour resolution field");
    } else if(!v["resolution"].IsNumber()){
      throw std::logic_error("Contour resolution is not numeric");
    }
    
    
    if(!v.HasMember("points")){
      throw std::logic_error("Missing contour points field");
    } else if(!v["points"].IsArray()){
      throw std::logic_error("Contour points is not an array");
    }
    
    auto tmp = v["points"].GetArray();
    for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
      try{
        if(!it->IsObject()){
          throw std::logic_error("Unexpected non object point");
        }
        points.push_back( parsePoint(it->GetObject()));
      } catch( std::logic_error e){
        process_error(e);
        NSTR_LOG_(info, "Erroneous contour points are omitted");  
      }
    }
    
    Contour c(points);
    
    c.name(v["name"].GetString());
    c.face_color(v["face_color"].GetString());
    c.back_color(v["back_color"].GetString());
    c.fill_density(v["fill"].GetFloat());
    c.resolution(v["resolution"].GetFloat());
    
    if(v["closed"].GetBool())
      c.close();
    
    return c;
  }
  
  std::unique_ptr<Reconstruction> JSONParser::parse_document(const std::string& name ,
                                                             const rapidjson::Document& doc){
    
     // Create reconstruction
    Reconstruction* r = new Reconstruction(name);
    
    
    // Check if it is a single neuron or a neuron set
    if(doc.HasMember("neurons")){
      if(!doc["neurons"].IsArray()){
        throw std::logic_error("neurons field is not an array");
      }
      
      // Is a rec. set
      auto tmp = doc["neurons"].GetArray();
      for(auto it = tmp.Begin() ; it != tmp.End() ; ++it){
        try{
          if(!it->IsObject()){
            throw std::logic_error("Unexpected non object neuron");
          }
          r->addNeuron(parseNeuron(it->GetObject()));
        } catch (std::logic_error e){
          process_error(e);
          NSTR_LOG_(info, "Erroneous neurons are ignored");
        }
      }
      
      // Read contour
      if(doc.HasMember("contours")){
        if(!doc["contours"].IsArray()){
          NSTR_LOG_(warn,"Contours field is not an array - skipping");
          ++warn_count;
        } else {
          auto tmp = doc["contours"].GetArray();
          for(auto it = tmp.Begin() ; it != tmp.End() ; ++it){
            try{
              if(!it->IsObject()){
                throw std::logic_error("Unexpected non object contour");
              }
              r->addContour(parseContour(it->GetObject()));
            } catch (std::logic_error e){
              process_error(e);
              NSTR_LOG_(info, "Erroneous contours are ignored");
            }
          }
        }
      }
      
      // Read properties
      if(doc.HasMember("properties")){
        if(!doc["properties"].IsObject() ){
          NSTR_LOG_(warn,"Reconstruction properties field is not an object - Skipping");
          ++warn_count;
        } else {
          r->properties = parseProperties(doc["properties"].GetObject());
        }
      }
      
      
    
    } else {
      // Single
      
      try{
        r->addNeuron(parseNeuron(doc.GetObject()));
      } catch (std::logic_error e){
          process_error(e);
          NSTR_LOG_(info, "Erroneous neurons are ignored");
      }
    }
    
    return std::unique_ptr<Reconstruction>(r);
  }
  
  std::unique_ptr<Reconstruction> JSONParser::read(const std::string& name){
    
    // Create and open doc
    rapidjson::Document doc;
    
    reset_errors();
    
    rapidjson::IStreamWrapper isw(stream_);
    doc.ParseStream(isw);
    
    if(doc.HasParseError()){
      critical_error = true;
      NSTR_LOG_(critical, rapidjson::GetParseError_En(doc.GetParseError()));
      ++error_count;
      return std::unique_ptr<Reconstruction>( new Reconstruction(name) );
    }
    //assert(doc.IsObject());
    std::unique_ptr<Reconstruction> ret;
    try{
      ret = parse_document(name,doc);
      
    } catch(std::exception e){
      critical_error = true;
      NSTR_LOG_(critical, e.what());
      ++error_count;
    }
    
    if(error_count > 0){
      NSTR_LOG_(warn, std::to_string(error_count) + 
      " were detected while processing the file. Please, check the file and correct the errors.")
    }
    
    return ret;
  }
  
} // IO NS end
} // Neurostr NS end
