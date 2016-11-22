/**
 * JSON Files parser
 *
 * @author Luis Rodriguez
 *
 */

#ifndef NEUROSTRLIB_IO_JSONPARSER_H_
#define NEUROSTRLIB_IO_JSONPARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include <neurostr/io/parser.h>
#include <neurostr/io/nl_structure.h>

#include <neurostr/core/property.h>
#include <neurostr/core/node.h>
#include <neurostr/core/branch.h>
#include <neurostr/core/neurite.h>
#include <neurostr/core/neuron.h>
#include <neurostr/core/log.h>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/error/en.h>




namespace neurostr {
namespace io {

  /**
   * @class JSONParser
   * @file JSONParser.h
   * @brief Parser specialization for JSON files (custom definition)
   */
class JSONParser : public Parser{
  
  
  public:

  /**
   * @brief Creates a JSON parser
   * @param s Input stream to read from
   * @return JSON parser
   */
  JSONParser(std::istream& stream) 
    : Parser(stream){};

  /**
   * @brief Default
   */
  ~JSONParser() {};
  
  // Data members
  private:
  

  
  public:

  /**
   * @brief Reads a reconstruction from the stream
   * @param name Reconstruction ID
   * @return Unique ptr to the reconstruction (Ownership)
   */
  std::unique_ptr<Reconstruction> read(const std::string& name);

  

  protected:
 

  private:
  
  /**
   * @brief Processes a 3D point JSON object
   * @param v Point object
   * @return  3D Point
   */
  point_type parsePoint(const rapidjson::Value::ConstObject& v);
  
  /**
   * @brief Processes the value of a given property and creates the property
   * @param v Member of a property map 
   * @return Property
   */
  PropertyMap::property_type parsePropertyValue(const rapidjson::Value::Member& v );
  
  /**
   * @brief Parses a JSON property map (Objects where member are props)
   * @param v Property Map object
   * @return Property map
   */
  PropertyMap parseProperties(const rapidjson::Value::ConstObject& v );
  
  /**
   * @brief Processes a JSON node
   * @param v JSON node
   * @return  Node object
   */
  Node parseNode(const rapidjson::Value::ConstObject& v );
  
  /**
   * @brief Parses a single neuron object
   * @param v Single neuron object
   * @return Neuron
   */
  Neuron* parseNeuron(const rapidjson::Value::ConstObject& v );
  
  /**
   * @brief Processes a single neurite object 
   * @param v Neurite object
   * @return  Neurite
   */
  Neurite* parseNeurite(const rapidjson::Value::ConstObject& v );
  
  /**
   * @brief Parses a single branch and interts its content in the Branch
   * pointed by pos
   * @param v JSON BRanch object
   * @param pos Branch position
   */
  void parseBranch(const rapidjson::Value::ConstObject& v,
                     const Neurite::branch_iterator& pos);
                     
  /**
   * @brief Processes a contour JSON object
   * @param v JOSN Object
   * @return Contour
   */
  Contour parseContour(const rapidjson::Value::ConstObject& v);
                    
  /**
   * @brief Reads a JSON document and produces a Reconstruction.
   *  It supports single-neuron documents and reconstruction objects
   * @param name Reconstruction name
   * @param doc Parsed JSON document
   */
  std::unique_ptr<Reconstruction> 
    parse_document(const std::string& name, const rapidjson::Document& doc);

};


}  // Namespace io
}  // Namespace neurostr

#endif
