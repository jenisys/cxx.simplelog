// -- COMPILE-TIME CHECK ONLY (for now):
/**
 * @file tests/simplelog.backend.null/test_LogMacros.compiled.cpp
 * Compile-time checks if all SIMPLELOG_xxx() macros are usabled.
 *
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- INCLUDES:
#include "simplelog/LogMacros.hpp"
#include "doctest/doctest.h"
// -- MORE-INCLUDES:
// #include <memory>   //< USE: std::shared_ptr<T>

namespace {

// ============================================================================
// TEST CONFIG:
// ============================================================================
const bool NO_SHORT_MACROS = (SIMPLELOG_HAVE_SHORT_MACROS == 0);

// ============================================================================
// TEST SUPPORT:
// ============================================================================
// NONE.

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.backend_null.compilable_LogMacros");
TEST_CASE("LogMacros: can use all macros (compile-time check)")
{
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

    SIMPLELOG_FATAL("USE-LEVEL: FATAL");
    SIMPLELOG_CRITICAL("USE-LEVEL: CRITICAL");
    SIMPLELOG_ERROR("USE_LEVEL: ERROR");
    SIMPLELOG_WARN( "USE_LEVEL: WARN");
    SIMPLELOG_INFO( "USE_LEVEL:  INFO");
    SIMPLELOG_DEBUG("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");

        SIMPLELOG_FATAL_IF(   true, "USE-LEVEL: FATAL");
        SIMPLELOG_CRITICAL_IF(true, "USE-LEVEL: CRITICAL");
        SIMPLELOG_ERROR_IF(   true, "USE_LEVEL: ERROR");
        SIMPLELOG_WARN_IF(    true, "USE_LEVEL: WARN");
        SIMPLELOG_INFO_IF(    true, "USE_LEVEL:  INFO");
        SIMPLELOG_DEBUG_IF(   true, "USE_LEVEL: DEBUG");

        SIMPLELOG_FATAL_IF(   false, "USE-LEVEL: FATAL");
        SIMPLELOG_CRITICAL_IF(false, "USE-LEVEL: CRITICAL");
        SIMPLELOG_ERROR_IF(   false, "USE_LEVEL: ERROR");
        SIMPLELOG_WARN_IF(    false, "USE_LEVEL: WARN");
        SIMPLELOG_INFO_IF(    false, "USE_LEVEL:  INFO");
        SIMPLELOG_DEBUG_IF(   false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        SIMPLELOGM_FATAL(logger1, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL(logger1, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR(logger1, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN(logger1, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO(logger1, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        SIMPLELOGM_FATAL_IF(   true, logger2, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL_IF(true, logger2, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR_IF(   true, logger2, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN_IF(    true, logger2, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO_IF(    true, logger2, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG_IF(   true, logger2, "USE_LEVEL: DEBUG");

        SIMPLELOGM_FATAL_IF(   false, logger2, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL_IF(false, logger2, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR_IF(   false, logger2, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN_IF(    false, logger2, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO_IF(    false, logger2, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG_IF(   false, logger2, "USE_LEVEL: DEBUG");
    }
}

TEST_CASE("LogMacros: can use short macros (compile-time check)" * doctest::skip(NO_SHORT_MACROS))
{
#if SIMPLELOG_HAVE_SHORT_MACROS
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    SLOG_FATAL("USE-LEVEL: FATAL");
    SLOG_CRITICAL("USE-LEVEL: CRITICAL");
    SLOG_ERROR("USE_LEVEL: ERROR");
    SLOG_WARN( "USE_LEVEL: WARN");
    SLOG_INFO( "USE_LEVEL:  INFO");
    SLOG_DEBUG("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");
        SLOG_FATAL_IF(   true, "USE-LEVEL: FATAL");
        SLOG_CRITICAL_IF(true, "USE-LEVEL: CRITICAL");
        SLOG_ERROR_IF(   true, "USE_LEVEL: ERROR");
        SLOG_WARN_IF(    true, "USE_LEVEL: WARN");
        SLOG_INFO_IF(    true, "USE_LEVEL:  INFO");
        SLOG_DEBUG_IF(   true, "USE_LEVEL: DEBUG");

        SLOG_FATAL_IF(   false, "USE-LEVEL: FATAL");
        SLOG_CRITICAL_IF(false, "USE-LEVEL: CRITICAL");
        SLOG_ERROR_IF(   false, "USE_LEVEL: ERROR");
        SLOG_WARN_IF(    false, "USE_LEVEL: WARN");
        SLOG_INFO_IF(    false, "USE_LEVEL:  INFO");
        SLOG_DEBUG_IF(   false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        SLOGM_FATAL(logger1, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL(logger1, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR(logger1, "USE_LEVEL: ERROR");
        SLOGM_WARN(logger1, "USE_LEVEL: WARN");
        SLOGM_INFO(logger1, "USE_LEVEL:  INFO");
        SLOGM_DEBUG(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        SLOGM_FATAL_IF(   true, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL_IF(true, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR_IF(   true, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN_IF(    true, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO_IF(    true, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG_IF(   true, logger2, "USE_LEVEL: DEBUG");

        SLOGM_FATAL_IF(   false, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL_IF(false, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR_IF(   false, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN_IF(    false, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO_IF(    false, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG_IF(   false, logger2, "USE_LEVEL: DEBUG");
    }
#endif
}

TEST_SUITE_END();
} // < NAMESPACE-END.
//< ENDOF(__TEST_SOURCE_FILE__)
