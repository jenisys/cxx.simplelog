# -*- coding: UTF-8 -*-
# pylint: disable=wrong-import-position, wrong-import-order
"""
Invoke tasks for building C/C++ projects w/ CMake.

.. code-block:: YAML

    # -- FILE: invoke.yaml
    cmake:
        generator: ninja
        project_dirs:
          - 01_Program_example1
          - 01_Program_example2
          - CTEST_example1

.. seealso::

    * https://cmake.org
"""

from __future__ import absolute_import, print_function

# -----------------------------------------------------------------------------
# IMPORTS:
# -----------------------------------------------------------------------------
import sys
import os.path
from invoke import task, Collection
from invoke.util import cd
from path import Path

# -- TASK-LIBRARY:
from ._tasklet_cleanup import cleanup_tasks, cleanup_dirs


# -----------------------------------------------------------------------------
# CMAKE PROJECT CONFIGURATION:
# -----------------------------------------------------------------------------
BUILD_DIR = "build"

CMAKE_PROJECT_DIRS = [
    # "01_Program_example1",
    # "01_Program_example2",
    # "CTEST_example1",
]

CMAKE_GENERATOR_ALIAS_MAP = {
    "ninja": "Ninja",
    "make": "Unix Makefiles",
}

CMAKE_DEFAULT_GENERATOR = "make"    # EMPTY means Makefiles ('Unix Makefiles')


# -----------------------------------------------------------------------------
# CMAKE UTILITY CLASSES:
# -----------------------------------------------------------------------------
# @wip
class CMakeProject(object):
    def __init__(self, project_dir=None, project_build_dir=None, 
                 cmake_generator=None, build_dir=BUILD_DIR, ctx=None):
        build_dir = build_dir or BUILD_DIR
        project_dir = Path(project_dir)
        if project_dir and not project_build_dir:
            project_build_dir = project_dir/build_dir
        if not project_dir and project_build_dir:
            project_build_dir = Path(project_build_dir)
            project_dir = project_build_dir.dirname()
            build_dir = project_build_dir.basename()

        self.project_dir = project_dir
        self.project_build_dir = project_build_dir
        self.cmake_generator = cmake_generator
        self.cmake_stored_generator = self.load_cmake_generator()
        self.build_dir = build_dir
        self.ctx = ctx

    @property
    def initialized(self):
        return (self.project_build_dir.exists() and self.cmake_stored_generator
                and self.cmake_stored_generator == self.cmake_generator)

    def cleanup(self):
        if self.project_build_dir.isdir():
            self.project_build_dir.rmtree_p()
    
    def init(self, cmake_generator):
        if self.initialized:
            # -- CASE: ALREADY DONE w/ same cmake_generator.
            return
        if self.project_build_dir.isdir():
            self.cleanup()
        self.project_build_dir.makedirs_p()
        # XXX-TODO self.ctx.run("cmake")        
        self.store_cmake_generator(cmake_generator)

    def store_cmake_generator(self, cmake_generator):
        marker_file = self.project_build_dir/".cmake_generator"
        marker_file.write_text(cmake_generator)

    def load_cmake_generator(self, cmake_generator_default=None):
        marker_file = self.project_build_dir/".cmake_generator"
        if marker_file.exists():
            return marker_file.open().read().strip()
        return cmake_generator_default

    @classmethod
    def from_project_dir(cls, ctx, project_dir, cmake_generator=None, build_dir=BUILD_DIR):
        project_dir = Path(project_dir)
        project_build_dir = project_dir/build_dir
        return cls(project_dir, project_build_dir, 
                   cmake_generator=cmake_generator, build_dir=build_dir, ctx=ctx)

    @classmethod
    def from_project_build_dir(cls, ctx, project_build_dir, cmake_generator=None):
        project_build_dir = Path(project_build_dir)
        project_dir = project_build_dir.dirname()
        build_dir = project_build_dir.basename()
        return cls(project_dir, project_build_dir,
                   cmake_generator=cmake_generator, build_dir=build_dir, ctx=ctx)

# -----------------------------------------------------------------------------
# CMAKE UTILS:
# -----------------------------------------------------------------------------
def _cmake_init(ctx, project_dir, generator=None, args=None, build_dir=BUILD_DIR):
    if args is None:
        args = ""
    cmake_generator = _cmake_use_generator(ctx, generator)
    if cmake_generator:
        cmake_generator_name = (CMAKE_GENERATOR_ALIAS_MAP.get(cmake_generator) 
                                or cmake_generator)
        cmake_generator_arg = "-G '%s' " % cmake_generator_name
        args = cmake_generator_arg + args
    
    project_dir = Path(project_dir)
    project_build_dir = project_dir/build_dir
    project_build_dir.makedirs_p()
    
    with cd(project_build_dir):
        print("CMAKE-INIT: %s (using cmake.generator=%s)" % \
              (project_build_dir, cmake_generator))
        ctx.run("cmake %s .." % args)
        # -- FINALLY: If cmake-init worked, store used cmake_generator.
        cmake_generator_marker_file = Path(".cmake_generator")
        cmake_generator_marker_file.write_text(cmake_generator)
        

