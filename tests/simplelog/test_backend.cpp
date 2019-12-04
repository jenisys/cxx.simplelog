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
// PREPARED: #include "CleanupLoggingFixture.hpp"

namespace {

// PREPARED: using tests::simplelog::backend_spdlog::CleanupLoggingFixture;
using LoggerPtr = std::shared_ptr<spdlog::logger>;
using Level = ::spdlog::level::level_enum;

// ============================================================================
// TEST SUPPORT:
// ============================================================================
auto makeLogger(const std::string& name) -> LoggerPtr
{
    return std::make_shared<spdlog::logger>(name);
}

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog");
TEST_CASE("xxx: ..." * doctest::skip())
{
    MESSAGE("TODO");
    CHECK(true);
}

TEST_SUITE_END();
} // < NAMESPACE-END.
//< ENDOF(__TEST_SOURCE_FILE__)
