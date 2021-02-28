# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/null
# ===========================================================================

# -- BACKEND-SPECIFIC LIBRARY: simplelog_null (HEADER-ONLY)
# USED-FOR: Use simplelog library with configured simplelog.backend.null.
add_library(simplelog_null INTERFACE)
target_link_libraries(simplelog_null INTERFACE ${PROJECT_NAMESPACE}::simplelog)
target_compile_definitions(
    simplelog_null INTERFACE SIMPLELOG_USE_BACKEND_NULL=1
)

# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_null
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )

# install the target and create export-set
if(ON)
    add_library(${PROJECT_NAMESPACE}::simplelog_null ALIAS simplelog_null)
    install(
        TARGETS simplelog_null
        EXPORT ${PROJECT_NAMESPACE}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES
        DESTINATION include
    )
else()
    packageProject(
        NAME simplelog_null
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAMESPACE}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${SIMPLELOG_INCLUDE_DIR}
        INCLUDE_DESTINATION include
        COMPATIBILITY SameMajorVersion
        DISABLE_VERSION_SUFFIX YES
        DEPENDENCIES "simplelog ${PROJECT_VERSION}"
    )
endif()
