#ifndef NEUROSTRLIB_IO_PARSER_H_
#define NEUROSTRLIB_IO_PARSER_H_

#include <iostream>

#include "core/log.h"
#include "core/neuron.h"

namespace neurostr {
namespace io {
  
/**
 * @class Parser
 * @author luis
 * @date 28/10/16
 * @file parser.h
 * @brief Base virutal class for reconstruction parsers
 */
class Parser {

public:

  /**
   * @brief Constructs copy the istream reference
   * @param s Input stream
   */
  Parser( std::istream& s) 
    : stream_(s)
    , error_count(0)
    , warn_count(0)
    , critical_error(false){};
  
  
  virtual ~Parser(){};
  // dO NOT allow copy
  /**
   * @brief Deleted copy constructor
   */
  Parser(const Parser&) = delete;
  
  /**
   * @brief Deleted copy operator
   */
  Parser& operator=(const Parser&) = delete;
  
  /**
   * @brief Set the error count to the default state
   */
  void reset_errors() { error_count = warn_count = 0; critical_error=false; }
  
  /**
   * @brief Get number of errors
   * @return Error count
   */
  int error() const { return error_count; };
  
  /**
   * @brief Get number of warnigs
   * @return  Warning count
   */
  int warn() const { return warn_count; };
  
  
  /**
   * @brief Critical error flag
   * @return  True if a critical error has happened.
   */
  bool critical() const { return critical_error; };
  
  /**
   * @brief Reads a reconstruction from the stream and returns a unique_ptr
   * @param name Reconstruction ID
   * @return Unique ptr to the reconstruction (Ownership)
   */
  virtual std::unique_ptr<Reconstruction> read(const std::string& name) = 0;
  
  
protected:

  /**
  * Input stream variable
  */
  std::istream& stream_;
  
  /**
   * Error status
   */
  int error_count;
  int warn_count;
  bool critical_error;
  
  /**
   * @brief Processes the error, log it and increments the error count
   * @param e Error
   */
  void process_error(const std::exception& e){
    NSTR_LOG_(error, e.what());
    ++error_count;
  }
   
};

} // io
} // neurostr

#endif
