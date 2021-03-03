# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindSystemd
-----------

This module determines if the syslog library of the system is available.

Imported Targets
^^^^^^^^^^^^^^^^

This module defines the following :prop_tgt:`IMPORTED` target:

``Systemd::libsystemd``
  The systemd library, if found.

Result Variables
^^^^^^^^^^^^^^^^

The following variables are set:

``Sysdemd_FOUND``
  If the systemd library was found.

SEE ALSO: https://man7.org/linux/man-pages/man3/sd_journal_send.3.html
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
    message(
        FATAL_ERROR
            "FindSystemd: Only works if either C or CXX language is enabled"
    )
endif()

# simple pthread test code
set(SYSTEMD_C_CXX_TEST_SOURCE
    [====[
#include <systemd/sd-journal.h>

int main(void)
{
    sd_journal_print(LOG_INFO, "Hello systemd");
    return 0;
}
]====]
)

if(CMAKE_C_COMPILER_LOADED)
    check_include_file("systemd/sd-journal.h" CMAKE_HAVE_SYSTEMD_SD_JOURNAL_H)
else()
    check_include_file_cxx(
        "systemd/sd-journal.h" CMAKE_HAVE_SYSTEMD_SD_JOURNAL_H
    )
endif()

if(CMAKE_HAVE_SYSTEMD_SD_JOURNAL_H)
    set(Systemd_FOUND TRUE)
endif()
message(
    STATUS "CMAKE_HAVE_SYSTEMD_SD_JOURNAL_H=${CMAKE_HAVE_SYSTEMD_SD_JOURNAL_H}"
)

set(CMAKE_REQUIRED_QUIET ${CMAKE_REQUIRED_QUIET_SAVE})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Systemd DEFAULT_MSG Systemd_FOUND)

if(Systemd_FOUND AND NOT TARGET Systemd::systemd)
    add_library(Systemd::systemd INTERFACE IMPORTED)
    set_property(
        TARGET Systemd::systemd PROPERTY INTERFACE_LINK_LIBRARIES "-lsystemd"
    )
    # -- HINT: Existance of systemd-library is NOT CHECKED.
endif()
