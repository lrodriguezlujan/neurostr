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

#include "core/log.h"
#include "core/neuron.h"

#include "io/parser_dispatcher.h"

#include "methods/boxCutter.h"

#include "io/JSONWriter.h"

namespace po = boost::program_options;

/**
 * @brief 
 * @param ac
 * @param av
 * @return 
 */
int main(int ac, char **av)
{
  // Log errors in std::cerr
  neurostr::log::init_log_cerr();
  neurostr::log::enable_log();
  
  std::string ifile;
  std::string ofile;
  
  float min_corner[3];
  float max_corner[3];
  
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "Produce help message")
    ("input,i", po::value< std::string >(&ifile), "Neuron reconstruction file")
    ("output,o", po::value< std::string >(&ofile), "Neuron reconstruction JSON output file")
    ("minx", po::value< float >(min_corner) ,"Box min corner - x value")
    ("miny", po::value< float >(min_corner+1) ,"Box min corner - y value")
    ("minz", po::value< float >(min_corner+2) ,"Box min corner - z value")
    ("maxx", po::value< float >(max_corner) ,"Box max corner - x value")
    ("maxy", po::value< float >(max_corner+1) ,"Box max corner - y value")
    ("maxz", po::value< float >(max_corner+2) ,"Box max corner - z value");
  
  
  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).run(), vm);
  po::notify(vm);    
  
	if (vm.count("help")){
    std::cout << desc << "\n";
    std::cout << "Example: BoxCutter -i test.swc -o test_cutz10.json --minz 10 " << std::endl << std::endl ;
    return 1;
  }
  
  if(!vm.count("input") || !vm.count("output")){
    std::cout << "ERROR: input and output files required" << std::endl << std::endl;
    std::cout << desc << "\n";
    std::cout << "Example: BoxCutter -i test.swc -o test_cutz10.json --minz 10 " << std::endl << std::endl ;
    return 2;
  }
  
  // Open ostream
  std::ofstream ofs(ofile);
  
  /*** END PARAMETER PARSING */
  
  // Read
  auto r = neurostr::io::read_file_by_ext(ifile);
  
  // For each neuron
  for(auto n_it = r->begin(); n_it != r->end(); ++n_it){
    
    // Cut every neuron in the reconstruction
    neurostr::Neuron& n = *n_it;
    
    // Default box
    auto box = n.boundingBox();
    neurostr::point_type original_min_corner = box.min_corner();
    neurostr::point_type original_max_corner = box.max_corner();
    
    // Set given positions
    if(!vm.count("minx")) min_corner[0] = neurostr::geometry::getx(original_min_corner);
    if(!vm.count("miny")) min_corner[1] = neurostr::geometry::gety(original_min_corner);
    if(!vm.count("minz")) min_corner[2] = neurostr::geometry::getz(original_min_corner);
    
    if(!vm.count("maxx")) max_corner[0] = neurostr::geometry::getx(original_max_corner);
    if(!vm.count("maxy")) max_corner[1] = neurostr::geometry::gety(original_max_corner);
    if(!vm.count("maxz")) max_corner[2] = neurostr::geometry::getz(original_max_corner);
    
    // Cut neuron
    neurostr::methods::neuronBoxCutter(n, 
                                       neurostr::point_type(min_corner[0],min_corner[1],min_corner[2]),
                                       neurostr::point_type(max_corner[0],max_corner[1],max_corner[2]));
    
  } // End neuron for
  neurostr::io::JSONWriter writer(ofs);
  writer.write(*r);
}

