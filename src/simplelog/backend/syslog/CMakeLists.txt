# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/syslog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
if(NOT TARGET Syslog::syslog)
    find_package(Syslog)
endif()
if(NOT Syslog_FOUND)
    # -- BAIL-OUT-HERE: syslog is not AVAILABLE.
    message(STATUS "DISABLE LIBRARY: ${PROJECT_NAMESPACE}::simplelog_syslog")
    return()
endif()

if(NOT TARGET fmt::fmt)
    find_package(fmt 5.3.0 REQUIRED)
endif()


# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_syslog (HEADER-ONLY, but depends on OTHER_LIBS)
# ---------------------------------------------------------------------------
# USED-FOR: Use simplelog library with configured simplelog.backend.syslog.
message(STATUS "USE LIBRARY: ${PROJECT_NAMESPACE}::simplelog_syslog")

# add_library(simplelog_syslog INTERFACE)
# add_library(${PROJECT_NAMESPACE}::simplelog_syslog ALIAS simplelog_syslog)
# target_link_libraries(simplelog_syslog INTERFACE simplelog fmt::fmt Syslog::syslog)
# target_compile_definitions(simplelog_syslog INTERFACE
#     SIMPLELOG_USE_BACKEND_SYSLOG=1
# )
# set_target_properties(simplelog_syslog
#     PROPERTIES INTERFACE_COMPILE_DEFINITIONS "SIMPLELOG_USE_BACKEND_SYSLOG=1"
# )

add_library(simplelog_syslog STATIC
    ModuleRegistry.cpp
    # -- HEADERS:
    LogBackendMacros.hpp
    Module.hpp
    ModuleRegistry.hpp
)
add_library(${PROJECT_NAMESPACE}::simplelog_syslog ALIAS simplelog_syslog)
target_link_libraries(simplelog_syslog PUBLIC simplelog fmt::fmt Syslog::syslog)
target_compile_definitions(simplelog_syslog PUBLIC
    SIMPLELOG_USE_BACKEND_SYSLOG=1
)
target_compile_features(simplelog_syslog PUBLIC
    cxx_auto_type
    cxx_lambdas
    cxx_variadic_macros
)
