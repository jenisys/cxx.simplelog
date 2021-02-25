// -- COMPILE-TIME CHECK ONLY (for now):
/**
 * @file tests/simplelog.backend.spdlog/test_ModuleUtil.cpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- INCLUDES:
#include "doctest/doctest.h"

// -- MORE-INCLUDES:
#include "simplelog/LogMacros.hpp"
#include "simplelog/TraceMacros.hpp"

namespace {

// ============================================================================
// TEST CONFIG:
// ============================================================================
const bool NO_SHORT_MACROS = (SIMPLELOG_HAVE_SHORT_MACROS == 0);

#ifndef DEBUG
#    define DEBUG 0
#endif
const bool TRACE_MACROS_DISABLED = (DEBUG == 0);

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.backend_null.compilable_TraceMacros");
TEST_CASE("TraceMacros: can use all macros (compile-time check)" *
          doctest::skip(TRACE_MACROS_DISABLED))
{
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

    SIMPLELOG_TRACE_FATAL("USE-LEVEL: FATAL");
    SIMPLELOG_TRACE_CRITICAL("USE-LEVEL: CRITICAL");
    SIMPLELOG_TRACE_ERROR("USE_LEVEL: ERROR");
    SIMPLELOG_TRACE_WARN("USE_LEVEL: WARN");
    SIMPLELOG_TRACE_INFO("USE_LEVEL:  INFO");
    SIMPLELOG_TRACE_DEBUG("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");

        SIMPLELOG_TRACE_FATAL_IF(true, "USE-LEVEL: FATAL");
        SIMPLELOG_TRACE_CRITICAL_IF(true, "USE-LEVEL: CRITICAL");
        SIMPLELOG_TRACE_ERROR_IF(true, "USE_LEVEL: ERROR");
        SIMPLELOG_TRACE_WARN_IF(true, "USE_LEVEL: WARN");
        SIMPLELOG_TRACE_INFO_IF(true, "USE_LEVEL:  INFO");
        SIMPLELOG_TRACE_DEBUG_IF(true, "USE_LEVEL: DEBUG");

        SIMPLELOG_TRACE_FATAL_IF(false, "USE-LEVEL: FATAL");
        SIMPLELOG_TRACE_CRITICAL_IF(false, "USE-LEVEL: CRITICAL");
        SIMPLELOG_TRACE_ERROR_IF(false, "USE_LEVEL: ERROR");
        SIMPLELOG_TRACE_WARN_IF(false, "USE_LEVEL: WARN");
        SIMPLELOG_TRACE_INFO_IF(false, "USE_LEVEL:  INFO");
        SIMPLELOG_TRACE_DEBUG_IF(false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        STRACEM_FATAL(logger1, "USE-LEVEL: FATAL");
        STRACEM_CRITICAL(logger1, "USE-LEVEL: CRITICAL");
        STRACEM_ERROR(logger1, "USE_LEVEL: ERROR");
        STRACEM_WARN(logger1, "USE_LEVEL: WARN");
        STRACEM_INFO(logger1, "USE_LEVEL:  INFO");
        STRACEM_DEBUG(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        STRACEM_FATAL_IF(true, logger2, "USE-LEVEL: FATAL");
        STRACEM_CRITICAL_IF(true, logger2, "USE-LEVEL: CRITICAL");
        STRACEM_ERROR_IF(true, logger2, "USE_LEVEL: ERROR");
        STRACEM_WARN_IF(true, logger2, "USE_LEVEL: WARN");
        STRACEM_INFO_IF(true, logger2, "USE_LEVEL:  INFO");
        STRACEM_DEBUG_IF(true, logger2, "USE_LEVEL: DEBUG");

        STRACEM_FATAL_IF(false, logger2, "USE-LEVEL: FATAL");
        STRACEM_CRITICAL_IF(false, logger2, "USE-LEVEL: CRITICAL");
        STRACEM_ERROR_IF(false, logger2, "USE_LEVEL: ERROR");
        STRACEM_WARN_IF(false, logger2, "USE_LEVEL: WARN");
        STRACEM_INFO_IF(false, logger2, "USE_LEVEL:  INFO");
        STRACEM_DEBUG_IF(false, logger2, "USE_LEVEL: DEBUG");
    }
}

TEST_CASE("TraceMacros: can use short macros (compile-time check)" *
          doctest::skip(TRACE_MACROS_DISABLED))
{
#if SIMPLELOG_HAVE_SHORT_MACROS
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    STRACE_FATAL("USE-LEVEL: FATAL");
    STRACE_CRITICAL("USE-LEVEL: CRITICAL");
    STRACE_ERROR("USE_LEVEL: ERROR");
    STRACE_WARN("USE_LEVEL: WARN");
    STRACE_INFO("USE_LEVEL:  INFO");
    STRACE_DEBUG("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");
        STRACE_FATAL_IF(true, "USE-LEVEL: FATAL");
        STRACE_CRITICAL_IF(true, "USE-LEVEL: CRITICAL");
        STRACE_ERROR_IF(true, "USE_LEVEL: ERROR");
        STRACE_WARN_IF(true, "USE_LEVEL: WARN");
        STRACE_INFO_IF(true, "USE_LEVEL:  INFO");
        STRACE_DEBUG_IF(true, "USE_LEVEL: DEBUG");

        STRACE_FATAL_IF(false, "USE-LEVEL: FATAL");
        STRACE_CRITICAL_IF(false, "USE-LEVEL: CRITICAL");
        STRACE_ERROR_IF(false, "USE_LEVEL: ERROR");
        STRACE_WARN_IF(false, "USE_LEVEL: WARN");
        STRACE_INFO_IF(false, "USE_LEVEL:  INFO");
        STRACE_DEBUG_IF(false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        STRACEM_FATAL(logger1, "USE-LEVEL: FATAL");
        STRACEM_CRITICAL(logger1, "USE-LEVEL: CRITICAL");
        STRACEM_ERROR(logger1, "USE_LEVEL: ERROR");
        STRACEM_WARN(logger1, "USE_LEVEL: WARN");
        STRACEM_INFO(logger1, "USE_LEVEL:  INFO");
        STRACEM_DEBUG(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        SLOGM_FATAL_IF(true, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL_IF(true, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR_IF(true, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN_IF(true, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO_IF(true, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG_IF(true, logger2, "USE_LEVEL: DEBUG");

        SLOGM_FATAL_IF(false, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL_IF(false, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR_IF(false, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN_IF(false, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO_IF(false, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG_IF(false, logger2, "USE_LEVEL: DEBUG");
    }
#endif
}

TEST_SUITE_END();
} // namespace
//< ENDOF(__TEST_SOURCE_FILE__)
