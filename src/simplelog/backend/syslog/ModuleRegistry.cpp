/**
 * @file simplelog/backend/syslog/ModuleRegistry.cpp
 * Provides a ModuleRegistry for the syslog backend.
 **/

// -- INCLUDES:
#include "simplelog/backend/syslog/ModuleRegistry.hpp"

namespace simplelog {
namespace backend_syslog {

#if 1
//! Provides access to the ModuleRegistry instance.
ModuleRegistry &getModuleRegistry()
{
    static ModuleRegistry theRegistry;
    return theRegistry;
}
#endif

} // namespace backend_syslog
} // namespace simplelog
