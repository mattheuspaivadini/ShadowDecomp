#!/bin/bash
# Install the decompme ee-gcc2.96 distribution at the prefix its GCC driver
# expects (/usr/local/sce/ee/gcc), by symlinking the unpacked tarball. Run as
# root in WSL. The toolchain itself lives in tools/cc/ (gitignored).
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PREFIX=/usr/local/sce/ee
mkdir -p "$PREFIX"
ln -sfn "$HERE/ee-gcc2.96" "$PREFIX/gcc"
ls -la "$PREFIX"/
ls "$PREFIX/gcc/"
