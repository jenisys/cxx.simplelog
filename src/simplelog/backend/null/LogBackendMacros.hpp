/**
 * @file simplelog/backend/null/LogBackendMacros.hpp
 * Null implementation of a logging backend.
 * @note Any logging statement output is suppressed.
 **/

#pragma once

namespace simplelog { namespace backend { namespace null {

struct NullCategory {};

}}}

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
// #define CXXLOG_BACKEND_NULL_IDENTIER(x) (x ## __LINE__)
#define CXXLOG_BACKEND_NULL_STATEMENT /* (void) */
#define CXXLOG_BACKEND_DEFINE_CATEGORY(vname, name) ::simplelog::backend::null::NullCategory *vname = nullptr
#define CXXLOG_BACKEND_DEFINE_STATIC_CATEGORY(vname, name) static ::simplelog::backend::null::NullCategory* vname = nullptr
#define CXXLOG_BACKEND_LOG(logger, level, format, ...)  CXXLOG_BACKEND_NULL_STATEMENT
#define CXXLOG_BACKEND_LOG0(logger, level, message)     CXXLOG_BACKEND_NULL_STATEMENT
#define CXXLOG_BACKEND_LOG_IF(condition, logger, level, format, ...) CXXLOG_BACKEND_NULL_STATEMENT
#define CXXLOG_BACKEND_LOG0_IF(condition, logger, level, message)    CXXLOG_BACKEND_NULL_STATEMENT

#define CXXLOG_BACKEND_LEVEL_OFF        10
#define CXXLOG_BACKEND_LEVEL_FATAL      6
#define CXXLOG_BACKEND_LEVEL_CRITICAL   5
#define CXXLOG_BACKEND_LEVEL_ERROR      4
#define CXXLOG_BACKEND_LEVEL_WARN       3
#define CXXLOG_BACKEND_LEVEL_INFO       2
#define CXXLOG_BACKEND_LEVEL_DEBUG      1
