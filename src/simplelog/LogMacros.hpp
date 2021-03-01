/**
 * @file simplelog/LogMacros.hpp
 * Provides preprocessor macros for users of the logging subsystem.
 *
 * Maps logging macros to logging backend macros to make it easy
 * to replace the logging subsystem/backend with another logging framework.
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/detail/LogBackendMacros.hpp"
#include "simplelog/detail/SelectLogBackend.hpp"

// --------------------------------------------------------------------------
// SIMPLELOG LOGGING MACROS
// --------------------------------------------------------------------------
/**
 * @par Simplelog Example
 * @code
 *  #include "simplelog/LogMacros.hpp"
 *
 *  namespace {
 *      SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE("foo");      //< DEFAULT_MODULE_0
 *      SIMPLELOG_DEFINE_STATIC_MODULE(log0, "foo.one");    //< LOG_MODULE_0
 *  };
 *
 *  void example_use_predefinedDefaultLogger(void)
 *  {
 *      // -- USE DEFAULT LOGGING-MODULE from outer-scope (DEFAULT_MODULE_0)
 *      // HINT: short-log-macro are preferred over long-macro-names if possible
 *      //       EXAMPLE: SLOG_WARN(...) <=> SIMPLELOG_WARN(...)
 *      SLOG_WARN("Hello Alice");
 *      SLOG_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *
 *      int value = 42;
 *      SLOG_FATAL_IF(value == 42,
 *                    "Show value={0} (if conditition is true)", value);
 *  }
 *
 *  void example_use_ownDefaultLogger(void)
 *  {
 *      // -- DEFINE AND USE DEFAULT LOGGING-MODULE (hint: less params in
 *log-macros) SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.default"); SLOG_WARN("Hello
 *Alice"); SLOG_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 *
 *  void example_use_severalLoggers(void)
 *  {
 *      SIMPLELOG_DEFINE_MODULE(log, "foo.two");
 *
 *      SLOGM_WARN(log0, "Hello Alice");  //< Only message (use module above)
 *      SLOGM_ERROR(log, "Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 * @endcode
 **/
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// DEFINE MODULES: SPECIFIC-MODULE (logger)
// ----------------------------------------------------------------------------
#define SIMPLELOG_DEFINE_MODULE(var_name, name) SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_STATIC_MODULE(var_name, name)                                                \
    SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_DEFAULT_MODULE(name)                                                         \
    SIMPLELOG_BACKEND_DEFINE_MODULE(simplelog_defaultModule, name)
#define SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE(name)                                                  \
    SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(simplelog_defaultModule, name)

// ----------------------------------------------------------------------------
// SIMPLELOG LOG MACROS
// ----------------------------------------------------------------------------
// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  SIMPLELOG_xxx(message)        -- Message as string w/o placeholders.
//  SIMPLELOG_xxx(format, ...)    -- Message w/ placeholders; format describes
//  message schema.
#define SIMPLELOG_FATAL(...)                                                                          \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOG_CRITICAL(...)                                                                       \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOG_ERROR(...)                                                                          \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOG_WARN(...)                                                                           \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOG_INFO(...)                                                                           \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOG_DEBUG(...)                                                                          \
    SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// MACRO-SIGNATURE:
//  SIMPLELOG_xxx_IF(condition, message)        -- Message as string w/o
//  placeholders. SIMPLELOG_xxx_IF(condition, format, ...)    -- Message w/
//  placeholders; format describes message schema.
#define SIMPLELOG_FATAL_IF(condition, ...)                                                            \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL,       \
                             __VA_ARGS__)
#define SIMPLELOG_CRITICAL_IF(condition, ...)                                                         \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL,    \
                             __VA_ARGS__)
#define SIMPLELOG_ERROR_IF(condition, ...)                                                            \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR,       \
                             __VA_ARGS__)
#define SIMPLELOG_WARN_IF(condition, ...)                                                             \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN,        \
                             __VA_ARGS__)
#define SIMPLELOG_INFO_IF(condition, ...)                                                             \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO,        \
                             __VA_ARGS__)
#define SIMPLELOG_DEBUG_IF(condition, ...)                                                            \
    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG,       \
                             __VA_ARGS__)

// -- USE: SPECIFIC-MODULE (logger)
#define SIMPLELOGM_FATAL(logger, ...)                                                                 \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL(logger, ...)                                                              \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOGM_ERROR(logger, ...)                                                                 \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOGM_WARN(logger, ...)                                                                  \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOGM_INFO(logger, ...)                                                                  \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOGM_DEBUG(logger, ...)                                                                 \
    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

#define SIMPLELOGM_FATAL_IF(condition, logger, ...)                                                   \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL_IF(condition, logger, ...)                                                \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOGM_ERROR_IF(condition, logger, ...)                                                   \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOGM_WARN_IF(condition, logger, ...)                                                    \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOGM_INFO_IF(condition, logger, ...)                                                    \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOGM_DEBUG_IF(condition, logger, ...)                                                   \
    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// --------------------------------------------------------------------------
