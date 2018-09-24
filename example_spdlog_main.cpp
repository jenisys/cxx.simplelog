/**
 * @file example_spdlog_main.cpp
 * 
 * Simple example how a generic logging framework w/ different logging 
 * subsystems could look like.
 * 
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 **/

// -- INCLUDES:
#define SIMPLELOG_USE_BACKEND_SPDLOG 1
// #define SIMPLELOG_USE_BACKEND 10
#include "simplelog/LogMacros.hpp"
#include "simplelog/backend/spdlog/Utils.hpp"
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>


// ==========================================================================
// EXAMPLE
// ==========================================================================
void example_useLogging(void)
{
    CXXLOG_DEFINE_CATEGORY(log, "foo.bar");
    // spdlog_setLevelToAll(CXXLOG_BACKEND_LEVEL_INFO);

    CXXLOG_ERROR0(log, "Hello Alice");
    CXXLOG_WARN(log, "Hello {}", "Bob");
    CXXLOG_INFO(log, "Hello {0} and {1}", "Alice", "Bob");
    CXXLOG_INFO(log, "Hello type {0}, int:{1} and bool:{2}", "Alice", 42, true);
}

void example_useTwoLoggers(void)
{
    CXXLOG_DEFINE_CATEGORY(log1, "foo.one");
    CXXLOG_DEFINE_CATEGORY(log2, "foo.two");

    CXXLOG_ERROR0(log1, "Logger_1");
    CXXLOG_WARN0(log2, "Logger_2");
}

void example_useTwoLoggersWithSameName(void)
{
    CXXLOG_DEFINE_CATEGORY(log1, "foo.same");
    CXXLOG_DEFINE_CATEGORY(log2, "foo.same");

    CXXLOG_ERROR0(log1, "Logger_1");
    CXXLOG_WARN0(log2,  "Logger_2");
}

// std::shared_ptr<spdlog::logger>
auto getLogger(void)
{
    // static CXXLOG_DEFINE_CATEGORY(theLog, "foo.static");
    CXXLOG_DEFINE_STATIC_CATEGORY(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getLogger();
    CXXLOG_ERROR0(log, "Hello Alice");
}


CXXLOG_DEFINE_STATIC_CATEGORY(rootLog, "root");


// ==========================================================================
// MAIN-FUNCTION:
// ==========================================================================
int main(int argc, char **argv)
{
    // -- SETUP LOGGING SUBSYSTEM:
    auto console = spdlog::stdout_color_mt("console");
    // auto console = spdlog::stdout_logger_mt("console");
    spdlog::set_level(spdlog::level::debug);
    spdlog_useSinkAsDefaultSink(console);
    // spdlog_setLevelToAll(CXXLOG_BACKEND_LEVEL_INFO);
    spdlog_setLevelToAll(spdlog::level::info);

    console->warn("main: Logging started.");
    rootLog->info("main: Use static logger.root");
    example_useLogging();
    // spdlog_setLevelToAll(CXXLOG_BACKEND_LEVEL_WARN);
    spdlog_setLevelToAll(spdlog::level::warn);
    example_useTwoLoggers();
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();
    console->warn("main: Ends here.");
    return 0;
}
