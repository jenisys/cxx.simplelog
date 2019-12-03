/**
 * @file simplelog/backend/detail/LogBackendDerivedMacros.hpp
 * 
 * Generic derived logging backend macros that simplify writing 
 * a logging backend.
 **/

#pragma once

#ifndef SIMPLELOG_BACKEND_LOG
#  error "INCLUDE-ORDERING: Include LogBackendMacros.hpp first."
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

#define SIMPLELOG_BACKEND_LOG_IF(condition, logger, level, format, ...) \
    if (condition) { SIMPLELOG_BACKEND_LOG(logger, level, format, ## __VA_AGRS__); }
#define SIMPLELOG_BACKEND_LOG0_IF(condition, logger, level, message) \
    if (condition) { SIMPLELOG_BACKEND_LOG0(logger, level, message); }
