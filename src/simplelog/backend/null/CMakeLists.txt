# ===========================================================================
# CMAKE: cxx.simplelog/src/simplelog/backend/null
# ===========================================================================

# -- BACKEND-SPECIFIC LIBRARY: simplelog_null (HEADER-ONLY)
# USED-FOR: Use simplelog library with configured simplelog.backend.null.
add_library(simplelog_null INTERFACE)
add_library(${PROJECT_NAMESPACE}::simplelog_null ALIAS simplelog_null)
target_link_libraries(simplelog_null INTERFACE simplelog)
set_target_properties(
    simplelog_null PROPERTIES INTERFACE_COMPILE_DEFINITIONS "SIMPLELOG_USE_BACKEND_NULL=1"
)
# -- INHERITED-FROM: simplelog
# target_include_directories(simplelog_null
#     INTERFACE
#         $<BUILD_INTERFACE:${SIMPLELOG_INCLUDE_DIR}>
#         $<INSTALL_INTERFACE:include>
# )
