/**
 * @file simplelog/backend/spdlog/LogBackendMacros.hpp
 * 
 * Simple example how a generic logging framework w/ different logging 
 * subsystems could look like.
 * 
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 **/

#pragma once

// -- INCLUDES:
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>
// MAYBE: #include <spdlog/sinks/stdout_color_sinks.h>

// --------------------------------------------------------------------------
// LOGGING BACKEND ADAPTER HELPERS
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_spdlog {

inline auto getDefaultSink(void)
{
    static ::spdlog::sink_ptr theSink(new ::spdlog::sinks::stdout_sink_mt());
    return theSink;
}
inline auto useOrCreateLogger(std::string name)
{
    auto logPtr = spdlog::get(name);
    if (!logPtr)
    {
        // logPtr = ::spdlog::stdout_logger_mt(name);
        logPtr.reset(new ::spdlog::logger(name, getDefaultSink()));
        spdlog::register_logger(logPtr);
    }
    // return std::move(logPtr);
    return logPtr;
}

}} //< NAMESPACE-END: simplelog::backend::spdlog
