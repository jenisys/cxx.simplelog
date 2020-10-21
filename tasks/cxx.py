# -*- coding: UTF-8 -*-
"""
Provides C++ related tasks.

Config File Format
-------------------------------------------------------------------------------

XXX

.. code-block:: yaml

    # -- FILE: invoke.yaml
    # USE: cleanup.directories, cleanup.files to override current configuration.
    cleanup:
        # directories: Default directory patterns (can be overwritten).
        # files:       Default file patterns      (can be ovewritten).
        extra_directories:
            - **/tmp/
        extra_files:
            - **/*.log
            - **/*.bak

"""

from __future__ import absolute_import, print_function
import os
import sys
from invoke import task, Collection
from invoke.executor import Executor
from invoke.exceptions import Exit, Failure, UnexpectedExit
from invoke.util import cd
from path import Path

# -----------------------------------------------------------------------------
# CONSTANTS:
# -----------------------------------------------------------------------------
VERSION = "0.1.0"
HERE = Path(__file__).dirname().abspath()
TOPDIR = Path(HERE/"..").abspath()

# -----------------------------------------------------------------------------
# CPPCHECK UTILITIES:
# -----------------------------------------------------------------------------
def ensure_directory_exists(directory):
    directory = Path(directory)
    if not directory.isdir():
        print("CREATE-DIRECTORY: {0}".format(directory))
        directory.makedirs_p()

def ensure_compile_commands_file_exists_or_cmake_build(ctx, compile_commands_file):
    compile_commands_file = Path(compile_commands_file)
    if not compile_commands_file.exists():
        # ctx.run("cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .")
        print("MISSING COMPILE-DATABASE: {0}".format(compile_commands_file))
        print("REBUILD")
        print("USING: PWD={0}".format(Path.getcwd().relpathto(TOPDIR)))
        with cd(TOPDIR):
            ctx.run("cmake-build update -d CMAKE_EXPORT_COMPILE_COMMANDS=ON")
            ctx.run("cmake-build")

# -----------------------------------------------------------------------------
# CPPCHECK TASKS:
# -----------------------------------------------------------------------------
PWD = Path.getcwd()
DEFAULT_BUILD_DIR = Path("build.Darwin_x86_64_debug")
CPPCHECK_REPORT_DIR = Path("build/cppcheck")
CPPCHECKS_PROJECT_OPTIONS = [
    "-i {0}/lib".format(TOPDIR),
    "-i {0}/tests".format(TOPDIR),
]
CPPCHECKS_PROFILE_OPTIONS = CPPCHECKS_PROJECT_OPTIONS + [
    "--enable=all",
    "--relative-paths={0}".format(TOPDIR),
    "--xml",
    # DISABLED: "--addon=cert",
]

@task(help={
    "path": "Path/File to check.",
})
def cppcheck(ctx, path=None, build_dir=None, report_dir=None, format="html"):
    """Apply cppcheck static analyzer to C/C++ CMake project."""
    path = path or "."
    report_dir = Path(report_dir or CPPCHECK_REPORT_DIR)
    report_xml = report_dir/"report.xml"
    cppcheck_options = CPPCHECKS_PROFILE_OPTIONS + [
        # "--check-config",
        "--output-file={0}".format(report_xml),
    ]
    if build_dir is None:
        # MAYBE: Auto-discover build-dirs
        for base_directory in [Path("."), TOPDIR]:
            build_dir = base_directory/DEFAULT_BUILD_DIR
            if build_dir.isdir():
                break

    compile_commands_file = build_dir/"compile_commands.json"
    ensure_compile_commands_file_exists_or_cmake_build(ctx, compile_commands_file)
    ensure_directory_exists(report_dir)
    with cd(TOPDIR):
        path = Path(path).relpathto(TOPDIR)
        ctx.run("cppcheck --project={project} {options} {path}".format(
                project=compile_commands_file,
                options=" ".join(cppcheck_options), path=path))
    print("REPORT WRITTEN TO: {0}".format(report_xml))
    if format == "html":
        cppcheck_html(ctx, report_xml=report_xml, report_dir=report_dir)


