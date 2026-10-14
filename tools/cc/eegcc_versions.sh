#!/bin/bash
# Print `ee-gcc --version` for every Linux (ELF i386) distribution in tools/cc.
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$HERE"
for d in ee-gcc*/; do
  d="${d%/}"
  drv=""
  for c in "$d/bin/ee-gcc" "$d/bin/ee-gcc.exe" "$d/bin/ee-gcc.bin"; do
    [ -e "$c" ] && drv="$c" && break
  done
  kind="$(file -b "$drv" 2>/dev/null | cut -d, -f1)"
  case "$kind" in
    ELF*|"Bourne-Again shell script"*)
      out="$(EE_GCC_DIR="$PWD/$d" "$HERE/eegcc.sh" --version 2>&1 | head -1)"
      printf '%-32s %s\n' "$d" "$out"
      ;;
    *)
      printf '%-32s SKIP (%s)\n' "$d" "$kind"
      ;;
  esac
done
