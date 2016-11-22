/**
 * Neurolucida DAT (binary) format interpreter
 *
 * Basic Specs from http://www.neuronland.org/NLMorphologyConverter/MorphologyFormats/NeurolucidaDAT/Spec.html (few
 *enhancemets made over that tool)
 *
 * @author Luis Rodriguez
 *
 */
#ifndef NEUROSTRLIB_IO_NL_DATPARSER_H_
#define NEUROSTRLIB_IO_NL_DATPARSER_H_

#include <iostream>
#include <vector>
#include <cstdint>

#include "io/parser.h"

#include "io/nl_structure.h"

#include "core/log.h"
#include "core/property.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"

namespace neurostr {
namespace io {
  
/**
 * @class DATParser
 * @file DATParser.h
 * @brief Parser specialization for neurolucida Binary files. Initial specification
 * taken from neuronland.
 */
class DATParser : public Parser{
    
public:

  

  /**
   * @brief Creates a DAT parser
   * @param s Input stream to read from
   * @return A DAT parser
   */
  DATParser(std::istream& stream)
      : Parser(stream)
      , buffer_head_(nullptr)
      , in_buffer_(0)
      , in_buffer_real_(0)
      , read_bytes_(0)
      , extended_bytes_(0)
      , type_in_buffer_(block_type::ROOT)
      , error_status_(0)
      , checked_header_(false)
      , valid_header_(false) {};

  /**
   * @brief Default
   */
  ~DATParser() {};

  // Consts
  const static std::size_t buffer_size = 1024 * 1024;  // 1MB
  const static std::size_t header_size = 70;
  const static std::uint8_t header[header_size];
  const static std::uint32_t footer;
  const static std::size_t block_header_size = 6;

  /**
   * @brief Reads a reconstruction from the stream
   * @param name Reconstruction ID
   * @return Unique ptr to the reconstruction (Ownership)
   */
  std::unique_ptr<Reconstruction> read(const std::string&);
  
 protected:
  
  /**
   * @brief Checks that the header is correct
   * @return True if header is valid
   */
  bool valid_header();
  
  /**
   * @brief Process binary string block
   * @param len String length
   * @return String
   */
  std::string process_string(std::size_t len);
  
  /**
   * @brief Process binary sample block
   * @return  Node
   */
  Node process_sample();
  
  /**
   * @brief Process binary property block
   * @return Property
   */
  PropertyMap::property_type process_property();
  
  /**
   * @brief Proces binary markeset block
   * @return Marker
   */
  marker_type process_markerset();

  // List processing
  
  /**
   * @brief  Process sample list block
   * @return Node vector
   */
  std::vector<Node> process_samplelist_();
  
  /**
   * @brief Porcess list of properties
   * @return Property vector
   */
  std::vector<PropertyMap::property_type> process_proplist_();
  
  /**
   * @brief Process list of markers
   * @return  Vector of markers
   */
  std::vector<marker_type> process_markersetlist_();

  /**
   * @brief Process container block in buffer
   * @param pos Insertion position
   * @return Number of bytes extended
   */
  std::size_t process_container_(
      const Neurite::branch_iterator& pos);

  /**
   * @brief Process block in buffer
   * @param r Reconstruction to fill
   */
  void process_block_(Reconstruction& r);

  /**
   * @brief Skips current block in buffer
   */
  void skip_block();

    private:
 
  /**
   * @brief Header check (internal)
   * @return  True if header is valid
   */
  bool check_header_();
  
  /**
   * @brief Reads from the stream into the buffer
   * @param n Maximum Number of characters to read 
   * @return Read char count
   */
  std::streamsize fill_buffer_(int n);
  
  /**
   * @brief Append nbytes at the end of the buffer
   * @return Readed chars
   */
  std::streamsize expand_buffer_(std::size_t nbytes);
  
  /**
   * @brief True if buffer is empty
   * @return  True/False
   */
  bool empty();
  
  /**
   * @brief Put the next block in the stream into the buffer
   * @return Block size
   */
  std::streamsize read_next_block_();
  

  
  /**
   * @brief Process block header and returns its size
   * @return block size
   */
  std::size_t process_block_header_();
  
  /**
   * @brief Read as many bytes from the buffer as necessary to ensure that
   * the buffer contains at least min_size bytes left
   * @return False if it failed
   */
  bool ensure_buffer_size_(std::size_t min_size);
  
  /**
   * @brief Process block info
   * @param b Block type
   * @return Property vector
   */
  std::vector<PropertyMap::property_type> process_block_info_(block_type& b);

  // Data
  std::uint8_t buffer_[buffer_size];
  std::uint8_t* buffer_head_;
  std::size_t in_buffer_;
  std::size_t in_buffer_real_;
  std::size_t read_bytes_;
  std::size_t extended_bytes_;
  block_type type_in_buffer_;

  int error_status_;
  bool checked_header_;
  bool valid_header_;
  int node_count_;
};

}  // Namespace io
}  // Namespace neurostr

#endif
