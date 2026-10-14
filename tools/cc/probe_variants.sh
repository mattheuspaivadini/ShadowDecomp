#!/bin/bash
# Variant probe for the 009268 / 014918 flag-pinning cases.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf varprobe && mkdir varprobe && cd varprobe

cat > v1.c <<'EOF'
struct S { char p[0x10]; int f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFE; p->f18 = 0; }
EOF
cat > v2.c <<'EOF'
struct S { char p[0x10]; int f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFEu; p->f18 = 0; }
EOF
cat > v3.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 &= 0xFFFFFFFEu; p->f18 = 0; }
EOF
cat > v4.c <<'EOF'
struct S { char p[0x10]; int f10; int f14; int f18; };
void f(struct S *p) { p->f10 = (p->f10 & 0xFFFFFFFE) | 0; p->f18 = 0; }
EOF

cat > w1.c <<'EOF'
extern int D[];
int f(unsigned i) { if (i < 10u) return D[i]; return 0; }
EOF
cat > w2.c <<'EOF'
extern int D[];
int f(unsigned i) { if (i >= 10u) return 0; return D[i]; }
EOF
cat > w3.c <<'EOF'
extern int D[];
int f(unsigned i) { return (i < 10u) ? D[i] : 0; }
EOF

for f in v1 v2 v3 v4 w1 w2 w3; do
  echo "== $f"
  "$EE" -c -O2 -g2 $f.c -o $f.o && mips-linux-gnu-objdump -d $f.o | sed -n '/^00000000/,$p' | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr '\n' '|'
  echo
done
