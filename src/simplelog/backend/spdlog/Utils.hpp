/**
 * @file simplelog/backend/spdlog/Utils.hpp
 * Some utility functions for spdlog.
 * 
 * @see https://github.com/gabime/spdlog
 **/

#pragma once

// -- INCLUDES:
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
// #include <spdlog/sinks/stdout_sinks.h>
// #include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>


// ==========================================================================
// LOGGING SUBSYSTEM UTILTIES:
// ==========================================================================
void spdlog_useSinkAsDefaultSink(std::shared_ptr<spdlog::logger> theLog)
{
    auto defaultSink = theLog->sinks().front();
    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> logPtr) {
        std::cout << "UseDefaultSink with logger=" << logPtr->name() << std::endl;
        if (logPtr != theLog)
        {
            // -- REASSIGN: Log-sink.
            std::cout << "UseDefaultSink with reassign for: " << logPtr->name() << std::endl;
            logPtr->sinks().clear();
            logPtr->sinks().push_back(defaultSink);
        }
    });
}

void spdlog_setLevelToAll(spdlog::level::level_enum threshold)
{
    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> log) {
        auto levelBefore = log->level();
        log->set_level(threshold);
        std::cout << "SetLevel: " << log->name()
                  << ".level=" << log->level()
                  << " (was: " << levelBefore << ")" << std::endl;
    });
}
