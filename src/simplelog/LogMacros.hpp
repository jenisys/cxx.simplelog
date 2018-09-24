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
// GENERIC LOGGING MACROS
// --------------------------------------------------------------------------
/**
 * @code
 *  #include "simplelog/LogMacros.hpp"
 * 
 *  namespace {
 *      CXXLOG_DEFINE_STATIC_CATEGORY(log0, "foo.one");
 *  };
 * 
 *  void my_func(void)
 *  {
 *      CXXLOG_DEFINE_CATEGORY(log, "foo.two");
 *      
 *      CXXLOG_WARN0(log0, "Hello Alice");  //< Only message
 *      CXXLOG_ERROR(log, "Hello {0} and {1}", "Alice", "Bob"); //< With params
 *  }
 * @endcode
 **/
#define CXXLOG_DEFINE_CATEGORY(vname, name) CXXLOG_BACKEND_DEFINE_CATEGORY(vname, name)
#define CXXLOG_DEFINE_STATIC_CATEGORY(vname, name) CXXLOG_BACKEND_DEFINE_STATIC_CATEGORY(vname, name)

#define CXXLOG_FATAL(logger, format, ...)       CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define CXXLOG_CRITICAL(logger, format, ...)    CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define CXXLOG_ERROR(logger, format, ...)       CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define CXXLOG_WARN(logger, format, ...)        CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define CXXLOG_INFO(logger, format, ...)        CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define CXXLOG_DEBUG(logger, format, ...)       CXXLOG_BACKEND_LOG(logger, CXXLOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

#define CXXLOG_FATAL0(logger, message)      CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_FATAL, message)
#define CXXLOG_CRITICAL0(logger, message)   CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_CRITICAL, message)
#define CXXLOG_ERROR0(logger, message)      CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_ERROR, message)
#define CXXLOG_WARN0(logger, message)       CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_WARN, message)
#define CXXLOG_INFO0(logger, message)       CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_INFO, message)
#define CXXLOG_DEBUG0(logger, message)      CXXLOG_BACKEND_LOG0(logger, CXXLOG_BACKEND_LEVEL_DEBUG, message)

#define CXXLOG_FATAL_IF(condition, logger, format, ...)     CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_FATAL, format, __VA_ARGS__)
#define CXXLOG_CRITICAL_IF(condition, logger, format, ...)  CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_CRITICAL, format, __VA_ARGS__)
#define CXXLOG_ERROR_IF(condition, logger, format, ...)     CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_ERROR, format, __VA_ARGS__)
#define CXXLOG_WARN_IF(condition, logger, format, ...)      CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_WARN, format, __VA_ARGS__)
#define CXXLOG_INFO_IF(condition, logger, format, ...)      CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_INFO, format, __VA_ARGS__)
#define CXXLOG_DEBUG_IF(condition, logger, format, ...)     CXXLOG_BACKEND_LOG_IF(condition, logger, CXXLOG_BACKEND_LEVEL_DEBUG, format, __VA_ARGS__)

#define CXXLOG_FATAL0_IF(condition, logger, message)    CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_FATAL, message)
#define CXXLOG_CRITICAL0_IF(condition, logger, message) CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_CRITICAL, message)
#define CXXLOG_ERROR0_IF(condition, logger, message)    CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_ERROR, message)
#define CXXLOG_WARN0_IF(condition, logger, message)     CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_WARN, message)
#define CXXLOG_INFO0_IF(condition, logger, message)     CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_INFO, message)
#define CXXLOG_DEBUG0_IF(condition, logger, message)    CXXLOG_BACKEND_LOG0_IF(condition, logger, CXXLOG_BACKEND_LEVEL_DEBUG, message)

