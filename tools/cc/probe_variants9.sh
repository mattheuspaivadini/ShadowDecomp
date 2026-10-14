#!/bin/bash
# Probe batch-2 variants: store ordering (013078) and register allocation (02E890).
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp9 && mkdir vp9 && cd vp9
cat > a1.c <<'EOF'
void f(int *p, int v) { p[0] = v; p[2] = 0; p[1] = v; }
EOF
cat > a2.c <<'EOF'
void f(int *p, int v) { p[0] = v; p[1] = v; p[2] = 0; }
EOF
cat > a3.c <<'EOF'
void f(int *p, int v) { p[1] = v; p[0] = v; p[2] = 0; }
EOF
cat > a4.c <<'EOF'
void f(int *p, int v) { p[2] = 0; p[0] = v; p[1] = v; }
EOF
cat > a5.c <<'EOF'
struct S { int a; int b; int c; };
void f(struct S *p, int v) { p->a = v; p->c = 0; p->b = v; }
EOF
cat > b1.c <<'EOF'
struct A { char p[0x4C]; int *t; };
struct B { int n; int i; };
void f(struct A *a, struct B *b) {
    if (b != 0) { int *s = &a->t[b->i]; b->n = *s; *s = (int)b; }
}
EOF
cat > b2.c <<'EOF'
struct A { char p[0x4C]; int *t; };
struct B { int n; int i; };
void f(struct A *a, struct B *b) {
    int *s;
    if (b == 0) return;
    s = &a->t[b->i];
    b->n = *s;
    *s = (int)b;
}
EOF
cat > b3.c <<'EOF'
struct A { char p[0x4C]; int *t; };
struct B { int n; int i; };
void f(struct A *a, struct B *b) {
    int *s;
    if (b) { s = a->t + b->i; b->n = s[0]; s[0] = (int)b; }
}
EOF
cat > c1.c <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
extern int D;
int f(void) { if (D < 0) return 0x80008001; return HWREG(0x10001010) & 3; }
EOF
for f in a1 a2 a3 a4 a5 b1 b2 b3 c1; do
  for g in "-g2" "-g0"; do
    printf '%-3s %-4s ' "$f" "$g"
    "$EE" -c -O2 $g $f.c -o t.o 2>/dev/null && \
      mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' \
        | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
    echo
  done
done
echo "013078 ORIGINAL: sw a1,0(a0) | sw zero,8(a0) | jr | sw a1,4(a0)"
echo "02E890 ORIGINAL: beqz a1 | nop | lw v0,4(a1) | lw a0,0x4C(a0) | sll v0,v0,2 | addu v0,v0,a0 | lw v1,0(v0) | sw v1,0(a1) | sw a1,0(v0) | jr | nop"
echo "010640 ORIGINAL: lui v0,%hi(D) | lw v1,%lo(D)(v0) | bgez v1,L | lui v1,0x1000 | lui v0,0x8000 | jr | ori v0,0x8001 || L: ori v1,0x1010 | lw v0,0(v1) | jr | andi v0,3"
