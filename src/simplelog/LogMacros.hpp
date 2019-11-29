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
// -- DEFINE: SPECIFIC-MODULE (logger)
#define SIMPLELOG_DEFINE_MODULE(var_name, name)            SIMPLELOG_BACKEND_DEFINE_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_STATIC_MODULE(var_name, name)     SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(var_name, name)
#define SIMPLELOG_DEFINE_DEFAULT_MODULE(name)              SIMPLELOG_BACKEND_DEFINE_MODULE(simplelog_defaultLogger, name)
#define SIMPLELOG_DEFINE_STATIC_DEFAULT_MODULE(name)       SIMPLELOG_BACKEND_DEFINE_STATIC_MODULE(simplelog_defaultLogger, name)

// -- USE: DEFAULT-MODULE (logger)
#define SIMPLELOG_FATAL(format, ...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define SIMPLELOG_CRITICAL(format, ...)     SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define SIMPLELOG_ERROR(format, ...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define SIMPLELOG_WARN(format, ...)         SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define SIMPLELOG_INFO(format, ...)         SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define SIMPLELOG_DEBUG(format, ...)        SIMPLELOG_BACKEND_LOG(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

#define SIMPLELOG_FATAL0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0(message)   SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0(message)       SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0(message)       SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0(message)      SIMPLELOG_BACKEND_LOG0(simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOG_FATAL_IF(condition, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define SIMPLELOG_CRITICAL_IF(condition, format, ...)  SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define SIMPLELOG_ERROR_IF(condition, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define SIMPLELOG_WARN_IF(condition, format, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define SIMPLELOG_INFO_IF(condition, format, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define SIMPLELOG_DEBUG_IF(condition, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

#define SIMPLELOG_FATAL0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0_IF(condition, message) SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0_IF(condition, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0_IF(condition, message)     SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0_IF(condition, message)    SIMPLELOG_BACKEND_LOG0_IF(condition, simplelog_defaultLogger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

// -- USE: SPECIFIC-MODULE (logger)
#define SIMPLELOGM_FATAL(logger, format, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL(logger, format, ...)    SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define SIMPLELOGM_ERROR(logger, format, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define SIMPLELOGM_WARN(logger, format, ...)        SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define SIMPLELOGM_INFO(logger, format, ...)        SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define SIMPLELOGM_DEBUG(logger, format, ...)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

#define SIMPLELOGM_FATAL0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOGM_CRITICAL0(logger, message)   SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOGM_ERROR0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOGM_WARN0(logger, message)       SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOGM_INFO0(logger, message)       SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOGM_DEBUG0(logger, message)      SIMPLELOG_BACKEND_LOG0(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOGM_FATAL_IF(condition, logger, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define SIMPLELOGM_CRITICAL_IF(condition, logger, format, ...)  SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define SIMPLELOGM_ERROR_IF(condition, logger, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define SIMPLELOGM_WARN_IF(condition, logger, format, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define SIMPLELOGM_INFO_IF(condition, logger, format, ...)      SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define SIMPLELOGM_DEBUG_IF(condition, logger, format, ...)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

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
#define SLOG_FATAL(format, ...)       SIMPLELOG_FATAL(format, __VA_ARGS__)
#define SLOG_CRITICAL(format, ...)    SIMPLELOG_CRITICAL(format, __VA_ARGS__)
#define SLOG_ERROR(format, ...)       SIMPLELOG_ERROR(format, __VA_ARGS__)
#define SLOG_WARN(format, ...)        SIMPLELOG_WARN(format, __VA_ARGS__)
#define SLOG_INFO(format, ...)        SIMPLELOG_INFO(format, __VA_ARGS__)
#define SLOG_DEBUG(format, ...)       SIMPLELOG_DEBUG(format, __VA_ARGS__)

#define SLOG_FATAL0(message)          SIMPLELOG_FATAL0(message)
#define SLOG_CRITICAL0(message)       SIMPLELOG_CRITICAL0(message)
#define SLOG_ERROR0(message)          SIMPLELOG_ERROR0(message)
#define SLOG_WARN0(message)           SIMPLELOG_WARN0(message)
#define SLOG_INFO0(message)           SIMPLELOG_INFO0(message)
#define SLOG_DEBUG0(message)          SIMPLELOG_DEBUG0(message)

