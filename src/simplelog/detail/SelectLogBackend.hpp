/**
 * @file simplelog/detail/SelectLogBackend.hpp
 * Provides configuration logic to select logging backend to use.
 *
 * @note RELATED: simplelog/detail/LogBackendMacros.hpp
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/config.hpp"


// --------------------------------------------------------------------------
// SIMPLELOG CONFIGURATION: Select backend, etc.
// --------------------------------------------------------------------------
#ifndef SIMPLELOG_DEFAULT_BACKEND_MACROS_HEADER_FILE
#  define SIMPLELOG_DEFAULT_BACKEND_MACROS_HEADER_FILE  "simplelog/backend/spdlog/LogBackendMacros.hpp"
#  define SIMPLELOG_DEFAULT_BACKEND 1  //< SIMPLELOG_USE_BACKEND_SPDLOG
#endif

// -- STEP: Select SIMPLELOG_BACKEND by using SIMPLELOG_BACKEND_xxx flags.
#ifndef SIMPLELOG_BACKEND_MACROS_HEADER_FILE
#  if SIMPLELOG_USE_BACKEND_NULL
#   define SIMPLELOG_BACKEND_MACROS_HEADER_FILE "simplelog/backend/null/LogBackendMacros.hpp"
#   define SIMPLELOG_USE_BACKEND 0
#  elif SIMPLELOG_USE_BACKEND_SPDLOG
#   define SIMPLELOG_BACKEND_MACROS_HEADER_FILE "simplelog/backend/spdlog/LogBackendMacros.hpp"
#   define SIMPLELOG_USE_BACKEND 1
#  elif SIMPLELOG_USE_BACKEND_SYSLOG
#   define SIMPLELOG_BACKEND_MACROS_HEADER_FILE "simplelog/backend/syslog/LogBackendMacros.hpp"
#   define SIMPLELOG_USE_BACKEND 2
#  elif SIMPLELOG_USE_BACKEND_SYSTEMD_JOURNAL
#   define SIMPLELOG_BACKEND_MACROS_HEADER_FILE "simplelog/backend/systemd_journal/LogBackendMacros.hpp"
#   define SIMPLELOG_USE_BACKEND 3
#  else
#   define SIMPLELOG_BACKEND_MACROS_HEADER_FILE SIMPLELOG_DEFAULT_BACKEND_MACROS_HEADER_FILE
#   define SIMPLELOG_USE_BACKEND SIMPLELOG_DEFAULT_BACKEND
#  endif
#endif

#ifndef SIMPLELOG_BACKEND_MACROS_HEADER_FILE
#error "CONFIG-ERROR in SelectLogBackend: SIMPLELOG_BACKEND_MACROS_HEADER_FILE is UNDEFINED."
#endif

// -- ENDOF-HEADER-FILE
