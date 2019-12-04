/**
 * @file
 * Provides configuration logic to select logging backend to use.
 **/ 

#pragma once

// -- PRE-CONFIGURED:
// DISABLED: #define SIMPLELOG_DIAG 1

// --------------------------------------------------------------------------
// SIMPLELOG CONFIGURATION EXTENSION-POINT: User-specific
// --------------------------------------------------------------------------
// USING: C++/CPP __has_include() macro to check if header-file exists.
// SINCE: C++17 (or for some compilers before: C++14, ...)
// SEE: https://en.cppreference.com/w/cpp/preprocessor/include
#ifdef __has_include
#  if  __has_include("simplelog.user_config.hpp")
#    include "simplelog.user_config.hpp"
#  elif defined(SIMPLELOG_USE_USER_CONFIG) && (SIMPLELOG_USE_USER_CONFIG >= 0)
#    include "simplelog.user_config.hpp"
#  endif
#endif

// --------------------------------------------------------------------------
// SIMPLELOG CONFIGURATION: Select backend, etc.
// --------------------------------------------------------------------------
#ifndef SIMPLELOG_DEFAULT_BACKEND
#  define SIMPLELOG_DEFAULT_BACKEND 1
#endif
#ifndef SIMPLELOG_USE_BACKEND
#  if SIMPLELOG_USE_BACKEND_NULL
#  define SIMPLELOG_USE_BACKEND 0
#  elif SIMPLELOG_USE_BACKEND_SPDLOG
#  define SIMPLELOG_USE_BACKEND 1
#  else
#  define SIMPLELOG_USE_BACKEND SIMPLELOG_DEFAULT_BACKEND
#  endif
#endif

#if (SIMPLELOG_USE_BACKEND == 0)
#  include "simplelog/backend/null/LogBackendMacros.hpp"
#elif (SIMPLELOG_USE_BACKEND == 1)
#  include "simplelog/backend/spdlog/LogBackendMacros.hpp"
#else
#  error "UNKNOWN: SIMPLELOG_USE_BACKEND" SIMPLELOG_USE_BACKEND
#  include "simplelog/backend/null/LogBackendMacros.hpp"
#endif

// -- ENABLE/DISABLE: Short LOG macros, like: 
// SLOG_ERROR(...)       instead of SIMPLELOG_ERROR(...)
// SLOGM_ERROR(log, ...) instead of SIMPLELOGM_ERROR(log, ...)
#if SIMPLELOG_DISABLE_SHORT_MACROS
#  undef SIMPLELOG_HAVE_SHORT_MACROS
#  define SIMPLELOG_HAVE_SHORT_MACROS  0
#endif
#ifndef SIMPLELOG_HAVE_SHORT_MACROS
#  define SIMPLELOG_HAVE_SHORT_MACROS  1
#endif

#ifndef SIMPLELOG_DIAG
#  define SIMPLELOG_DIAG 0
#endif

// -- ENDOF-HEADER-FILE
