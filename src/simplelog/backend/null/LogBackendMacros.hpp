/**
 * @file simplelog/backend/null/LogBackendMacros.hpp
 * Null implementation of a logging backend.
 * @note Any logging statement output is suppressed.
 **/

#pragma once

namespace simplelog {
namespace backend_null {

struct NullCategory
{};
typedef NullCategory* LoggerPtr;

} // namespace backend_null
} // namespace simplelog

// -- SPECIFY: LoggerPtr in a backend-independent way.
#if 0
namespace simplelog { namespace backend {
    using simplelog::backend_null::LoggerPtr;
}
#endif

// --------------------------------------------------------------------------
// LOGGING BACKEND MACROS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_NULL_STATEMENT             (void)0
#define SIMPLELOG_BACKEND_DEFINE_MODULE(vname, name) ::simplelog::backend_null::NullCategory* vname = nullptr

#define SIMPLELOG_BACKEND_LOG(logger, level, ...)               SIMPLELOG_BACKEND_NULL_STATEMENT
#define SIMPLELOG_BACKEND_LOG_IF(condition, logger, level, ...) SIMPLELOG_BACKEND_NULL_STATEMENT

// --------------------------------------------------------------------------
// LOGGING BACKEND: LEVEL DEFINITIONS
// --------------------------------------------------------------------------
#define SIMPLELOG_BACKEND_LEVEL_OFF      10
#define SIMPLELOG_BACKEND_LEVEL_FATAL    6
#define SIMPLELOG_BACKEND_LEVEL_CRITICAL 5
#define SIMPLELOG_BACKEND_LEVEL_ERROR    4
#define SIMPLELOG_BACKEND_LEVEL_WARN     3
#define SIMPLELOG_BACKEND_LEVEL_INFO     2
#define SIMPLELOG_BACKEND_LEVEL_DEBUG    1

// --------------------------------------------------------------------------
// REUSE: LOGGING BACKEND DERIVED MACROS
// --------------------------------------------------------------------------
#include "simplelog/detail/LogBackendDerivedMacros.hpp"

// -- ENDOF-HEADER-FILE
