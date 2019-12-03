/**
 * @file simplelog/backend/spdlog/SetupUtil.hpp
 * Some utility functions for spdlog.
 * 
 * @see https://github.com/gabime/spdlog
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/detail/DiagMacros.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <vector>


// ==========================================================================
// SIMPLELOG BACKEND SPDLOG: LOGGING SUBSYSTEM UTILTIES
// ==========================================================================
namespace simplelog { namespace backend_spdlog {

    using Level = ::spdlog::level::level_enum;
    using LoggerPtr = std::shared_ptr<::spdlog::logger>;
    using Loggers = std::vector<LoggerPtr>;
    using LoggerFunc = std::function<void(const LoggerPtr)>;
    using Predicate = std::function<bool(LoggerPtr log)>;
    using SinkPtr = ::spdlog::sink_ptr;
    using Sinks = std::vector<SinkPtr>;


//! Lambda predicate function that matches any logger.
// DISABLED: constexpr
const auto matchesEachLogger = [](LoggerPtr) {
    return true; 
};

/**
 * Assigns a new log-level to the logging subsystem and all existing loggers.
 * @note Newly created loggers will inherit this new default log-level.
 **/
inline void setLevel(const Level&  value)
{
    ::spdlog::set_level(value);
}

/**
 * Apply a function-object to any logger that matches the predicate.
 * @param func      Function that operates on the the logger.
 * @param predicate Predicate function to select matching loggers.
 * @note Uses logging-registry synchronized operation mechanism
 ***/
inline void applyToAny(const LoggerFunc& func, const Predicate& predicate)
{
    ::spdlog::apply_all([&](LoggerPtr log) {
        if (predicate(log)) {
            func(log);
        }
    });
}

/**
 * Assigns a new logging sink to any logger that matches the predicate.
 * @note Overrides and removes any pre-existing assigned sinks.
 **/
inline void assignSinkToAny(SinkPtr sink, const Predicate& predicate)
{
    const auto clearAndAssignSink = [&](LoggerPtr log) {
        auto& currentSinks = log->sinks();
        currentSinks.clear();
        currentSinks.push_back(sink);
    };
    applyToAny(clearAndAssignSink, predicate);
}

/**
 * Assigns a new logging sink to all loggers.
 * @note Overrides and removes any pre-existing assigned sinks.
 **/
inline void assignSink(SinkPtr sink)
{
    // const auto matchesEachLogger = [](LoggerPtr) { return true; };
    const auto& defaultLogger = spdlog::default_logger();
    if (defaultLogger == nullptr) {
        // -- HINT: Need DEFAULT_LOGGER 
        // DEFAULT_LOGGER is used to inherit sinks in newly created loggers.
        SIMPLELOG_DIAG_TRACE0("assignSink: Create DEFAULT_LOGGER");
        spdlog::set_default_logger(makeLogger(""));
    }
    assignSinkToAny(sink, matchesEachLogger);
}

/**
 * Assigns a many logging sinks to any logger that matches the predicate.
 * @note Overrides and removes any pre-existing assigned sinks.
 **/
inline void assignSinksToAny(const Sinks& sinks, const Predicate& predicate)
{
    const auto clearAndAssignSinks = [&](LoggerPtr log) {
        auto& currentSinks = log->sinks();
        currentSinks.clear();
        currentSinks = sinks;
    };
    applyToAny(clearAndAssignSinks, predicate);
}

/**
 * Assigns a many logging sinks to all loggers.
 * @note Overrides and removes any pre-existing assigned sinks.
 **/
inline void assignSinks(const Sinks& sinks)
{
    const auto& defaultLogger = spdlog::default_logger();
    if (defaultLogger == nullptr) {
        SIMPLELOG_DIAG_TRACE0("assignSinks: Create DEFAULT_LOGGER");
        spdlog::set_default_logger(makeLogger(""));
    }
    assignSinksToAny(sinks, matchesEachLogger);
}

/**
 * Assign log-level to any loggers where predicate(logger) is true.
 * 
 * @code
 *  #include "simplelog/LogMacros.hpp"
 *  #include "simplelog/backend/spdlog/SetupUtil.hpp"
 *  #include <cassert>
 * 
 *  void example() 
 *  {
 *      const auto LOG_LEVEL1 = SIMPLELOG_BACKEND_LEVEL_INFO;
 *      const auto LOG_LEVEL2 = SIMPLELOG_BACKEND_LEVEL_ERROR;
 *      auto log1 = getLogger("foo.1");
 *      auto log2 = getLogger("foo.2");
 *      log1->set_level(LOG_LEVEL1);
 *      log2->set_level(LOG_LEVEL2);
 * 
 *      const auto DESIRED_LEVEL = SIMPLELOG_BACKEND_LEVEL_WARN;
 *      const auto hasName = [](LoggerPtr log) {
 *          return log->name() == "foo.2";
 *      };
 *      simplelog::backend_spdlog::setLevelToAny(DESIRED_LEVEL, hasName);
 *      assert(log1->level() != DESIRED_LEVEL);
 *      assert(log2->level() == DESIRED_LEVEL);
 *      assert(hasName(log2));
 *  }
 * @endcode
 **/
inline void setLevelToAny(Level level, const Predicate& predicate)
{
    const auto& assignThisLevel = [=](LoggerPtr log) {
        log->set_level(level);
    };
    applyToAny(assignThisLevel, predicate);
}

