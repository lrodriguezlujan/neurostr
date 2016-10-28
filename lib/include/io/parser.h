#ifndef NEUROSTRLIB_IO_PARSER_H_
#define NEUROSTRLIB_IO_PARSER_H_

#include <iostream>

#include "core/log.h"
#include "core/neuron.h"

namespace neurostr {
namespace io {
  

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
  
  void reset_errors() { error_count = warn_count = 0; critical_error=false; }
  int error() const { return error_count; };
  int warn() const { return warn_count; };
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
  
  // Process exception
  void process_error(const std::exception& e){
    NSTR_LOG_(error, e.what());
    ++error_count;
  }
   
};

} // io
} // neurostr

#endif
