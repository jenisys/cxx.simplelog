/**
 * @file
 * Provides configuration logic to select logging backend to use.
 **/

#pragma once

// --------------------------------------------------------------------------
// SIMPLELOG CONFIGURATION EXTENSION-POINT: User-specific
// --------------------------------------------------------------------------
// USING: C++/CPP __has_include() macro to check if header-file exists.
// SINCE: C++17 (or for some compilers before: C++14, ...)
// SEE: https://en.cppreference.com/w/cpp/preprocessor/include
#ifdef __has_include
#  if  __has_include("simplelog.user_config.hpp")
#    include "simplelog.user_config.hpp"
#  elif defined(SIMPLELOG_USE_USER_CONFIG) && !(SIMPLELOG_USE_USER_CONFIG == 0)
#    include "simplelog.user_config.hpp"
#  endif
#endif

// -- ENABLE/DISABLE: Short LOG macros, like:
// SLOG_ERROR(...)       instead of SIMPLELOG_ERROR(...)
// SLOGM_ERROR(log, ...) instead of SIMPLELOGM_ERROR(log, ...)
#ifndef SIMPLELOG_HAVE_SHORT_MACROS
#  define SIMPLELOG_HAVE_SHORT_MACROS  1    //< ENABLED
#endif
#ifndef SIMPLELOG_HAVE_MACROS0
#  define SIMPLELOG_HAVE_MACROS0  1         //< ENABLED (for now)
#endif

#ifndef SIMPLELOG_DIAG
#  define SIMPLELOG_DIAG 0      //< DISABLED
#endif

// -- ENDOF-HEADER-FILE
