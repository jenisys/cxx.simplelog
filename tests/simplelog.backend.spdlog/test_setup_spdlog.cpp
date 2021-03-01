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

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.spdlog.setup");
TEST_CASE("spdlog::set_level(): New level should override levels in "
          "pre-existing logger")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    const Level DESIRED_LEVEL = SIMPLELOG_BACKEND_LEVEL_ERROR;
    auto logger = useOrCreateLogger("foo");
    logger->set_level(SIMPLELOG_BACKEND_LEVEL_DEBUG);

    spdlog::set_level(DESIRED_LEVEL);
    REQUIRE_EQ(logger->level(), DESIRED_LEVEL);
    spdlog::apply_all([&](LoggerPtr log) { CHECK_EQ(log->level(), DESIRED_LEVEL); });
}

TEST_CASE("spdlog::set_level(): Assigned level should be used for newly "
          "created loggers")
{
    using simplelog::backend_spdlog::useOrCreateLogger;
    CleanupLoggingFixture cleanupGuard;
    const auto DESIRED_LEVEL1 = SIMPLELOG_BACKEND_LEVEL_ERROR;
    CHECK_EQ(spdlog::get("foo.1"), nullptr);
    spdlog::set_level(DESIRED_LEVEL1);
    SIMPLELOG_DEFINE_MODULE(log1, "foo.1");
    CHECK_EQ(log1->level(), DESIRED_LEVEL1);

    // -- CASE: Reduce default log-level => Newly created loggers use new level.
    const auto DESIRED_LEVEL2 = SIMPLELOG_BACKEND_LEVEL_DEBUG;
    CHECK(spdlog::get("foo.2") == nullptr);
    spdlog::set_level(DESIRED_LEVEL2);
    SIMPLELOG_DEFINE_STATIC_MODULE(log2, "foo.2");
    CHECK_EQ(log2->level(), DESIRED_LEVEL2);
    // -- SIDE-EFFECT:
    CHECK_EQ(log1->level(), DESIRED_LEVEL2);
}

TEST_SUITE_END();
} // namespace
//< ENDOF(__TEST_SOURCE_FILE__)
