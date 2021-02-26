# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/null
# ===========================================================================

# -- BACKEND-SPECIFIC LIBRARY: simplelog_null (HEADER-ONLY)
# USED-FOR: Use simplelog library with configured simplelog.backend.null.
add_library(simplelog_null INTERFACE)
target_link_libraries(simplelog_null INTERFACE ${PROJECT_NAMESPACE}::simplelog)
target_compile_definitions(simplelog_null INTERFACE SIMPLELOG_USE_BACKEND_NULL=1)

# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_null
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )

packageProject(
    NAME simplelog_null
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAMESPACE}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${SIMPLELOG_INCLUDE_DIR}
    INCLUDE_DESTINATION include
    COMPATIBILITY SameMajorVersion
    DISABLE_VERSION_SUFFIX YES
    # DEPENDENCIES "fmt ${FMT_MIN_VERSION}; spdlog ${SPDLOG_MIN_VERSION}"
)
