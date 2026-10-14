#!/bin/bash
# Download the EE-GCC builds published by `decompme/compilers`
# (release tag "compilers") into tools/cc/<stem>/ (gitignored).
#
# Usage:
#   tools/cc/fetch_eegcc.sh              # all known EE-GCC assets
#   tools/cc/fetch_eegcc.sh ee-gcc2.9-991111a ...
#
# Every archive is unpacked in place; the GCC driver is then found by
# tools/cc/eegcc.sh (see docs/compiler.md). Run inside WSL.
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BASE="https://github.com/decompme/compilers/releases/download/compilers"

# Every EE-GCC asset in the decompme/compilers release (2026-10-14).
ALL=(
  ee-gcc2.9-990721.tar.xz
  ee-gcc2.9-991111.tar.gz
  ee-gcc2.9-991111.tar.xz
  ee-gcc2.9-991111-01.tar.xz
  ee-gcc2.9-991111-01-dtls13010.tar.gz
  ee-gcc2.9-991111a.tar.xz
  ee-gcc2.95.2-273a.tar.gz
  ee-gcc2.95.3-114.tar.gz
  ee-gcc2.95.3-136.tar.gz
  ee-gcc2.96.tar.xz
  ee-gcc3.2-030210-beta2.tar.gz
  ee-gcc3.2-030926.tar.gz
  ee-gcc3.2-040921.tar.xz
)

if [ "$#" -gt 0 ]; then
  ASSETS=("$@")
else
  ASSETS=("${ALL[@]}")
fi

for a in "${ASSETS[@]}"; do
  stem="${a%.tar.*}"
  dest="$HERE/$stem"
  if [ -d "$dest" ] && [ -n "$(ls -A "$dest" 2>/dev/null)" ]; then
    echo "have   $stem"
    continue
  fi
  echo "fetch  $a"
  curl -fsSL "$BASE/$a" -o "$HERE/$a"
  mkdir -p "$dest"
  tar -xf "$HERE/$a" -C "$dest"
  echo "unpack $stem"
done
