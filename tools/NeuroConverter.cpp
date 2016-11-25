#include <string>
#include <iostream>
#include <algorithm>
#include <exception>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/format.hpp>

//#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

#include <neurostr/core/log.h>
#include <neurostr/io/parser_dispatcher.h>
#include <neurostr/io/SWCWriter.h>
#include <neurostr/io/JSONWriter.h>

namespace po = boost::program_options;

int main(int ac, char **av)
{
  
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();
  
  // Input file
  std::string ifile;
  
  // Output file
  std::string ofile;
  
  // Output Format
  std::string ext;
  
  // Apply correct
  bool correct = false;
  
  // Apply RDP simplification
  float eps = 0.0;
  
  // Program options declaration
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("format,f", po::value< std::string>(&ext), "Output format (swc or json)")
    ("output,o", po::value< std::string>(&ofile), "Output file")
    ("correct,c", "Try to correct errors in the reconstruction")
    ("eps,e", po::value< float >(&eps) -> default_value(0.0), "Output file")
    ("verbose,v", "Verbose log output")
    ;
  
  // Parse options into the variable map
  po::variables_map vm;
  try{
    po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
    po::notify(vm);    
  } catch (std::exception e){
    // Something went wrong in the param. parsing
    NSTR_LOG_(error, "Unrecognized option");
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_converter -i test.swc -o test.json  -f json" << std::endl << std::endl ;
    return 1;
  }
  
  // Help option
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_converter -i test.swc -o test.json -f json " << std::endl << std::endl ;
    return 2;
  }
  
  // Missing input/output
  if(!vm.count("input") || !vm.count("output")){
    NSTR_LOG_(error, "Input/output file required");
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_converter -i test.swc -o test.json -f json " << std::endl << std::endl ;
    return 3;
  }
  
  //Get correct flag
  correct = vm.count("correct");
  
  // Verbosity
  if(vm.count("verbose")){
    neurostr::log::set_level(neurostr::log::severity_level::debug);
  }
  
  // Create ofstream /ifstreams
  std::ofstream ofs(ofile);
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Simpify / correct
  for(auto it = r->begin(); it != r->end(); ++it){
    if(correct) it->correct();
    if(eps != 0.0 ){
      it->simplify(eps);
    }
  }
  
  // Transform extension to lower
  std::transform(ext.begin(),ext.end(),ext.begin(),::tolower);
  
  // Select a writer depending on the extension
  if(ext == "swc"){
    if(r->size() > 1){
      NSTR_LOG_(warn, "The output SWC file will only contain the first neuron in the reconstruction. The rest are ignored");
    }
    neurostr::io::SWCWriter writer(ofs);
    writer.write(*(r->begin()));  // Writes first neuron
    
  } else if (ext == "json"){
    neurostr::io::JSONWriter writer(ofs);
    writer.write(*r);
  } else {
    // Error - Unrecognized
    NSTR_LOG_(error,"Unrecognized output format");
    std::cout << desc << "\n";
    std::cout << "Accepted formats: swc, json" << std::endl << std::endl ;
    return 4;
  }
  
  // Close stream - Reconstruction should be autom. free'd (unique_ptr)
  ofs.close();
}
