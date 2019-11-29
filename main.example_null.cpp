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
    SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.bar");
    // spdlog_setLevelToAll(SIMPLELOG_BACKEND_LEVEL_INFO);

    SLOG_ERROR0("Hello Alice");
    SLOG_WARN("Hello {}", "Bob");
    SLOG_INFO("Hello {0} and {1}", "Alice", std::string("Bob"));
    SLOG_INFO("Hello type {0}, int:{1} and bool:{2}", "Alice", 42, true);
}

void example_useTwoLoggers(void)
{
    SIMPLELOG_DEFINE_MODULE(log1, "foo.one");
    SIMPLELOG_DEFINE_MODULE(log2, "foo.two");

    SLOGM_ERROR0(log1, "Logger_1");
    SLOGM_WARN0(log2, "Logger_2");
}

void example_useTwoLoggersWithSameName(void)
{
    SIMPLELOG_DEFINE_MODULE(log1, "foo.same");
    SIMPLELOG_DEFINE_MODULE(log2, "foo.same");

    SLOGM_ERROR0(log1, "Logger_1");
    SLOGM_WARN0(log2,  "Logger_2");
}

auto getStaticLogger(void)
{
    SIMPLELOG_DEFINE_STATIC_MODULE(theLog, "foo.static");
    // -- SAME AS: static SIMPLELOG_DEFINE_MODULE(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getStaticLogger();
    SLOGM_ERROR0(log, "Hello Alice");
}


SIMPLELOG_DEFINE_STATIC_MODULE(rootLog, "root");


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
