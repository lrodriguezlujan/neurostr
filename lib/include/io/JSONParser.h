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

#include "io/parser.h"

#include "io/nl_structure.h"

#include "core/property.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>



namespace neurostr {
namespace io {

class JSONParser : public Parser{
  
  
  public:

  /**
   * @brief Creates a JSON parser
   * @param s Input stream to read from
   * @return JSON parser
   */
  JSONParser(std::istream& stream) 
    : Parser(stream){};

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
  
  // Single parsers
  point_type parsePoint(const rapidjson::Value::ConstObject& v);
  
  PropertyMap::property_type parsePropertyValue(const rapidjson::Value::Member& v );
  PropertyMap parseProperties(const rapidjson::Value::ConstObject& v );
  
  Node parseNode(const rapidjson::Value::ConstObject& v );
  Neuron* parseNeuron(const rapidjson::Value::ConstObject& v );
  Neurite* parseNeurite(const rapidjson::Value::ConstObject& v );
  void parseBranch(const rapidjson::Value::ConstObject& v,
                     const Neurite::branch_iterator& pos);
  Contour parseContour(const rapidjson::Value::ConstObject& v);
                     
  std::unique_ptr<Reconstruction> 
    parse_document(const std::string& name, const rapidjson::Document& doc);

};


}  // Namespace io
}  // Namespace neurostr

#endif