@task
def cppcheck_html(ctx, report_xml=None, report_dir=None, title=None, source_dir=None):
    """Generate cppcheck HTML report from previous cppcheck-run (XML report)."""
    report_dir = Path(report_dir or CPPCHECK_REPORT_DIR)
    if not report_dir.isdir():
        print("MISSING-DIRECTORY: report_dir={0}".format(report_dir))

    title = title or Path(".").abspath().basename()
    report_xml = Path(report_xml or report_dir/"report.xml")
    if not report_xml.exists():
        print("MISSING-REPORT: {0}".format(report_xml))

    if not report_dir.isdir():
        print("CREATE-DIRECTORY: {0}".format(report_dir))
        report_dir.makedirs_p()

    source_dir = source_dir or "."
    report_html = report_dir/"index.html"
    with cd(TOPDIR):
        ctx.run("cppcheck-htmlreport --title={title} --file={report_xml} --report-dir={report_dir} --source-dir={source_dir}".format(
            title=title, report_xml=report_xml,
            report_dir=report_dir, source_dir=(source_dir or ".")
        ))
    print("HTML-REPORT WRITTEN TO: {0}".format(report_html))


# -----------------------------------------------------------------------------
# CLANG-TIDY TASKS:
# -----------------------------------------------------------------------------
@task(help={
    "path": "Path/File to check.",
    "build_dir": "Build directory to use (contains: compile_commands.json)",
    "checks": "Checks to apply, like: --checks='cert-*'"
})
def clang_tidy(ctx, path=None, build_dir=None, checks=None, config=None):
    """Apply clang-tidy (via run-clang-tidy.py) static analyzer to C/C++ CMake project."""
    path = path or "."
    build_dir = Path(build_dir or DEFAULT_BUILD_DIR)
    options = []
    if checks:
        options.append("-checks='{0}'".format(checks))
    if config:
        print("config: NOT SUPPORTED YET")

    ctx.run("run-clang-tidy.py {options} -p {build_dir} {source_path}".format(
        build_dir=build_dir, source_path=path, options=" ".join(options)
    ))

CPP_SOURCE_FILE_PATTERNS = ["*.cpp", "*.hpp", "*.h", "*.c", "*.cxx", "*.hxx"]
def select_modified_git_files(ctx, path=None, file_patterns=CPP_SOURCE_FILE_PATTERNS):
    # -- HINTS: Disable pty to avoid ANSI escape codes.
    from fnmatch import fnmatch
    path = path or "."
    result = ctx.run("git diff --name-only {0}".format(path), echo=False, pty=False)
    filenames = []
    for name in result.stdout.strip().splitlines():
        name = name.strip()
        if not name:
            continue

        matched = False
        for pattern in file_patterns:
            if fnmatch(name, pattern): # or name.endswith(".cpp") or name.endswith(".hpp"):
                print("MATCHED: '{0}' (pattern: {1})".format(name, pattern))
                filenames.append(name)
                matched = True
                break
        # if not matched:
        #    print("UNMATCHED: '{0}' (len: {1:d})".format(name, len(name)))

    # for index, name in enumerate(filenames):
    #    print("{i}  {name}".format(i=index, name=name))
    return filenames
    # HINT: Probably ANSI escapted filenames

@task(help={
    "path": "Path scope to check (normally directory).",
    "build_dir": "Build directory to use (contains: compile_commands.json)",
    "checks": "Checks to apply, like: --checks='cert-*'"
})
def clang_tidy_delta(ctx, path=None, build_dir=None, checks=None):
    """Apply clang-tidy to modified source files."""
    filenames = select_modified_git_files(ctx, path=path)
    # filenames = [
    #     "src/simplelog/backend/common/ModuleRegistry.hpp",
    #     "src/simplelog/backend/common/ModuleRegistry.cpp",
    # ]
    parts = " ".join(filenames)
    # MAYBE: clang_tidy(ctx, path=parts, build_dir=build_dir, checks=checks)
    for filename in filenames:
         print("CLANG-TIDY: {0}".format(filename))
    print("{0:d} modified file(s)".format(len(filenames)))

# -----------------------------------------------------------------------------
# TASK CONFIGURATION:
# -----------------------------------------------------------------------------
CPPCHECK_EMPTY_CONFIG = {
    "options": [],
    "report_dir": "build/cppcheck",
}
def make_cppcheck_config(**kwargs):
    config_data = CPPCHECK_EMPTY_CONFIG.copy()
    config_data.update(kwargs)
    return config_data

namespace = Collection(cppcheck, cppcheck_html, clang_tidy, clang_tidy_delta)
namespace.configure({
    "cppcheck": {
        "profiles": {
            "default": make_cppcheck_config()
        },
        "profile": "default",
    },
})
