/**
 * @file example_main.cpp
 * 
 * Simple example how a generic logging framework w/ different logging 
 * subsystems could look like.
 * 
 * @see https://github.com/gabime/spdlog
 * @see https://github.com/fmtlib/fmt
 **/

// -- INCLUDES:
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/stdout_color_sinks.h>


// ==========================================================================
// LOGGING SUBSYSTEM SPECIFIC IMPLEMENTATION
// ==========================================================================
namespace {
// static auto CXXLOG_DEFAULT_SINK = spdlog::stdout_color_mt("console");
// static auto CXXLOG_DEFAULT_SINK = spdlog::sinks::stdout_sink_mt("console");
// XXX static spdlog::sink_ptr CXXLOG_DEFAULT_SINK_PTR = new spdlog::sinks::stdout_sink_mt();
}; // namespace

// #define _CXXLOG_IMPL_DEFINE_CATEGORY(name) ::spdlog::logger(name, CXXLOG_DEFAULT_SINK_PTR))
auto spdlog_useOrCreateLogger(std::string name)
{
    auto logPtr = spdlog::get(name);
    if (!logPtr) {
        logPtr = ::spdlog::stdout_logger_mt(name);
    }
    return std::move(logPtr);
}

#define _CXXLOG_IMPL_DEFINE_CATEGORY(vname, name) auto vname = spdlog_useOrCreateLogger(name)
#define _CXXLOG_IMPL_LOG(logger, level, format, ...) logger->log(level, format, __VA_ARGS__)
#define _CXXLOG_IMPL_LOG0(logger, level, message) logger->log(level, message)

#define _CXXLOG_IMPL_LEVEL_ERROR ::spdlog::level::err
#define _CXXLOG_IMPL_LEVEL_WARN ::spdlog::level::warn
#define _CXXLOG_IMPL_LEVEL_INFO ::spdlog::level::info


// ==========================================================================
// GENERIC LOGGING MACROS
// ==========================================================================
#define CXXLOG_DEFINE_CATEGORY(vname, name)        _CXXLOG_IMPL_DEFINE_CATEGORY(vname, name)
#define CXXLOG_ERROR(logger, format, ...)   _CXXLOG_IMPL_LOG(logger, _CXXLOG_IMPL_LEVEL_ERROR, format, __VA_ARGS__)
#define CXXLOG_WARN(logger, format, ...)    _CXXLOG_IMPL_LOG(logger, _CXXLOG_IMPL_LEVEL_WARN, format, __VA_ARGS__)
#define CXXLOG_INFO(logger, format, ...)    _CXXLOG_IMPL_LOG(logger, _CXXLOG_IMPL_LEVEL_INFO, format, __VA_ARGS__)

#define CXXLOG_ERROR0(logger, message) _CXXLOG_IMPL_LOG0(logger, _CXXLOG_IMPL_LEVEL_ERROR, message)
#define CXXLOG_WARN0(logger, message)  _CXXLOG_IMPL_LOG0(logger, _CXXLOG_IMPL_LEVEL_WARN, message)
#define CXXLOG_INFO0(logger, message)  _CXXLOG_IMPL_LOG0(logger, _CXXLOG_IMPL_LEVEL_INFO, message)

// ==========================================================================
// EXAMPLE
// ==========================================================================
void example_useLogging(void)
{
    // auto log0 = CXXLOG_DEFINE_CATEGORY("foo.bar");
    // auto log  = CXXLOG_DEFINE_CATEGORY("foo.bar");
    CXXLOG_DEFINE_CATEGORY(log0, "foo.bar");
    CXXLOG_DEFINE_CATEGORY(log,  "foo.bar");

    CXXLOG_ERROR0(log, "Hello Alice");
    CXXLOG_WARN(log, "Hello {}", "Bob");
    CXXLOG_INFO(log, "Hello {0} and {1}", "Alice", "Bob");
}

void spdlog_useSinkAsDefaultSink(std::shared_ptr<spdlog::logger> theLog)
{
    auto defaultSink = theLog->sinks().front();
    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> logPtr) {
        if (logPtr != theLog)
        {
            // -- REASSIGN: Log-sink.
            CXXLOG_WARN0(theLog, "Reassign sink to logger");
            logPtr->sinks().clear();
            logPtr->sinks().push_back(defaultSink);
        }
    });
} 

int main(int argc, char **argv)
{
    // -- SETUP LOGGING SUBSYSTEM:
    auto console = spdlog::stdout_color_mt("console");
    // auto console = spdlog::stdout_logger_mt("console");
    spdlog::set_level(spdlog::level::debug);
    spdlog_useSinkAsDefaultSink(console);

    console->warn("main: Logging started.");
    example_useLogging();
    console->warn("main: Ends here.");
    return 0;
}
