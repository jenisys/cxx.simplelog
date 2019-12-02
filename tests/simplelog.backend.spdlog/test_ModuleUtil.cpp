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
#include <memory>   //< USE: std::shared_ptr<T>

// -- LOCAL-INCLUDES:
#include "CleanupLoggingFixture.hpp"

namespace {

using tests::simplelog::backend_spdlog::CleanupLoggingFixture;
using LoggerPtr = std::shared_ptr<spdlog::logger>;
using Level = ::spdlog::level::level_enum;

// ============================================================================
// TEST SUPPORT:
// ============================================================================
#if 0
auto& spdlog_registry(void)
{
    return ::spdlog::details::registry::instance();
}
#endif

auto makeLogger(const std::string& name)
{
    return std::make_shared<spdlog::logger>(name);
}

void require_logger_is_unknown(const std::string& name)
{
    REQUIRE_EQ(spdlog::get(name), nullptr);
}

void require_logger_is_known(const std::string& name)
{
    REQUIRE_NE(spdlog::get(name), nullptr);
}

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.spdlog.ModuleUtil");
TEST_CASE("useOrCreateLogger: Should create, init and register an unknown logger")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    require_logger_is_unknown("foo");
    auto logger1 = useOrCreateLogger("foo");
    CHECK_NE(logger1, nullptr);
    require_logger_is_known("foo");
}

TEST_CASE("useOrCreateLogger: Created logger should inherit current config (log-level, ...)")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    spdlog::set_level(SIMPLELOG_BACKEND_LEVEL_ERROR);
    require_logger_is_unknown("foo.1");
    auto logger1 = useOrCreateLogger("foo.1");
    CHECK_EQ(logger1->level(), SIMPLELOG_BACKEND_LEVEL_ERROR);

    // -- RE-VERIFY: Drop default logging-level.
    // HINT: set_level() assigns new-level to all loggers.
    spdlog::set_level(SIMPLELOG_BACKEND_LEVEL_DEBUG);
    require_logger_is_unknown("foo.2");
    auto logger2 = useOrCreateLogger("foo.2");
    CHECK_EQ(logger1->level(), SIMPLELOG_BACKEND_LEVEL_DEBUG);
    CHECK_EQ(logger2->level(), SIMPLELOG_BACKEND_LEVEL_DEBUG);
}

TEST_CASE("useOrCreateLogger: Should return a known logger")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    auto logger1 = makeLogger("foo");
    spdlog::register_logger(logger1);
    
    require_logger_is_known("foo");
    REQUIRE_EQ(logger1, spdlog::get("foo"));
    auto logger2 = useOrCreateLogger("foo");
    CHECK_EQ(logger1, logger2);
}


TEST_SUITE_END();
} // < NAMESPACE-END.
//< ENDOF(__TEST_SOURCE_FILE__)
