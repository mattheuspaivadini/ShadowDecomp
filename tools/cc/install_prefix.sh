#!/bin/bash
# Point the Sony SDK prefix (/usr/local/sce/ee/gcc) at one of the unpacked
# EE-GCC distributions in tools/cc/. The driver normally finds cc1/as through
# PATH (see eegcc.sh) but keeping the prefix correct avoids surprises for any
# code that hard-codes it. Run as root in WSL.
#
#   tools/cc/install_prefix.sh                    # default: ee-gcc2.96
#   tools/cc/install_prefix.sh ee-gcc3.2-040921
set -e
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SEL="${1:-ee-gcc2.96}"
case "$SEL" in
  /*) TARGET="$SEL" ;;
  *)  TARGET="$HERE/$SEL" ;;
esac
if [ ! -d "$TARGET" ]; then
  echo "install_prefix.sh: no such distribution: $TARGET" >&2
  exit 1
fi
PREFIX=/usr/local/sce/ee
mkdir -p "$PREFIX"
ln -sfn "$TARGET" "$PREFIX/gcc"
ls -la "$PREFIX"/
ls "$PREFIX/gcc/"
