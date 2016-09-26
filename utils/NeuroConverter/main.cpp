#include <stdio.h>

#include <stdio.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/format.hpp>

//#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include "io/parser_dispatcher.h"
#include "io/SWCWriter.h"
#include "io/JSONWriter.h"

namespace po = boost::program_options;

int main(int ac, char **av)
{
  std::string ifile;
  std::string ofile;
  std::string ext;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("format,f", po::value< std::string>(&ext), "Output format (swc or json)")
    ("output,o", po::value< std::string>(&ofile), "Output file")
    ;
    
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: NeuroConverter -i test.swc -o test.json  " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input/output file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: NeuroConverter -i test.swc -o test.json  " << std::endl << std::endl ;
    return 2;
  }
  
  // Create ofstream /ifstreams
  std::ofstream ofs(ofile);
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);
  if(ext == "swc"){
    neurostr::io::SWCWriter writer(ofs);
    writer.write(*(r->begin())); // STANDARIZEME
    
  } else if (ext == "json"){
    neurostr::io::JSONWriter writer(ofs);
    writer.write(*r);
  } else {
    std::cout << "ERROR: unrecognized output format" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Accepted formats: swc, json" << std::endl << std::endl ;
    return 3;
  }
  
  ofs.close();
}
