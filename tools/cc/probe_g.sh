#!/bin/bash
# Probe: default -G value of ee-gcc2.96 and which declaration forms make GCC
# emit absolute lui/%lo instead of %gp_rel (for out-of-gp-window globals).
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf gprobe && mkdir gprobe && cd gprobe

cat > sizes.c <<'EOF'
extern int  a_int;
extern char a_buf[3];
extern int  a_arr[3];
extern char a_big[16];
void f1(int v) { a_int = v; }
void f2(int v) { a_buf[0] = v; }
void f3(int v) { a_arr[0] = v; }
void f4(int v) { a_big[0] = v; }
EOF
echo "=== default -G ==="
"$EE" -c -O2 sizes.c -o sizes.o && mips-linux-gnu-objdump -dr sizes.o | grep -E 'gp_rel|hi\(|lo\(|lui|sw|sb' | head -30
echo
cat > defs.c <<'EOF'
int g1;            /* 4 bytes  */
int g2[2];         /* 8 bytes  */
int g3[3];         /* 12 bytes */
static int s1;     /* 4 bytes  */
int *pf(void) { return &g1; }
int *pg(void) { return &g2; }
int *ph(void) { return &g3; }
int *pi(void) { return &s1; }
EOF
echo "=== definition placement (default -G) ==="
"$EE" -c -O2 defs.c -o defs.o && mips-linux-gnu-objdump -h defs.o | grep -E 'sdata|sbss|\.data|\.bss'
echo "(need -S to see sections; using readelf sizes)"
mips-linux-gnu-readelf -SW defs.o | grep -E 'sdata|sbss|\.data|\.bss|\.rodata'
echo
echo "=== -G0 baseline ==="
"$EE" -c -O2 -G0 defs.c -o defs0.o && mips-linux-gnu-readelf -SW defs0.o | grep -E 'sdata|sbss|\.data|\.bss'
