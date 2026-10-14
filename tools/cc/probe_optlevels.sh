#!/bin/bash
# Does a different -O level reproduce 010640 / 02E890 / 0029C8?
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vpc && mkdir vpc && cd vpc
mkdir -p inc && cat > inc/symbols.h <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
extern int D __attribute__((section(".data")));
extern char B[];
EOF
cat > t.c <<'EOF'
#include "symbols.h"
int f(void) { if (D >= 0) { return HWREG(0x10001010) & 3; } return 0x80008001; }
EOF
cat > u.c <<'EOF'
struct A { char p[0x4C]; int *t; };
struct B { int n; int i; };
void f(struct A *a, struct B *b) {
    if (b != 0) { int *s = &a->t[b->i]; b->n = *s; *s = (int)b; }
}
EOF
cat > v.c <<'EOF'
#include "symbols.h"
void f(void) { int *p = (int *)B; int i; for (i = 0xFF; i >= 0; i--) { p[1] = -1; p[0] = -1; p += 2; } }
EOF
for f in t u v; do
  for o in "-O1" "-O2" "-O3" "-Os"; do
    for g in "-g2" "-g0"; do
      printf '%-2s %-4s %-4s ' "$f" "$o" "$g"
      "$EE" -c $o $g -Iinc $f.c -o x.o 2>/dev/null && \
        mips-linux-gnu-objdump -d x.o | sed -n '/^00000000/,$p' \
          | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
      echo
    done
  done
done
echo "010640 ORIG: bgez-normal-first, error falls through, lui v1,0x1000 in delay slot"
echo "02E890 ORIG: lw a0,0x4C(a0) | addu v0,v0,a0 | lw v1,0(v0) | sw v1,0(a1) | sw a1,0(v0)"
echo "0029C8 ORIG: lui v0,%hi | addiu a0,zero,-1 | addiu v0,%lo | addiu v1,zero,0xFF | L: addiu v1,v1,-1 | sw a0,4(v0) | sw a0,0(v0)"
