#ifndef NEUROSTRLIB_IO_PARSER_DISPATCHER_H_
#define NEUROSTRLIB_IO_PARSER_DISPATCHER_H_

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include "core/neuron.h"

#include "io/parser.h"
#include "io/ASCParser.h"
#include "io/DATParser.h"
#include "io/SWCParser.h"
#include "io/JSONParser.h"

namespace neurostr {
namespace io{
  
  /**
   * @brief Given a string with the file extension, returns a pointer to the adequate parser
   * @param ext File extension
   * @return Parser pointer
   */
  Parser* get_parser_by_ext(const std::string& ext);

  /**
   * @brief Opens a filestream. If the extension is DAT the file is open with the binary flag activated
   * @param path File path
   * @param s File extension
   * @param ret Stream to be opened
   */
  void open_filestream(const std::string& path, const std::string& s, std::ifstream& ret) ;

  /**
   * @brief Given a file path, selects the parser by the file extension and processes its content
   * @param path File path
   * @return Reconstruction
   */
  std::unique_ptr<Reconstruction> read_file_by_ext(const std::string& path);
}
}

#endif
