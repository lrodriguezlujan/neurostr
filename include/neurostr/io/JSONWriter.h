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
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <neurostr/core/contour.h>
#include <neurostr/core/neuron.h>




namespace neurostr {
namespace io {
  
  /**
   * @class JSONWriter
   * @file JSONWriter.h
   * @brief Writes a reconstruction in JSON format in the given output stream
   */
  class JSONWriter {
    public:
    /*rapidjson::Document doc;
    rapidjson::IStreamWrapper isw(stream_);
    doc.ParseStream(isw);*/
    using OutputStream = rapidjson::OStreamWrapper;
    using writer_type = rapidjson::Writer<OutputStream>;
    
    /**
     * @brief Creates a writer over the given output stream
     * @param s Stream
     * @param pretty If true, ouptut is prettyfied
     */
    JSONWriter(std::ostream& s,bool pretty = false);
      
    
    /**
     * @brief Default
     */
    ~JSONWriter(){};
    
    // DATA ELEMENTS
    private:
      OutputStream buffer;
      std::unique_ptr<writer_type> writer; // JSON Document
    
    // TODO: Define possible parameters (FLAGS)
    
    // Write  reconstruction
    public:
    
    /**
     * @brief Writes a reconstruction 
     * @param r Reconstruction
     */
    void write(const neurostr::Reconstruction& r);
    /**
     * @brief Writes a single neuron (wo rec. contours)
     * @param n Neuron
     */
    void writeNeuron(const neurostr::Neuron& n);
    
    protected:

    /**
     * @brief Writes a point object as {x,y,z}
     * @param point 3D Point
     */
    void writePoint(const neurostr::point_type& point);
    
    /**
     * @brief Writes the given property as key:value
     * @param p Property iterator
     */
    void writeProperty(const neurostr::PropertyMap::const_iterator& p);
    
    /**
     * @brief Writes the neuron soma as {nodes:[nodes]}
     * @param n Neuron
     */
    void writeSoma(const neurostr::Neuron& n);
    
    /**
     * @brief Writes the given contour as an object. Contour points are
     * in a array
     * @param c Contour
     */
    void writeContour(const neurostr::Contour& c);
    
    /**
     * @brief Writes the property map as an object {}
     * @param pm Property map
     */
    void writePropertyMap(const neurostr::PropertyMap& pm);
    
    /**
     * @brief Writes the neurite as an object { id:, type: , tree:}
     * @param n Neurite
     */
    void writeNeurite(const neurostr::Neurite& n);
    
    /**
     * @brief Writes the given branch (member of n) as {root: node, properties: , nodes:[], children:[] }
     * @param b Branch iterator
     * @param n Neurite
     */
    void writeBranch(const neurostr::Neurite::tree_type::iterator_base& b, const neurostr::Neurite& n);
    
    /**
     * @brief Writes a single node as {id,x,y,z,r,properties:{}}
     * @param n Node
     */
    void writeNode(const neurostr::Node& n);    
  };
}
}
#endif
