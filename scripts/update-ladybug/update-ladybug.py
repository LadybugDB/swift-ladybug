"""Update the vendored Ladybug C++ submodule to a released version.

Usage:
    python3 update-ladybug.py [--version <tag|latest>] [--repo <url>]

- Resolves `latest` to the newest `vX.Y.Z` tag in LadybugDB/ladybug.
- Checks out that tag in the Sources/LadybugCpp submodule (plus the
  nested `dataset`/`extension` submodules the source collection needs).
- Regenerates Package.swift via collect-ladybug-src.py.
- Bumps the default LBUG_VERSION in scripts/download-liblbug.sh.
- Validates the result with `swift package dump-package`.

Changes are left uncommitted so the caller (CI or a developer) can
review them and commit/PR as appropriate. Exits non-zero on any
failure. Re-running with the current version is a no-op.
"""

import argparse
import logging
import os
import re
import subprocess
import sys

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
)
logger = logging.getLogger(__name__)

REPO_URL = "https://github.com/LadybugDB/ladybug.git"
ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
SUBMODULE_PATH = "Sources/LadybugCpp"
SUBMODULE_DIR = os.path.join(ROOT_DIR, SUBMODULE_PATH)
# Nested submodules of ladybug required by collect-ladybug-src.py.
NESTED_SUBMODULES = ["dataset", "extension"]
COLLECT_SCRIPT_DIR = os.path.join(ROOT_DIR, "scripts", "collect-ladybug-src")
COLLECT_SCRIPT = os.path.join(COLLECT_SCRIPT_DIR, "collect-ladybug-src.py")
DOWNLOAD_SCRIPT = os.path.join(ROOT_DIR, "scripts", "download-liblbug.sh")
VERSION_PATTERN = re.compile(r"^v?\d+\.\d+\.\d+$")


def run(cmd, **kwargs):
    logger.info("+ %s", " ".join(cmd))
    subprocess.run(cmd, check=True, **kwargs)


def resolve_latest_tag(repo_url):
    out = subprocess.run(
        ["git", "ls-remote", "--tags", "--sort=-v:refname", repo_url, "v*"],
        check=True,
        capture_output=True,
        text=True,
    )
    for line in out.stdout.splitlines():
        ref = line.split("\t", 1)[1]
        tag = ref.removeprefix("refs/tags/").removesuffix("^{}")
        if VERSION_PATTERN.match(tag):
            return tag
    raise RuntimeError(f"No vX.Y.Z tag found in {repo_url}")


def normalize_version(version, repo_url):
    version = version.strip()
    if not version or version == "latest":
        tag = resolve_latest_tag(repo_url)
        logger.info("Resolved latest Ladybug version: %s", tag)
        return tag
    if version.startswith("refs/tags/"):
        version = version.removeprefix("refs/tags/")
    tag = version if version.startswith("v") else f"v{version}"
    if not VERSION_PATTERN.match(tag):
        raise ValueError(
            f"Invalid version {version!r}: expected 'latest' or a tag like 'v0.21.2'"
        )
    return tag


def current_submodule_tag():
    out = subprocess.run(
        ["git", "describe", "--tags", "--exact-match", "HEAD"],
        cwd=SUBMODULE_DIR,
        capture_output=True,
        text=True,
    )
    return out.stdout.strip() if out.returncode == 0 else None


def update_download_script_default(tag):
    bare = tag.removeprefix("v")
    with open(DOWNLOAD_SCRIPT) as f:
        content = f.read()
    new_content, count = re.subn(
        r'(VERSION_OVERRIDE="\$\{LBUG_VERSION:-)[^}]+(\}")',
        rf"\g<1>{bare}\g<2>",
        content,
    )
    if count != 1:
        raise RuntimeError(
            f"Expected exactly 1 VERSION_OVERRIDE default in {DOWNLOAD_SCRIPT}, found {count}"
        )
    if new_content != content:
        with open(DOWNLOAD_SCRIPT, "w") as f:
            f.write(new_content)
        logger.info("Bumped default prebuilt liblbug version to %s", bare)
    else:
        logger.info("Prebuilt liblbug default already at %s", bare)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--version",
        default=os.getenv("LADYBUG_VERSION", "latest"),
        help="Ladybug tag (e.g. v0.21.2) or 'latest' (default)",
    )
    parser.add_argument("--repo", default=REPO_URL)
    args = parser.parse_args()

    tag = normalize_version(args.version, args.repo)

    run(["git", "submodule", "update", "--init", SUBMODULE_PATH], cwd=ROOT_DIR)
    run(["git", "fetch", "--tags", "origin"], cwd=SUBMODULE_DIR)
    if current_submodule_tag() == tag:
        logger.info("Submodule already at %s", tag)
    else:
        run(["git", "checkout", tag], cwd=SUBMODULE_DIR)
    run(
        ["git", "submodule", "update", "--init", *NESTED_SUBMODULES],
        cwd=SUBMODULE_DIR,
    )

    run([sys.executable, COLLECT_SCRIPT], cwd=COLLECT_SCRIPT_DIR)
    update_download_script_default(tag)

    run(["swift", "package", "dump-package"], cwd=ROOT_DIR,
        stdout=subprocess.DEVNULL)

    status = subprocess.run(
        ["git", "status", "--short"], cwd=ROOT_DIR, check=True,
        capture_output=True, text=True,
    ).stdout.strip()
    logger.info("Update to %s completed successfully.", tag)
    if status:
        logger.info("Changed files:\n%s", status)
    else:
        logger.info("Working tree clean: already up to date.")


if __name__ == "__main__":
    main()
