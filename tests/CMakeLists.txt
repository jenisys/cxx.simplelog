# ===========================================================================
# CMAKE: cxx.simplelog/tests
# ===========================================================================

set(SIMPLELOG_TEST__COMMON_CXX_COMPILE_DEFINITIONS 
    "SIMPLELOG_DIAG=1"
)

# add_subdirectory(simplelog)
# add_subdirectory(simplelog.backend.null)
add_subdirectory(simplelog.backend.spdlog)
