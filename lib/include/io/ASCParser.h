/**
 * Neurolucida ASC (ASCII) files parser
 *
 * @author Luis Rodriguez
 *
 */

#ifndef NEUROSTRLIB_IO_ASCPARSER_H_
#define NEUROSTRLIB_IO_ASCPARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include <boost/any.hpp>

#include "io/parser.h"

#include "io/nl_structure.h"

#include "core/property.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"



namespace neurostr {
namespace io {

class ASCParser : public Parser{
    public:

  /**
   * @brief Creates a ASC parser
   * @param s Input stream to read from
   * @return A ASC parser
   */
  ASCParser(std::istream& stream) : Parser(stream), val_(boost::any()) {};

  ~ASCParser() {};

  // Consts
  const static char comment = ';';
  const static char block_start = '(';
  const static char block_end = ')';
  const static char branch_start = '|';
  const static char spine_start = '<';
  const static char spine_end = '>';
  const static char string_escape = '"';
  const static std::string marker;

  /**
   * @brief Reads a reconstruction from the stream
   * @param name Reconstruction ID
   * @return Unique ptr to the reconstruction (Ownership)
   */
  std::unique_ptr<Reconstruction> read(const std::string& name);

  

    protected:
 
  /**
   * @brief Deduces the type of the next block
   * @param in_block Flag: Called inside another block
   * @return block type
   */
  block_type next_block_type(bool in_block);
  
  /**
   * @brief Process a single reconstruction 
   * @param r Reconstruction to be fill
   */
  void process_(Reconstruction& r);

  /**
   * @brief Process a property in the stream
   * @return Extracted property
   */
  PropertyMap::property_type process_property();
  
  /**
   * @brief Process a sample (node) in the stream
   * @return Node
   */
  Node process_sample();
  
  /**
   * @brief Process a Tree (or contour) inserting the nodes in the container
   *  as children of the given parent
   * @param parent Point of insertion
   * @return Last point of insertion
   */
  Neurite::branch_iterator process_container_(const Neurite::branch_iterator& pos);

    private:
  
  /**
   * @brief Process a color property (Special case)
   * @return Property
   */
  PropertyMap::property_type process_color();  // Special color block
  
  /**
   * @brief Process markerset type
   * @return Marker type
   */
  marker_type process_marker();
  
  /**
   * @brief Skips a comment in the buffer
   * @return true if it skips at least one character
   */
  bool skip_comment();
  
  /**
   * @brief Skip current block
   */
  void skip_block();
  
  /**
   * @brief Skips spaces and EOL character in the buffer
   * @return true if it skips at least one character
   */
  bool skip_spaces_eol();
  
  /**
   * @brief Skips until it finds an stop character
   * @return Character that makes the procedure stop
   */
  int skip_to_stopper();
  
  /**
   * @brief Skips a spine block (currently they arent processed)
   */
  void process_spine();
  
  /**
   * @brief Consumes the block end character from the stream
   * @return True if it succesffuly consumes the block end character
   */
  bool pass_block_end();
  
  /**
   * @brief Consumes a value in the stream and puts it in \param{val_} bufer
   * @return Stop character
   */
  int get_value();
  
  /**
   * @brief Checks whether the given string should stop us
   * @param s String to check
   * @param next Next character in the buffer
   * @return True if is a stop sequence
   */
  static bool is_stopper(std::string& s, char next);
  
  /**
   * @brief Auxiliar function that tries to recover from an error skipping the current block
   */
  void recover_from_error();

  boost::any val_;
  int node_count_;
};


}  // Namespace io
}  // Namespace neurostr

#endif
