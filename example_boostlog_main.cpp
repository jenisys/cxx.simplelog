/**
 * @file example_null_main.cpp
 * Simple example of generic logging w/ NULL backend.
 **/

// -- INCLUDES:
#define SIMPLELOG_USE_BACKEND_NULL 1
#include "simplelog/LogMacros.hpp"
#include <iostream>


// ==========================================================================
// EXAMPLE
// ==========================================================================
void example_useLogging(void)
{
    CXXLOG_DEFINE_CATEGORY(log, "foo.bar");
    // spdlog_setLevelToAll(CXXLOG_BACKEND_LEVEL_INFO);

    CXXLOG_ERROR0(log, "Hello Alice");
    CXXLOG_WARN(log, "Hello {}", "Bob");
    CXXLOG_INFO(log, "Hello {0} and {1}", "Alice", "Bob");
    CXXLOG_INFO(log, "Hello type {0}, int:{1} and bool:{2}", "Alice", 42, true);
}

void example_useTwoLoggers(void)
{
    CXXLOG_DEFINE_CATEGORY(log1, "foo.one");
    CXXLOG_DEFINE_CATEGORY(log2, "foo.two");

    CXXLOG_ERROR0(log1, "Logger_1");
    CXXLOG_WARN0(log2, "Logger_2");
}

void example_useTwoLoggersWithSameName(void)
{
    CXXLOG_DEFINE_CATEGORY(log1, "foo.same");
    CXXLOG_DEFINE_CATEGORY(log2, "foo.same");

    CXXLOG_ERROR0(log1, "Logger_1");
    CXXLOG_WARN0(log2,  "Logger_2");
}

// std::shared_ptr<spdlog::logger>
auto getLogger(void)
{
    // static CXXLOG_DEFINE_CATEGORY(theLog, "foo.static");
    CXXLOG_DEFINE_STATIC_CATEGORY(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getLogger();
    CXXLOG_ERROR0(log, "Hello Alice");
}


CXXLOG_DEFINE_STATIC_CATEGORY(rootLog, "root");

// ==========================================================================
// MAIN-FUNCTION
// ==========================================================================
// http://gernotklingler.com/blog/simple-customized-logger-based-boost-log-v2/
// https://www.johnlamp.net/cmake-tutorial-6-realistically-getting-a-boost.html
// https://stackoverflow.com/questions/16540171/boost-log-gcc-4-4-and-cmake
// https://www.boost.org/doc/libs/1_68_0/libs/log/doc/html/index.html
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

enum class LogLevel : int {
    debug = 1,
    info = 2,
    warn = 3,
    error = 4,
    critical = 5,
    fatal = 6
};

// Here we define our application severity levels.
#if 0
enum severity_level {
    normal,
    info,
    warn,
    error,
    critical
};
#endif

#if 0
// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, LogLevel level)
{
    static const char *const names[] =
    {
        	"debug",
            "info",
            "warn",
            "error",
            "critical",
            "fatal",
    };
    if (static_cast<std::size_t>(level) < (sizeof(names)/sizeof(*names)))
        strm << names[level];
    else
        strm << static_cast<int>(level);
    return strm;
}
#endif

#if 0
// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char *const str[] =
        {
            "normal",
            "info",
            "warn",
            "error",
            "critical"};
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast<int>(lvl);
    return strm;
}
#endif

// XXX-LINK-ERROR
int main(int argc, char **argv)
{
	// -- IDEA: Using boost::log::trivial
	// #include <boost/log/trivial.hpp>
	// boost::log::trivial::logger_type = severity_logger
	// boost::trivial::severity_level (enum)

    // -- SETUP LOGGING SUBSYSTEM: noop
    std::cout << "BOOST.LOG-EXAMPLE:"<< std::endl;
#if 0    
    example_useLogging();
    example_useTwoLoggers();
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();
#else
    // XXX typedef boost::log::sources::severity_logger<LogLevel> slogger;
    // typedef boost::log::sources::severity_logger<severity_level> slogger;
    typedef boost::log::trivial::logger_type slogger;
    namespace logging = boost::log;
    namespace keywords = boost::log::keywords;
    namespace attrs = boost::log::attributes;

    logging::add_console_log(std::clog,
    		keywords::format = "%TimeStamp%: %Severity%: %Message%");
    logging::add_common_attributes();
#if 1
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
#endif    
    // logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());
    BOOST_LOG_FUNCTION();
    // using boost::log::v2s_mt_posix::record;
    // using boost::log::v2s_mt_posix::record_view;

    slogger log;

#define BOOST_LOG_TSEV(log, lvl)\
	    BOOST_LOG_STREAM_WITH_PARAMS(log, \
	        (::boost::log::keywords::severity = ::boost::log::trivial::lvl))

#if 1
    BOOST_LOG_TSEV(log, info) << "A regular message";
    BOOST_LOG_TSEV(log, warning) << "Something bad is going on but I can handle it";
    BOOST_LOG_TSEV(log, error) << "Everything crumbles, shoot me now!";
#elif 0
    BOOST_LOG_SEV(log, info) << "A regular message";
    BOOST_LOG_SEV(log, warning) << "Something bad is going on but I can handle it";
    BOOST_LOG_SEV(log, error) << "Everything crumbles, shoot me now!";
#else
    BOOST_LOG_SEV(log, LogLevel::info) << "A regular message";
    BOOST_LOG_SEV(log, LogLevel::warn) << "Something bad is going on but I can handle it";
    BOOST_LOG_SEV(log, LogLevel::error) << "Everything crumbles, shoot me now!";
#endif
#endif
    std::cout << "BOOST.LOG-EXAMPLE: Finished." << std::endl;
    return 0;
}
