/**
 * @file simplelog/backend/spdlog/LogBackendMacros.hpp
 *
 * Simple example how a generic logging framework w/ different logging
 * subsystems could look like.
 *
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/detail/DiagMacros.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <cassert>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

// --------------------------------------------------------------------------
// LOGGING BACKEND ADAPTER HELPERS
// --------------------------------------------------------------------------
namespace simplelog {
namespace backend_spdlog {

using Level = spdlog::level::level_enum;
using LoggerPtr = std::shared_ptr<::spdlog::logger>;

/**
 * Logger inherits logging-sinks from other logger (serves as prototype).
 **/
inline void inheritSinksFromOther(LoggerPtr &log, const LoggerPtr &other)
{
    if (!log || !other) {
        return;
    }
    // -- INHERIT SINKS FROM: DEFAULT_LOGGER (used as prototype)
    const auto &defaultSinks = other->sinks();
    auto &currentSinks = log->sinks();
    currentSinks = defaultSinks;
#if 0    
    SIMPLELOG_DIAG_TRACE("inheritSinksFromOther: "
        << (log->name().empty() ? "DEFAULT_LOGGER" : log->name()) 
        << " inherits "<< defaultSinks.size() << " sink(s) from "
        << (other->name().empty() ? "DEFAULT_LOGGER" : other->name()));
#endif
    SIMPLELOG_DIAG_TRACE(
        "inheritSinksFromOther: {0} inherits {2} sink(s) from {1}",
        (log->name().empty() ? std::string("DEFAULT_LOGGER") : log->name()),
        (other->name().empty() ? std::string("DEFAULT_LOGGER") : other->name()),
        defaultSinks.size());
}

/**
 * Creates an unregistered logger without sink.
 * @param name  Name of the logger/category/module (as string).
 * @return Pointer to newly created logger (as shared_ptr).
 **/
inline auto makeLogger(std::string name) -> LoggerPtr
{
    return std::make_shared<::spdlog::logger>(name);
}

/**
 * Create a new logger that is initialized and registered.
 * @note The configuration is inherited from the logging registry.
 * @note The sinks are inherited from the DEFAULT_LOGGER (if any).
 *
 * @param name  Name of logger module/category.
 * @return Logger pointer to newly created logger (shared_ptr)
 * @see spdlog::create<Sink>(name, sinkArgs...)
 **/
inline auto createAndRegisterLogger(const std::string &name,
                                    bool inheritSinks = true) -> LoggerPtr
{
    auto newLogger = makeLogger(name);
    spdlog::initialize_logger(newLogger);
    const auto defaultLogger = spdlog::default_logger();
    if (inheritSinks &&
        defaultLogger) { // DISABLED: && newLogger->sinks().empty()) {
        // -- INHERIT SINKS FROM: DEFAULT_LOGGER (used as prototype)
        inheritSinksFromOther(newLogger, defaultLogger);
    }
    // ALREADY-DONE: spdlog::register_logger(logPtr);
    // POSTCONDITION(spdlog::get(name) == logPtr, "logger is registered");
    assert(spdlog::get(name) == newLogger); // NOLINT
    return newLogger;
}

/**
 * Use existing logger or create a new one with this name.
 *
 * @param name  Logger (module) name.
 * @param level Default level for the logger (if it is newly created).
 * @return Pointer to logger object.
 **/
inline auto useOrCreateLogger(const std::string &name) -> LoggerPtr
{
    auto logPtr = spdlog::get(name);
    if (!logPtr) {
        // -- INHERIT-LOGGER: From REGISTRY and/or DEFAULT_LOGGER.
        const auto prototype = spdlog::default_logger();
        if (prototype) {
            // -- STRATEGY 1: Clone DEFAULT_LOGGER to inherit configuration.
            logPtr = prototype->clone(name);
            spdlog::register_logger(logPtr);
            SIMPLELOG_DIAG_TRACE("useOrCreateLogger: Create log={0}  with "
                                 "config from DEFAULT_LOGGER (cloned)",
                                 (logPtr->name().empty()
                                      ? std::string("DEFAULT_LOGGER")
                                      : logPtr->name()));
        } else {
            // -- STRATEGY 2: REGISTRY and/or DEFAULT_LOGGER
            // Init logger from REGISTRY config and
            // assign sinks from DEFAULT_LOGGER
            logPtr = createAndRegisterLogger(name);
        }
        // POSTCONDITION(spdlog::get(name) == logPtr, "logger is registered");
        assert(spdlog::get(name) == logPtr); // NOLINT
    }
    return logPtr;
}

} // namespace backend_spdlog
} // namespace simplelog
