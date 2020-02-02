/**
 * @file
 * Provide preprocessor macros for users of the logging subsystem.
 *
 * Maps logging macros to logging backend macros to make it easy
 * to replace the logging subsystem/backend with another logging framework.
 **/

#pragma once

// -- INCLUDES:
// REUSE: LogMacros
#include "simplelog/LogMacros.hpp"

// --------------------------------------------------------------------------
// SIMPLELOG TRACING MACROS
// --------------------------------------------------------------------------
/**
 * @par Simplelog Trace Example
 * Tracing is only enabled in DEBUG mode.
 * Therefore, trace-macros are removed in non-DEBUG (release) builds.
 * @note Log-macros remain usable in non-DEBUG (release) builds.
 *
 * @code
 *  #include "simplelog/TraceMacros.hpp"
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
 *      //       EXAMPLE: STRACE_WARN(...) <=> SIMPLELOG_WARN(...)
 *      STRACE_WARN("Hello Alice");
 *      STRACE_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *
 *      int value = 42;
 *      STRACE_FATAL_IF(value == 42,
 *                    "Show value={0} (if conditition is true)", value);
 *  }
 *
 *  void example_use_ownDefaultLogger(void)
 *  {
 *      // -- DEFINE AND USE DEFAULT LOGGING-MODULE (hint: less params in log-macros)
 *      SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.default");
 *      STRACE_WARN("Hello Alice");
 *      STRACE_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 *
 *  void example_use_severalLoggers(void)
 *  {
 *      SIMPLELOG_DEFINE_MODULE(log, "foo.two");
 *
 *      STRACEM_WARN(log0, "Hello Alice");  //< Only message (use module above)
 *      STRACEM_ERROR(log, "Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 * @endcode
 **/
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// DEFINE MODULES: SPECIFIC-MODULE (logger)
// ----------------------------------------------------------------------------
// ALREADY-DEFINED: Inherited from LogMacros.hpp
// #define SIMPLELOG_DEFINE_MODULE(var_name, name)            SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
// #define SIMPLELOG_DEFINE_STATIC_MODULE(var_name, name)     SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(var_name, name)
// #define SIMPLELOG_DEFINE_DEFAULT_MODULE(name)              SIMPLELOG_BACKEND_DEFINE_MODULE(simplelog_defaultModule,
// name) #define SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE(name)
// SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(simplelog_defaultModule, name)

#ifndef SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_NULL_STATEMENT (void)0
#endif

// ----------------------------------------------------------------------------
// SIMPLELOG TRACE MACROS: Enabled in DEBUG mode
// ----------------------------------------------------------------------------
#ifdef DEBUG
// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  SIMPLELOG_TRACE_xxx(message)        -- Message as string w/o placeholders.
//  SIMPLELOG_TRACE_xxx(format, ...)    -- Message w/ placeholders; format describes message schema.
#    define SIMPLELOG_TRACE_FATAL(...)                                                                                    \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#    define SIMPLELOG_TRACE_CRITICAL(...)                                                                                 \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#    define SIMPLELOG_TRACE_ERROR(...)                                                                                    \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#    define SIMPLELOG_TRACE_WARN(...)                                                                                     \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#    define SIMPLELOG_TRACE_INFO(...)                                                                                     \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#    define SIMPLELOG_TRACE_DEBUG(...)                                                                                    \
        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// MACRO-SIGNATURE:
//  SIMPLELOG_TRACE_xxx_IF(condition, message)        -- Message as string w/o placeholders.
//  SIMPLELOG_TRACE_xxx_IF(condition, format, ...)    -- Message w/ placeholders; format describes message schema.
#    define SIMPLELOG_TRACE_FATAL_IF(condition, ...)                                                                      \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#    define SIMPLELOG_TRACE_CRITICAL_IF(condition, ...)                                                                   \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#    define SIMPLELOG_TRACE_ERROR_IF(condition, ...)                                                                      \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#    define SIMPLELOG_TRACE_WARN_IF(condition, ...)                                                                       \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#    define SIMPLELOG_TRACE_INFO_IF(condition, ...)                                                                       \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#    define SIMPLELOG_TRACE_DEBUG_IF(condition, ...)                                                                      \
        SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// -- USE: SPECIFIC-MODULE (logger)
