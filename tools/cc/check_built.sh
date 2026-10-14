#!/bin/bash
cd /mnt/c/Users/Matheus/Documents/ShadowDecomp
for f in 002FE0 0128C0 012908 011D50 004E78; do
  printf '%-8s ' "$f"
  mips-linux-gnu-readelf -SW "build/asm/cod/$f.o" | awk '/\.text/ {print $3, $6, $7, $8}'
done
echo "--- symbols ---"
mips-linux-gnu-readelf -sW build/asm/cod/0128C0.o | grep -E 'FUNC' | head -5
