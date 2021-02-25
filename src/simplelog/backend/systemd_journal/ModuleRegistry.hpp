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
#include "simplelog/backend/common/ModuleRegistry.hpp"
#include "simplelog/backend/systemd_journal/Module.hpp"

#include <memory>

// --------------------------------------------------------------------------
// LOGGING BACKEND ADAPTER HELPERS
// --------------------------------------------------------------------------
namespace simplelog {
namespace backend_systemd_journal {

using ModulePtr = std::shared_ptr<simplelog::backend_systemd_journal::Module>;
using ModuleRegistry = simplelog::backend_common::ModuleRegistry<Module>;

// -- FORWARD-DECLARATION:
// ModuleRegistry& getModuleRegistry();
ModuleRegistry &getModuleRegistry()
{
    static ModuleRegistry theRegistry;
    return theRegistry;
}

inline ModulePtr useOrCreateModule(const std::string &name)
{
    return getModuleRegistry().useOrCreateModule(name);
}

} // namespace backend_systemd_journal
} // namespace simplelog
