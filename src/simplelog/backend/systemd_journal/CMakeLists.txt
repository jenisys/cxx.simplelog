# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/spdlog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
if(NOT TARGET Systemd::systemd)
   find_package(Systemd)
endif()
if(NOT Systemd_FOUND AND NOT TARGET Systemd::systemd)
   message(STATUS "DISABLE LIBRARY: ${PROJECT_NAMESPACE}::simplelog_systemd_journal")
   return()
endif()

if(NOT TARGET fmt::fmt)
    find_package(fmt 5.3.0 REQUIRED)
endif()

# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_systemd_journal
# ---------------------------------------------------------------------------
add_library(simplelog_systemd_journal INTERFACE)
add_library(${PROJECT_NAMESPACE}::simplelog_systemd_journal ALIAS simplelog_systemd_journal)
target_link_libraries(simplelog_systemd_journal INTERFACE simplelog fmt::fmt Systemd::systemd)
target_compile_definitions(simplelog_systemd_journal INTERFACE
    SIMPLELOG_USE_BACKEND_SYSTEMD_JOURNAL=1
)
target_compile_features(simplelog_systemd_journal INTERFACE
    cxx_auto_type
    cxx_lambdas
    cxx_variadic_macros
)

# set_target_properties(simplelog_systemd_journal
#     PROPERTIES INTERFACE_COMPILE_DEFINITIONS
#         "SIMPLELOG_USE_BACKEND_SYSTEMD_JOURNAL=1"
# )
