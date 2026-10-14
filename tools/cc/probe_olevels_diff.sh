#!/bin/bash
# Does -O3 differ from -O2 in the EE-GCC 2.9x/2.96 line?  In stock GCC 2.9x the
# only -O3 delta vs -O2 is -finline-functions, so the probe includes shapes that
# give the inliner / loop optimiser something to do.
#
# Run in WSL:   bash tools/cc/probe_olevels_diff.sh
set -u
EE=${EE:-/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh}
W=$(mktemp -d)
trap 'rm -rf "$W"' EXIT
mkdir -p "$W/inc"
cat > "$W/inc/symbols.h" <<'EOF'
extern int  D[]  __attribute__((section(".data")));
extern char B[];
EOF

# t1: static helper called from a loop -> inline candidate
cat > "$W/t1.c" <<'EOF'
#include "symbols.h"
static int h(int x) { return x * 3 + 1; }
int f(int n) { int s = 0, i; for (i = 0; i < n; i++) s += h(D[i]); return s; }
EOF
# t2: constant-trip loop -> unroll candidate
cat > "$W/t2.c" <<'EOF'
#include "symbols.h"
void f(void) { int i; for (i = 0; i < 8; i++) D[i] = D[i] * 2 + 1; }
EOF
# t3: static function called once (classic integrate.c candidate)
cat > "$W/t3.c" <<'EOF'
#include "symbols.h"
static int h(int x) { return (x << 3) ^ (x >> 2); }
int f(int n) { return h(n) + h(n + 1); }
EOF
# t4: small static string-ish loop
cat > "$W/t4.c" <<'EOF'
#include "symbols.h"
static int st(int x) { return x + 7; }
int f(int *p, int n) { int s = 0, i; for (i = 0; i < n; i++) s += st(p[i]); return s; }
EOF

for cc in ee-gcc2.96 ee-gcc2.9-991111-01; do
  echo "=== $cc ==="
  for t in t1 t2 t3 t4; do
    prev=""
    for o in "-O1" "-O2" "-O3" "-Os"; do
      EE_GCC_DIR=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/$cc \
        "$EE" -c $o -g2 -G8 -I"$W/inc" "$W/$t.c" -o "$W/$t.o" 2>/dev/null
      asm=$(mips-linux-gnu-objdump -d "$W/$t.o" 2>/dev/null \
            | sed -n '/^00000000/,$p' | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' \
            | tr -s ' \t' ' ' | tr '\n' '|')
      if [ -z "$prev" ]; then tag="base"; elif [ "$asm" = "$prev" ]; then tag="=-O2"; else tag="DIFF"; fi
      printf '%-4s %-5s %s\n' "$t" "$o" "$tag"
      prev=$asm
    done
  done
done
echo "done (a 'DIFF' at -O3 means -O2/-O3 are separable in that shape)"
