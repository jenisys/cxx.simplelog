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
#include <iostream>


// ==========================================================================
// LOGGING SUBSYSTEM SPECIFIC IMPLEMENTATION
// ==========================================================================
namespace {
// static auto CXXLOG_DEFAULT_SINK = spdlog::stdout_color_mt("console");
// static auto CXXLOG_DEFAULT_SINK = spdlog::sinks::stdout_sink_mt("console");
// XXX static spdlog::sink_ptr CXXLOG_DEFAULT_SINK_PTR = new spdlog::sinks::stdout_sink_mt();
}; // namespace

// #define _CXXLOG_IMPL_DEFINE_CATEGORY(name) ::spdlog::logger(name, CXXLOG_DEFAULT_SINK_PTR))
auto spdlog_getDefaultSink(void)
{
    static ::spdlog::sink_ptr theSink(new ::spdlog::sinks::stdout_sink_mt());
    return theSink;
}
auto spdlog_useOrCreateLogger(std::string name)
{
    auto logPtr = spdlog::get(name);
    if (!logPtr) {
        // logPtr = ::spdlog::stdout_logger_mt(name);
        logPtr.reset(new ::spdlog::logger(name, spdlog_getDefaultSink()));
        spdlog::register_logger(logPtr);
    }
    return std::move(logPtr);
}

#define _CXXLOG_NUMARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#define _CXXLOG_IMPL_DEFINE_CATEGORY(vname, name) auto vname = spdlog_useOrCreateLogger(name)
#define _CXXLOG_IMPL_DEFINE_STATIC_CATEGORY(vname, name) static _CXXLOG_IMPL_DEFINE_CATEGORY(vname, name)
#define _CXXLOG_IMPL_LOG(logger, level, format, ...) logger->log(level, format, __VA_ARGS__)
#define _CXXLOG_IMPL_LOG0(logger, level, message)    logger->log(level, message)

#define _CXXLOG_IMPL_LEVEL_ERROR ::spdlog::level::err
#define _CXXLOG_IMPL_LEVEL_WARN ::spdlog::level::warn
#define _CXXLOG_IMPL_LEVEL_INFO ::spdlog::level::info

// -- LOGGING SUBSYSTEM IMPL UTILTIES:
void spdlog_useSinkAsDefaultSink(std::shared_ptr<spdlog::logger> theLog)
{
    auto defaultSink = theLog->sinks().front();
    spdlog::apply_all([&](std::shared_ptr<spdlog::logger> logPtr) {
        std::cout << "UseDefaultSink with logger="<< logPtr->name() << std::endl;
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
        std::cout << "SetLevel: "<< log->name()
        		  <<".level="<< log->level()
				  <<" (was: "<< levelBefore <<")" << std::endl;
    });
}


// ==========================================================================
// GENERIC LOGGING MACROS
// ==========================================================================
#define CXXLOG_DEFINE_CATEGORY(vname, name)        _CXXLOG_IMPL_DEFINE_CATEGORY(vname, name)
#define CXXLOG_DEFINE_STATIC_CATEGORY(vname, name) _CXXLOG_IMPL_DEFINE_STATIC_CATEGORY(vname, name)
#define CXXLOG_ERROR(logger, format, ...) _CXXLOG_IMPL_LOG(logger, _CXXLOG_IMPL_LEVEL_ERROR, format, __VA_ARGS__)
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
    CXXLOG_DEFINE_CATEGORY(log, "foo.bar");
    // spdlog_setLevelToAll(_CXXLOG_IMPL_LEVEL_INFO);

    CXXLOG_ERROR0(log, "Hello Alice");
    CXXLOG_WARN(log, "Hello {}", "Bob");
    CXXLOG_INFO(log, "Hello {0} and {1}", "Alice", "Bob");
}

void example_useTwoLoggersWithSameName(void)
{
    CXXLOG_DEFINE_CATEGORY(log1, "foo.two");
    CXXLOG_DEFINE_CATEGORY(log2, "foo.two");

    CXXLOG_ERROR0(log1, "Logger_1");
    CXXLOG_WARN0(log2,  "Logger_2");
}

// std::shared_ptr<spdlog::logger>
auto getLogger(void)
{
    // static CXXLOG_DEFINE_CATEGORY(theLog, "foo.static");
    CXXLOG_DEFINE_STATIC_CATEGORY(theLog, "foo.static");
    return theLog;
}

void example_useStaticLogger(void)
{
    auto log = getLogger();
    CXXLOG_ERROR0(log, "Hello Alice");
}


CXXLOG_DEFINE_STATIC_CATEGORY(rootLog, "root");

int main(int argc, char **argv)
{
    // -- SETUP LOGGING SUBSYSTEM:
    auto console = spdlog::stdout_color_mt("console");
    // auto console = spdlog::stdout_logger_mt("console");
    spdlog::set_level(spdlog::level::debug);
    spdlog_useSinkAsDefaultSink(console);
    spdlog_setLevelToAll(_CXXLOG_IMPL_LEVEL_INFO);

    console->warn("main: Logging started.");
    rootLog->info("main: Use static logger.root");
    example_useLogging();
    spdlog_setLevelToAll(_CXXLOG_IMPL_LEVEL_WARN);
    example_useTwoLoggersWithSameName();
    example_useStaticLogger();
    console->warn("main: Ends here.");
    return 0;
}
