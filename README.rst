SIMPLELOG: Meta-Logging for C++
=============================================================================

:REQUIRES: Modern C++ (C++11 or newer)
:LICENSE:  MIT

CORE IDEAS:

* Provide common set of preprocessor macros for logging (and tracing)
* Log engine/subsystem is hidden and can be replaced w/ another implementation
* Log setup can be specific w/ concrete logging subsystem

ASPECTS:

* log-user: log statements are used in many places
* log-user: Does not care about setup of logging subsystem and threshold levels
* log-admin: Setup of logging subsystem/backend
* log-admin: Setup of log levels, log-sinks, formatters, ...
* log-admin: Done only in main/main.cpp context (decision: Per program)


INTENTIONS:

* Keep log-user code clean (independent of the concrete logging subsystem)
* log-user: Recompile of library w/ different logging subsystem is acceptable
* Support multiple logging subsystems/backends (if possible)
* Avoid vendor-lockin (of concrete logging subsystem)


NEEDS:

* Support for multiple categories/loggers per program
  (reason: configuration-point for threshold, context for functionality)

PROBLEMS:

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
* Define/Redefine default sink
* Read logging configuration from config-file



EXAMPLE
------------------------------------------------------------------------------

.. code-block: c++

    // -- USE DEFAULT LOGGING-MODULE (within a scope)
    SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.bar");

    // -- MACROS: SLOG_xxx() = SIMPLELOG_xxx()
    // SAME AS: SLOG_xxx0(cstring)  -- Only cstring message.
    SLOG_FATAL0("Message ...");
    SLOG_ERROR0("Message ...");
    SLOG_WARN0("Message ...");
    SLOG_INFO0("Message ...");
    SLOG_DEBUG0("Message ...");

    // -- MACROS WITH CONDITION: SLOG_xxx0_IF(cstring)
    SLOG_FATAL0_IF(condition, "Message ...");
    SLOG_ERROR0_IF(condition, "Message ...");
    SLOG_WARN0_IF(condition, "Message ...");
    SLOG_INFO0_IF(condition, "Message ...");
    SLOG_DEBUG0_IF(condition, "Message ...");

    // -- CASE: Log message w/ parameters => SLOG_xxx()
    std::string name("Alice");
    SLOG_ERROR("Hello {0} (number={1:d}", name, 42);

.. code-block: c++

    // -- USE MULTIPLE LOGGING-MODULES (loggers): In same scope
    SIMPLELOG_DEFINE_MODULE(log1, "foo.bar");
    SIMPLELOG_DEFINE_MODULE(log2, "foo.BAZ");

    // -- MACROS: SLOGM_xxx() = SIMPLELOGM_xxx()
    // SAME AS: SLOG_ERROR()
    SLOGM_FATAL0(log1, "Message ...");
    SLOGM_ERROR( log2, "Hello {0}", "Alice");


DEPENDENCIES
------------------------------------------------------------------------------

* spdlog: https://github.com/gabime/spdlog.git (as default logging backend)
* fmt: https://github.com/fmtlib/fmt.git (used by spdlog; embedded)
* doctest: https://github.com/onqtam/doctest.git (for unit tests)


SCRATCHPAD: C++ Logging Libraries
-----------------------------------------------------------------------------

SEE ALSO:
* https://cpp.libhunt.com/categories/779-logging

LIBS:
* spdlog (license: BSD)
* boost.log
* log4cpp
* ...

* blackhole (license: MIT): https://github.com/3Hren/blackhole
    - Blackhole is an attribute-based logger with strong focus on gaining maximum performance as possible for such kind of loggers.
    - Was a header-only lib, is now a shared lib.
    - Support fmt library !?!
    - Formatter: JSON, ...
    - Sinks: Null, Console, File, Socket, ...

* loguru: https://github.com/emilk/loguru
    - header-only library
    - Only one log category
    - Supports as option also fmtlib::fmt

* reckless (license: MIT): https://github.com/mattiasflodin/reckless

BROWSING:
* templog (license: Boost): http://www.templog.org
    - Stream-based

* logog (license: BSD-like): https://github.com/johnwbyrd/logog

MORE:
* https://github.com/3Hren/blackhole
* https://www.boost.org/doc/libs/1_56_0/libs/log/doc/html

RELATED: CMake and FindBoost
* https://www.johnlamp.net/cmake-tutorial-6-realistically-getting-a-boost.html
* http://gernotklingler.com/blog/simple-customized-logger-based-boost-log-v2/