def _cmake_build(ctx, project_dir, args=None, generator=None, build_dir=BUILD_DIR):
    build_args = ""
    if args:
        build_args = "-- %s" % args
    project_dir = Path(project_dir)
    project_build_dir = project_dir/build_dir
    project_build_dir.makedirs_p()

    with cd(project_build_dir):
        print("CMAKE-BUILD: %s" % project_build_dir)  # XXX os.getcwd())
        ctx.run("cmake --build . %s" % build_args)


def _cmake_test(ctx, project_dir, args=None, generator=None, build_dir=BUILD_DIR):
    build_args = ""
    if args:
        build_args = " ".join(args)
    project_dir = Path(project_dir)
    project_build_dir = project_dir/build_dir
    project_build_dir.makedirs_p()

    with cd(project_build_dir):
        print("CMAKE-TEST: %s" % project_build_dir)  # XXX os.getcwd())
        ctx.run("ctest %s" % build_args)

def _cmake_ensure_init(ctx, project_dir, generator=None, args=None, build_dir=BUILD_DIR):
    project_dir = Path(project_dir)
    project_build_dir = project_dir/build_dir
    cmake_generator_marker_file = project_build_dir/".cmake_generator"
    if cmake_generator_marker_file.exists():
        cmake_generator1 = cmake_generator_marker_file.open().read().strip()
        cmake_generator2 = _cmake_use_generator(ctx, generator)
        if cmake_generator1 == cmake_generator2:
            print("CMAKE-INIT:  %s directory exists already (SKIPPED, generator=%s)." % \
                  (project_build_dir, cmake_generator1))
            return
        else:
            print("CMAKE-REINIT %s: Use generator=%s (was: %s)" % \
                  (project_build_dir, cmake_generator2, cmake_generator1))
            _cmake_cleanup(ctx, project_dir)
        
    # -- OTHERWISE:
    _cmake_init(ctx, project_dir, generator=generator, args=args, build_dir=build_dir)


def _cmake_cleanup(ctx, project_dir, build_dir=BUILD_DIR, dry_run=False):
    project_dir = Path(project_dir)
    project_build_dir = project_dir/build_dir
    if dry_run:
        print("REMOVE_DIR: %s (DRY-RUN SIMULATED)" % project_build_dir)
    elif project_build_dir.isdir():
        print("RMTREE: %s" % project_build_dir)
        project_build_dir.rmtree_p()

def _cmake_select_projects(ctx, project):
    cmake_projects = ctx.cmake.project_dirs or CMAKE_PROJECT_DIRS
    if project and project != "all":
        cmake_projects = [project]
    return cmake_projects

def _cmake_use_generator(ctx, cmake_generator=None):
    default_cmake_generator = ctx.cmake.generator or CMAKE_DEFAULT_GENERATOR
    if cmake_generator is None:
        cmake_generator = default_cmake_generator
    return cmake_generator


def _cmake_project_load_generator(cmake_project, cmake_generator_default=None):
    project_build_dir = Path(cmake_project)/BUILD_DIR
    cmake_generator_marker_file = project_build_dir/".cmake_generator"
    if cmake_generator_marker_file.exists():
        current_cmake_generator = cmake_generator_marker_file.open().read().strip()
        return current_cmake_generator
    # -- OTHERWISE:
    return cmake_generator_default


def _cmake_project_store_generator(cmake_project, cmake_generator):
    project_build_dir = Path(cmake_project)/BUILD_DIR
    cmake_generator_marker_file = project_build_dir/".cmake_generator"
    cmake_generator_marker_file.write_text(cmake_generator)


def _cmake_project_load_generator_and_ensure_init(ctx, cmake_project, generator=None, 
                                           init_args=None):
    cmake_generator = _cmake_project_load_generator(cmake_project)
    if generator and (cmake_generator != generator):
        cmake_generator = generator
    _cmake_ensure_init(ctx, cmake_project, generator=cmake_generator, args=init_args)
    return cmake_generator


