/**
 * @file simplelog/backend/systemd_journal/Module.hpp
 * Simplelog backend for systemd journald logging service.
 *
 * @see https://systemd.io
 * @see https://linuxconfig.org/introduction-to-the-systemd-journal
 * @see https://www.freedesktop.org/software/systemd
 * @see https://www.freedesktop.org/software/systemd/man/sd_journal_print.html#
 **/

#pragma once

// -- INCLUDES:
#include "simplelog/backend/common/ModuleBase.hpp"
#include <systemd/sd-journal.h>

#include <fmt/format.h>

// --------------------------------------------------------------------------
// LOGGING MODULE
// --------------------------------------------------------------------------
namespace simplelog {
namespace backend_systemd_journal {

/**
 * @class Module
 * Provides a named logging module (logger) to log to systemd-journal.
 * Provides an thin adapter around the systemd-journal API.
 *
 * @see https://man7.org/linux/man-pages/man3/sd_journal_print.3.html
 **/
class Module : public simplelog::backend_common::ModuleBase
{
public:
    explicit Module(const std::string &name = "")
        : simplelog::backend_common::ModuleBase(name, LOG_WARNING)
    {}
    explicit Module(const std::string &name, int level)
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

    template <typename... Args> void log(int level, const Args &...args)
    {
        if (isLevelEnabled(level)) {
            // -- HINT: Need format string part and args.
            // OTHERWISE: Compiler will complain with -Wformat-security.
            std::string text = fmt::format(args...);
            sd_journal_print(level, "%s", text.c_str());
            // MAYBE: sd_journal_printv(level, "%s", text.c_str());
        }
    }
};

} // namespace backend_systemd_journal
} // namespace simplelog
