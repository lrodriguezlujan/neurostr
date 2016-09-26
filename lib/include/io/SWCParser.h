#ifndef NEUROSTRLIB_IO_SWCPARSER_H_
#define NEUROSTRLIB_IO_SWCPARSER_H_

#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

#include "io/parser.h"
#include "core/property.h"
#include "core/node.h"
#include "core/branch.h"
#include "core/neurite.h"
#include "core/neuron.h"


namespace neurostr {
namespace io {
class SWCParser : public Parser{ // Could be templated
    public:
  
  // Boost tokenizer defs
  typedef boost::escaped_list_separator<char> separator;
  typedef boost::tokenizer<separator> tokenizer;
  
  // Consts
  
  // Character that marks the line as comment
  const char comment_char = '#';
  // Number of fields in a SWC file
  const size_t field_count = 7;

  /**
   * @brief Creates a SWC parser with default separators (space)
   * @param s Input stream to read from
   * @return A SWC parser
   */
  SWCParser(std::istream& s);
  
  /**
   * @brief Creates a SWC parser with given separators
   * @param s Input stream
   * @param sep String of separator characters
   * @return A SWC parser
   */
  SWCParser(std::istream& s, const std::string& sep);
  
  ~SWCParser();
  
  /**
   * @brief Reads a reconstruction from the stream. For SWC files the return
   * will always consist of a reconstruction with exactly one neuron and no contour
   * @param name Reconstruction ID
   * @return Unique ptr to the reconstruction (Ownership)
   */
  std::unique_ptr<Reconstruction> read(const std::string& name);
  
  /**
   * @brief Checks if the given string is a known property name
   * @param s String to check
   * @return True if the string is in the property key set
   */
  bool is_key(const std::string& s) const;
  
  /**
   * @brief Adds a string to the set of recognized property keys
   * @param s String to add 
   */
  void add_property_key(const std::string&);
  
  /**
   * @brief Removes a string of the set of recognized property keys
   * @param s String to add 
   */
  void remove_property_key(const std::string&);
  
  /**
   * @brief Retrieves the set of recognized property keys
   * @return Set of strings
   */
  const std::set<std::string>& get_property_keys() const;
  
  protected:
  
  // Data members
  separator sep_;
  Neuron* neuron_;
  std::set<std::string> property_keys_;
  
   // Properties management
  
  
  /**
   * @brief Initialize property key set to the default values
   */
  void initialize_property_keys();

    private:
  
  /**
   * @brief Process a single line
   * @param s Line to process
   */
  void process_line_(const std::string& s);
  
  /**
   * @brief Process a line as header line
   * @param s Line to process
   */
  void process_header_(const std::string& s);
  
  /**
   * @brief Process a line as data line
   * @param s Line to process
   */
  void process_data_(const std::string& s);
  
  /**
   * @brief Checks whether a line is a header line or a data line
   * @param s Line to check
   * @return True if \param{s} is a header line
   */
  bool is_headerline(const std::string& s) const;

};  // Class swc parser

}  // Namespace neurostr
}  // namespace io

#endif
