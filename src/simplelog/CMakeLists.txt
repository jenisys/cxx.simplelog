# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog
# ===========================================================================

# ---------------------------------------------------------------------------
# SECTION: LIBS
# ---------------------------------------------------------------------------
# -- HEADER-ONLY LIBRARY:
add_library(simplelog INTERFACE)
target_include_directories(
    simplelog INTERFACE "$<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>"
                        "$<INSTALL_INTERFACE:include>"
)
# -- SIMPLELOG DEFAULT-BACKEND:
# if(SIMPLELOG_USE_BACKEND_SPDLOG)
#     target_link_libraries(simplelog INTERFACE spdlog::spdlog)
#     set_target_properties(simplelog
#         PROPERTIES INTERFACE_COMPILE_DEFINITIONS
#             "SIMPLELOG_USE_BACKEND_SPDLOG=1"
#     )
# endif()

# install the target and create export-set
if(ON)
    add_library(${PROJECT_NAMESPACE}::simplelog ALIAS simplelog)
    install(
        TARGETS simplelog
        EXPORT ${PROJECT_NAMESPACE}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES
        DESTINATION include
    )
else()
    packageProject(
        NAME simplelog_simplelog
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAMESPACE}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${SIMPLELOG_INCLUDE_DIR}
        INCLUDE_DESTINATION include
        COMPATIBILITY SameMajorVersion
        DISABLE_VERSION_SUFFIX YES
        DEPENDENCIES "fmt ${FMT_MIN_VERSION}; spdlog ${SPDLOG_MIN_VERSION}"
    )
endif()
