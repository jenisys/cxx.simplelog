/**
 * @file main.example_syslog.cpp
 * Simple example how to simplelog.backend.syslog with syslog facility.
 * @see https://linux.die.net/man/3/syslog
 * @see https://www.man7.org/linux/man-pages/man3/syslog.3.html
 *
 * @note FORMAT (FMT) library is supported
 * @see https://github.com/fmtlib/fmt
 **/

// -- INCLUDES:
// #include "simplelog/config.hpp"
#include "simplelog/LogMacros.hpp"
#include "simplelog/detail/StringifyMacro.hpp"
#include <syslog.h>
#include <fmt/format.h> // -- USE: fmt::format()

// -- SANITY-CHECK: SIMPLEGEN-SELECT-BACKEND
#if !(defined(SIMPLELOG_USE_BACKEND_SYSLOG) && (SIMPLELOG_USE_BACKEND == 2))
#   pragma message("SIMPLELOG_USE_BACKEND_SYSLOG=" STRINGIFY(SIMPLELOG_USE_BACKEND_SYSLOG))
#   pragma message("SIMPLELOG_USE_BACKEND=" STRINGIFY(SIMPLELOG_USE_BACKEND))
#   error "NOT-DEFINED: SIMPLELOG_USE_BACKEND_SYSLOG"
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


// ==========================================================================
// EXAMPLE: Use logging subsystem (see above)
// ==========================================================================
SIMPLELOG_DEFINE_STATIC_MODULE(rootLog, "root");

void use_simplelog(void)
{
    SIMPLELOG_DEFINE_MODULE(console, "console");
    example_useLoggingWithDefaultModule();
    example_useLoggingWithOverriddenDefaultModule();

    // -- FINALLY:
    console->log(LOG_WARNING, "MAIN: Ends here.");
}

// ==========================================================================
// MAIN-FUNCTION: Setup logging subsystem
// ==========================================================================
#include <simplelog/backend/syslog/ModuleRegistry.hpp>
#include <simplelog/backend/syslog/Module.hpp>

void process_setupLogging(void)
{
    // using namespace simplelog::backend_syslog;
    using simplelog::backend_syslog::useOrCreateModule;
    using simplelog::backend_syslog::getModuleRegistry;
    auto& registry = getModuleRegistry();

    registry.setDefaultLevel(LOG_INFO);
    registry.applyToModules([](auto module) {
        module->setLevel(LOG_INFO);
    });

    // -- SPECIFIC SETUP: OVERRIDE CONFIG FOR SPECIFIC MODULES: log-level, ...
    auto module1 = useOrCreateModule("foo.bar");
    module1->setLevel(LOG_DEBUG);
}

int main(int argc, char **argv)
{
    // -- PHASE 1: SETUP LOGGING SUBSYSTEM
    // NOTE: Specific for each logging-backend / logging-framework.
    // MAYBE: setlogmask(LOG_UPTO(LOG_INFO));
    openlog(nullptr, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    process_setupLogging();

    // -- PHASE 2: USE LOGGING SUBSYSTEM
    use_simplelog();
    closelog();
    return EXIT_SUCCESS;
}
