#!/bin/bash
# Variant probe #2 for the 009268 / 014918 flag-pinning cases.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp2 && mkdir vp2 && cd vp2

# ---- 009268: original uses lui/ori (0xFFFF/0xFFFE) instead of li -2 ----
cat > a1.c <<'EOF'
struct S { char p[0x10]; unsigned long long f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFEULL; p->f18 = 0; }
EOF
cat > a2.c <<'EOF'
struct S { char p[0x10]; long long f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFELL; p->f18 = 0; }
EOF
cat > a3.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 = p->f10 & 0xFFFFFFFFFFFF0000u | (p->f10 & 0xFFFEu); p->f18 = 0; }
EOF
cat > a4.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFFu - 1; p->f18 = 0; }
EOF
cat > a5.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { unsigned m = 0xFFFFFFFEu; p->f10 &= m; p->f18 = 0; }
EOF
cat > a6.c <<'EOF'
struct S { char p[0x10]; volatile int f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFE; p->f18 = 0; }
EOF

# ---- 014918: original = sltiu v0 / beqz v0 / delay lui v0 / sll v1 ----
cat > b1.c <<'EOF'
extern int D[];
int f(int i) { if ((unsigned) i < 10u) return D[i]; return 0; }
EOF
cat > b2.c <<'EOF'
extern int D[10];
int f(unsigned i) { if (i < 10u) return D[i]; return 0; }
EOF
cat > b3.c <<'EOF'
extern int D[10];
int f(int i) { if (i < 10u) return D[i]; return 0; }
EOF
cat > b4.c <<'EOF'
extern int D[];
int f(unsigned i) { if (i < 10u) return *(D + i); return 0; }
EOF
cat > b5.c <<'EOF'
extern int D[];
int f(unsigned i) { return i < 10u ? D[i] : 0; }
EOF
cat > b6.c <<'EOF'
extern int D[];
unsigned g(unsigned i);
int f(unsigned i) { if (i < 10u) return D[i]; return 0; }
EOF

for f in a1 a2 a3 a4 a5 a6 b1 b2 b3 b4 b5 b6; do
  echo "== $f"
  if "$EE" -c -O2 -g2 $f.c -o $f.o 2>/tmp/vp2/$f.err; then
    mips-linux-gnu-objdump -d $f.o | sed -n '/^00000000/,$p' \
      | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr '\n' '|'
    echo
  else
    head -2 /tmp/vp2/$f.err
  fi
done
