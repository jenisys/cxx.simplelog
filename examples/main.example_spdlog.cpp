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

// -- SPECIAL CASE:
// PREPARED: #include "fmt/format.h" // -- USE: fmt::format()


// ==========================================================================
// EXAMPLE: Logging sources/users
// ==========================================================================
void example_useLoggingWithDefaultModule(void)
{
    SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.bar");

    // -- USING fmtlib/fmt: For safe, fast/efficient formatting of parameters.
    // NOTE: Python-like: print("Hello {}".format("Alice"))
    // SEE:  https://github.com/fmtlib/fmt
    SIMPLELOG_ERROR0("Hello Alice");
    SIMPLELOG_WARN("Hello {}", "Bob");
    SIMPLELOG_INFO("Hello {0} and {1}", "Alice", std::string("Bob"));
    SIMPLELOG_INFO("Hello type {0}, int:{1} and bool:{2}", "Alice", 42, true);

    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    SLOG_ERROR0("Hello Alice");
    SLOG_WARN("Hello {}", "Bob");
}

void example_useLoggingWithOverriddenDefaultModule(void)
{
    SIMPLELOG_DEFINE_DEFAULT_MODULE("OUTER");
    SLOG_WARN0("Use module=OUTER");

    {
        // -- OVERRIDE DEFAULT LOGGING-MODULE: In this scope
        SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("INNER");
        SLOG_WARN0("Use module=INNER (overrides: OUTER)");
    }
    SLOG_WARN0("Use module=OUTER (again, after scope-exit)");
}

#if 0
void example_useDefaultLoggerWithoutDefiningOne_does_not_compile(void)
{
    // UNDEFINED: SIMPLELOG_DEFINE_DEFAULT_MODULE("foo");

    SIMPLELOG_ERROR0("Hello Alice");
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES.
    SLOG_ERROR0("Hello Alice");
}
#endif

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

    SLOGM_ERROR0(log1, "Use Logger_1");
    SLOGM_WARN0( log2, "Use Logger_2");
}

// std::shared_ptr<spdlog::logger>
auto getLogger(void)
{
    // static SIMPLELOG_DEFINE_MODULE(theLog, "foo.static");
    SIMPLELOG_DEFINE_STATIC_MODULE(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getLogger();
    SLOGM_ERROR0(log, "Hello Alice");
}


// ==========================================================================
// MAIN-FUNCTION: Setup logging subsystem
// ==========================================================================
#include "simplelog/backend/spdlog/SetupUtil.hpp"
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

SIMPLELOG_DEFINE_STATIC_MODULE(rootLog, "root");

void use_simplelog(void)
{
    example_useLoggingWithDefaultModule();
    example_useLoggingWithOverriddenDefaultModule();

    // -- SPECIAL CASE: Reassign LOGGING_THRESHOLD_LEVEL here.
    // OR: SIMPLELOG_BACKEND_LEVEL_WARN
    SIMPLELOG_DEFINE_MODULE(console, "console");
    SLOGM_WARN0(console, "SETUP_LOGGING: setMinLevel=warn");
    simplelog::backend_spdlog::setMinLevel(spdlog::level::warn);
    
    // -- SPECIAL CASE END.
    example_useTwoLoggers();
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();
}

int main(int argc, char **argv)
{
    // -- PHASE 1: SETUP LOGGING SUBSYSTEM
    // NOTE: Specific for each logging-backend / logging-framework.
    auto logger1 = getLogger(); //< ENSURE: Logger is created and registered.
    auto console = spdlog::stdout_color_mt("console");
    // auto console = spdlog::stdout_logger_mt("console");

    // -- CHANGE: LOG-MESSAGE FORMAT PATTERN:
    // SEE: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // PATTERN %v: message text
    // PATTERN %@: source-location
    // SCHEMA: <ISO_DATE>_<ISO_TIME>.<microseconds> <name>::<level>  <message>
    spdlog::set_pattern("%Y-%m-%d_%T.%f  %^%10n::%-7l%$  %v");
    
    console->warn("SETUP_LOGGING: Set level=debug");
    spdlog::set_level(spdlog::level::debug);
    auto theSink = console->sinks().front();
    simplelog::backend_spdlog::assignSink(theSink);
    console->warn("SETUP_LOGGING: Set min-level=info");
    simplelog::backend_spdlog::setMinLevel(spdlog::level::info);
    // -- SAME AS: setMinLevel(SIMPLELOG_BACKEND_LEVEL_INFO);

    // -- PHASE 2: USE LOGGING SUBSYSTEM
    console->warn("main: Logging started.");
    rootLog->info("main: Use static logger.root");
    use_simplelog();
    console->warn("main: Ends here.");
    return 0;
}
