#!/bin/bash
# Variant probe #5: 0148B8 (mask ops) and 014918 (bounded lookup).
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp5 && mkdir vp5 && cd vp5

cat > h1.c <<'EOF'
unsigned int f(unsigned int x) { if ((x >> 28) == 7) x = (x & 0x0FFFFFFF) | 0x80000000; return x; }
EOF
cat > h2.c <<'EOF'
unsigned int f(unsigned int x) { if ((x >> 28) == 7) { x &= 0x0FFFFFFF; x |= 0x80000000; } return x; }
EOF
cat > h3.c <<'EOF'
unsigned int f(unsigned int x) { if ((x >> 28) == 7) x = 0x80000000 | (x & 0x0FFFFFFF); return x; }
EOF
cat > h4.c <<'EOF'
unsigned int f(unsigned int x) { unsigned int r = x; if ((x >> 28) == 7) r = (x & 0x0FFFFFFF) | 0x80000000; return r; }
EOF
cat > h5.c <<'EOF'
unsigned int f(unsigned int x) { if (x >> 28 == 7) { x = (x & 0x0FFFFFFF) | 0x80000000; } return x; }
EOF

cat > k1.c <<'EOF'
extern int D[];
int f(unsigned i) { if (i < 10u) { return D[i]; } return 0; }
EOF
cat > k2.c <<'EOF'
extern int D[];
int f(unsigned i) { return (i < 10u) * D[i]; }
EOF
cat > k3.c <<'EOF'
extern int D[];
int f(unsigned i) { unsigned j = i; if (j < 10u) return D[j]; return 0; }
EOF
cat > k4.c <<'EOF'
extern int D[];
int f(unsigned i) { if (i - 10u > -11u) return 0; return D[i]; }
EOF

for f in h1 h2 h3 h4 h5 k1 k2 k3 k4; do
  echo "== $f"
  if "$EE" -c -O2 -g2 $f.c -o $f.o 2>/tmp/vp5/$f.err; then
    mips-linux-gnu-objdump -d $f.o | sed -n '/^00000000/,$p' \
      | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr '\n' '|'
    echo
  else
    head -2 /tmp/vp5/$f.err
  fi
done
