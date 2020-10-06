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
#include "simplelog/backend/syslog/Module.hpp"
#include "simplelog/backend/common/ModuleRegistry.hpp"
#include <memory>


// --------------------------------------------------------------------------
// LOGGING BACKEND ADAPTER HELPERS
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_syslog {

using ModulePtr = std::shared_ptr<simplelog::backend_syslog::Module>;
using ModuleRegistry = simplelog::backend_common::ModuleRegistry<Module>;

// -- FORWARD-DECLARATION:
ModuleRegistry& getModuleRegistry();
#if 0
ModuleRegistry& getModuleRegistry()
{
    static ModuleRegistry theRegistry;
    return theRegistry;
}
#endif

inline ModulePtr useOrCreateModule(const std::string& name)
{
    return getModuleRegistry().useOrCreateModule(name);
}

}} //< NAMESPACE-END: simplelog::backend::spdlog
