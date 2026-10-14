#!/bin/bash
# Show the -O2 vs -O3 codegen delta for an inlinable static helper (GCC 2.9x:
# -O3 == -O2 + -finline-functions).  Run:  bash tools/cc/probe_inline_dump.sh [cc]
set -u
CC=${1:-ee-gcc2.96}
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
DIR=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc
W=$(mktemp -d); trap 'rm -rf "$W"' EXIT; mkdir -p "$W/inc"
cat > "$W/inc/symbols.h" <<'EOF'
extern int D[] __attribute__((section(".data")));
EOF
cat > "$W/t.c" <<'EOF'
#include "symbols.h"
static int h(int x) { return (x << 3) ^ (x >> 2); }
int f(int n) { return h(n) + h(n + 1); }
EOF
for o in "-O2" "-O3"; do
  echo "=== $CC $o ==="
  EE_GCC_DIR="$DIR/$CC" "$EE" -c $o -g2 -G8 -I"$W/inc" "$W/t.c" -o "$W/t.o" 2>/dev/null
  mips-linux-gnu-objdump -dr "$W/t.o" | sed -n '/^00000000/,$p' | head -30
done
