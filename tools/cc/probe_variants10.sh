#!/bin/bash
# Probe batch-2 variants #2: branch polarity (010640), copy loop (00FFC0),
# clear loops (0029C8).
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vpa && mkdir vpa && cd vpa
mkdir -p inc && cat > inc/symbols.h <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
extern int D __attribute__((section(".data")));
EOF
cat > c1.c <<'EOF'
#include "symbols.h"
int f(void) { if (D >= 0) { return HWREG(0x10001010) & 3; } return 0x80008001; }
EOF
cat > d1.c <<'EOF'
int f(unsigned char *d, unsigned char *s, unsigned int n) {
    unsigned int i = 0;
    if (n != 0) { do { *d = *s; i++; s++; d++; } while (i < n); }
    return 0;
}
EOF
cat > d2.c <<'EOF'
int f(unsigned char *d, unsigned char *s, int n) {
    while (n-- > 0) *d++ = *s++;
    return 0;
}
EOF
cat > d3.c <<'EOF'
int f(char *d, char *s, unsigned int n) {
    unsigned int i;
    for (i = 0; i < n; i++) { *d++ = *s++; }
    return 0;
}
EOF
cat > e1.c <<'EOF'
extern int D[];
void f(void) { int *p = D; int i; for (i = 0xFF; i >= 0; i--) { p[1] = -1; p[0] = -1; p += 2; } }
EOF
cat > e2.c <<'EOF'
extern int D[];
void f(void) { int *p = D; int i; for (i = 255; i >= 0; i--) { p[0] = -1; p[1] = -1; p += 2; } }
EOF
for f in c1 d1 d2 d3 e1 e2; do
  for g in "-g2" "-g0"; do
    printf '%-3s %-4s ' "$f" "$g"
    "$EE" -c -O2 $g -Iinc $f.c -o t.o 2>/dev/null && \
      mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' \
        | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
    echo
  done
done
echo "010640 ORIG: lui v0,%hi(D) | lw v1,%lo(D)(v0) | bgez v1,L | lui v1,0x1000 || lui v0,0x8000 | jr | ori v0,0x8001 || L: ori v1,0x1010 | lw v0,0(v1) | jr | andi v0,3"
echo "00FFC0 ORIG: beqz a2,L | daddu a3,zero,zero || lbu v1,0(a1) | addiu a3,a3,1 | addiu a1,a1,1 | sltu v0,a3,a2 | sb v1,0(a0) | addiu a0,a0,1 | bnez v0,L | nop || L: jr | daddu v0,zero,zero"
echo "0029C8 ORIG: lui v0,%hi | addiu a0,zero,-1 | addiu v0,%lo | addiu v1,zero,0xFF || L: addiu v1,v1,-1 | sw a0,4(v0) | sw a0,0(v0) | nop | nop | bgez v1,L | addiu v0,v0,8 || jr | nop"
