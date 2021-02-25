/**
 * @file simplelog/backend/syslog/LogBackendMacros.hpp
 * Provides LOG_BACKEND_xxx() macros for syslog logging facility.
 *
 * @see https://linux.die.net/man/3/syslog
 * @see https://www.man7.org/linux/man-pages/man3/syslog.3.html
 * @see https://github.com/fmtlib/fmt
 *
 * @note ALTERNATIVE:
 *  Use simplelog.backend.spdlog and use syslog LogSink.
 **/

#pragma once

// -- REQUIRE: syslog is available/supported.
// #include "simplelog/detail/RequiresHeaderFileMacro.hpp"
// SIMPLELOG_REQUIRES_HEADER_FILE(<syslog.h>)
// #ifdef __has_include
// #  if  !__has_include(<syslog.h>)
// #   error "simplelog.backend.syslog: REQUIRES <syslog.h> HEADER-FILE (NOT
// FOUND)" #  endif #endif

// -- INCLUDES:
#include "simplelog/backend/syslog/ModuleRegistry.hpp"

#include <syslog.h>

#ifdef SIMPLELOG_BACKEND_LOG
#    error "ALREADY_DEFINED: SIMPLELOG_BACKEND_LOG"
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_DEFINE_MODULE(module, name)                          \
    auto module = ::simplelog::backend_syslog::useOrCreateModule(name)
#define SIMPLELOG_BACKEND_LOG(module, level, ...)                              \
    module->log(level, __VA_ARGS__)
#define SIMPLELOG_BACKEND_LOG0(module, level, message)                         \
    module->log(level, message)

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_LEVEL_OFF LOG_EMERG
#define SIMPLELOG_BACKEND_LEVEL_FATAL LOG_EMERG
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL LOG_CRITICAL
#define SIMPLELOG_BACKEND_LEVEL_ERROR LOG_ERR
#define SIMPLELOG_BACKEND_LEVEL_WARN LOG_WARNING
#define SIMPLELOG_BACKEND_LEVEL_INFO LOG_INFO
#define SIMPLELOG_BACKEND_LEVEL_DEBUG LOG_DEBUG

// -- UNUSED LEVELS:
#define SIMPLELOG_BACKEND_LEVEL_ALERT LOG_ALERT //< .., CRITICAL, ALERT, EMERG
#define SIMPLELOG_BACKEND_LEVEL_NOTICE                                         \
    LOG_NOTICE //< .., INFO, NOTICE, WARNING, ..

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
// HINT: Derive other LogBackendMacros from existing ones.
#include "simplelog/detail/LogBackendDerivedMacros.hpp"

//< HEADER-FILE-END
