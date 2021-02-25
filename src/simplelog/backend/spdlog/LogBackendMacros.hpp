/**
 * @file simplelog/backend/spdlog/LogBackendMacros.hpp
 * Provides logging backend macros for spdlog (as logging framework).
 *
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 * @see https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/backend/spdlog/ModuleUtil.hpp"

#include <spdlog/spdlog.h>

#ifdef SIMPLELOG_BACKEND_LOG
#    error "ALREADY_DEFINED: SIMPLELOG_BACKEND_LOG"
#endif
// -- AUTO-CONFIGURE:
#ifndef SIMPLELOG_BACKEND_SPDLOG__USE_SOURCE_LOCATION
#    define SIMPLELOG_BACKEND_SPDLOG__USE_SOURCE_LOCATION 1
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
/**
 * @macro SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
 * Defines a logging module (logger).
 **/
#define SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)                        \
    auto var_name = ::simplelog::backend_spdlog::useOrCreateLogger(name)

/**
 * @macro SIMPLELOG_BACKEND_LOG(logger, level, ...)
 * Logs a log-record with the logging backend (concrete logging framework).
 *
 * CASE 1: SIMPLELOG_BACKEND_LOG(logger, level, message)
 * CASE 2: SIMPLELOG_BACKEND_LOG(logger, level, format, ...)  -- With
 *placeholders
 **/
#if SIMPLELOG_BACKEND_SPDLOG__USE_SOURCE_LOCATION
#    define SIMPLELOG_BACKEND_LOG(logger, level, ...)                          \
        logger->log(::spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, \
                    level, __VA_ARGS__)
#else
#    define SIMPLELOG_BACKEND_LOG(logger, level, ...)                          \
        logger->log(level, __VA_ARGS__)
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_LEVEL_OFF ::spdlog::level::off
#define SIMPLELOG_BACKEND_LEVEL_FATAL ::spdlog::level::off
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL ::spdlog::level::critical
#define SIMPLELOG_BACKEND_LEVEL_ERROR ::spdlog::level::err
#define SIMPLELOG_BACKEND_LEVEL_WARN ::spdlog::level::warn
#define SIMPLELOG_BACKEND_LEVEL_INFO ::spdlog::level::info
#define SIMPLELOG_BACKEND_LEVEL_DEBUG ::spdlog::level::debug

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
#include "simplelog/detail/LogBackendDerivedMacros.hpp"
