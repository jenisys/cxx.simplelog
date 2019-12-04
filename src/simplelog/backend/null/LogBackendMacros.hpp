/**
 * @file simplelog/backend/null/LogBackendMacros.hpp
 * Null implementation of a logging backend.
 * @note Any logging statement output is suppressed.
 **/

#pragma once

namespace simplelog { namespace backend_null {

struct NullCategory {};
typedef NullCategory* LoggerPtr;

}}

// -- SPECIFY: LoggerPtr in a backend-independent way.
#if 0
namespace simplelog { namespace backend {
    using simplelog::backend_null::LoggerPtr;
}
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
// #define SIMPLELOG_BACKEND_NULL_IDENTIER(x) (x ## __LINE__)
#define SIMPLELOG_BACKEND_NULL_STATEMENT /* (void) */
#define SIMPLELOG_BACKEND_DEFINE_MODULE(vname, name) ::simplelog::backend_null::NullCategory *vname = nullptr
#define SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(vname, name) \
    static SIMPLELOG_BACKEND_DEFINE_MODULE(vname, name)

#define SIMPLELOG_BACKEND_LOG(logger, level, format, ...)  SIMPLELOG_BACKEND_NULL_STATEMENT
#define SIMPLELOG_BACKEND_LOG0(logger, level, message)     SIMPLELOG_BACKEND_NULL_STATEMENT
#define SIMPLELOG_BACKEND_LOG_IF(condition, logger, level, format, ...) SIMPLELOG_BACKEND_NULL_STATEMENT
#define SIMPLELOG_BACKEND_LOG0_IF(condition, logger, level, message)    SIMPLELOG_BACKEND_NULL_STATEMENT

#define SIMPLELOG_BACKEND_LEVEL_OFF        10
#define SIMPLELOG_BACKEND_LEVEL_FATAL      6
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL   5
#define SIMPLELOG_BACKEND_LEVEL_ERROR      4
#define SIMPLELOG_BACKEND_LEVEL_WARN       3
#define SIMPLELOG_BACKEND_LEVEL_INFO       2
#define SIMPLELOG_BACKEND_LEVEL_DEBUG      1

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
// AVOIDED: #include "simplelog/backend/detail/LogBackendDerivedMacros.hpp"
