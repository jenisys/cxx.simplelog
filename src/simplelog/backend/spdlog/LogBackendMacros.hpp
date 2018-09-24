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

#ifdef CXXLOG_BACKEND_LOG
#error "ALREADY_DEFINED: CXXLOG_BACKEND_LOG"
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND ADAPTER HELPERS
// --------------------------------------------------------------------------
#if 0
namespace
{
// static auto CXXLOG_DEFAULT_SINK = spdlog::stdout_color_mt("console");
// static auto CXXLOG_DEFAULT_SINK = spdlog::sinks::stdout_sink_mt("console");
// XXX static spdlog::sink_ptr CXXLOG_DEFAULT_SINK_PTR = new spdlog::sinks::stdout_sink_mt();
}; // namespace
#endif

// #define _CXXLOG_IMPL_DEFINE_CATEGORY(name) ::spdlog::logger(name, CXXLOG_DEFAULT_SINK_PTR))
auto spdlog_getDefaultSink(void)
{
    static ::spdlog::sink_ptr theSink(new ::spdlog::sinks::stdout_sink_mt());
    return theSink;
}
auto spdlog_useOrCreateLogger(std::string name)
{
    auto logPtr = spdlog::get(name);
    if (!logPtr)
    {
        // logPtr = ::spdlog::stdout_logger_mt(name);
        logPtr.reset(new ::spdlog::logger(name, spdlog_getDefaultSink()));
        spdlog::register_logger(logPtr);
    }
    return std::move(logPtr);
}

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
// #define _CXXLOG_NUMARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#define CXXLOG_BACKEND_DEFINE_CATEGORY(vname, name) auto vname = spdlog_useOrCreateLogger(name)
#define CXXLOG_BACKEND_DEFINE_STATIC_CATEGORY(vname, name) static CXXLOG_BACKEND_DEFINE_CATEGORY(vname, name)
#define CXXLOG_BACKEND_LOG(logger, level, format, ...) logger->log(level, format, __VA_ARGS__)
#define CXXLOG_BACKEND_LOG0(logger, level, message) logger->log(level, message)
#define CXXLOG_BACKEND_LOG_IF(condition, logger, level, format, ...) \
    if (condition) { CXXLOG_BACKEND_LOG(logger, level, format, __VA_AGRS__); }
#define CXXLOG_BACKEND_LOG0_IF(condition, logger, level, message) \
    if (condition) { CXXLOG_BACKEND_LOG0(logger, level, message); }

#define CXXLOG_BACKEND_LEVEL_OFF ::spdlog::level::off
#define CXXLOG_BACKEND_LEVEL_FATAL ::spdlog::level::off
#define CXXLOG_BACKEND_LEVEL_CRITICAL ::spdlog::level::critical
#define CXXLOG_BACKEND_LEVEL_ERROR ::spdlog::level::err
#define CXXLOG_BACKEND_LEVEL_WARN ::spdlog::level::warn
#define CXXLOG_BACKEND_LEVEL_INFO ::spdlog::level::info
#define CXXLOG_BACKEND_LEVEL_DEBUG ::spdlog::level::debug

