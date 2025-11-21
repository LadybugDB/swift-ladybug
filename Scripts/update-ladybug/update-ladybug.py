import os
import shutil
import sys
from subprocess import Popen
import logging

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
)
logger = logging.getLogger(__name__)


LADYBUG = "ladybug"
REPO_URL = "https://github.com/LadybugDB/ladybug.git"
ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
LADYBUG_ROOT_DIR = os.path.abspath(os.path.join(ROOT_DIR, LADYBUG))
COLLECT_LADYBUG_SRC_SCRIPT_DIR = os.path.abspath(
    os.path.join(ROOT_DIR, "Scripts", "collect-ladybug-src")
)
COLLECT_LADYBUG_SRC_SCRIPT_NAME = "collect-ladybug-src.py"
LADYBUG_BRANCH = os.getenv("LADYBUG_BRANCH", "")
LADYBUG_BRANCH = LADYBUG_BRANCH.strip()
if not LADYBUG_BRANCH:
    logger.info("LADYBUG_BRANCH is not set or invalid, using default branch")
    LADYBUG_BRANCH = "master"
else:
    logger.info(f"LADYBUG_BRANCH is set to {LADYBUG_BRANCH}")

PYTHON_EXECUTABLE = sys.executable

if os.path.exists(LADYBUG_ROOT_DIR):
    logger.info(f"Removing existing {LADYBUG_ROOT_DIR} directory")
    shutil.rmtree(LADYBUG_ROOT_DIR)
logger.info(f"Cloning {LADYBUG} repository from branch {LADYBUG_BRANCH}")
Popen(
    [
        "git",
        "clone",
        "--branch",
        LADYBUG_BRANCH,
        "--depth",
        "1",
        "https://github.com/LadybugDB/ladybug.git",
        LADYBUG_ROOT_DIR,
    ],
).wait()

Popen(
    ["git", "checkout", LADYBUG_BRANCH],
    cwd=LADYBUG_ROOT_DIR,
).wait()

logger.info(f"Running {COLLECT_LADYBUG_SRC_SCRIPT_NAME} script")
Popen(
    [PYTHON_EXECUTABLE, COLLECT_LADYBUG_SRC_SCRIPT_NAME],
    cwd=COLLECT_LADYBUG_SRC_SCRIPT_DIR,
).wait()
logger.info(f"Update process for {LADYBUG} completed successfully.")

logger.info("Cleaning up temporary files...")
shutil.rmtree(LADYBUG_ROOT_DIR, ignore_errors=True)
logger.info("Temporary files cleaned up.")
