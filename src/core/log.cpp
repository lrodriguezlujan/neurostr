#include <neurostr/core/log.h>

namespace neurostr{
namespace log{

 _logger_storage _nstr_logger_;


void init_log_file(const std::string& path) {
  spdlog::drop("global");
  _nstr_logger_.set(spdlog::basic_logger_mt("global",path));
                    
  
}

void init_log_cout(){
  spdlog::drop("global");
  _nstr_logger_.set(spdlog::stdout_color_mt("global"));
}

void init_log_cerr(){
  spdlog::drop("global");
  _nstr_logger_.set(spdlog::stderr_color_mt("global"));
}

void disable_log(){
  _nstr_logger_.disable();
}

void enable_log(){
  _nstr_logger_.enable();
}

void set_format(const std::string& s){
  _nstr_logger_.set_format(s);
}


void set_level(severity_level l){
  _nstr_logger_.set_level(l);
}

} // log
} // neurostr
