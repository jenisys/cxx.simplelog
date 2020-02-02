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
#include "simplelog/backend/spdlog/ModuleUtil.hpp"

#include <spdlog/spdlog.h>
// #include <spdlog/logger.h>
// #include <spdlog/sinks/stdout_sinks.h>
// MAYBE: #include <spdlog/sinks/stdout_color_sinks.h>

#ifdef SIMPLELOG_BACKEND_LOG
#    error "ALREADY_DEFINED: SIMPLELOG_BACKEND_LOG"
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
// #define _SIMPLELOG_NUMARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#define SIMPLELOG_BACKEND_DEFINE_MODULE(vname, name)      auto vname = ::simplelog::backend_spdlog::useOrCreateLogger(name)
#define SIMPLELOG_BACKEND_LOG(logger, level, format, ...) logger->log(level, format, __VA_ARGS__)
#define SIMPLELOG_BACKEND_LOG0(logger, level, message)    logger->log(level, message)

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_LEVEL_OFF      ::spdlog::level::off
#define SIMPLELOG_BACKEND_LEVEL_FATAL    ::spdlog::level::off
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL ::spdlog::level::critical
#define SIMPLELOG_BACKEND_LEVEL_ERROR    ::spdlog::level::err
#define SIMPLELOG_BACKEND_LEVEL_WARN     ::spdlog::level::warn
#define SIMPLELOG_BACKEND_LEVEL_INFO     ::spdlog::level::info
#define SIMPLELOG_BACKEND_LEVEL_DEBUG    ::spdlog::level::debug

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
#include "simplelog/backend/detail/LogBackendDerivedMacros.hpp"
