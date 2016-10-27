#ifndef NEUROSTR_LOG_H_
#define NEUROSTR_LOG_H_

#include <spdlog/spdlog.h>

namespace neurostr{
namespace log{


/**
*  expose severity levels
*/
using severity_level = spdlog::level::level_enum;

// Unique logger
class _logger_storage {

private:
  std::shared_ptr<spdlog::logger> ptr_;
  bool enabled = false;
  
  std::string format = "[%l]   %v";
  severity_level level = severity_level::warn;

public:
  
  void set(std::shared_ptr<spdlog::logger>&& l){
      ptr_ = l;
      ptr_->set_level(level);
      ptr_->set_pattern(format);
  }
  
  void set_level(severity_level l){
    level = l;
    ptr_->set_level(level);
  }
  
  void set_format(const std::string& fmt){
    format = fmt;
    ptr_->set_pattern(format);
  }
  
  void enable() {
    enabled = true;
  }
  
  void disable() {
    enabled = false;
  }
  
  bool status() const {
    return enabled;
  }
  
  spdlog::logger& get(){
    return *ptr_;
  }
};

extern _logger_storage _nstr_logger_;

// Less verbosity
#ifndef NSTR_NOLOG
#define NSTR_LOG_(lvl, msg) \
  if(neurostr::log::_nstr_logger_.status()){neurostr::log::_nstr_logger_.get().lvl(msg+std::string("\t(@")+std::string(__FUNCTION__)+")\t" );}
#else
#define NSTR_LOG_(lvl, msg) 
#endif
/**
 * @brief Inits file logger
 * @param path Log file path
 * @param format_string Log format string
 */
void init_log_file(const std::string& path);

/**
 * @brief Inits logger thorugh cout
 * @param format_string Log format 
 */
void init_log_cout();
void init_log_cerr();


void disable_log();
void enable_log();

void set_format(const std::string& s);
void set_level(severity_level l);

} // log
} // neurostr

#endif
