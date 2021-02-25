/**
 * @file tests/simplelog.backend.null/test_LogMacros.cpp
 * @note REQUIRES: doctest >= 2.3.5
 * @author Jens Engel
 **/

// -- INCLUDES:
#include "../test_support/CaptureOutputStream.hpp"
#include "doctest/doctest.h"
#include "simplelog/LogMacros.hpp"

// -- MORE-INCLUDES:
#include <memory> //< USE: std::shared_ptr<T>
#include <sstream>

namespace {

// ============================================================================
// TEST CONFIG:
// ============================================================================
const bool NO_SHORT_MACROS = (SIMPLELOG_HAVE_SHORT_MACROS == 0);
const std::string EMPTY_STRING{};

// ============================================================================
// TEST SUPPORT:
// ============================================================================

// ============================================================================
// TEST SUITE:
// ============================================================================
TEST_SUITE_BEGIN("simplelog.backend_null");
TEST_CASE("LogMacros: can use all macros")
{
    CaptureOutputStream captured;

    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    captured.enable();
    SIMPLELOG_FATAL("USE_LEVEL: FATAL");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_CRITICAL("USE_LEVEL: CRITICAL");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_ERROR("USE_LEVEL: ERROR");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_WARN("USE_LEVEL: WARN");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_INFO("USE_LEVEL: INFO");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_DEBUG("USE_LEVEL: DEBUG");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();
}

TEST_CASE("LogMacros: can use all macros with placeholders")
{
    CaptureOutputStream captured;

    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    captured.enable();
    SIMPLELOG_ERROR("Hello {}", std::string("Alice"));
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SIMPLELOG_WARN("Hello {} and {}", std::string("Alice"), "BOB");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();
}

TEST_CASE("LogMacros: can use short macros" * doctest::skip(NO_SHORT_MACROS))
{
    CaptureOutputStream captured;

    SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("default_1");
    captured.enable();
    SLOG_FATAL("USE_LEVEL: FATAL");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SLOG_CRITICAL("USE_LEVEL: CRITICAL");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SLOG_ERROR("USE_LEVEL: ERROR");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SLOG_WARN("USE_LEVEL: WARN");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SLOG_INFO("USE_LEVEL: INFO");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();

    captured.enable();
    SLOG_DEBUG("USE_LEVEL: DEBUG");
    captured.disable();
    CHECK_EQ(captured.str(), EMPTY_STRING);
    captured.clear();
}

TEST_SUITE_END();
} // namespace
//< ENDOF(__TEST_SOURCE_FILE__)
