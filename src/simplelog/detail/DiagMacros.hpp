/**
 * @file simplelog/detail/DiagMacros.hpp
 * Some internal diagnostic macros.
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/config.hpp"

#if SIMPLELOG_DIAG
#  include <iostream>
#  ifndef SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB
#    define SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB 1
#  endif
#  if SIMPLELOG_DIAG__USE_SPDLOG_FMTLIB
#    include <spdlog/fmt/fmt.h>
#  else 
#    include <fmt/fmt.h>
#  endif
// XXX #  define SIMPLELOG_DIAG_TRACE0(message)     fmt::print("SIMPLELOG_DIAG: " message "\n")
// XXX #  define SIMPLELOG_DIAG_TRACE(format, ...)  fmt::print("SIMPLELOG_DIAG: " format  "\n", __VA_ARGS__)
// OLD: #  include <iostream>
// OLD: #  define SIMPLELOG_DIAG_TRACE__0(x) std::cout << x << std::endl
#  define SIMPLELOG_DIAG_TRACE0(message)      std::cout <<"SIMPLELOG_DIAG: "<< message <<"\n"
#  define SIMPLELOG_DIAG_TRACE(format_, ...)  std::cout <<"SIMPLELOG_DIAG: "<< fmt::format(format_, __VA_ARGS__) <<"\n"
#else
#  define SIMPLELOG_DIAG_TRACE0(message)     (void)0
#  define SIMPLELOG_DIAG_TRACE(format, ...)  (void)0
// #  define SIMPLELOG_DIAG_TRACE(x) (void)0
#endif


/**
 * @code
 *  SIMPLELOG_DIAG_TRACE0("Hello fmt::print");
 *  SIMPLELOG_DIAG_TRACE("Hello fmt::print, args={0}", 42);
 *  SIMPLELOG_DIAG_TRACE("Hello fmt::print, args={0}, {1}", "one", "two");
 * @endcode
 **/

//< ENDOF-HEADER-FILE
