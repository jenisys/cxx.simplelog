// -- COMPILE-TIME CHECK ONLY (for now):
#include "simplelog/detail/LogMacros0.hpp"

/**
 * @file tests/simplelog.backend.spdlog/test_ModuleUtil.cpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- INCLUDES:
#include "doctest/doctest.h"

// -- MORE-INCLUDES:
#include "../simplelog.backend.spdlog/CleanupLoggingFixture.hpp"
#include "simplelog/LogMacros.hpp"
#include "simplelog/backend/spdlog/ModuleUtil.hpp"
#include "simplelog/backend/spdlog/SetupUtil.hpp"

#include <spdlog/sinks/null_sink.h>
#include <spdlog/spdlog.h>

#include <memory> //< USE: std::shared_ptr<T>

// -- LOCAL-INCLUDES:
// PREPARED: #include "CleanupLoggingFixture.hpp"

namespace {

// PREPARED: using tests::simplelog::backend_spdlog::CleanupLoggingFixture;
using LoggerPtr = std::shared_ptr<spdlog::logger>;
using Level = ::spdlog::level::level_enum;
using tests::simplelog::backend_spdlog::CleanupLoggingFixture;

// ============================================================================
// TEST CONFIG:
// ============================================================================
const bool NO_SHORT_MACROS = (SIMPLELOG_HAVE_SHORT_MACROS == 0);

// ============================================================================
// TEST SUPPORT:
// ============================================================================
// auto makeLogger(const std::string& name) -> LoggerPtr
// {
//     return std::make_shared<spdlog::logger>(name);
// }

void setupLoggingToNullSink()
{
    // OR: using NullSink = spdlog::sinks::null_sink_st;
    using NullSink = spdlog::sinks::null_sink_mt;
    auto theSink = std::make_shared<NullSink>();
    simplelog::backend_spdlog::assignSink(theSink);
    simplelog::backend_spdlog::setLevel(spdlog::level::info);
    // MAYBE: auto logger = spdlog::create<NullSink>("");
}

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.backend_spdlog.compilable_LogMacros0");
TEST_CASE("LogMacros0: can use all macros (compile-time check)")
{
    CleanupLoggingFixture cleanupGuard;
    setupLoggingToNullSink();

    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

    SIMPLELOG_FATAL0("USE-LEVEL: FATAL");
    SIMPLELOG_CRITICAL0("USE-LEVEL: CRITICAL");
    SIMPLELOG_ERROR0("USE_LEVEL: ERROR");
    SIMPLELOG_WARN0("USE_LEVEL: WARN");
    SIMPLELOG_INFO0("USE_LEVEL:  INFO");
    SIMPLELOG_DEBUG0("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");

        SIMPLELOG_FATAL0_IF(true, "USE-LEVEL: FATAL");
        SIMPLELOG_CRITICAL0_IF(true, "USE-LEVEL: CRITICAL");
        SIMPLELOG_ERROR0_IF(true, "USE_LEVEL: ERROR");
        SIMPLELOG_WARN0_IF(true, "USE_LEVEL: WARN");
        SIMPLELOG_INFO0_IF(true, "USE_LEVEL:  INFO");
        SIMPLELOG_DEBUG0_IF(true, "USE_LEVEL: DEBUG");

        SIMPLELOG_FATAL0_IF(false, "USE-LEVEL: FATAL");
        SIMPLELOG_CRITICAL0_IF(false, "USE-LEVEL: CRITICAL");
        SIMPLELOG_ERROR0_IF(false, "USE_LEVEL: ERROR");
        SIMPLELOG_WARN0_IF(false, "USE_LEVEL: WARN");
        SIMPLELOG_INFO0_IF(false, "USE_LEVEL:  INFO");
        SIMPLELOG_DEBUG0_IF(false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        SIMPLELOGM_FATAL0(logger1, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL0(logger1, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR0(logger1, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN0(logger1, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO0(logger1, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG0(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        SIMPLELOGM_FATAL0_IF(true, logger2, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL0_IF(true, logger2, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR0_IF(true, logger2, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN0_IF(true, logger2, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO0_IF(true, logger2, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG0_IF(true, logger2, "USE_LEVEL: DEBUG");

        SIMPLELOGM_FATAL0_IF(false, logger2, "USE-LEVEL: FATAL");
        SIMPLELOGM_CRITICAL0_IF(false, logger2, "USE-LEVEL: CRITICAL");
        SIMPLELOGM_ERROR0_IF(false, logger2, "USE_LEVEL: ERROR");
        SIMPLELOGM_WARN0_IF(false, logger2, "USE_LEVEL: WARN");
        SIMPLELOGM_INFO0_IF(false, logger2, "USE_LEVEL:  INFO");
        SIMPLELOGM_DEBUG0_IF(false, logger2, "USE_LEVEL: DEBUG");
    }
}

TEST_CASE("LogMacros0: can use short macros (compile-time check)" * doctest::skip(NO_SHORT_MACROS))
{
#if SIMPLELOG_HAVE_SHORT_MACROS
    CleanupLoggingFixture cleanupGuard;
    setupLoggingToNullSink();

    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default.static_1");
    SLOG_FATAL0("USE-LEVEL: FATAL");
    SLOG_CRITICAL0("USE-LEVEL: CRITICAL");
    SLOG_ERROR0("USE_LEVEL: ERROR");
    SLOG_WARN0("USE_LEVEL: WARN");
    SLOG_INFO0("USE_LEVEL:  INFO");
    SLOG_DEBUG0("USE_LEVEL: DEBUG");

    {
        SIMPLELOG_DEFINE_DEFAULT_MODULE("default.normal_2");
        SLOG_FATAL0_IF(true, "USE-LEVEL: FATAL");
        SLOG_CRITICAL0_IF(true, "USE-LEVEL: CRITICAL");
        SLOG_ERROR0_IF(true, "USE_LEVEL: ERROR");
        SLOG_WARN0_IF(true, "USE_LEVEL: WARN");
        SLOG_INFO0_IF(true, "USE_LEVEL:  INFO");
        SLOG_DEBUG0_IF(true, "USE_LEVEL: DEBUG");

        SLOG_FATAL0_IF(false, "USE-LEVEL: FATAL");
        SLOG_CRITICAL0_IF(false, "USE-LEVEL: CRITICAL");
        SLOG_ERROR0_IF(false, "USE_LEVEL: ERROR");
        SLOG_WARN0_IF(false, "USE_LEVEL: WARN");
        SLOG_INFO0_IF(false, "USE_LEVEL:  INFO");
        SLOG_DEBUG0_IF(false, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_STATIC_MODULE(logger1, "static_1");

        SLOGM_FATAL0(logger1, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL0(logger1, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR0(logger1, "USE_LEVEL: ERROR");
        SLOGM_WARN0(logger1, "USE_LEVEL: WARN");
        SLOGM_INFO0(logger1, "USE_LEVEL:  INFO");
        SLOGM_DEBUG0(logger1, "USE_LEVEL: DEBUG");
    }
    {
        SIMPLELOG_DEFINE_MODULE(logger2, "normal_2");

        SLOGM_FATAL0_IF(true, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL0_IF(true, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR0_IF(true, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN0_IF(true, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO0_IF(true, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG0_IF(true, logger2, "USE_LEVEL: DEBUG");

        SLOGM_FATAL0_IF(false, logger2, "USE-LEVEL: FATAL");
        SLOGM_CRITICAL0_IF(false, logger2, "USE-LEVEL: CRITICAL");
        SLOGM_ERROR0_IF(false, logger2, "USE_LEVEL: ERROR");
        SLOGM_WARN0_IF(false, logger2, "USE_LEVEL: WARN");
        SLOGM_INFO0_IF(false, logger2, "USE_LEVEL:  INFO");
        SLOGM_DEBUG0_IF(false, logger2, "USE_LEVEL: DEBUG");
    }
#endif
}

TEST_SUITE_END();
} // namespace
//< ENDOF(__TEST_SOURCE_FILE__)
