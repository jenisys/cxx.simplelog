/**
 * @file simplelog/backend/common/ModuleRegistry.hpp
 * Simplelog common backend functionality of a ModuleReistry.
 **/

#pragma once

// -- INCLUDES:
#include <string>
#include <map>
#include <memory>   //< USE: std::shared_ptr<T>, std::make_shared<T>()
#include <mutex>


// --------------------------------------------------------------------------
// LOGGING MODULE
// --------------------------------------------------------------------------
namespace simplelog { namespace backend_common {

/**
 * @class ModuleRegistry
 * Provides a ModuleRegistry usable from the common cases.
 **/
template<typename Module, typename Level=int>
class ModuleRegistry
{
private:
    using ModulePtr = std::shared_ptr<Module>;
    using ModuleMap = std::map<std::string, ModulePtr>;
    ModuleMap m_moduleMap;
    Level m_defaultLevel;
    mutable std::mutex m_mutex;

protected:
    // -- INTERNAL METHODS: Assume multi-threading locked state.
    inline bool hasModule_(const std::string& name) const
    {
        return m_moduleMap.find(name) != m_moduleMap.end();
    }

    inline ModulePtr addModule_(const std::string& name)
    {
        assert(!hasModule_(name));
        auto newModulePtr = std::make_shared<Module>(name, getDefaultLevel());
        m_moduleMap.emplace(std::make_pair(name, newModulePtr));
        return newModulePtr;
    }

public:
    ModuleRegistry()
        : m_moduleMap(), m_defaultLevel(), m_mutex()
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> lock(m_mutex);
        addModule_("");
    }
    ~ModuleRegistry() = default;
    ModuleRegistry(const ModuleRegistry& other) = delete;
    ModuleRegistry(const ModuleRegistry&& other) = delete;
    ModuleRegistry& operator=(const ModuleRegistry& other) = delete;
    ModuleRegistry& operator=(const ModuleRegistry&& other) = delete;

    inline Level getDefaultLevel() const { return m_defaultLevel; }
    inline void setDefaultLevel(Level value) { m_defaultLevel = value; }

    inline bool empty() const { return m_moduleMap.empty(); }
    inline std::size_t size() const { return m_moduleMap.size(); }

    inline void clear()
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> guard(m_mutex);
        m_moduleMap.clear();
    }

    inline bool hasModule(const std::string& name) const
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> guard(m_mutex);
        return hasModule_(name);
    }

    inline ModulePtr useOrCreateModule(const std::string& name)
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> guard(m_mutex);
        auto moduleIter = m_moduleMap.find(name);
        if (moduleIter != m_moduleMap.end()) {
            return moduleIter->second;
        }
        return addModule_(name);
    }

    template<typename Callable>
    inline void applyToModules(Callable func)
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& moduleItem : m_moduleMap) {
            auto modulePtr = moduleItem.second;
            func(modulePtr);
        }
    }

    template<typename Callable, typename Predicate>
    inline void applyToModuleIf(Predicate&& predicate, Callable&& func)
    {
        // -- CRITICAL-SECTION
        const std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& moduleItem : m_moduleMap) {
            auto& modulePtr = moduleItem.second;
            if (predicate(modulePtr)) {
                func(modulePtr);
            }
        }
    }
};

}} //< NAMESPACE-END: simplelog::backend_common
