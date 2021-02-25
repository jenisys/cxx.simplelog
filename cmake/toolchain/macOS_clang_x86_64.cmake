# ===========================================================================
# CMAKE HOST EXTRA TOOLCHAIN: clang
# ===========================================================================
# CMAKE_SYSTEM_NAME:        Darwin (macOS)
# CMAKE_SYSTEM_PROCESSOR:   x86_64
# DESCRIPTION:
#   Extra llvm/clang/clang++ compiler, installed with homebrew.
# ===========================================================================

# ---------------------------------------------------------------------------
# CHECK TOOLCHAIN ASSUMPTIONS:
# ---------------------------------------------------------------------------
if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    message(FATAL_ERROR "CMAKE_HOST_SYSTEM_NAME=${CMAKE_HOST_SYSTEM_NAME} (expected: Darwin)")
endif()
set(__TOOLCHAIN_PREFIX "/usr/local/opt/llvm")
if(NOT EXISTS "${__TOOLCHAIN_PREFIX}/bin/clang++")
    message(FATAL_ERROR "clang++ not installed (${__TOOLCHAIN_PREFIX}/bin/clang++)")
endif()

# ---------------------------------------------------------------------------
# CMAKE TOOLCHAIN DEFINITION:
# ---------------------------------------------------------------------------
# ENABLES: CROSS-COMPILE MODE
# set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

set(CMAKE_CXX_COMPILER "${__TOOLCHAIN_PREFIX}/bin/clang++")
if(EXISTS "${__TOOLCHAIN_PREFIX}/bin/clang")
    set(CMAKE_C_COMPILER "${__TOOLCHAIN_PREFIX}/bin/clang")
endif()
include_directories(BEFORE SYSTEM ${__TOOLCHAIN_PREFIX}/include)
# set(CMAKE_SYSROOT "${__TOOLCHAIN_PREFIX}")
# MAYBE: set(CMAKE_SYSROOT "${__TOOLCHAIN_PREFIX}/Toolchains/LLVM9.0.0.xctoolchain/")

# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
# ---------------------------------------------------------------------------
# CMAKE TOOLCHAIN POSTCONDITIONS:
# ---------------------------------------------------------------------------
# NONE
