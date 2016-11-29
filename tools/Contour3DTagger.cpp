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

#include <neurostr/core/log.h>
#include <neurostr/io/parser_dispatcher.h>
#include <neurostr/io/SWCWriter.h>
#include <neurostr/io/JSONWriter.h>
#include <neurostr/methods/triContour.h>

namespace po = boost::program_options;

int main(int ac, char **av)
{
  
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();
  
  std::string ifile;
  std::string ofile;
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("output,o", po::value< std::string>(&ofile), "Output file")
    ("name,n", po::value< std::vector<std::string>>(), "Contour names")
    ;
    
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_contourtag -i axon.dat -o test.json  -n \"Layer VI\" -n \"Layer V\" -n \"Layer IV\" -n \"Layer II-III\"  " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("input")){
    std::cout << "ERROR: input/output file required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: neurostr_contourtag -i test.swc -o test.json  -n \"Layer VI\" -n \"Layer V\" -n \"Layer IV\" -n \"Layer II-III\" " << std::endl << std::endl ;
    return 2;
  }
  
  // Create ofstream /ifstreams
  std::ofstream ofs(ofile);
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // Process contour
   std::vector<std::string> names = vm["name"].as<std::vector<std::string>>();
   for(auto it = names.begin(); it != names.end(); ++it){
     // always assume contours are parallel in "z" - 2 is static
      neurostr::methods::reconstructionContourProcess(*r,*it,2);
   }
  
  
  // Write in JSON (We should get the property set)
  neurostr::io::JSONWriter writer(ofs);
  writer.write(*r);
  
  
  ofs.close();
}
