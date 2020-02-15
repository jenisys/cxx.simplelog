# -*- coding: UTF-8 -*-
# pylint: disable=wrong-import-position, wrong-import-order
"""
Invoke build script.
Show all tasks with::

    invoke -l

.. seealso::

    * http://pyinvoke.org
    * https://github.com/pyinvoke/invoke
"""

from __future__ import absolute_import, print_function

# -----------------------------------------------------------------------------
# BOOTSTRAP PATH: Use provided vendor bundle if "invoke" is not installed
# -----------------------------------------------------------------------------
from . import _setup    # pylint: disable=wrong-import-order
INVOKE_MINVERSION = "1.2.0"
_setup.setup_path()
_setup.require_invoke_minversion(INVOKE_MINVERSION)

# -----------------------------------------------------------------------------
# IMPORTS:
# -----------------------------------------------------------------------------
import sys
import os.path
from invoke import task, Collection
from invoke.util import cd
from path import Path
from contextlib import contextmanager

# -----------------------------------------------------------------------------
# TASK-LIBRARY:
# -----------------------------------------------------------------------------
from . import invoke_cleanup as cleanup
from cmake_build import tasks as cmake_tasks


# -----------------------------------------------------------------------------
# TASKS:
# -----------------------------------------------------------------------------
# None.

# -----------------------------------------------------------------------------
# TASK CONFIGURATION:
# -----------------------------------------------------------------------------
namespace = Collection()
namespace.add_collection(Collection.from_module(cmake_tasks, name="cmake"))
namespace.add_collection(Collection.from_module(cleanup, name="cleanup"))

# -- INJECT: clean configuration into this namespace
namespace.configure(cleanup.namespace.configuration())

# -- EXTENSTION-POINT: CLEANUP TASKS (called by: "clean" task):
cleanup.cleanup_tasks.add_task(cleanup.clean_python)

run_settings = dict(echo=True, pty=True, shell="/bin/sh")
if sys.platform.startswith("win"):
    # -- OVERRIDE SETTINGS: For platform=win32, ... (Windows)
    from ._compat_shutil import which
    run_settings = dict(echo=True, pty=False, shell=which("cmd"))
    namespace.configure({"run": run_settings})

namespace.configure({"run": run_settings})
