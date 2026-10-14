#!/bin/bash
# Does a later -g0 override an earlier -g2 in ee-gcc2.96?
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp8 && mkdir vp8 && cd vp8
cat > a.c <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
unsigned int f(unsigned int v) { unsigned int old = HWREG(0x1000E060); HWREG(0x1000E060) = v; return old; }
EOF
for opt in "-g2" "-g2 -g0" "-g0 -g2" "-g2 -g1" "-g0" "-g"; do
  printf '%-12s ' "$opt"
  "$EE" -c -O2 $opt a.c -o t.o 2>/dev/null && \
    mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' \
      | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
  echo
done
echo "ORIGINAL: lui v1,0x1000 | ori v1,0xe060 | lw v0,0(v1) | jr | sw a0,0(v1)"
