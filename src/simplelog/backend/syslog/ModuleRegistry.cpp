/**
 * @file simplelog/backend/syslog/ModuleRegistry.cpp
 * Provides a ModuleRegistry for the syslog backend.
 **/

// -- INCLUDES:
#include "simplelog/backend/syslog/ModuleRegistry.hpp"


namespace simplelog { namespace backend_syslog {

//! Provides access to the ModuleRegistry instance.
ModuleRegistry& getModuleRegistry()
{
    static ModuleRegistry theRegistry;
    return theRegistry;
}

}} //< NAMESPACE-END: simplelog::backend::syslog
