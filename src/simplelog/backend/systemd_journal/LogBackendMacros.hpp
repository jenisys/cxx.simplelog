/**
 * @file simplelog/backend/systemd_journal/LogBackendMacros.hpp
 * Simplelog backend for systemd journald logging service.
 *
 * @see https://www.freedesktop.org/software/systemd
 * @see https://www.freedesktop.org/software/systemd/man/sd_journal_print.html#
 **/

#pragma once

#error "WIP: Not usable yet"

// -- INCLUDES:
#include <systemd/sd-journal.h>
#include "simplelog/backend/systemd_journal/Module.hpp"

#ifdef SIMPLELOG_BACKEND_LOG
#error "ALREADY_DEFINED: SIMPLELOG_BACKEND_LOG"
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
// #define _SIMPLELOG_NUMARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#define SIMPLELOG_BACKEND_DEFINE_MODULE(vname, name) auto vname = ::simplelog::backend_systemd_journal::Module(name)
#define SIMPLELOG_BACKEND_LOG(logger, level, format, ...) logger.log(level, format, __VA_ARGS__)
#define SIMPLELOG_BACKEND_LOG0(logger, level, message)    logger.log(level, message)

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
// SAME-AS: syslog levels (unused: LOG_ALERT
// #define SIMPLELOG_BACKEND_LEVEL_OFF ::spdlog::level::off
#define SIMPLELOG_BACKEND_LEVEL_FATAL   LOG_EMERG
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL LOG_CRIT
#define SIMPLELOG_BACKEND_LEVEL_ERROR   LOG_ERR
#define SIMPLELOG_BACKEND_LEVEL_WARN    LOG_WARNING
#define SIMPLELOG_BACKEND_LEVEL_INFO    LOG_INFO
#define SIMPLELOG_BACKEND_LEVEL_DEBUG   LOG_DEBUG

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
#include "simplelog/detail/LogBackendDerivedMacros.hpp"
