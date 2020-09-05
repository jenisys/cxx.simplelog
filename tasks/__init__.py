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
INVOKE_MINVERSION = "0.14.0"
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
# TASKS:
# -----------------------------------------------------------------------------
# -- TASK-LIBRARY:
from cmake_build import tasks as cmake_tasks
from . import invoke_cleanup as cleanup
# DISABLED: from . import docs
# DISABLED: from . import test
# DISABLED: from . import release


# -----------------------------------------------------------------------------
# TASK CONFIGURATION:
# -----------------------------------------------------------------------------
namespace = Collection()
namespace.add_collection(Collection.from_module(cmake_tasks, name="cmake"))
namespace.add_collection(Collection.from_module(cleanup, name="cleanup"))
# DISABLED: namespace.add_collection(Collection.from_module(docs))
# DISABLED: namespace.add_collection(Collection.from_module(test))
# DISABLED: namespace.add_collection(Collection.from_module(release))

# -- INJECT: clean configuration into this namespace
namespace.configure(cleanup.namespace.configuration())

# -- EXTENSTION-POINT: CLEANUP TASKS (called by: "clean" task):
cleanup.cleanup_tasks.add_task(cleanup.clean_python)

if sys.platform.startswith("win"):
    # -- OVERRIDE SETTINGS: For platform=win32, ... (Windows)
    from ._compat_shutil import which
    run_settings = dict(echo=True, pty=False, shell=which("cmd"))
    namespace.configure({"run": run_settings})
