// -- COMPILE-TIME CHECK ONLY (for now):
#include "simplelog/LogMacros.hpp"

// -- MORE: XXX
/**
 * @file tests/simplelog.backend.spdlog/test_ModuleUtil.cpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- INCLUDES:
#include "doctest/doctest.h"

// -- MORE-INCLUDES:
#include "simplelog/LogMacros.hpp"
#include "simplelog/backend/spdlog/ModuleUtil.hpp"
#include "simplelog/backend/spdlog/SetupUtil.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/details/os.h>
#include <memory>   //< USE: std::shared_ptr<T>
#include "../simplelog.backend.spdlog/CleanupLoggingFixture.hpp"
#include <sstream>

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
const auto DEFAULT_EOL = std::string(spdlog::details::os::default_eol);

// ============================================================================
// TEST SUPPORT:
// ============================================================================
// auto makeLogger(const std::string& name) -> LoggerPtr
// {
//     return std::make_shared<spdlog::logger>(name);
// }

void setupLoggingToNullSink(void)
{
    // OR: using NullSink = spdlog::sinks::null_sink_st;
    using NullSink = spdlog::sinks::null_sink_mt;
    auto theSink = std::make_shared<NullSink>();
    simplelog::backend_spdlog::assignSink(theSink);
    simplelog::backend_spdlog::setLevel(spdlog::level::info);
    // MAYBE: auto logger = spdlog::create<NullSink>("");
}

void setupLoggingToStreamSink(std::ostream& outputStream)
{
    // OR: using NullSink = spdlog::sinks::null_sink_st;
    using OutputStreamSink = spdlog::sinks::ostream_sink_mt;
    auto theSink = std::make_shared<OutputStreamSink>(outputStream);
    simplelog::backend_spdlog::assignSink(theSink);
    simplelog::backend_spdlog::setLevel(spdlog::level::info);
}

unsigned count(const std::string& subject, const std::string& part)
{
    unsigned counter = 0;
    size_t pos = subject.find(part);
    while (pos != std::string::npos) {
        ++counter;
        pos = subject.find(part, pos+1);
    }
    return counter;
}

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog");
TEST_CASE("LogMacros: can use all macros")
{
    CleanupLoggingFixture cleanupGuard;
    std::ostringstream oss;
    setupLoggingToStreamSink(oss);
    simplelog::backend_spdlog::setLevel(spdlog::level::debug);
    spdlog::set_pattern("*** %v");
    // PATTERN: "%10n::%-7l  %v"
    
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    SIMPLELOG_FATAL("USE_LEVEL: FATAL");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: FATAL"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_CRITICAL("USE_LEVEL: CRITICAL");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: CRITICAL"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_ERROR("USE_LEVEL: ERROR");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: ERROR"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_WARN( "USE_LEVEL: WARN");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: WARN"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_INFO( "USE_LEVEL: INFO");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: INFO"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_DEBUG("USE_LEVEL: DEBUG");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: DEBUG"+ DEFAULT_EOL);
    oss.str("");
}

TEST_CASE("LogMacros: can use all macros with placeholders")
{
    CleanupLoggingFixture cleanupGuard;
    std::ostringstream oss;
    setupLoggingToStreamSink(oss);
    spdlog::set_pattern("*** %v");
    
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    SIMPLELOG_ERROR("Hello {}", std::string("Alice"));
    CHECK_EQ(oss.str(), "*** Hello Alice"+ DEFAULT_EOL);
    oss.str("");

    SIMPLELOG_WARN("Hello {} and {}", std::string("Alice"), "BOB");
    CHECK_EQ(oss.str(), "*** Hello Alice and BOB"+ DEFAULT_EOL);
    oss.str("");
}

TEST_CASE("LogMacros: LogLevel below threshold is filtered-out")
{
    CleanupLoggingFixture cleanupGuard;
    std::ostringstream oss;
    setupLoggingToStreamSink(oss);
    spdlog::set_pattern("*** %v");
    
    SIMPLELOG_DEFINE_STATIC_MODULE(logger, "default_1");
    logger->set_level(SIMPLELOG_BACKEND_LEVEL_ERROR);
    SIMPLELOGM_WARN(logger, "__FILTERED_OUT__");
    SIMPLELOGM_INFO(logger, "__FILTERED_OUT__");
    SIMPLELOGM_DEBUG(logger, "__FILTERED_OUT__");

    logger->set_level(SIMPLELOG_BACKEND_LEVEL_WARN);
    SIMPLELOGM_INFO(logger, "__FILTERED_OUT__");
    SIMPLELOGM_DEBUG(logger, "__FILTERED_OUT__");

    logger->set_level(SIMPLELOG_BACKEND_LEVEL_INFO);
    SIMPLELOGM_DEBUG(logger, "__FILTERED_OUT__");
}

TEST_CASE("LogMacros: LogLevel >= threshold emits log-record")
{
    CleanupLoggingFixture cleanupGuard;
    std::ostringstream oss;
    setupLoggingToStreamSink(oss);
    spdlog::set_pattern("%v");
    
    SIMPLELOG_DEFINE_STATIC_MODULE(logger, "default_1");
    logger->set_level(SIMPLELOG_BACKEND_LEVEL_ERROR);
    SIMPLELOGM_ERROR(logger, "__EMITS_RECORD__");
    SIMPLELOGM_FATAL(logger, "__EMITS_RECORD__");
    SIMPLELOGM_CRITICAL(logger, "__EMITS_RECORD__");
    const std::string logRecords = oss.str();
    CHECK(count(logRecords, "__EMITS_RECORD__") == 3);
    oss.str("");
}


TEST_CASE("LogMacros: can use short macros" 
    * doctest::skip(NO_SHORT_MACROS))
{
    CleanupLoggingFixture cleanupGuard;
    std::ostringstream oss;
    setupLoggingToStreamSink(oss);
    simplelog::backend_spdlog::setLevel(spdlog::level::debug);
    spdlog::set_pattern("*** %v");
    // PATTERN: "%10n::%-7l  %v"
    
    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    SLOG_FATAL("USE_LEVEL: FATAL");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: FATAL"+ DEFAULT_EOL);
    oss.str("");

    SLOG_CRITICAL("USE_LEVEL: CRITICAL");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: CRITICAL"+ DEFAULT_EOL);
    oss.str("");

    SLOG_ERROR("USE_LEVEL: ERROR");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: ERROR"+ DEFAULT_EOL);
    oss.str("");

    SLOG_WARN( "USE_LEVEL: WARN");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: WARN"+ DEFAULT_EOL);
    oss.str("");

    SLOG_INFO( "USE_LEVEL: INFO");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: INFO"+ DEFAULT_EOL);
    oss.str("");

    SLOG_DEBUG("USE_LEVEL: DEBUG");
    CHECK_EQ(oss.str(), "*** USE_LEVEL: DEBUG"+ DEFAULT_EOL);
    oss.str("");
}

TEST_SUITE_END();
} // < NAMESPACE-END.
//< ENDOF(__TEST_SOURCE_FILE__)
