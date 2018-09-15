PROOF-OF-CONCEPT: Generic Logging/Tracing Macros for C++
=============================================================================

CORE IDEAS:

* Provide common set of preprocessor macros for logging (and tracing)
* Log engine/subsystem is hidden and can be replaced w/ another implementation
* Log setup can be specific

PROBLEMS:

* Log with parameters / placeholders: 
  vargs, iostream-like, format-like, ...


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


EXAMPLE
------------------------------------------------------------------------------

.. code-block: c++

    auto log = CXXLOG_DEFINE_CATEGORY("hello");
    
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
    LOG_ERROR_F(log4me, "Hello {0} (number={1:d}", name, 42);
