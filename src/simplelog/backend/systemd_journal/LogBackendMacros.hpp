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
#include "simplelog/backend/systemd_journal/ModuleRegistry.hpp"
#include "simplelog/backend/systemd_journal/Module.hpp"

#ifdef SIMPLELOG_BACKEND_LOG
#error "ALREADY_DEFINED: SIMPLELOG_BACKEND_LOG"
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_DEFINE_MODULE(module, name) auto module = ::simplelog::backend_systemd_journal::useOrCreateModule(name)
#define SIMPLELOG_BACKEND_LOG(module, level, ...)       module.log(level, __VA_ARGS__)
#define SIMPLELOG_BACKEND_LOG0(module, level, message)  module.log(level, message)

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_LEVEL_OFF LOG_EMERG
#define SIMPLELOG_BACKEND_LEVEL_FATAL   LOG_EMERG
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL LOG_CRIT
#define SIMPLELOG_BACKEND_LEVEL_ERROR   LOG_ERR
#define SIMPLELOG_BACKEND_LEVEL_WARN    LOG_WARNING
#define SIMPLELOG_BACKEND_LEVEL_INFO    LOG_INFO
#define SIMPLELOG_BACKEND_LEVEL_DEBUG   LOG_DEBUG

// -- UNUSED LEVELS:
#define SIMPLELOG_BACKEND_LEVEL_ALERT   LOG_ALERT   //< .., CRITICAL, ALERT, EMERG
#define SIMPLELOG_BACKEND_LEVEL_NOTICE  LOG_NOTICE  //< .., INFO, NOTICE, WARNING, ..
// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
// HINT: Derive other LogBackendMacros from existing ones.
#include "simplelog/detail/LogBackendDerivedMacros.hpp"