/**
 * Ensures that all loggers that use at least the new minimal log-level (min_level).
 * @note Changes logger.level only if logger.level < min_level.
 * 
 * @code
 *  #include "simplelog/LogMacros.hpp"
 *  #include "simplelog/backend/spdlog/SetupUtil.hpp"
 *  #include <cassert>
 * 
 *  void example() 
 *  {
 *      auto log1 = useOrCreateLogger("foo.1");
 *      auto log2 = useOrCreateLogger("foo.2");
 *      log1->set_level(SIMPLELOG_BACKEND_LEVEL_INFO);
 *      log2->set_level(SIMPLELOG_BACKEND_LEVEL_ERROR);
 * 
 *      simplelog::backend_spdlog::setMinLevel(SIMPLELOG_BACKEND_LEVEL_WARN);
 *      assert(log1->level() == SIMPLELOG_BACKEND_LEVEL_WARN);
 *      assert(log2->level() == SIMPLELOG_BACKEND_LEVEL_ERROR);
 *  }
 * @endcode
 * @note This operation does not change the registry config.
 *  Therefore, any new logger that is created later and initialized 
 *  w/ the registry will have log.level = registry.level (instead min_level).
 **/
inline void setMinLevel(const Level& minLevel)
{
    const auto hasLoggerLessThanMinLevel = [=](LoggerPtr log) {
        return log && (log->level() < minLevel);
    };
    const auto assignMinLevel = [=](LoggerPtr log) {
        // SIMPLELOG_DIAG_TRACE("setMinLevel: log={0} from {1} to {2}", log->name(), log->level(), minLevel);
        log->set_level(minLevel);
    };
    applyToAny(assignMinLevel, hasLoggerLessThanMinLevel);
    // setLevelToAny(minLevel, hasLoggerLessThanMinLevel);
}

/**
 * Select loggers by name-pattern.
 * @code
 *  using simplelog::backend_spdlog::selectLoggersByName;
 *  for (log : selectLoggersByName("foo.*")) {
 *      log->set_level(SIMPLE)
 *  }
 * @endcode
 * 
 * @param pattern Name pattern to use.
 * @return Selected loggers (as vector).
 **/
#if 0
inline std::vector<LoggerPtr>
selectLoggersByName(const std::string& pattern)
{
    std::vector<LoggerPtr> selected;
    auto matches = [=](auto pattern) {
        if pattern.count("*")
    }
    ::spdlog::apply_all([&](LoggerPtr log) {
        if (matches(log->name()) {
            selected.push_back(log);
        };
    }
    return selected;
}
#endif

/**
 * Selects zero or more loggers by using a predicate.
 * @code
 *   using simplelog::backend_spdlog::selectLoggers;
 *   const auto nameStartsWithFoo = [](const LoggerPtr log) {
 *      return log.name().find("foo") == 0;
 *   }
 *   for (auto log : selectLoggers(nameStartsWithFoo)) {
 *      print(log->name());
 *   }
 * @endcode
 * @param predicate  Predicate function to selec loggers
 * @return Selected, matching loggers.
 * @note Logging registry multi-threading protection mechanism is no longer available
 * @see applyToAny(func, predicate)
 **/ 
inline std::vector<LoggerPtr> selectLoggers(const Predicate& predicate)
{
    std::vector<LoggerPtr> selected;
    ::spdlog::apply_all([&](LoggerPtr log) {
        if (predicate(log)) {
            selected.push_back(log);
        };
    });
    return selected;
}

#define SIMPLELOG_BACKEND_SPDLOG__USE_INCUBATOR_FUNC 1
#if SIMPLELOG_BACKEND_SPDLOG__USE_INCUBATOR_FUNC
inline void useLogSinkAsDefaultSink(LoggerPtr theLog)
{
    auto defaultSink = theLog->sinks().front();
    ::spdlog::apply_all([&](LoggerPtr logPtr) {
        if (logPtr != theLog)
        {
            // -- REASSIGN: Log-sink.
            SIMPLELOG_DIAG_TRACE("UseDefaultSink with reassign for: {0}", logPtr->name());
            logPtr->sinks().clear();
            logPtr->sinks().push_back(defaultSink);
        }
    });
}
#endif
/**
 * Assign new log-level to all loggers that have a lower threshold.
 * 
 * @code
 *  #include "simplelog/LogMacros.hpp"
 *  #include "simplelog/backend/spdlog/SetupUtil.hpp"
 *  #include <cassert>
 * 
 *  void example() 
 *  {
 *      auto log1 = getLogger("foo.1");
 *      auto log2 = getLogger("foo.2");
 *      log1->set_level(SIMPLELOG_BACKEND_LEVEL_INFO);
 *      log2->set_level(SIMPLELOG_BACKEND_LEVEL_ERROR);
 * 
 *      simplelog::backend_spdlog::setLevelToAll(SIMPLELOG_BACKEND_LEVEL_WARN);
 *      assert(log1->level() == SIMPLELOG_BACKEND_LEVEL_WARN);
 *      assert(log2->level() == SIMPLELOG_BACKEND_LEVEL_WARN);
 *  }
 * @endcode
 **/
#if 0
inline void setLevelToAll(Level threshold)
{
    ::spdlog::apply_all([&](LoggerPtr log) {
#if SIMPLELOG_DIAG
        const auto INITIAL_LEVEL = log->level();
#endif
        log->set_level(threshold);
        SIMPLELOG_DIAG_TRACE("SetLevel: {0}.level={1} (was: {2})", 
            (log->name().empty() ? "ROOT" : log->name()),
            log->level(), INITIAL_LEVEL);
    });
}
#endif

}} //< NAMESPACE-END: simplelog::backend_spdlog
