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
// ALREADY: #define SIMPLELOG_USE_BACKEND_SPDLOG 1
#include <simplelog/LogMacros.hpp>
#include <simplelog/detail/StringifyMacro.hpp>

// -- SPECIAL CASE:
// #include <fmt/format.h> // -- USE: fmt::format()

// -- SANITY-CHECK: SIMPLEGEN-SELECT-BACKEND
#if !(defined(SIMPLELOG_USE_BACKEND_SPDLOG) && (SIMPLELOG_USE_BACKEND == 1))
#    pragma message("SIMPLELOG_USE_BACKEND_SPDLOG=" STRINGIFY(                 \
        SIMPLELOG_USE_BACKEND_SPDLOG))
#    pragma message("SIMPLELOG_USE_BACKEND=" STRINGIFY(SIMPLELOG_USE_BACKEND))
#    error "NOT-DEFINED: SIMPLELOG_USE_BACKEND_SPDLOG"
#endif

// ==========================================================================
// EXAMPLE: Logging sources/users
// ==========================================================================
void example_useLoggingWithDefaultModule(void)
{
    SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.bar");

    // -- USING fmtlib/fmt: For safe, fast/efficient formatting of parameters.
    // NOTE: Python-like: print("Hello {}".format("Alice"))
    // SEE:  https://github.com/fmtlib/fmt
    SIMPLELOG_ERROR("Hello Alice");
    SIMPLELOG_WARN("Hello {}", "Bob");
    SIMPLELOG_INFO("Hello {0} and {1}", "Alice", std::string("Bob"));
    SIMPLELOG_INFO("Hello type {0}, int:{1} and bool:{2}", "Alice", 42, true);

    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES => PREFERRED.
    SLOG_ERROR("Hello Alice");
    SLOG_WARN("Hello {}", "Bob");
}

void example_useLoggingWithOverriddenDefaultModule(void)
{
    SIMPLELOG_DEFINE_DEFAULT_MODULE("OUTER");
    SLOG_WARN("Use module=OUTER");

    {
        // -- OVERRIDE DEFAULT LOGGING-MODULE: In this scope
        SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("INNER");
        SLOG_WARN("Use module=INNER (overrides: OUTER)");
    }
    SLOG_WARN("Use module=OUTER (again, after scope-exit)");
}

#if 0
void example_useDefaultLoggerWithoutDefiningOne_does_not_compile(void)
{
    // UNDEFINED: SIMPLELOG_DEFINE_DEFAULT_MODULE("foo");

    SIMPLELOG_ERROR("Hello Alice");
    // -- ALTERNATIVE: Use SHORTER-MACRO-NAMES.
    SLOG_ERROR("Hello Alice");
}
#endif

void example_useTwoLoggers(void)
{
    SIMPLELOG_DEFINE_MODULE(log1, "foo.one");
    SIMPLELOG_DEFINE_MODULE(log2, "foo.two");

    SLOGM_ERROR(log1, "Logger_1");
    SLOGM_WARN(log2, "Logger_2");
}

void example_useTwoLoggersWithSameName(void)
{
    SIMPLELOG_DEFINE_MODULE(log1, "foo.same");
    SIMPLELOG_DEFINE_MODULE(log2, "foo.same");

    SLOGM_ERROR(log1, "Use Logger_1");
    SLOGM_WARN(log2, "Use Logger_2");
}

// std::shared_ptr<spdlog::logger>
// HINT: C++11 needs trailing-return-type specification, C++14 not.
auto getLogger(void) -> simplelog::backend_spdlog::LoggerPtr
{
    // static SIMPLELOG_DEFINE_MODULE(theLog, "foo.static");
    SIMPLELOG_DEFINE_STATIC_MODULE(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getLogger();
    SLOGM_ERROR(log, "Hello Alice");
}

// ==========================================================================
// EXAMPLE: Use logging subsystem (see above)
// ==========================================================================
#include "simplelog/backend/spdlog/SetupUtil.hpp" //< USE: setMinLevel()

SIMPLELOG_DEFINE_STATIC_MODULE(rootLog, "root");

void use_simplelog(void)
{
    SIMPLELOG_DEFINE_MODULE(console, "console");
    console->warn("MAIN: Logging started.");
    rootLog->info("MAIN: Use static logger.root");
    example_useLoggingWithDefaultModule();
    example_useLoggingWithOverriddenDefaultModule();

    // -- SPECIAL CASE: Reassign LOGGING_THRESHOLD_LEVEL here.
    // OR: SIMPLELOG_BACKEND_LEVEL_WARN
    SLOGM_WARN(console, "MAIN: SETUP_LOGGING with setMinLevel=warn");
    simplelog::backend_spdlog::setMinLevel(spdlog::level::warn);

    // -- SPECIAL CASE END.
    example_useTwoLoggers();
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();

    // -- FINALLY:
    console->warn("MAIN: Ends here.");
}

// ==========================================================================
// MAIN-FUNCTION: Setup logging subsystem
// ==========================================================================
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <iostream>
#include <simplelog/backend/spdlog/ModuleUtil.hpp> //< USE: useOrCreateLogger()
#include <simplelog/backend/spdlog/SetupUtil.hpp>  //< USE: assignSink(), ...

void process_setupLogging(void)
{
    // -- HERE is the LOGGING-BACKEND-SPECIFIC part.
    auto console = spdlog::stdout_color_mt("console");
    auto theSink = console->sinks().front();

    // -- GLOBAL SETUP: Define log-sink(s), formatter pattern and DEFAULT
    // log-level. SEE:
    // https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
    // PATTERN SCHEMA: <ISO_DATE>_<ISO_TIME>.<microseconds> <name>::<level>
    // <message>
    simplelog::backend_spdlog::assignSink(theSink);
    spdlog::set_pattern("%Y-%m-%d_%T.%f  %^%10n::%-7l%$  %v");
    spdlog::set_level(spdlog::level::warn);
    // SAME AS: simplelog::backend_spdlog::setLevel(spdlog::level::warn);

    // -- SPECIFIC SETUP: OVERRIDE CONFIG FOR SPECIFIC MODULES: log-level, ...
    using simplelog::backend_spdlog::useOrCreateLogger;
    auto log1 = useOrCreateLogger("foo.bar");
    auto log2 = useOrCreateLogger("example.1");
    log1->set_level(spdlog::level::info);
    log2->set_level(spdlog::level::debug);

    // -- MAYBE: Ensure that at least level=info is used (by all loggers).
    simplelog::backend_spdlog::setMinLevel(spdlog::level::info);
}

int main(int argc, char **argv)
{
    // -- PHASE 1: SETUP LOGGING SUBSYSTEM
    // NOTE: Specific for each logging-backend / logging-framework.
    process_setupLogging();

    // -- PHASE 2: USE LOGGING SUBSYSTEM
    use_simplelog();
    return EXIT_SUCCESS;
}
