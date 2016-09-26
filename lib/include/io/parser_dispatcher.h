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
  Parser* get_parser_by_ext(const std::string& ext);

  void open_filestream(const std::string& path, const std::string& s, std::ifstream& ret) ;
  
  std::unique_ptr<Reconstruction> read_file_by_ext(const std::string& path);
}
}

#endif