// SHORTER LOGGING MACROS: SLOG_xxx() = SIMPLELOG_xxx(), SLOGM_xxx() =
// SIMPLELOGM_xxx()
// --------------------------------------------------------------------------
#if SIMPLELOG_HAVE_SHORT_MACROS
// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  SLOG_xxx(message)        -- Message as string w/o placeholders.
//  SLOG_xxx(format, ...)    -- Message w/ placeholders; format describes
//  message schema.
#    define SLOG_FATAL(...)    SIMPLELOG_FATAL(__VA_ARGS__)
#    define SLOG_CRITICAL(...) SIMPLELOG_CRITICAL(__VA_ARGS__)
#    define SLOG_ERROR(...)    SIMPLELOG_ERROR(__VA_ARGS__)
#    define SLOG_WARN(...)     SIMPLELOG_WARN(__VA_ARGS__)
#    define SLOG_INFO(...)     SIMPLELOG_INFO(__VA_ARGS__)
#    define SLOG_DEBUG(...)    SIMPLELOG_DEBUG(__VA_ARGS__)

// MACRO-SIGNATURE:
//  SLOG_xxx_IF(condition, message)        -- Message as string w/o
//  placeholders. SLOG_xxx_IF(condition, format, ...)    -- Message w/
//  placeholders; format describes message schema.
#    define SLOG_FATAL_IF(condition, ...)    SIMPLELOG_FATAL_IF(condition, __VA_ARGS__)
#    define SLOG_CRITICAL_IF(condition, ...) SIMPLELOG_CRITICAL_IF(condition, __VA_ARGS__)
#    define SLOG_ERROR_IF(condition, ...)    SIMPLELOG_ERROR_IF(condition, __VA_ARGS__)
#    define SLOG_WARN_IF(condition, ...)     SIMPLELOG_WARN_IF(condition, __VA_ARGS__)
#    define SLOG_INFO_IF(condition, ...)     SIMPLELOG_INFO_IF(condition, __VA_ARGS__)
#    define SLOG_DEBUG_IF(condition, ...)    SIMPLELOG_DEBUG_IF(condition, __VA_ARGS__)

// -- USE: SPECIFIC-MODULE (logger)
// MACRO-SIGNATURE:
//  SLOGM_xxx(logger, message)        -- Message as string w/o placeholders.
//  SLOG;_xxx(logger, format, ...)    -- Message w/ placeholders; format
//  describes message schema.
#    define SLOGM_FATAL(logger, ...)    SIMPLELOGM_FATAL(logger, __VA_ARGS__)
#    define SLOGM_CRITICAL(logger, ...) SIMPLELOGM_CRITICAL(logger, __VA_ARGS__)
#    define SLOGM_ERROR(logger, ...)    SIMPLELOGM_ERROR(logger, __VA_ARGS__)
#    define SLOGM_WARN(logger, ...)     SIMPLELOGM_WARN(logger, __VA_ARGS__)
#    define SLOGM_INFO(logger, ...)     SIMPLELOGM_INFO(logger, __VA_ARGS__)
#    define SLOGM_DEBUG(logger, ...)    SIMPLELOGM_DEBUG(logger, __VA_ARGS__)

// MACRO-SIGNATURE:
//  SLOGM_xxx_IF(condition, logger, message)        -- Message as string w/o
//  placeholders. SLOGM_xxx_IF(condition, logger, format, ...)    -- Message w/
//  placeholders; format describes message schema.
#    define SLOGM_FATAL_IF(condition, logger, ...) SIMPLELOGM_FATAL_IF(condition, logger, __VA_ARGS__)
#    define SLOGM_CRITICAL_IF(condition, logger, ...)                                                 \
        SIMPLELOGM_CRITICAL_IF(condition, logger, __VA_ARGS__)
#    define SLOGM_ERROR_IF(condition, logger, ...) SIMPLELOGM_ERROR_IF(condition, logger, __VA_ARGS__)
#    define SLOGM_WARN_IF(condition, logger, ...)  SIMPLELOGM_WARN_IF(condition, logger, __VA_ARGS__)
#    define SLOGM_INFO_IF(condition, logger, ...)  SIMPLELOGM_INFO_IF(condition, logger, __VA_ARGS__)
#    define SLOGM_DEBUG_IF(condition, logger, ...) SIMPLELOGM_DEBUG_IF(condition, logger, __VA_ARGS__)
#endif

// -- AFTER-HEADER: CONVENIENCE-INCLUDE
#if SIMPLELOG_HAVE_MACROS0
#    include "simplelog/detail/LogMacros0.hpp"
#endif

// -- ENDOF-HEADER-FILE
