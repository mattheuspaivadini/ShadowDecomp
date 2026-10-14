#!/bin/bash
# Probe: is the ee-gcc2.96 32-bit driver able to read sources on /mnt/c (drvfs)?
set -e
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
mkdir -p /tmp/drvfsprobe && cd /tmp/drvfsprobe
cp /mnt/c/Users/Matheus/Documents/ShadowDecomp/src/cod/002FE0.c ./a.c
echo "native source, native output:"
"$EE" -c -O2 a.c -o a.o && echo "  OK" || echo "  FAIL"
echo "drvfs source:"
"$EE" -c -O2 /mnt/c/Users/Matheus/Documents/ShadowDecomp/src/cod/002FE0.c -o b.o && echo "  OK" || echo "  FAIL"
echo "native source, drvfs output:"
"$EE" -c -O2 a.c -o /mnt/c/Users/Matheus/Documents/ShadowDecomp/build/phase3/probe.o && echo "  OK" || echo "  FAIL"
