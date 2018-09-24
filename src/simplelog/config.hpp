/**
 * @file
 * Provides configuration logic to select logging backend to use.
 **/ 

#pragma once

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
