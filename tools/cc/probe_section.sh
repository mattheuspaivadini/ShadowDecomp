#!/bin/bash
# How to make ee-gcc2.96 address an extern global absolutely (non-small-data)?
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp4 && mkdir vp4 && cd vp4
cat > t.c <<'EOF'
extern int A;                                  /* 4 bytes  -> small  */
extern int B[3];                               /* 12 bytes -> big    */
extern int C __attribute__((section(".data")));
extern int D __attribute__((aligned(64)));
extern int E[];                                /* unknown size       */
extern int F[10];
void fa(int v) { A = v; }
void fb(int v) { B[0] = v; }
void fc(int v) { C = v; }
void fd(int v) { D = v; }
void fe(int v) { E[0] = v; }
void ff(int v) { F[0] = v; }
EOF
"$EE" -c -O2 -g2 t.c -o t.o && mips-linux-gnu-objdump -dr t.o | sed -n '/^00000000/,$p'
