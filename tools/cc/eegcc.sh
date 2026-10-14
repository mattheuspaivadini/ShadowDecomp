#!/bin/bash
# Wrapper for the decompme ee-gcc2.96 distribution (32-bit i386 host driver).
#
# The driver (GCC 2.96) locates `cc1` by searching PATH, and `as` likewise, so
# we prepend the toolchain's own cc1 directory and its EE assembler directory.
# Host requirement: libc6:i386 (the driver is a 32-bit ELF).
#
# Usage:  eegcc.sh <gcc args...>
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GV=2.96-ee-001003-1
GCCDIR="$HERE/ee-gcc2.96/lib/gcc-lib/ee/$GV"
ASDIR="$HERE/ee-gcc2.96/ee/bin"
export PATH="$GCCDIR:$ASDIR:$PATH"
exec "$HERE/ee-gcc2.96/bin/ee-gcc" "$@"
