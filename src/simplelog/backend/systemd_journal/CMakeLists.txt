# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/spdlog
# ===========================================================================

# ---------------------------------------------------------------------------
# DEPENDENCIES
# ---------------------------------------------------------------------------
# if(NOT TARGET Systemd::systemd)
#     find_package(Systemd)
# endif()
# if(NOT Systemd_FOUND AND NOT TARGET Systemd::systemd)
#     message(
#         STATUS
#             "DISABLE LIBRARY: ${PROJECT_NAMESPACE}::simplelog_systemd_journal"
#     )
#     return()
# endif()
#
# if(NOT TARGET fmt::fmt)
#     find_package(fmt ${FMT_MIN_VERSION} REQUIRED)
# endif()

# ---------------------------------------------------------------------------
# BACKEND-SPECIFIC LIBRARY: simplelog_systemd_journal
# ---------------------------------------------------------------------------
add_library(simplelog_systemd_journal INTERFACE)
target_link_libraries(
    simplelog_systemd_journal INTERFACE ${PROJECT_NAMESPACE}::simplelog
                                        fmt::fmt Systemd::systemd
)
target_compile_definitions(
    simplelog_systemd_journal INTERFACE SIMPLELOG_USE_BACKEND_SYSTEMD_JOURNAL=1
)
target_compile_features(
    simplelog_systemd_journal INTERFACE cxx_auto_type cxx_lambdas
                                        cxx_variadic_macros
)

# install the target and create export-set
if(ON)
    add_library(${PROJECT_NAMESPACE}::simplelog_systemd_journal ALIAS simplelog_systemd_journal)
    install(
        TARGETS simplelog_systemd_journal
        EXPORT ${PROJECT_NAMESPACE}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES
        DESTINATION include
    )
else()
    packageProject(
        NAME simplelog_systemd_journal
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAMESPACE}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${SIMPLELOG_INCLUDE_DIR}
        INCLUDE_DESTINATION include
        COMPATIBILITY SameMajorVersion
        DISABLE_VERSION_SUFFIX YES
        DEPENDENCIES "fmt ${FMT_MIN_VERSION}; Systemd"
    )
endif()
