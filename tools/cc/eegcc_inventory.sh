#!/bin/bash
# Inventory every EE-GCC distribution unpacked in tools/cc/ (step 1.1/1.4 of
# Session 4): host platform, driver, cc1 directory, version string, sections of
# a probe object, and the assembler directory. Run inside WSL.
#
#   tools/cc/eegcc_inventory.sh
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$HERE"
printf '%-30s %-9s %-20s %-34s\n' DIST HOST VERSION SECTIONS
for d in ee-gcc*/; do
  d="${d%/}"
  drv=""
  for c in "$d/bin/ee-gcc" "$d/bin/ee-gcc.exe" "$d/bin/ee-gcc.bin"; do
    [ -e "$c" ] && drv="$c" && break
  done
  kind="$(file -b "$drv" 2>/dev/null | cut -d, -f1)"
  host="PE(wine)"
  case "$kind" in
    ELF*|"Bourne-Again shell script"*) host="linux" ;;
  esac
  ver="?"
  case "$host" in
    linux) ver="$(EE_GCC_DIR="$PWD/$d" "$HERE/eegcc.sh" --version 2>&1 | head -1)" ;;
  esac
  printf '%-30s %-9s %-20s\n' "$d" "$host" "$ver"
  printf '    cc1 : %s\n' "$(ls "$d"/lib/gcc-lib/ee/*/cc1* 2>/dev/null | head -1)"
  printf '    as  : %s\n' "$(ls "$d"/ee/bin/as* 2>/dev/null | head -1)"
done
