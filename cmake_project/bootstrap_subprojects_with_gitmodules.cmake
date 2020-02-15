# ===========================================================================
# CMAKE PART: Bootstrap with git-submodule
# ===========================================================================
# PHASE: Executed during cmake-init (before generation of build-scripts)
# DESCRIPTION:
#   Automatically checkout(s)/clones git-subprojects if they do not exist yet.
#
# REQUIRES-FILE: $HERE/.gitmodules
# ===========================================================================

set(GIT_SUBPROJECTS_UPDATE_DONE_MARKER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlog/CMakeLists.txt")
set(GIT_SUBPROJECT_DIRS
    lib/spdlog
    lib/fmt
    lib/doctest
)

# -----------------------------------------------------------------------------
# TARGETS:
# -----------------------------------------------------------------------------
# HINT: manually trigger update of subprojects in build-script.
add_custom_target(git-submodule-update
    COMMAND git submodule update --init --recursive
    BYPRODUCTS ${GIT_SUBPROJECT_DIRS}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "GIT-SUBMODULE-UPDATE: Update/checkout git.submodules ..."
)

# -----------------------------------------------------------------------------
# ENFORCE-INIT: If lib/spdlog/, ... are missing
# -----------------------------------------------------------------------------
# HINT: Must be executed immediatly before other CMake parts (that depend on it).
if(NOT EXISTS "${GIT_SUBPROJECTS_UPDATE_DONE_MARKER_FILE}")
    message(STATUS "REQUIRES-GIT-SUBMODULE-UPDATE: Checkout subprojects => lib/spdlog, ...")
    execute_process(COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
endif()
