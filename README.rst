PROOF-OF-CONCEPT: Generic Logging/Tracing Macros for C++
=============================================================================

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
* Keep log-user code clean (meaning: independent of the concrete logging subsystem)
* log-user: Recompile of library w/ different logging subsystem is acceptable
* Support multiple logging subsystems/backends (if possible)
* Avoid vendor-lockin (of concrete logging subsystem)

NEEDS:
* Support for multiple categories/loggers per program 
  (reason: configuration-point for threshold, context for functionality)

PROBLEMS:
* Log with parameters / placeholders: 
  printf-like/vargs, iostream-like, format-like, ...


DESIGN DECISION:
* Use fmt by default (reason: readable, rather efficient/speedy)
* Use explicit log-level configuration with wildcards
  (instead of: log-level inheritance)
* Avoid log-level enums/types at log-points 
  (should be hidden by macro to make it easier to replace implementation)
* Use short-macro names if possible and enabled


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

    CXXLOG_DEFINE_CATEGORY(log, "foo.bar");
    
    // -- MACROS:
    // SAME AS: CXXLOG_ERROR()
    LOG_FATAL(log, "Message ...");
    LOG_ERROR(log, "Message ...");
    LOG_WARN(log, "Message ...");
    LOG_INFO(log, "Message ...");
    LOG_DEBUG(log, "Message ...");

    // -- MACROS WITH CONDITION:
    LOG_FATAL_IF(condition, log, "Message ...");
    LOG_ERROR_IF(condition, log, "Message ...");
    LOG_WARN_IF(condition, log, "Message ...");
    LOG_INFO_IF(condition, log, "Message ...");
    LOG_DEBUG_IF(condition, log, "Message ...");

    // -- CASE: Log message w/ parameters
    std::string name("Alice");
    LOG_ERROR_F(log, "Hello {0} (number={1:d}", name, 42);


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
    - 
