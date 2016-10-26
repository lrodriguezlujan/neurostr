#include "core/log.h"

namespace neurostr{
namespace log{

  using namespace boost::log::trivial;
  namespace expr = boost::log::expressions;



BOOST_LOG_GLOBAL_LOGGER_INIT(logger, boost::log::sources::severity_logger_mt<severity_level>){
  boost::log::sources::severity_logger_mt<severity_level> lg;
  boost::log::add_common_attributes();
  boost::log::core::get()->set_filter( boost::log::trivial::severity >= boost::log::trivial::info );
  return lg;
}

void init_log_file(const std::string& path) {
                     boost::log::add_file_log(path,
                                boost::log::keywords::format = expr::stream
                                     <<  "[" << severity << "]\t\t" << expr::smessage);
                    
  
}

void init_log_cout(){
  boost::log::add_console_log(std::cout,  
                              boost::log::keywords::format = expr::stream
                                    << "[" << severity << "]\t\t" << expr::smessage);
}

void init_log_cerr(){
  boost::log::add_console_log(std::cerr,  
                              boost::log::keywords::format = expr::stream
                                    << "[" << severity << "]\t\t" << expr::smessage);
}

void disable_log(){
  boost::log::core::get()->set_logging_enabled(false);
}

void enable_log(){
  boost::log::core::get()->set_logging_enabled(true);
}

} // log
} // neurostr
