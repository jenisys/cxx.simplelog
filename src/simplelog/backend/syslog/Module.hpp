/**
 * @file simplelog/backend/syslog/Module.hpp
 * Simplelog backend for syslog logging service.
 *
 * @see https://linux.die.net/man/3/syslog
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/backend/common/ModuleBase.hpp"
#include <syslog.h>
#include <fmt/format.h>


// --------------------------------------------------------------------------
// LOGGING MODULE
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_syslog {

/**
 * @class Module
 * Provides a named logging module (logger) to log to syslog.
 * Provides an thin adapter around the syslog API.
 *
 * @see https://linux.die.net/man/3/syslog
 * @see https://www.man7.org/linux/man-pages/man3/syslog.3.html
 * @see https://github.com/fmtlib/fmt
 **/
class Module : public simplelog::backend_common::ModuleBase
{
public:
    explicit Module(const std::string& name="")
        : simplelog::backend_common::ModuleBase(name, LOG_WARNING)
    {}
    explicit Module(const std::string& name, int level)
        : simplelog::backend_common::ModuleBase(name, level)
    {}

    inline bool isLevelEnabled(int level) const
    {
        // LOG_EMERG=0, ..., LOG_DEBUG=7
        return (level <= getLevel());
    }

    void setMinLevel(int minLevel)
    {
        if (isLevelEnabled(minLevel)) {
            // -- INCREASE-LEVEL: To MIN-LEVEL (from SAME-LEVEL or LOWER-LEVEL).
            setLevel(minLevel);
        }
    }

    template<typename... Args>
    void log(int level, const Args& ... args)
    {
        if (isLevelEnabled(level)) {
            // -- HINT: Need format string part and args.
            // OTHERWISE: Compiler will complain with -Wformat-security.
            std::string text = fmt::format(args...);
            syslog(level, "%s", text.c_str());
        }
    }
};

}} //< NAMESPACE-END: simplelog::backend_syslog