#define SLOG_FATAL_IF(condition, format, ...)     SIMPLELOG_FATAL_IF(condition, format, __VA_ARGS__)
#define SLOG_CRITICAL_IF(condition, format, ...)  SIMPLELOG_CRITICAL_IF(condition, format, __VA_ARGS__)
#define SLOG_ERROR_IF(condition, format, ...)     SIMPLELOG_ERROR_IF(condition, format, __VA_ARGS__)
#define SLOG_WARN_IF(condition, format, ...)      SIMPLELOG_WARN_IF(condition, format, __VA_ARGS__)
#define SLOG_INFO_IF(condition, format, ...)      SIMPLELOG_INFO_IF(condition, format, __VA_ARGS__)
#define SLOG_DEBUG_IF(condition, format, ...)     SIMPLELOG_DEBUG_IF(condition, format, __VA_ARGS__)

#define SLOG_FATAL0_IF(condition, message)    SIMPLELOG_FATAL0_IF(condition, message)
#define SLOG_CRITICAL0_IF(condition, message) SIMPLELOG_CRITICAL0_IF(condition, message)
#define SLOG_ERROR0_IF(condition, message)    SIMPLELOG_ERROR0_IF(condition, message)
#define SLOG_WARN0_IF(condition, message)     SIMPLELOG_WARN0_IF(condition, message)
#define SLOG_INFO0_IF(condition, message)     SIMPLELOG_INFO0_IF(condition, message)
#define SLOG_DEBUG0_IF(condition, message)    SIMPLELOG_DEBUG0_IF(condition, message)

// -- USE: SPECIFIC-MODULE (logger)
#define SLOGM_FATAL(logger, format, ...)       SIMPLELOGM_FATAL(logger, format, __VA_ARGS__)
#define SLOGM_CRITICAL(logger, format, ...)    SIMPLELOGM_CRITICAL(logger, format, __VA_ARGS__)
#define SLOGM_ERROR(logger, format, ...)       SIMPLELOGM_ERROR(logger, format, __VA_ARGS__)
#define SLOGM_WARN(logger, format, ...)        SIMPLELOGM_WARN(logger, format, __VA_ARGS__)
#define SLOGM_INFO(logger, format, ...)        SIMPLELOGM_INFO(logger, format, __VA_ARGS__)
#define SLOGM_DEBUG(logger, format, ...)       SIMPLELOGM_DEBUG(logger, format, __VA_ARGS__)

#define SLOGM_FATAL0(logger, message)      SIMPLELOGM_FATAL0(logger, message)
#define SLOGM_CRITICAL0(logger, message)   SIMPLELOGM_CRITICAL0(logger, message)
#define SLOGM_ERROR0(logger, message)      SIMPLELOGM_ERROR0(logger, message)
#define SLOGM_WARN0(logger, message)       SIMPLELOGM_WARN0(logger, message)
#define SLOGM_INFO0(logger, message)       SIMPLELOGM_INFO0(logger, message)
#define SLOGM_DEBUG0(logger, message)      SIMPLELOGM_DEBUG0(logger, message)

#define SLOGM_FATAL_IF(condition, logger, format, ...)     SIMPLELOGM_FATAL_IF(condition, logger, format, __VA_ARGS__)
#define SLOGM_CRITICAL_IF(condition, logger, format, ...)  SIMPLELOGM_CRITICAL_IF(condition, logger, format, __VA_ARGS__)
#define SLOGM_ERROR_IF(condition, logger, format, ...)     SIMPLELOGM_ERROR_IF(condition, logger, format, __VA_ARGS__)
#define SLOGM_WARN_IF(condition, logger, format, ...)      SIMPLELOGM_WARN_IF(condition, logger, format, __VA_ARGS__)
#define SLOGM_INFO_IF(condition, logger, format, ...)      SIMPLELOGM_INFO_IF(condition, logger, format, __VA_ARGS__)
#define SLOGM_DEBUG_IF(condition, logger, format, ...)     SIMPLELOGM_DEBUG_IF(condition, logger, format, __VA_ARGS__)

#define SLOGM_FATAL0_IF(condition, logger, message)    SIMPLELOGM_FATAL0_IF(condition, logger, message)
#define SLOGM_CRITICAL0_IF(condition, logger, message) SIMPLELOGM_CRTICAL0_IF(condition, logger, message)
#define SLOGM_ERROR0_IF(condition, logger, message)    SIMPLELOGM_ERROR0_IF(condition, logger, message)
#define SLOGM_WARN0_IF(condition, logger, message)     SIMPLELOGM_WARN0_IF(condition, logger, message)
#define SLOGM_INFO0_IF(condition, logger, message)     SIMPLELOGM_INFO0_IF(condition, logger, message)
#define SLOGM_DEBUG0_IF(condition, logger, message)    SIMPLELOGM_DEBUG0_IF(condition, logger, message)
#endif