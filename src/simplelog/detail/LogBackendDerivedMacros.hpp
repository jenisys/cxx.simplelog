/**
 * @file simplelog/detail/LogBackendDerivedMacros.hpp
 * Provides generic derived logging backend macros
 * that simplify writing a logging backend.
 **/

#pragma once

#ifndef SIMPLELOG_BACKEND_LOG
#  error "INCLUDE-ORDERING: Include simplelog/backend/xxx/LogBackendMacros.hpp first."
#endif
// SAME FOR: SIMPLELOG_BACKEND_LOG0
// SAME FOR: SIMPLELOG_BACKEND_DEFINE_MODULE

// --------------------------------------------------------------------------
// LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
#ifndef SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE
#define SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(var_name, name) \
    static SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
#endif

#ifndef SIMPLELOG_BACKEND_LOG_IF
#define SIMPLELOG_BACKEND_LOG_IF(condition, logger, level, ...) \
    if (condition) { SIMPLELOG_BACKEND_LOG(logger, level, __VA_ARGS__); }
#endif

// -- ENDOF-HEADER-FILE