#    define SIMPLELOGM_TRACE_FATAL(logger, ...) SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_CRITICAL(logger, ...)                                                                        \
        SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_ERROR(logger, ...) SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_WARN(logger, ...)  SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_INFO(logger, ...)  SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_DEBUG(logger, ...) SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

#    define SIMPLELOGM_TRACE_FATAL_IF(condition, logger, ...)                                                             \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_CRITICAL_IF(condition, logger, ...)                                                          \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_ERROR_IF(condition, logger, ...)                                                             \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_WARN_IF(condition, logger, ...)                                                              \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_INFO_IF(condition, logger, ...)                                                              \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#    define SIMPLELOGM_TRACE_DEBUG_IF(condition, logger, ...)                                                             \
        SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

#else
// ----------------------------------------------------------------------------
// SIMPLELOG TRACE MACROS: DISABLED in NON-DEBUG mode
// ----------------------------------------------------------------------------
#    define SIMPLELOG_TRACE_FATAL(...)                  SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_CRITICAL(...)               SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_ERROR(...)                  SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_WARN(...)                   SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_INFO(...)                   SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_DEBUG(...)                  SIMPLELOG_NULL_STATEMENT

// MACRO-SIGNATURE:
//  SIMPLELOG_TRACE_xxx_IF(condition, message)        -- Message as string w/o placeholders.
//  SIMPLELOG_TRACE_xxx_IF(condition, format, ...)    -- Message w/ placeholders; format describes message schema.
#    define SIMPLELOG_TRACE_FATAL_IF(condition, ...)    SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_CRITICAL_IF(condition, ...) SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_ERROR_IF(condition, ...)    SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_WARN_IF(condition, ...)     SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_INFO_IF(condition, ...)     SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOG_TRACE_DEBUG_IF(condition, ...)    SIMPLELOG_NULL_STATEMENT

// -- USE: SPECIFIC-MODULE (logger)
#    define SIMPLELOGM_TRACE_FATAL(logger, ...)         SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_CRITICAL(logger, ...)      SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_ERROR(logger, ...)         SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_WARN(logger, ...)          SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_INFO(logger, ...)          SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_DEBUG(logger, ...)         SIMPLELOG_NULL_STATEMENT

#    define SIMPLELOGM_TRACE_FATAL_IF(condition, logger, ...)    SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_CRITICAL_IF(condition, logger, ...) SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_ERROR_IF(condition, logger, ...)    SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_WARN_IF(condition, logger, ...)     SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_INFO_IF(condition, logger, ...)     SIMPLELOG_NULL_STATEMENT
#    define SIMPLELOGM_TRACE_DEBUG_IF(condition, logger, ...)    SIMPLELOG_NULL_STATEMENT
#endif

// --------------------------------------------------------------------------
// SHORTER TRACE MACROS: STRACE_xxx() = SIMPLELOG_TRACE_xxx(), STRACEM_xxx() = SIMPLELOGM_TRACE_xxx()
// --------------------------------------------------------------------------
#if SIMPLELOG_HAVE_SHORT_MACROS
// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  STRACE_xxx(message)        -- Message as string w/o placeholders.
//  STRACE_xxx(format, ...)    -- Message w/ placeholders; format describes message schema.
#    define STRACE_FATAL(...)    SIMPLELOG_TRACE_FATAL(__VA_ARGS__)
#    define STRACE_CRITICAL(...) SIMPLELOG_TRACE_CRITICAL(__VA_ARGS__)
#    define STRACE_ERROR(...)    SIMPLELOG_TRACE_ERROR(__VA_ARGS__)
#    define STRACE_WARN(...)     SIMPLELOG_TRACE_WARN(__VA_ARGS__)
#    define STRACE_INFO(...)     SIMPLELOG_TRACE_INFO(__VA_ARGS__)
#    define STRACE_DEBUG(...)    SIMPLELOG_TRACE_DEBUG(__VA_ARGS__)

