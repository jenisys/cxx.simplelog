# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindSyslog
-----------

This module determines if the syslog library of the system is available.

Imported Targets
^^^^^^^^^^^^^^^^

This module defines the following :prop_tgt:`IMPORTED` target:

``Syslog::syslog``
  The syslog library, if found.

Result Variables
^^^^^^^^^^^^^^^^

The following variables are set:

``Syslog_FOUND``
  If the syslog library was found.

#]=======================================================================]

include(CheckLibraryExists)
set(Syslog_FOUND FALSE)
set(CMAKE_REQUIRED_QUIET_SAVE ${CMAKE_REQUIRED_QUIET})
set(CMAKE_REQUIRED_QUIET ${Syslog_FIND_QUIETLY})

if(CMAKE_C_COMPILER_LOADED)
  include(CheckIncludeFile)
  include(CheckCSourceCompiles)
elseif(CMAKE_CXX_COMPILER_LOADED)
  include(CheckIncludeFileCXX)
  include(CheckCXXSourceCompiles)
else()
  message(FATAL_ERROR "FindSyslog: Only works if either C or CXX language is enabled")
endif()

# simple pthread test code
set(SYSLOG_C_CXX_TEST_SOURCE [====[
#include <syslog.h>

int main(void)
{
    openlog(NULL, LOG_CONS, LOG_USER);
    syslog(LOG_DEBUG, "cmake: Just a simple syslog test");
    closelog();
    return 0;
}
]====])

if(CMAKE_C_COMPILER_LOADED)
    CHECK_INCLUDE_FILE("syslog.h" CMAKE_HAVE_SYSLOG_H)
else()
    CHECK_INCLUDE_FILE_CXX("syslog.h" CMAKE_HAVE_SYSLOG_H)
endif()

if(CMAKE_HAVE_SYSLOG_H)
    set(Syslog_FOUND TRUE)
endif()
message(STATUS "CMAKE_HAVE_SYSLOG_H=${CMAKE_HAVE_SYSLOG_H}")

set(CMAKE_REQUIRED_QUIET ${CMAKE_REQUIRED_QUIET_SAVE})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Syslog DEFAULT_MSG Syslog_FOUND)

if(Syslog_FOUND AND NOT TARGET Syslog::syslog)
    add_library(Syslog::syslog INTERFACE IMPORTED)
    # -- DISABLED: syslog is part of clib.
    # set_property(TARGET Syslog::syslog PROPERTY INTERFACE_LINK_LIBRARIES "-lsyslog")
endif()
