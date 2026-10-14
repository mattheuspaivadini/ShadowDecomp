#!/bin/bash
# Probe 010640 branch layout: if/return vs ternary.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vpb && mkdir vpb && cd vpb
mkdir -p inc && cat > inc/symbols.h <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
extern int D __attribute__((section(".data")));
EOF
cat > t1.c <<'EOF'
#include "symbols.h"
int f(void) { return D >= 0 ? (HWREG(0x10001010) & 3) : 0x80008001; }
EOF
cat > t2.c <<'EOF'
#include "symbols.h"
int f(void) { int v = D; if (v >= 0) return HWREG(0x10001010) & 3; return 0x80008001; }
EOF
cat > t3.c <<'EOF'
#include "symbols.h"
int f(void) { if (D >= 0) { return HWREG(0x10001010) & 3; } else { return 0x80008001; } }
EOF
cat > t4.c <<'EOF'
#include "symbols.h"
int f(void) { int r = 0x80008001; if (D >= 0) { r = HWREG(0x10001010) & 3; } return r; }
EOF
for f in t1 t2 t3 t4; do
  for g in "-g2" "-g0"; do
    printf '%-3s %-4s ' "$f" "$g"
    "$EE" -c -O2 $g -Iinc $f.c -o t.o 2>/dev/null && \
      mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' \
        | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
    echo
  done
done
echo "ORIG: lui v0,%hi(D) | lw v1,%lo(D)(v0) | bgez v1,L | lui v1,0x1000 || lui v0,0x8000 | jr | ori v0,0x8001 || L: ori v1,0x1010 | lw v0,0(v1) | jr | andi v0,3"
