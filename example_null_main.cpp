/**
 * @file example_null_main.cpp
 * Simple example of generic logging w/ NULL backend.
 **/

// -- INCLUDES:
#define SIMPLELOG_USE_BACKEND_NULL 1
#include "simplelog/LogMacros.hpp"
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
// MAIN-FUNCTION
// ==========================================================================
int main(int argc, char **argv)
{
    // -- SETUP LOGGING SUBSYSTEM: noop
    std::cout << "NULL-EXAMPLE: No output expected."<< std::endl;
    example_useLogging();
    example_useTwoLoggers();
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();
    std::cout << "NULL-EXAMPLE: Finished." << std::endl;
    return 0;
}
