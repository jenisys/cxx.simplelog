SIMPLELOG: Meta-Logging for C++
=============================================================================

:REQUIRES: Modern C++ (C++11 or newer)
:LICENSE:  MIT

CORE IDEAS:

* Provide common set of preprocessor macros for logging (and tracing)
* Log engine/subsystem is hidden and can be replaced w/ another implementation
* Log setup can be specific w/ concrete logging subsystem

PROCESSING MODEL::

    0..N LOG-SOURCE(s) => LOGGING-SUBSYSTEM => 0..M LOG-SINKS

    * Log-source(s) generate log records by using the logging subsystem
    * Log-source(s) may perform log-level based filtering (to skip records)
    * The logging subsystem delegates log-record output to log-sinks
    * The logging subsystem has normally at least one log-sink (configured)
    * A log-source may have zero or more log-sink(s) (normally: 1 or more)
    * A log-source 1 may have other log-sink(s) than log-source 2

ASPECTS:

* log-user: log statements are used in many places
* log-user: Does not care about setup of logging subsystem and threshold levels
* log-admin: Setup of logging subsystem/backend
* log-admin: Setup of log levels, log-sinks, formatters, ...
* log-admin: Done only in main/main.cpp context (decision: Per program)


DESIGN INTENTIONS:

* Keep log-user code clean (independent of the concrete logging subsystem)
* log-user: Recompile of library w/ different logging subsystem is acceptable
* Support multiple logging subsystems/backends (if possible)
* Avoid vendor-lockin (of concrete logging subsystem)


NEEDS:

* Support for multiple categories/loggers per program
  (reason: configuration-point for threshold, context for functionality)

DESIGN OPTION: Compact, safe and efficient log-record placeholder needed

* Log with parameters / placeholders:
  printf-like/vargs, iostream-like, format-like (fmt), ...


DESIGN DECISION:

* Use fmt by default (reason: readable, rather efficient/speedy, part of C++20)
* Use explicit log-level configuration with wildcards (instead of: log-level inheritance)
* Avoid log-level enums/types at log-points (logging-sources)
  (should be hidden by macro to make it easier to replace implementation)
* Use short-log-macro names if possible and enabled
* Use default logging-module (logger) in most cases (if possible).
  REASON: Makes logging statement shorter/simpler (at logging source)


SEE ALSO:

* https://github.com/fmtlib/fmt
* https://github.com/gabime/spdlog

RELATED: Overview C++ logging libraries

* https://github.com/rigtorp/awesome-modern-cpp
* https://cpp.libhunt.com Overview C++ logging libraries

OPEN ISSUE: spdlog

* Read logging configuration from config-file


EXAMPLE
------------------------------------------------------------------------------

The following sections shows how the functionality can be used in C++:

* Use case: LOG-SOURCE that generates log-records (generic, backend independent)
* Use case: Setup of the logging subsystem (context: main.cpp; backend specific)

.. code-block:: c++

    // -- FILE: my_library1/.../example_1.cpp
    // EXAMPLE: Use LOG-MACROS with DEFAULT_MODULE in local scope

    // -- INCLUDES:
    #include <simplelog/LogMacros.hpp>

    namespace {
        // -- USE DEFAULT LOGGING-MODULE (within a scope)
        SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("example.1"); //< DEFAULT_MODULE_1
        SIMPLELOG_DEFINE_STATIC_MODULE(log1, "other");       //< OTHER_MODULE_2
    }

    void log_source_func1(void)
    {
        // -- USE-SHORT-MACROS: SLOG_xxx() == SIMPLELOG_xxx()  (if possible)
        // USE: DEFAULT_MODULE_1: name="example.1" 
        // OR: SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("example.2");
        SLOG_FATAL("Message with zero args");
        SLOG_ERROR("Hello {0}", "Alice");
        SLOG_WARN( "Hello {0} and {1}", "Alice", std::string("Bob"));
        SLOG_INFO_IF(true, "OOPS: Hello {0}", "Alice"_s);

        // -- USE: OTHER_MODULE_2
        // MACROS: SLOGM_xxx(log, ...) == SIMPLELOGM_xxx(log, ...)
        SLOGM_INFO(log1, "Use another logger"); //< OTHER_MODULE_2
    }

.. code-block:: c++

    // -- FILE: main.cpp
    // SETUP LOGGING HERE: With BACKEND=spdlog
    #define SIMPLELOG_USE_BACKEND_SPDLOG 1
    #include <simplelog/backend/spdlog/SetupUtil.hpp>

    void process_setupLogging(void)
    {
        // -- HERE is the LOGGING-BACKEND-SPECIFIC part.
        // SEE: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
        auto console = spdlog::stdout_color_mt("console");
        auto theSink = console->sinks().front();

        // -- GLOBAL SETUP: Define log-sink(s), formatter pattern and DEFAULT log-level.
        // PATTERN SCHEMA: <ISO_DATE>_<ISO_TIME>.<microseconds> <name>::<level>  <message>
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
        // simplelog::backend_spdlog::setMinLevel(spdlog::level::info);
    }

    int main(int argc, char** argv)
    {
        process_setupLogging();
        ...     // Do something (and log-sources will use logging);
        return EXIT_SUCCESS;
    }


DEPENDENCIES
------------------------------------------------------------------------------

* spdlog: https://github.com/gabime/spdlog.git (as default logging backend)
* fmt: https://github.com/fmtlib/fmt.git (used by spdlog; embedded)
* doctest: https://github.com/onqtam/doctest.git (for unit tests)
