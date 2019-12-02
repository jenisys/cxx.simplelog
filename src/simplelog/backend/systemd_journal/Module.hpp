/**
 * @file simplelog/backend/systemd_journal/Module.hpp
 * Simplelog backend for systemd journald logging service.
 * 
 * @see https://www.freedesktop.org/software/systemd
 * @see https://www.freedesktop.org/software/systemd/man/sd_journal_print.html#
 **/

#pragma once

// -- INCLUDES:
#include <systemd/sd-journal.h>


// --------------------------------------------------------------------------
// LOGGING MODULE
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_systemd_journal {

class Module
{
private:
    std::string m_name;
    int m_level;

public:
    explicit Module(const char* name="")
        : m_name((name != nullptr) ? name : ""), m_level(LOG_ERROR) 
    {}

    const std::string& getName(void) const { return m_name; }
    int getLevel(void) const { return m_level; }
    void setLevel(int level) { m_level = level; }
    bool isLevelEnabled(int level) const
    {
        // LOG_EMERG=0, ..., LOG_DEBUG=7
        return (level <= m_level);
    }
    void log(int level, const char* format, ...)
    {
        if (isLevelEnabled(level)) {
            sd_journal_print(level, format, __VA_ARGS__);
        }
    }
    void log(int level, const char* format, va_list varargs)
    {
        if (isLevelEnabled(level)) {
            sd_journal_printv(level, format, varargs);
        }
    }
};

}} //< NAMESPACE-END: simplelog::backend_systemd_journal
