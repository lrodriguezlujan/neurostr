#ifndef NEUROSTR_LOG_H_
#define NEUROSTR_LOG_H_

//#include <boost/logging/format/named_write_fwd.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>


#ifdef DEDICATED_LOG_THREAD
  #include <boost/logging/writer/on_dedicated_thread.hpp>
#endif

namespace neurostr{
namespace log{

using namespace boost::log::trivial;


//core->add_global_attribute("Scope", attrs::named_scope());

BOOST_LOG_GLOBAL_LOGGER(logger,  boost::log::sources::severity_logger_mt<severity_level>)



// Less verbosity
#define NSTR_LOG_(lvl) \
        BOOST_LOG_SEV(neurostr::log::logger::get(), boost::log::trivial::lvl)

/**
 *  expose severity levels
 */
const severity_level trace = boost::log::trivial::trace;
const severity_level debug = boost::log::trivial::debug;
const severity_level info = boost::log::trivial::info;
const severity_level warning = boost::log::trivial::warning;
const severity_level error = boost::log::trivial::error;
const severity_level fatal = boost::log::trivial::fatal;


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

} // log
} // neurostr

#endif
