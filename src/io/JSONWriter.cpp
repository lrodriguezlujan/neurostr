/**
 * JSON Writer
 *
 * Write a single nuron into a stream in JSON format
 * 
 * @author Luis Rodriguez
 *
 */

#include <neurostr/io/JSONWriter.h>

namespace neurostr {
namespace io {
  
 
    JSONWriter::JSONWriter(std::ostream& s,bool pretty) : buffer(s) {
      if(pretty)
        writer = std::unique_ptr<writer_type>(new rapidjson::PrettyWriter<OutputStream>(buffer));
      else 
        writer = std::unique_ptr<writer_type>(new rapidjson::Writer<OutputStream>(buffer));
      writer->SetMaxDecimalPlaces(3);
    };
      
    
    /**
     * @brief Writes a reconstruction 
     * @param r Reconstruction
     */
    void JSONWriter::write(const neurostr::Reconstruction& r){
        writer->StartObject();
        
        writer->Key("neurons");
        
        writer->StartArray();
        for(auto it = r.begin(); it != r.end(); ++it)
          writeNeuron(*it);
        writer->EndArray();
        
        if(r.properties.size()>0){
          writer->Key("properties");  
          writePropertyMap(r.properties);
        }
        
        // Contours        
        if(r.n_contours() > 0){
          writer->Key("contours");  
          writer->StartArray();
          for(auto it = r.contour_begin(); it != r.contour_end(); ++it){
            writeContour(*it);
          }
          writer->EndArray();
        }
        
        writer->EndObject();
    }
    
    /**
     * @brief Writes a single neuron (wo rec. contours)
     * @param n Neuron
     */
    void JSONWriter::writeNeuron(const neurostr::Neuron& n){
        
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
    
    /**
     * @brief Writes a point object as {x,y,z}
     * @param point 3D Point
     */
    void JSONWriter::writePoint(const neurostr::point_type& point){
      writer->StartObject();
          writer->Key("x");
          writer->Double(geometry::get<0>(point));
          writer->Key("y");
          writer->Double(geometry::get<1>(point));
          writer->Key("z");
          writer->Double(geometry::get<2>(point));
      writer->EndObject();
    }
    
    /**
     * @brief Writes the given property as key:value
     * @param p Property iterator
     */
    void JSONWriter::writeProperty(const neurostr::PropertyMap::const_iterator& p){
      
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
      } else if (PropertyMap::is<bool>(*p)){
          writer->Bool(PropertyMap::value<bool>(*p));
      } else if (PropertyMap::is<point_type>(*p)){
        point_type point = PropertyMap::value<point_type>(*p);
        writePoint(point);
      } else {
          writer->String(PropertyMap::value_as_string(*p).c_str());
      }
    }
    
    /**
     * @brief Writes the neuron soma as {nodes:[nodes]}
     * @param n Neuron
     */
    void JSONWriter::writeSoma(const neurostr::Neuron& n){  
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
    
    /**
     * @brief Writes the given contour as an object. Contour points are
     * in a array
     * @param c Contour
     */
    void JSONWriter::writeContour(const neurostr::Contour& c){
      // Write contour:: several properties and a point array
      writer->StartObject();
      
      // Write props
      
      writer->Key("name");
      writer->String(c.name().c_str());
      
      writer->Key("face_color");
      writer->String(c.face_color().c_str());
      
      writer->Key("back_color");
      writer->String(c.back_color().c_str());      
      
      writer->Key("closed");
      writer->Bool(c.is_closed());      
      
      writer->Key("fill");
      writer->Double(c.fill_density());      
      
      writer->Key("resolution");
      writer->Double(c.resolution());      
      
      // Write points
      writer->Key("points");
      writer->StartArray();
      for(auto it = c.begin(); it != c.end(); ++it){
        writePoint(*it);
      }
      writer->EndArray();
      
      writer->EndObject();
    }
    
    /**
     * @brief Writes the property map as an object {}
     * @param pm Property map
     */
    void JSONWriter::writePropertyMap(const neurostr::PropertyMap& pm){
      writer->StartObject();
      for(auto it = pm.begin(); it != pm.end(); ++it){
        writeProperty(it);
      }
      writer->EndObject();
    }
    
    /**
     * @brief Writes the neurite as an object { id:, type: , tree:}
     * @param n Neurite
     */
    void JSONWriter::writeNeurite(const neurostr::Neurite& n){
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
    
    /**
     * @brief Writes the given branch (member of n) as {root: node, properties: , nodes:[], children:[] }
     * @param b Branch iterator
     * @param n Neurite
     */
    void JSONWriter::writeBranch(const neurostr::Neurite::tree_type::iterator_base& b, const neurostr::Neurite& n){
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
    
    /**
     * @brief Writes a single node as {id,x,y,z,r,properties:{}}
     * @param n Node
     */
    void JSONWriter::writeNode(const neurostr::Node& n){
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
    
} //  end io namespace
} // end neurostr namespace
