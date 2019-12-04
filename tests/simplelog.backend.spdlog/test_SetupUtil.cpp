/**
 * @file tests/simplelog.backend.spdlog/test_setup_spdlog.cpp
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
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/null_sink.h>


// -- LOCAL-INCLUDES:
#include "CleanupLoggingFixture.hpp"

namespace {

using tests::simplelog::backend_spdlog::CleanupLoggingFixture;
using LoggerPtr = std::shared_ptr<spdlog::logger>;
using Level = ::spdlog::level::level_enum;
using simplelog::backend_spdlog::LoggerPtr;
using simplelog::backend_spdlog::SinkPtr;
using simplelog::backend_spdlog::Sinks;
using StdoutSink = ::spdlog::sinks::stdout_sink_mt;
using NullSink = ::spdlog::sinks::null_sink_mt;

// ============================================================================
// TEST SUPPORT:
// ============================================================================
#if 0
auto& spdlog_registry(void)
{
    return ::spdlog::details::registry::instance();
}
#endif

void assert_loggerHasSameSink(LoggerPtr logger, SinkPtr sink) 
{
    CHECK_NE(logger, nullptr);
    CHECK_EQ(logger->sinks().size(), 1);
    CHECK_EQ(logger->sinks().front(), sink);
}

void assert_loggerHasSameSinks(LoggerPtr logger, const Sinks& sinks)
{
    CHECK_NE(logger, nullptr);
    CHECK_EQ(logger->sinks(), sinks);
    CHECK_EQ(logger->sinks().size(), sinks.size());
}

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.backend_spdlog::SetupUtil");
TEST_CASE("setMinLevel: Overrides logger.level if logger.level < min_level")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    const auto LOG_LEVEL1 = SIMPLELOG_BACKEND_LEVEL_DEBUG;
    auto logger = useOrCreateLogger("foo_1");
    logger->set_level(LOG_LEVEL1);
    REQUIRE_EQ(logger->level(), LOG_LEVEL1);

    // -- CASE 1: Adjust logger.level=DEBUG to INFO
    const auto DESIRED_LEVEL1 = SIMPLELOG_BACKEND_LEVEL_INFO;
    REQUIRE_LT(logger->level(), DESIRED_LEVEL1);
    simplelog::backend_spdlog::setMinLevel(DESIRED_LEVEL1);
    CHECK_EQ(logger->level(), DESIRED_LEVEL1);

    // -- CASE 2: Adjust logger.level=INFO to ERROR
    const auto DESIRED_LEVEL2 = SIMPLELOG_BACKEND_LEVEL_ERROR;
    REQUIRE_LT(logger->level(), DESIRED_LEVEL2);
    simplelog::backend_spdlog::setMinLevel(DESIRED_LEVEL2);
    CHECK_EQ(logger->level(), DESIRED_LEVEL2);
}

TEST_CASE("setMinLevel: Keeps logger.level if logger.level >= min_level")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    const auto DESIRED_LEVEL = SIMPLELOG_BACKEND_LEVEL_WARN;
    const auto LOG_LEVEL1 = SIMPLELOG_BACKEND_LEVEL_WARN;
    const auto LOG_LEVEL2 = SIMPLELOG_BACKEND_LEVEL_ERROR;
    auto logger1 = useOrCreateLogger("foo_1");
    auto logger2 = useOrCreateLogger("foo_2");
    logger1->set_level(LOG_LEVEL1);
    logger2->set_level(LOG_LEVEL2);

    simplelog::backend_spdlog::setMinLevel(DESIRED_LEVEL);
    // -- VERIFY: logger.level == min_level
    CHECK_GE(logger1->level(), DESIRED_LEVEL);
    CHECK_EQ(logger1->level(), LOG_LEVEL1);    
    // -- VERIFY: logger.level > min_level
    CHECK_GT(logger2->level(), DESIRED_LEVEL);
    CHECK_EQ(logger2->level(), LOG_LEVEL2);
}

TEST_CASE("setLevelToAny: Should assigns level if predicate is true")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    using simplelog::backend_spdlog::LoggerPtr;
    CleanupLoggingFixture cleanupGuard;
    const auto DESIRED_LEVEL = SIMPLELOG_BACKEND_LEVEL_WARN;
    const auto LOG_LEVEL = SIMPLELOG_BACKEND_LEVEL_ERROR;
    auto logger = useOrCreateLogger("foo");
    logger->set_level(LOG_LEVEL);

    // -- PERFORM-TEST: logger.level == min_level
    // C++14: auto hasSameName = [](auto log) {
    auto hasSameName = [](LoggerPtr log) {
        return log->name() == "foo";
    };
    simplelog::backend_spdlog::setLevelToAny(DESIRED_LEVEL, hasSameName);
    CHECK_EQ(hasSameName(logger), true);
    CHECK_EQ(logger->level(), DESIRED_LEVEL);
    CHECK_NE(logger->level(), LOG_LEVEL);
}

TEST_CASE("setLevelToAny: Should keep level if predicate is false")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    using simplelog::backend_spdlog::LoggerPtr;
    CleanupLoggingFixture cleanupGuard;
    const auto DESIRED_LEVEL = SIMPLELOG_BACKEND_LEVEL_WARN;
    const auto LOG_LEVEL = SIMPLELOG_BACKEND_LEVEL_ERROR;
    auto logger = useOrCreateLogger("foo_1");
    logger->set_level(LOG_LEVEL);

    // -- PERFORM-TEST: logger.level == min_level
    // C++14: auto hasOthergName = [](auto log) {
    auto hasOthergName = [](LoggerPtr log) {
        return log->name() == "other";
    };
    simplelog::backend_spdlog::setLevelToAny(DESIRED_LEVEL, hasOthergName);
    CHECK_EQ(hasOthergName(logger), false);
    CHECK_EQ(logger->level(), LOG_LEVEL);
    CHECK_NE(logger->level(), DESIRED_LEVEL);
}

TEST_CASE("assignSink: Should assign new sink to all loggers")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    auto theSink = std::make_shared<spdlog::sinks::null_sink_mt>();
    auto logger1 = useOrCreateLogger("foo_1");
    auto logger2 = useOrCreateLogger("foo_2");

    // -- ACT:
    simplelog::backend_spdlog::assignSink(theSink);
    
    // -- VERIFY:
    const Sinks EXPECTED_SINKS{ theSink };
    INFO("logger1.sinks: " << logger1->name());
    CHECK_EQ(logger1->sinks(), EXPECTED_SINKS);
    CHECK_EQ(logger1->sinks().front(), theSink);
    INFO("logger2.sinks: "<< logger2->name());
    CHECK_EQ(logger2->sinks(), EXPECTED_SINKS);
    CHECK_EQ(logger2->sinks().front(), theSink);

    INFO("ENSURE: All logger.sinks are same.");
    ::spdlog::apply_all([&](LoggerPtr log) {
        INFO("ALL_LOGGERS.sinks: log="<< log->name());
        CHECK_EQ(log->sinks(), EXPECTED_SINKS);
        assert_loggerHasSameSink(log, theSink);
        // assert_loggerHasSameSinks(log, EXPECTED_SINKS);
    });
}

TEST_CASE("assignSink: Assigned sink should be inherited by new loggers")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    using DefaultSink = spdlog::sinks::null_sink_mt;
    CleanupLoggingFixture cleanupGuard;
    auto theSink = std::make_shared<spdlog::sinks::null_sink_mt>();
    auto logger1 = useOrCreateLogger("foo_1");

    // -- ACT:
    simplelog::backend_spdlog::assignSink(theSink);
    auto logger2 = useOrCreateLogger("new_1");
    // auto logger2  = spdlog::create<DefaultSink>("new_1");
    
    // -- VERIFY:
    const Sinks EXPECTED_SINKS{ theSink };
    INFO("logger1.sinks: " << logger1->name());
    CHECK_EQ(logger1->sinks(), EXPECTED_SINKS);
    CHECK_EQ(logger1->sinks().front(), theSink);
    INFO("logger2.sinks: "<< logger2->name());
    CHECK_EQ(logger2->sinks(), EXPECTED_SINKS);
    CHECK_EQ(logger2->sinks().front(), theSink);

    INFO("ENSURE: All logger.sinks are same.");
    ::spdlog::apply_all([&](LoggerPtr log) {
        INFO("ALL_LOGGERS.sinks: log="<< log->name());
        CHECK_EQ(log->sinks(), EXPECTED_SINKS);
        assert_loggerHasSameSink(log, theSink);
        // assert_loggerHasSameSinks(log, EXPECTED_SINKS);
    });
}

TEST_CASE("assignSinkToAny: Should assign sink to any matching loggers")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    auto sink1 = std::make_shared<spdlog::sinks::null_sink_mt>();
    auto sink2 = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto logger1 = useOrCreateLogger("foo_1");
    auto logger2 = useOrCreateLogger("foo_2");
    auto logger3 = useOrCreateLogger("foo_3");

    // -- ACT:
    const auto& hasLoggerSameName = [](LoggerPtr log) {
        return log->name() == "foo_2";
    };
    simplelog::backend_spdlog::assignSink(sink1);
    simplelog::backend_spdlog::assignSinkToAny(sink2, hasLoggerSameName);
    
    // -- VERIFY: Only logger2.sinks == EXPECTED_SINKS2
    const Sinks EXPECTED_SINKS1{ sink1 };
    const Sinks EXPECTED_SINKS2{ sink2 };
    INFO("logger1.sinks: " << logger1->name());
    CHECK(logger1->sinks() == EXPECTED_SINKS1);
    INFO("logger2.sinks: "<< logger2->name());
    CHECK(logger2->sinks() == EXPECTED_SINKS2);
    INFO("logger3.sinks: "<< logger3->name());
    CHECK(logger3->sinks() == EXPECTED_SINKS1);

    INFO("OTHER_LOGGERS use sink=sink1");
    ::spdlog::apply_all([&](LoggerPtr log) {
        // if (log->name() != "foo_2") {
        if (!hasLoggerSameName(log)) {
            INFO("OTHER_LOGGERS.sinks: log="<< log->name());
            CHECK(log->sinks() == EXPECTED_SINKS1);
        }
    });
}

TEST_CASE("assignSinks: Should assign several sinks to all loggers")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    auto sink1 = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto sink2 = std::make_shared<spdlog::sinks::null_sink_mt>();
    const Sinks EXPECTED_SINKS{ sink1, sink2 };


    // -- ACT:
    auto console = spdlog::stdout_color_mt("console");
    auto logger0 = spdlog::default_logger();
    // NOT-WORKING YET: Sinks are not inherited by loggers when sinks are assigned EARLY.
    simplelog::backend_spdlog::assignSinks(EXPECTED_SINKS);
    auto logger1 = useOrCreateLogger("foo_1");
    auto logger2 = useOrCreateLogger("foo_2");
    // XXX-BAD-WORKARDOUND: Late assign/override is needed.
    // simplelog::backend_spdlog::assignSinks(EXPECTED_SINKS);
    
    // -- VERIFY:
    INFO("logger1.sinks: " << logger1->name());
    CHECK(logger1->sinks().size() == EXPECTED_SINKS.size());
    CHECK(logger1->sinks() == EXPECTED_SINKS);
    // CHECK(logger1->sinks().front() == sink1);
    // CHECK(logger1->sinks().back()  == sink2);
    INFO("logger2.sinks: "<< logger2->name());
    CHECK_EQ(logger2->sinks(), EXPECTED_SINKS);

    INFO("ENSURE: ALL_LOGGERS.sinks are same.");
    ::spdlog::apply_all([&](LoggerPtr log) {
        INFO("ALL_LOGGERS.sinks: log="<< log->name());
        CHECK_EQ(log->sinks(), EXPECTED_SINKS);
    });
}

TEST_CASE("assignSinkToAny: Should assign sink to any matching loggers")
{
#if 0    
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    auto sink1 = std::make_shared<spdlog::sinks::null_sink_mt>();
    auto sink2 = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    auto logger1 = useOrCreateLogger("foo_1");
    auto logger2 = useOrCreateLogger("foo_2");
    auto logger3 = useOrCreateLogger("foo_3");

    // -- ACT:
    const auto& hasLoggerSameName = [](LoggerPtr log) {
        return log->name() == "foo_2";
    };
    simplelog::backend_spdlog::assignSink(sink1);
    simplelog::backend_spdlog::assignSinkToAny(sink2, hasLoggerSameName);
    
    // -- VERIFY: Only logger2.sinks == EXPECTED_SINKS2
    const Sinks EXPECTED_SINKS1{ sink1 };
    const Sinks EXPECTED_SINKS2{ sink2 };
    INFO("logger1.sinks: " << logger1->name());
    CHECK(logger1->sinks() == EXPECTED_SINKS1);
    INFO("logger2.sinks: "<< logger2->name());
    CHECK(logger2->sinks() == EXPECTED_SINKS2);
    INFO("logger3.sinks: "<< logger3->name());
    CHECK(logger3->sinks() == EXPECTED_SINKS1);

    INFO("OTHER_LOGGERS use sink=sink1");
    ::spdlog::apply_all([&](LoggerPtr log) {
        if (log->name() != "foo_2") {
            INFO("OTHER_LOGGERS.sinks: log="<< log->name());
            CHECK(log->sinks() == EXPECTED_SINKS1);
        }
    });
#endif
}

TEST_SUITE_END();
} // < NAMESPACE-END.
//< ENDOF(__TEST_SOURCE_FILE__)
