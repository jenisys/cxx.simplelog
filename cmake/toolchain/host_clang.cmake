# ===========================================================================
# CMAKE HOST TOOLCHAIN: clang
# ===========================================================================
# CMAKE_SYSTEM_NAME:        any
# CMAKE_SYSTEM_PROCESSOR:   any
# DESCRIPTION:
#   Host installed clang/clang++ compiler toolchain on SEARCH-PATH.
# ===========================================================================

# ---------------------------------------------------------------------------
# CMAKE TOOLCHAIN DEFINITION:
# ---------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER   "clang")

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
# ---------------------------------------------------------------------------
# CMAKE TOOLCHAIN POSTCONDITIONS:
# ---------------------------------------------------------------------------
# NONE
