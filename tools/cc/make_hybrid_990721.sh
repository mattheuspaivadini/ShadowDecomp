#!/bin/bash
# Build tools/cc/ee-gcc2.9-990721-as991111: the 2.9-ee-990721 driver/cc1 with the
# 2.9-ee-991111 assembler. Session 54 hypothesis for the libc MMI string TU (strlen/memcpy/
# memset drafts in src/non_matching/): this pairing reproduces both the 990721 delay-slot
# filling and the 991111 R5900 short-loop nops seen in the image. Run in WSL from the repo root.
set -e
cd "$(dirname "$0")"
out=ee-gcc2.9-990721-as991111
[ -d ee-gcc2.9-990721 ] && [ -d ee-gcc2.9-991111-01 ] || { echo "missing source distributions" >&2; exit 1; }
rm -rf "./$out"
mkdir -p "./$out/ee/bin"
cp -r ./ee-gcc2.9-990721/bin ./ee-gcc2.9-990721/lib "./$out/"
cp ./ee-gcc2.9-991111-01/ee/bin/as "./$out/ee/bin/as"
cp ./ee-gcc2.9-990721/ee/bin/gcc "./$out/ee/bin/gcc"
echo "$out: $("./$out/ee/bin/as" --version | head -1)"
