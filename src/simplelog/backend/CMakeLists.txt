# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend
# ===========================================================================

add_subdirectory(null   simplelog_backend_null)
add_subdirectory(spdlog simplelog_backend_spdlog)
if(SIMPLELOG_USE_BACKEND_SYSLOG)
    add_subdirectory(syslog simplelog_backend_syslog)
endif()
add_subdirectory(systemd_journal simplelog_backend_systemd_journal)
