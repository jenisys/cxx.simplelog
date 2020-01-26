CMake Common Modules
=============================================================================

.. _CMake: https://cmake.org/

`CMake`_ is a meta-build system often used for C/C++ projects.
It generates the build scripts that are used to build the projects.

This directory contains some common `CMake`_ modules that are often used
in `CMake`_-based build projects.


Setup CMake to use this Directory
-----------------------------------------------------------------------------

.. code-block:: cmake

    # -- FILE: CMakeLists.txt
    #
    cmake_minimum_required(VERSION 3.12)

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

    project(my.project VERSION 0.1.2 LANGUAGES CXX)
    ...
