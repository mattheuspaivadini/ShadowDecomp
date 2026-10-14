#!/bin/bash
# Generic wrapper for an EE-GCC distribution in tools/cc/<name>/.
#
# Which distribution is used is selected by $EE_GCC_DIR:
#   * empty/unset  -> tools/cc/ee-gcc2.96         (the pinned toolchain)
#   * a name       -> tools/cc/<name>
#   * a path       -> used as-is (absolute or relative to tools/cc/)
#
# EE-GCC host drivers are 32-bit i386 binaries that locate `cc1` and `as`
# through PATH (they ignore -B / GCC_EXEC_PREFIX), so we prepend the
# distribution's cc1 directory and its assembler directory. Host requirement:
# libc6:i386. Sources must live on ext4 (cc1 cannot stat /mnt/c - drvfs).
#
# Usage:  tools/cc/eegcc.sh <gcc args...>
#         EE_GCC_DIR=ee-gcc3.2-040921 tools/cc/eegcc.sh --version
set -e

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SEL="${EE_GCC_DIR:-ee-gcc2.96}"
case "$SEL" in
  /*) ROOT="$SEL" ;;
  *)  ROOT="$HERE/$SEL" ;;
esac
if [ ! -d "$ROOT" ]; then
  echo "eegcc.sh: no such distribution: $ROOT" >&2
  echo "installed: $(cd "$HERE" && ls -d ee-gcc*/ 2>/dev/null | tr '\n' ' ')" >&2
  exit 1
fi

# --- cc1 directory: lib/gcc-lib/ee/<version>/ -------------------------------
GCCDIR=""
for d in "$ROOT"/lib/gcc-lib/ee/*/; do
  [ -d "$d" ] && GCCDIR="${d%/}" && break
done
if [ -z "$GCCDIR" ]; then
  echo "eegcc.sh: no cc1 directory under $ROOT/lib/gcc-lib/ee/" >&2
  exit 1
fi

# --- assembler directory: ee/bin -------------------------------------------
ASDIR="$ROOT/ee/bin"
[ -d "$ASDIR" ] || ASDIR="$GCCDIR"

export PATH="$GCCDIR:$ASDIR:$ROOT/bin:$PATH"

# --- driver -----------------------------------------------------------------
DRV="$ROOT/bin/ee-gcc"
[ -x "$DRV" ] || DRV="$ROOT/bin/ee-gcc.bin"
if [ ! -x "$DRV" ]; then
  echo "eegcc.sh: no ee-gcc driver under $ROOT/bin/" >&2
  exit 1
fi
exec "$DRV" "$@"
