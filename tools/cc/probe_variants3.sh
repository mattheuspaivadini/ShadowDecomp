#!/bin/bash
# Variant probe #3: force SImode 0xFFFFFFFE to materialize as lui+ori, and
# alternative shapes for the bounds-checked lookup.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp3 && mkdir vp3 && cd vp3

cat > f1.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 = (unsigned) (p->f10 & 0xFFFFFFFEULL); p->f18 = 0; }
EOF
cat > f2.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 = (unsigned) ((unsigned long long) p->f10 & 0xFFFFFFFEULL); p->f18 = 0; }
EOF
cat > f3.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 = (unsigned) ((unsigned long long) p->f10 & ~1ULL); p->f18 = 0; }
EOF
cat > f4.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { p->f10 = p->f10 & (unsigned) 0xFFFFFFFEU; p->f18 = 0; }
EOF
cat > f5.c <<'EOF'
struct S { char p[0x10]; unsigned f10 : 31; unsigned f14 : 31; unsigned f18 : 31; };
void f(struct S *p) { p->f10 = 0; p->f18 = 0; }
EOF
cat > f6.c <<'EOF'
struct S { char p[0x10]; unsigned f10; int f14; int f18; };
void f(struct S *p) { unsigned v = p->f10; p->f10 = v & 0xFFFFFFFE; p->f18 = 0; }
EOF

cat > g1.c <<'EOF'
extern int D[];
int f(unsigned i) { int r = 0; if (i < 10u) r = D[i]; return r; }
EOF
cat > g2.c <<'EOF'
extern int D[];
int f(unsigned i) { int *p = D; if (i < 10u) return p[i]; return 0; }
EOF
cat > g3.c <<'EOF'
extern struct { int v; } D[];
int f(unsigned i) { if (i < 10u) return D[i].v; return 0; }
EOF
cat > g4.c <<'EOF'
extern int D[];
int f(unsigned i) { if (10u > i) return D[i]; return 0; }
EOF
cat > g5.c <<'EOF'
extern int *D;
int f(unsigned i) { if (i < 10u) return D[i]; return 0; }
EOF

for f in f1 f2 f3 f4 f5 f6 g1 g2 g3 g4 g5; do
  echo "== $f"
  if "$EE" -c -O2 -g2 $f.c -o $f.o 2>/tmp/vp3/$f.err; then
    mips-linux-gnu-objdump -d $f.o | sed -n '/^00000000/,$p' \
      | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr '\n' '|'
    echo
  else
    head -2 /tmp/vp3/$f.err
  fi
done
