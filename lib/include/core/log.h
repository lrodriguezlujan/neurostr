#ifndef NEUROSTR_LOG_H_
#define NEUROSTR_LOG_H_

#include <spdlog/spdlog.h>

namespace neurostr{
  
/**
* @brief Log namespace contains logger functions.
*/
namespace log{


/**
*@brief Log severity levels from spdlog
*/
using severity_level = spdlog::level::level_enum;

/**
 * @class _logger_storage
 * @file log.h
 * @brief Auxiliar structure to share a log across all files in the library
 */
class _logger_storage {

private:
  std::shared_ptr<spdlog::logger> ptr_;
  bool enabled = false;
  
  std::string format = "[%l]   %v";
  severity_level level = severity_level::warn;

    public:

  /**
   * @brief Changes the current logger (From spdlog=
   * @param l New logger
   */
  void set(std::shared_ptr<spdlog::logger>&& l){
      ptr_ = l;
      ptr_->set_level(level);
      ptr_->set_pattern(format);
  }
  
  /**
   * @brief Changes the severity level threshold
   * @param l New severity level
   */
  void set_level(severity_level l){
    level = l;
    ptr_->set_level(level);
  }
  
  /**
   * @brief Changes output format string
   * @param fmt Format string
   */
  void set_format(const std::string& fmt){
    format = fmt;
    ptr_->set_pattern(format);
  }
  
  /**
   * @brief Activates logger functions
   */
  void enable() {
    enabled = true;
  }
  
  /**
   * @brief Deactivates logger functions
   */
  void disable() {
    enabled = false;
  }
  
  /**
   * @brief Returns the current logger status
   * @return True if the logger is active
   */
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
/**
* @brief Log macro that outputs the given message through the logger.
* @param lvl Severity level
* @param msg Log message
*/
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
 * @brief Initializes the logger using the standard output stream
 */
void init_log_cout();

/**
 * @brief Initializes the logger using the standard error stream
 */
void init_log_cerr();

/**
 * @brief Disables the log
 */
void disable_log();

/**
 * @brief Enables the log
 */
void enable_log();

/**
 * @brief Changes current log format
 */
void set_format(const std::string& s);

/**
 * @brief Changes current logger severity threshold
 */
void set_level(severity_level l);

} // log
} // neurostr

#endif