// MACRO-SIGNATURE:
//  STRACE_xxx_IF(condition, message)        -- Message as string w/o placeholders.
//  STRACE_xxx_IF(condition, format, ...)    -- Message w/ placeholders; format describes message schema.
#    define STRACE_FATAL_IF(condition, ...)    SIMPLELOG_TRACE_FATAL_IF(condition, __VA_ARGS__)
#    define STRACE_CRITICAL_IF(condition, ...) SIMPLELOG_TRACE_CRITICAL_IF(condition, __VA_ARGS__)
#    define STRACE_ERROR_IF(condition, ...)    SIMPLELOG_TRACE_ERROR_IF(condition, __VA_ARGS__)
#    define STRACE_WARN_IF(condition, ...)     SIMPLELOG_TRACE_WARN_IF(condition, __VA_ARGS__)
#    define STRACE_INFO_IF(condition, ...)     SIMPLELOG_TRACE_INFO_IF(condition, __VA_ARGS__)
#    define STRACE_DEBUG_IF(condition, ...)    SIMPLELOG_TRACE_DEBUG_IF(condition, __VA_ARGS__)

// -- USE: SPECIFIC-MODULE (logger)
// MACRO-SIGNATURE:
//  STRACEM_xxx(logger, message)        -- Message as string w/o placeholders.
//  STRACEM_xxx(logger, format, ...)    -- Message w/ placeholders; format describes message schema.
#    define STRACEM_FATAL(logger, ...)    SIMPLELOGM_TRACE_FATAL(logger, __VA_ARGS__)
#    define STRACEM_CRITICAL(logger, ...) SIMPLELOGM_TRACE_CRITICAL(logger, __VA_ARGS__)
#    define STRACEM_ERROR(logger, ...)    SIMPLELOGM_TRACE_ERROR(logger, __VA_ARGS__)
#    define STRACEM_WARN(logger, ...)     SIMPLELOGM_TRACE_WARN(logger, __VA_ARGS__)
#    define STRACEM_INFO(logger, ...)     SIMPLELOGM_TRACE_INFO(logger, __VA_ARGS__)
#    define STRACEM_DEBUG(logger, ...)    SIMPLELOGM_TRACE_DEBUG(logger, __VA_ARGS__)

// MACRO-SIGNATURE:
//  STRACEM_xxx_IF(condition, logger, message)        -- Message as string w/o placeholders.
//  STRACEM_xxx_IF(condition, logger, format, ...)    -- Message w/ placeholders; format describes message schema.
#    define STRACEM_FATAL_IF(condition, logger, ...)    SIMPLELOGM_TRACE_FATAL_IF(condition, logger, __VA_ARGS__)
#    define STRACEM_CRITICAL_IF(condition, logger, ...) SIMPLELOGM_TRACE_CRITICAL_IF(condition, logger, __VA_ARGS__)
#    define STRACEM_ERROR_IF(condition, logger, ...)    SIMPLELOGM_TRACE_ERROR_IF(condition, logger, __VA_ARGS__)
#    define STRACEM_WARN_IF(condition, logger, ...)     SIMPLELOGM_TRACE_WARN_IF(condition, logger, __VA_ARGS__)
#    define STRACEM_INFO_IF(condition, logger, ...)     SIMPLELOGM_TRACE_INFO_IF(condition, logger, __VA_ARGS__)
#    define STRACEM_DEBUG_IF(condition, logger, ...)    SIMPLELOGM_TRACE_DEBUG_IF(condition, logger, __VA_ARGS__)
#endif

// -- AFTER-HEADER: CONVENIENCE-INCLUDE
// #if SIMPLELOG_HAVE_MACROS0
// #include "simplelog/detail/LogMacros0.hpp"
// #endif

// -- ENDOF-HEADER-FILE
