#include "io/JSONParser.h"

namespace neurostr {
namespace io {
  
  point_type JSONParser::parsePoint(const rapidjson::Value::ConstObject& v) {
    //assert(v.HasMember("x") && v["x"].IsNumber());
    //assert(v.HasMember("y") && v["y"].IsNumber());
    //assert(v.HasMember("z") && v["z"].IsNumber());
    
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
    } else if (m.value.IsFloat()) {
      return PropertyMap::property_type(name, boost::any(m.value.GetFloat()));
    } else if (m.value.IsString()) {
      return PropertyMap::property_type(name, boost::any(m.value.GetString()));
    } else if (m.value.IsObject()) {
      return PropertyMap::property_type(name, boost::any(parsePoint(m.value.GetObject())));
    } else {
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
    
    // Parse
    Node n( v["id"].GetInt(), 
            parsePoint(v),
            v["r"].GetFloat());
    // Parse properties
    if(v.HasMember("properties")){
      n.properties = parseProperties(v["properties"].GetObject());
    }
    return n;
    
  }
  

  
  
  //assert(v.HasValue("type") && v["type"].IsUint() ); 
  void JSONParser::parseBranch(const rapidjson::Value::ConstObject& v,
                     const Neurite::branch_iterator& pos){
                       
    //assert(v.HasMember["root"] && v["root"].IsObject());
    //assert(v.HasMember["nodes"] && v["nodes"].IsArray());
    
    // Root
    pos->root( parseNode(v["root"].GetObject()) );
    
    // nodes
    auto tmp = v["nodes"].GetArray();
    pos->clear();
    for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
      pos->push_back( parseNode(it->GetObject()));
    }
    
    // Properties
     if(v.HasMember("properties")){
      pos->properties = parseProperties(v["properties"].GetObject());
    }
    
    // Children
     if(v.HasMember("children")){
       //assert(v["children"].IsArray());
       auto tmp = v["children"].GetArray();
       for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
         
         // Add temporal branch
         auto newpos = pos->neurite()
                        .append_branch(pos,Branch()); // This copies neurite in b.
         
         // Parse recursive
         parseBranch(it->GetObject(), newpos);
       }
     }                  
  }
  
  
  Neurite* JSONParser::parseNeurite(const rapidjson::Value::ConstObject& v ){
    //assert(v.HasValue("id") && v["id"].IsUint() );
    //assert(v.HasValue("type") && v["type"].IsUint()) );
    //assert(v.HasValue("tree") && v["tree"].IsObject()) );
    
    // Create neurite
    Neurite * n = new Neurite(v["id"].GetUint(), NeuriteType(v["type"].GetUint()) );
    
    // Properties..
    if(v.HasMember("properties")){
      n->properties = parseProperties(v["properties"].GetObject());
    }
    
    // Tree
    n->set_root(); // Create empty root
    parseBranch(v["tree"].GetObject(), n->begin_branch());
    
    return n;
  }
  
  Neuron* JSONParser::parseNeuron(const rapidjson::Value::ConstObject& v ){
    //assert(v.HasValue("id") && v["id"].IsString() );
    //assert(v.HasValue("neurites") && v["neurites"].IsArray()) );
    
    Neuron* n = new Neuron(v["id"].GetString());
    
    // If has soma
    if(v.HasMember("soma")){
      //assert(v["soma"].IsObject());
      //assert(v["soma"].HasValue("nodes"));

      // Get soma nodes
      auto tmp = v["soma"]["nodes"].GetArray();

      std::vector<Node> soma(tmp.Size());
      
      // Parse each node
      for( auto it = tmp.begin(); it != tmp.end() ; ++it){
        soma.push_back(parseNode(it->GetObject()));
      }
      n->add_soma(soma);
    }
    
    // Properties..
    if(v.HasMember("properties")){
      n->properties = parseProperties(v["properties"].GetObject());
    }
    
    // Tree
    auto tmp = v["neurites"].GetArray();
    for(auto it = tmp.begin() ; it != tmp.end() ; ++it){
      n->add_neurite(parseNeurite(it->GetObject()));
    }
    
    return n;
  }
  
  std::unique_ptr<Reconstruction> JSONParser::parse_document(const std::string& name ,
                                                             const rapidjson::Document& doc){
    
     // Create reconstruction
    Reconstruction* r = new Reconstruction(name);
    
    
    // Check if it is a single neuron or a neuron set
    if(doc.HasMember("neurons")){
      // Is a rec. set
      auto tmp = doc["neurons"].GetArray();
      for(auto it = tmp.Begin() ; it != tmp.End() ; ++it){
        r->addNeuron(parseNeuron(it->GetObject()));
      } 
      
      // Read contour
      // TODO
    } else {
      // Single
      r->addNeuron(parseNeuron(doc.GetObject()));
    }
    
    return std::unique_ptr<Reconstruction>(r);
  }
  
  std::unique_ptr<Reconstruction> JSONParser::read(const std::string& name){
    
    // Create and open doc
    rapidjson::Document doc;
    rapidjson::IStreamWrapper isw(stream_);
    doc.ParseStream(isw);
    //assert(doc.IsObject());

    
    return parse_document(name,doc);

  }
  
} // IO NS end
} // Neurostr NS end
