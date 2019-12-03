/**
 * @file
 * Provide preprocessor macros for users of the logging subsystem.
 *
 * Maps logging macros to logging backend macros to make it easy
 * to replace the logging subsystem/backend with another logging framework.
 **/

#pragma once

#include "simplelog/config.hpp"

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
 *      SLOG_WARN0("Hello Alice");
 *      SLOG_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *
 *      int value = 42;
 *      SLOG_FATAL_IF(value == 42,
 *                    "Show value={0} (if conditition is true)", value);
 *  }
 *
 *  void example_use_ownDefaultLogger(void)
 *  {
 *      // -- DEFINE AND USE DEFAULT LOGGING-MODULE (hint: less params in log-macros)
 *      SIMPLELOG_DEFINE_DEFAULT_MODULE("foo.default");
 *      SLOG_WARN0("Hello Alice");
 *      SLOG_ERROR("Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 * 
 *  void example_use_severalLoggers(void)
 *  {
 *      SIMPLELOG_DEFINE_MODULE(log, "foo.two");
 *
 *      SLOGM_WARN0(log0, "Hello Alice");  //< Only message (use module above)
 *      SLOGM_ERROR(log, "Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 * @endcode
 **/
// ----------------------------------------------------------------------------

// -- DEFINE: SPECIFIC-MODULE (logger)
#define SIMPLELOG_DEFINE_MODULE(var_name, name)            SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_STATIC_MODULE(var_name, name)     SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_DEFAULT_MODULE(name)              SIMPLELOG_BACKEND_DEFINE_MODULE(simplelog_defaultModule, name)
#define SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE(name)       SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(simplelog_defaultModule, name)

// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  SIMPLELOG_xxx(message)        -- Message as string w/o placeholders.
//  SIMPLELOG_xxx(format, ...)    -- Message w/ placeholders; format describes message schema.
#define SIMPLELOG_FATAL(...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOG_CRITICAL(...)     SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOG_ERROR(...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOG_WARN(...)         SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOG_INFO(...)         SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOG_DEBUG(...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// MACRO-SIGNATURE:
//  SIMPLELOG_xxx_IF(condition, message)        -- Message as string w/o placeholders.
//  SIMPLELOG_xxx_IF(condition, format, ...)    -- Message w/ placeholders; format describes message schema.
#define SIMPLELOG_FATAL_IF(condition, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOG_CRITICAL_IF(condition, ...)  SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOG_ERROR_IF(condition, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOG_WARN_IF(condition, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOG_INFO_IF(condition, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOG_DEBUG_IF(condition, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// HINT: SIMPLELOG_xxx0(), SIMPLELOG_xxx0_IF() macros may become unused (and/or deprecated).
#define SIMPLELOG_FATAL0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0(message)   SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0(message)       SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0(message)       SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOG_FATAL0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0_IF(condition, message) SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0_IF(condition, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0_IF(condition, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

// -- USE: SPECIFIC-MODULE (logger)
#define SIMPLELOGM_FATAL(logger, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL(logger, ...)    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOGM_ERROR(logger, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOGM_WARN(logger, ...)        SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOGM_INFO(logger, ...)        SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOGM_DEBUG(logger, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

#define SIMPLELOGM_FATAL_IF(condition, logger, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL_IF(condition, logger, ...)  SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, __VA_ARGS__)
#define SIMPLELOGM_ERROR_IF(condition, logger, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, __VA_ARGS__)
#define SIMPLELOGM_WARN_IF(condition, logger, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, __VA_ARGS__)
#define SIMPLELOGM_INFO_IF(condition, logger, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, __VA_ARGS__)
#define SIMPLELOGM_DEBUG_IF(condition, logger, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, __VA_ARGS__)

// HINT: SIMPLELOGM_xxx0(), SIMPLELOGM_xxx0_IF() macros may become unused (and/or deprecated).
#define SIMPLELOGM_FATAL0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOGM_CRITICAL0(logger, message)   SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOGM_ERROR0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOGM_WARN0(logger, message)       SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOGM_INFO0(logger, message)       SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOGM_DEBUG0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOGM_FATAL0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOGM_CRITICAL0_IF(condition, logger, message) SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOGM_ERROR0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOGM_WARN0_IF(condition, logger, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOGM_INFO0_IF(condition, logger, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOGM_DEBUG0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)


// --------------------------------------------------------------------------
// SHORTER LOGGING MACROS: SLOG_xxx() = SIMPLELOG_xxx(), SLOGM_xxx() = SIMPLELOGM_xxx()
// --------------------------------------------------------------------------
#if SIMPLELOG_HAVE_SHORT_MACROS
// -- USE: DEFAULT-MODULE (logger)
// MACRO-SIGNATURE:
//  SLOG_xxx(message)        -- Message as string w/o placeholders.
//  SLOG_xxx(format, ...)    -- Message w/ placeholders; format describes message schema.
#define SLOG_FATAL(...)       SIMPLELOG_FATAL(__VA_ARGS__)
#define SLOG_CRITICAL(...)    SIMPLELOG_CRITICAL(__VA_ARGS__)
#define SLOG_ERROR(...)       SIMPLELOG_ERROR(__VA_ARGS__)
#define SLOG_WARN(...)        SIMPLELOG_WARN(__VA_ARGS__)
#define SLOG_INFO(...)        SIMPLELOG_INFO(__VA_ARGS__)
#define SLOG_DEBUG(...)       SIMPLELOG_DEBUG(__VA_ARGS__)

// MACRO-SIGNATURE:
//  SLOG_xxx_IF(condition, message)        -- Message as string w/o placeholders.
//  SLOG_xxx_IF(condition, format, ...)    -- Message w/ placeholders; format describes message schema.
#define SLOG_FATAL_IF(condition, ...)     SIMPLELOG_FATAL_IF(condition, __VA_ARGS__)
#define SLOG_CRITICAL_IF(condition, ...)  SIMPLELOG_CRITICAL_IF(condition, __VA_ARGS__)
#define SLOG_ERROR_IF(condition, ...)     SIMPLELOG_ERROR_IF(condition, __VA_ARGS__)
#define SLOG_WARN_IF(condition, ...)      SIMPLELOG_WARN_IF(condition, __VA_ARGS__)
#define SLOG_INFO_IF(condition, ...)      SIMPLELOG_INFO_IF(condition, __VA_ARGS__)
#define SLOG_DEBUG_IF(condition, ...)     SIMPLELOG_DEBUG_IF(condition, __VA_ARGS__)

// HINT: SLOG_xxx0(), SLOG_xxx0_IF() macros may become unused (and/or deprecated).
#define SLOG_FATAL0(message)          SIMPLELOG_FATAL0(message)
#define SLOG_CRITICAL0(message)       SIMPLELOG_CRITICAL0(message)
#define SLOG_ERROR0(message)          SIMPLELOG_ERROR0(message)
#define SLOG_WARN0(message)           SIMPLELOG_WARN0(message)
#define SLOG_INFO0(message)           SIMPLELOG_INFO0(message)
#define SLOG_DEBUG0(message)          SIMPLELOG_DEBUG0(message)

#define SLOG_FATAL0_IF(condition, message)    SIMPLELOG_FATAL0_IF(condition, message)
#define SLOG_CRITICAL0_IF(condition, message) SIMPLELOG_CRITICAL0_IF(condition, message)
#define SLOG_ERROR0_IF(condition, message)    SIMPLELOG_ERROR0_IF(condition, message)
#define SLOG_WARN0_IF(condition, message)     SIMPLELOG_WARN0_IF(condition, message)
#define SLOG_INFO0_IF(condition, message)     SIMPLELOG_INFO0_IF(condition, message)
#define SLOG_DEBUG0_IF(condition, message)    SIMPLELOG_DEBUG0_IF(condition, message)

// -- USE: SPECIFIC-MODULE (logger)
// MACRO-SIGNATURE:
//  SLOGM_xxx(logger, message)        -- Message as string w/o placeholders.
//  SLOG;_xxx(logger, format, ...)    -- Message w/ placeholders; format describes message schema.
#define SLOGM_FATAL(logger, ...)       SIMPLELOGM_FATAL(logger, __VA_ARGS__)
#define SLOGM_CRITICAL(logger, ...)    SIMPLELOGM_CRITICAL(logger, __VA_ARGS__)
#define SLOGM_ERROR(logger, ...)       SIMPLELOGM_ERROR(logger, __VA_ARGS__)
#define SLOGM_WARN(logger, ...)        SIMPLELOGM_WARN(logger, __VA_ARGS__)
#define SLOGM_INFO(logger, ...)        SIMPLELOGM_INFO(logger, __VA_ARGS__)
#define SLOGM_DEBUG(logger, ...)       SIMPLELOGM_DEBUG(logger, __VA_ARGS__)

// MACRO-SIGNATURE:
//  SLOGM_xxx_IF(condition, logger, message)        -- Message as string w/o placeholders.
//  SLOGM_xxx_IF(condition, logger, format, ...)    -- Message w/ placeholders; format describes message schema.
#define SLOGM_FATAL_IF(condition, logger, ...)     SIMPLELOGM_FATAL_IF(condition, logger, __VA_ARGS__)
#define SLOGM_CRITICAL_IF(condition, logger, ...)  SIMPLELOGM_CRITICAL_IF(condition, logger, __VA_ARGS__)
#define SLOGM_ERROR_IF(condition, logger, ...)     SIMPLELOGM_ERROR_IF(condition, logger, __VA_ARGS__)
#define SLOGM_WARN_IF(condition, logger, ...)      SIMPLELOGM_WARN_IF(condition, logger, __VA_ARGS__)
#define SLOGM_INFO_IF(condition, logger, ...)      SIMPLELOGM_INFO_IF(condition, logger, __VA_ARGS__)
#define SLOGM_DEBUG_IF(condition, logger, ...)     SIMPLELOGM_DEBUG_IF(condition, logger, __VA_ARGS__)

// HINT: SLOGM_xxx0(), SLOGM_xxx0_IF() macros may become unused (and/or deprecated).
#define SLOGM_FATAL0(logger, message)      SIMPLELOGM_FATAL0(logger, message)
#define SLOGM_CRITICAL0(logger, message)   SIMPLELOGM_CRITICAL0(logger, message)
#define SLOGM_ERROR0(logger, message)      SIMPLELOGM_ERROR0(logger, message)
#define SLOGM_WARN0(logger, message)       SIMPLELOGM_WARN0(logger, message)
#define SLOGM_INFO0(logger, message)       SIMPLELOGM_INFO0(logger, message)
#define SLOGM_DEBUG0(logger, message)      SIMPLELOGM_DEBUG0(logger, message)

#define SLOGM_FATAL0_IF(condition, logger, message)    SIMPLELOGM_FATAL0_IF(condition, logger, message)
#define SLOGM_CRITICAL0_IF(condition, logger, message) SIMPLELOGM_CRTICAL0_IF(condition, logger, message)
#define SLOGM_ERROR0_IF(condition, logger, message)    SIMPLELOGM_ERROR0_IF(condition, logger, message)
#define SLOGM_WARN0_IF(condition, logger, message)     SIMPLELOGM_WARN0_IF(condition, logger, message)
#define SLOGM_INFO0_IF(condition, logger, message)     SIMPLELOGM_INFO0_IF(condition, logger, message)
#define SLOGM_DEBUG0_IF(condition, logger, message)    SIMPLELOGM_DEBUG0_IF(condition, logger, message)
#endif

// -- ENDOF-HEADER-FILE
