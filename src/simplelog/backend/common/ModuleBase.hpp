/**
 * @file simplelog/backend/common/Module.hpp
 * Simplelog backend for systemd journald logging service.
 *
 * @see https://systemd.io
 * @see https://linuxconfig.org/introduction-to-the-systemd-journal
 * @see https://www.freedesktop.org/software/systemd
 * @see https://www.freedesktop.org/software/systemd/man/sd_journal_print.html#
 **/

#pragma once

// -- INCLUDES:
#include <string>


// --------------------------------------------------------------------------
// LOGGING MODULE
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_common {

/**
 * @class ModuleBase
 * Provides a named logging module (logger) to log to systemd-journal.
 * Provides an thin adapter around the systemd-journal API.
 **/
class ModuleBase
{
private:
    std::string m_name;
    int m_level;    //!< Log level as threshold to suppress messages.

public:
    explicit ModuleBase(std::string name="")
        : m_name(std::move(name)), m_level(0)
    {}
    explicit ModuleBase(std::string name, int level=0)
        : m_name(std::move(name)), m_level(level)
    {}

    const std::string& getName(void) const { return m_name; }
    int getLevel(void) const { return m_level; }
    void setLevel(int level) { m_level = level; }
};

}} //< NAMESPACE-END: simplelog::backend_common
