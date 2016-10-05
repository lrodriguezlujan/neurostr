/**
 * JSON Writer
 *
 * Write a single nuron into a stream in JSON format
 * 
 * @author Luis Rodriguez
 *
 */
#ifndef NEUROSTRLIB_IO_NL_JSONWRITER_H_
#define NEUROSTRLIB_IO_NL_JSONWRITER_H_


#include <iostream>
#include <boost/any.hpp>
#include <memory>
#include <rapidjson/ostreamwrapper.h>
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "core/neuron.h"



namespace neurostr {
namespace io {
  
  class JSONWriter {
    public:
    /*rapidjson::Document doc;
    rapidjson::IStreamWrapper isw(stream_);
    doc.ParseStream(isw);*/
    using OutputStream = rapidjson::OStreamWrapper;
    using writer_type = rapidjson::Writer<OutputStream>;
    
    JSONWriter(std::ostream& s,bool pretty = false) : buffer(s) {
      if(pretty)
        writer = std::unique_ptr<writer_type>(new rapidjson::PrettyWriter<OutputStream>(buffer));
      else 
        writer = std::unique_ptr<writer_type>(new rapidjson::Writer<OutputStream>(buffer));
      
      writer.SetMaxDecimalPlaces(3);
    };
      
    
    // Destructor
    ~JSONWriter(){};
    
    // DATA ELEMENTS
    private:
      OutputStream buffer;
      std::unique_ptr<writer_type> writer; // JSON Document
    
    // TODO: Define possible parameters (FLAGS)
    
    // Write  reconstruction
    public:
    
    void write(const neurostr::Reconstruction& r){
        writer->StartObject();
        
        writer->Key("neurons");
        writer->StartArray();
        for(auto it = r.begin(); it != r.end(); ++it)
          writeNeuron(*it);
        
        if(r.properties.size()>0){
          writer->Key("properties");  
          writePropertyMap(r.properties);
        }
        
        // TODO: Write contour
        
        writer->EndArray();
        writer->EndObject();
    }
    
    void writeNeuron(const neurostr::Neuron& n){
        
      // buffer.Clear();
      // id: string,
      // soma: SomaJSON, // Write soma
      // neurites: Array<NeuriteJSON>, // Write neurite
      // properties?: Array<NeuronPropertyJSON> // Write property
      
      writer->StartObject();
      
      // Write ID
      writer->Key("id");
      //const char * c = n.id().c_str();
      writer->String(n.id().c_str());
      
      // Write soma
      writer->Key("soma");
      writeSoma(n);
      
      // Write neurites
      writer->Key("neurites");
      writer->StartArray();
      for(auto it = n.begin_neurite(); it != n.end_neurite(); ++it){
        writeNeurite(*it);
      }
      writer->EndArray();
      
      // Write properties if any
      // Properties
      if(n.properties.size()>0){
        writer->Key("properties");  
        writePropertyMap(n.properties);
      }
      
      writer->EndObject();
    };
    
    
    protected:
    

    void writeProperty(const neurostr::PropertyMap::const_iterator& p){
      
      // Write property name
      writer->Key( PropertyMap::key(*p).c_str() );
      
      // Has value?
      if((PropertyMap::empty(*p))){
          writer->StartArray();
          writer->EndArray();
      }else if (PropertyMap::is<float>(*p)) {
          writer->Double(PropertyMap::value<float>(*p));
      } else if (PropertyMap::is<int>(*p)){
          writer->Int(PropertyMap::value<int>(*p));
      } else if (PropertyMap::is<point_type>(*p)){
        point_type point = PropertyMap::value<point_type>(*p);
          writer->StartObject();
          writer->Key("x");
          writer->Double(geometry::get<0>(point));
          writer->Key("y");
          writer->Double(geometry::get<1>(point));
          writer->Key("z");
          writer->Double(geometry::get<2>(point));
          writer->EndObject();
      } else {
          writer->String(PropertyMap::value_as_string(*p).c_str());
      }
    }
    
    void writeSoma(const neurostr::Neuron& n){  
      // ATM is quite simple.. just the nodes attribute
      //nodes : Array< Array<number> >,
      //isContour? : boolean,
      //status? : number // 0 for none, 1 for highlighted, 2 for hidden 3 for invisible
      writer->StartObject();
      writer->Key("nodes");
      
      writer->StartArray();
      for(auto it = n.begin_soma(); it != n.end_soma(); ++it){
        writeNode(*it);
      }
      writer->EndArray();
      
      // Close
      writer->EndObject();
    };
    
    void writePropertyMap(const neurostr::PropertyMap& pm){
      writer->StartObject();
      for(auto it = pm.begin(); it != pm.end(); ++it){
        writeProperty(it);
      }
      writer->EndObject();
    }
    
    // Write Neurite
    void writeNeurite(const neurostr::Neurite& n){
      // Neurite is an object with following elements
      // id : number, uint
      // type : number, // 1 soma, 2 axon, 3 dendrite, 4 apical, rest - unknown
      // materialIndex: number, (usually the neurite id)
      // tree: BranchJSON 
      writer->StartObject();
      
      // Write ID
      writer->Key("id");
      writer->Int(n.id());
      
      // Write type
      writer->Key("type");
      writer->Uint(static_cast<int>(n.type()));
      
      
      // Properties
      if(n.properties.size()>0){
        writer->Key("properties");  
        writePropertyMap(n.properties);
      }
      
      // Write tree
      writer->Key("tree");
      writeBranch(n.begin_branch(),n);
      
      // Close
      writer->EndObject();
    };
    
    // Write branch
    void writeBranch(const neurostr::Neurite::tree_type::iterator_base& b, const neurostr::Neurite& n){
      // Branch is an object with following elements
      // root : Array<number>, // This is a NODE
      // nodes : Array< Array<number> >, // Array of nodes
      // children? : Array< BranchJSON >, (this means that children array is optional)
      // highlighted? : boolean --- DOESNT APPLY IN THIS FN YET
      writer->StartObject();
      
      // Write the root
      if(b-> has_root()){
        writer->Key("root");
        writeNode(b->root());
      }
      
      // Properties
      if(b->properties.size()>0){
        writer->Key("properties");  
        writePropertyMap(b->properties);
      }
      
      // Write nodes
      writer->Key("nodes");
      writer->StartArray();
      for(auto it = b->begin(); it != b->end(); ++it)
        writeNode(*it);
      writer->EndArray();
      
      // Write children if any
      if( b.number_of_children() > 0 ){
        writer->Key("children");
        writer->StartArray();
        // Write each children
        for(auto it = n.begin_children(b); it != n.end_children(b); ++it){
          writeBranch(it, n);
        }
        // Close children array
        writer->EndArray();
      }
      
      // Close branch
      writer->EndObject();
    };
    
    // Write node
    void writeNode(const neurostr::Node& n){
      // Node JSON format is just [id, x, y ,z, r]
      writer->StartObject();
      writer->Key("id");
      writer->Uint(n.id());
      writer->Key("x");
      writer->Double(n.x()); 
      writer->Key("y");
      writer->Double(n.y()); 
      writer->Key("z");
      writer->Double(n.z()); 
      writer->Key("r");
      writer->Double(n.radius()); 
      
      // Properties
      if(n.properties.size()>0){
        writer->Key("properties");  
        writePropertyMap(n.properties);
      }
      
      writer->EndObject();
    };
    
  };
}
}
#endif