# -----------------------------------------------------------------------------
# TASKS:
# -----------------------------------------------------------------------------
@task
def init(ctx, project="all", generator=None, args=None):
    """Initialize all cmake projects."""
    cmake_projects = _cmake_select_projects(ctx, project)
    for cmake_project in cmake_projects:
        _cmake_project_load_generator_and_ensure_init(ctx, cmake_project, 
                                               generator, init_args=args)
        # cmake_generator = _cmake_project_load_generator(cmake_project)
        # if generator and (cmake_generator != generator):
        #     cmake_generator = generator
        # _cmake_ensure_init(ctx, cmake_project,
        #                    generator=cmake_generator, args=args)

@task
def build(ctx, project="all", args=None, generator=None, init_args=None):
    """Build one or all cmake projects."""
    cmake_projects = _cmake_select_projects(ctx, project)
    for cmake_project in cmake_projects:
        # cmake_generator = _cmake_project_load_generator(cmake_project)
        # if generator and (cmake_generator != generator):
        #     cmake_generator = generator
        # _cmake_ensure_init(ctx, cmake_project, generator=cmake_generator, args=init_args)
        _cmake_project_load_generator_and_ensure_init(ctx, cmake_project,
                                                      generator,
                                                      init_args=init_args)
        _cmake_build(ctx, cmake_project, args=args)


@task
def test(ctx, project="all", args=None, generator=None, init_args=None):
    """Test one or all cmake projects."""
    cmake_projects = _cmake_select_projects(ctx, project)
    for cmake_project in cmake_projects:
        _cmake_project_load_generator_and_ensure_init(ctx, cmake_project,
                                                      generator,
                                                      init_args=init_args)
        _cmake_test(ctx, cmake_project, args=args)

# @task
# def build_clean(ctx, project="all", args=None, generator=None, init_args=None):
#     """Build one or all cmake projects."""
#     more_build_args = args or ""
#     cmake_projects = _cmake_select_projects(ctx, project)
#     for cmake_project in cmake_projects:
#         _cmake_ensure_init(ctx, cmake_project,
#                            generator=generator, args=init_args)
#         _cmake_build(ctx, cmake_project, args="clean " + more_build_args)

@task
def clean(ctx, project="all", dry_run=False):
    """Cleanup all cmake projects."""
    cmake_projects = _cmake_select_projects(ctx, project)
    for cmake_project in cmake_projects:
        _cmake_cleanup(ctx, cmake_project, dry_run=dry_run)
    
    # BAD, AVOID: cleanup_dirs("**/build/", dry_run=dry_run)

@task
def reinit(ctx, project="all", generator=None, args=None, dry_run=False):
    """Reinit cmake projects."""
    clean(ctx, project=project, dry_run=dry_run)
    init(ctx, project=project, generator=generator, args=args)


@task
def rebuild(ctx, project="all", args=None, generator=None, init_args=None):
    """Rebuild one or all cmake projects."""
    build(ctx, project=project, args="clean", generator=generator, init_args=init_args)
    build(ctx, project=project, args=args, generator=generator, init_args=init_args)


@task
def all(ctx, project="all", args=None, generator=None, init_args=None, test_args=None):
    """Performs multiple stsps for one (or more) projects:
    
    - cmake.init
    - cmake.build
    - cmake.test (= ctest)
    """
    # init(ctx, project=project, generator=generator, args=init_args)
    build(ctx, project=project, args=args, generator=generator, init_args=init_args)
    test(ctx, project=project, args=test_args, generator=generator, init_args=init_args)
    

@task
def redo_all(ctx, project="all", args=None, generator=None, init_args=None, test_args=None):
    """Performs multiple steps for one (or more) projects:
    
    - cmake.reinit
    - cmake.build
    - cmake.test (= ctest)
    """
    reinit(ctx, project=project, generator=generator, args=init_args)
    build(ctx, project=project, args=args, generator=generator, init_args=init_args)
    test(ctx, project=project, args=test_args, generator=generator, init_args=init_args)
    

# -----------------------------------------------------------------------------
# TASK CONFIGURATION:
# -----------------------------------------------------------------------------
namespace = Collection()
namespace.add_task(all)
namespace.add_task(redo_all)
namespace.add_task(init)
namespace.add_task(build, default=True)
namespace.add_task(test)
namespace.add_task(clean)
namespace.add_task(reinit)
namespace.add_task(rebuild)
namespace.configure({
    "cmake": {
        "project_dirs": [
            CMAKE_PROJECT_DIRS
        ],
        "generator": None,
    },
})

# -- REGISTER CLEANUP TASKS:
cleanup_tasks.add_task(clean, "clean_cmake")
cleanup_tasks.configure(namespace.configuration())
