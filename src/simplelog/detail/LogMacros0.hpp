/**
 * @file
 * Provide preprocessor macros for users of the logging subsystem.
 *
 * Maps logging macros to logging backend macros to make it easy
 * to replace the logging subsystem/backend with another logging framework.
 **/

#pragma once

// -- INCLUDES:
// SELECT-BACKEND: And include SIMPLELOG_BACKEND_xxx() macros
#include "simplelog/LogMacros.hpp"


// --------------------------------------------------------------------------
// SIMPLELOG LOGGING MACROS with 0 parameters: SIMPLELOG_xxx0(), SLOG_xxx0()
// --------------------------------------------------------------------------
// HINT: SIMPLELOG_xxx0(), SIMPLELOG_xxx0_IF() macros may become unused (and/or deprecated).
#define SIMPLELOG_FATAL0(message)      SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0(message)   SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0(message)      SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0(message)       SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0(message)       SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0(message)      SIMPLELOG_BACKEND_LOG(simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOG_FATAL0_IF(condition, message)    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOG_CRITICAL0_IF(condition, message) SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOG_ERROR0_IF(condition, message)    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOG_WARN0_IF(condition, message)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOG_INFO0_IF(condition, message)     SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOG_DEBUG0_IF(condition, message)    SIMPLELOG_BACKEND_LOG_IF(condition, simplelog_defaultModule, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

// HINT: SIMPLELOGM_xxx0(), SIMPLELOGM_xxx0_IF() macros may become unused (and/or deprecated).
#define SIMPLELOGM_FATAL0(logger, message)      SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOGM_CRITICAL0(logger, message)   SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOGM_ERROR0(logger, message)      SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOGM_WARN0(logger, message)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOGM_INFO0(logger, message)       SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOGM_DEBUG0(logger, message)      SIMPLELOG_BACKEND_LOG(logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)

#define SIMPLELOGM_FATAL0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_FATAL, message)
#define SIMPLELOGM_CRITICAL0_IF(condition, logger, message) SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_CRITICAL, message)
#define SIMPLELOGM_ERROR0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_ERROR, message)
#define SIMPLELOGM_WARN0_IF(condition, logger, message)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_WARN, message)
#define SIMPLELOGM_INFO0_IF(condition, logger, message)     SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_INFO, message)
#define SIMPLELOGM_DEBUG0_IF(condition, logger, message)    SIMPLELOG_BACKEND_LOG_IF(condition, logger, SIMPLELOG_BACKEND_LEVEL_DEBUG, message)


// --------------------------------------------------------------------------
// SHORTER LOGGING MACROS: SLOG_xxx() = SIMPLELOG_xxx(), SLOGM_xxx() = SIMPLELOGM_xxx()
// --------------------------------------------------------------------------
#if SIMPLELOG_HAVE_SHORT_MACROS
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

// HINT: SLOGM_xxx0(), SLOGM_xxx0_IF() macros may become unused (and/or deprecated).
#define SLOGM_FATAL0(logger, message)      SIMPLELOGM_FATAL0(logger, message)
#define SLOGM_CRITICAL0(logger, message)   SIMPLELOGM_CRITICAL0(logger, message)
#define SLOGM_ERROR0(logger, message)      SIMPLELOGM_ERROR0(logger, message)
#define SLOGM_WARN0(logger, message)       SIMPLELOGM_WARN0(logger, message)
#define SLOGM_INFO0(logger, message)       SIMPLELOGM_INFO0(logger, message)
#define SLOGM_DEBUG0(logger, message)      SIMPLELOGM_DEBUG0(logger, message)

#define SLOGM_FATAL0_IF(condition, logger, message)    SIMPLELOGM_FATAL0_IF(condition, logger, message)
#define SLOGM_CRITICAL0_IF(condition, logger, message) SIMPLELOGM_CRITICAL0_IF(condition, logger, message)
#define SLOGM_ERROR0_IF(condition, logger, message)    SIMPLELOGM_ERROR0_IF(condition, logger, message)
#define SLOGM_WARN0_IF(condition, logger, message)     SIMPLELOGM_WARN0_IF(condition, logger, message)
#define SLOGM_INFO0_IF(condition, logger, message)     SIMPLELOGM_INFO0_IF(condition, logger, message)
#define SLOGM_DEBUG0_IF(condition, logger, message)    SIMPLELOGM_DEBUG0_IF(condition, logger, message)
#endif

// -- ENDOF-HEADER-FILE
