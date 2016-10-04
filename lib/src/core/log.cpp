#include "core/log.h"

namespace neurostr{
namespace log{

  using namespace boost::log::trivial;
  namespace expr = boost::log::expressions;

BOOST_LOG_GLOBAL_LOGGER_DEFAULT(logger, boost::log::sources::severity_logger_mt<severity_level>);

void init_log_file(const std::string& path) {
    
                     boost::log::add_file_log(path,
                                boost::log::keywords::format = expr::stream
                                    << expr::attr< unsigned int >("LineID")
                                    << ": [" << severity
                                    << "] " << expr::smessage);
                    
  
}

void init_log_cout(){
  boost::log::add_common_attributes();
  boost::log::add_console_log(std::cout,  
                              boost::log::keywords::format = expr::stream
                                    << "[" << severity
                                    << "]\t" << expr::smessage);
}

void log_level(severity_level lvl){
   boost::log::core::get()->set_filter( boost::log::trivial::severity >= lvl );
}

} // log
} // neurostr
