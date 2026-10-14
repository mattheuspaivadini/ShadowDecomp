#!/bin/bash
# Probe the four remaining mismatches from the first decompilation batch.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp6 && mkdir vp6 && cd vp6
cat > a.c <<'EOF'
#define HWREG(a) (*(volatile unsigned int *)(a))
unsigned int f(unsigned int v) { unsigned int old = HWREG(0x1000E060); HWREG(0x1000E060) = v; return old; }
EOF
cat > b1.c <<'EOF'
extern int D[];
int f(int i) { return D[i]; }
EOF
cat > b2.c <<'EOF'
extern int D[];
int f(unsigned i) { return D[i]; }
EOF
cat > b3.c <<'EOF'
extern int D[];
int f(int i) { int *p = D; return p[i]; }
EOF
cat > b4.c <<'EOF'
extern int D[];
int f(int i) { unsigned j = i; return D[j]; }
EOF
cat > c1.c <<'EOF'
extern int D[];
int f(int i, int v) { D[i] = v; return v; }
EOF
cat > c2.c <<'EOF'
extern int D[];
int f(unsigned i, int v) { D[i] = v; return v; }
EOF
cat > c3.c <<'EOF'
extern int D[];
int f(int i, int v) { int *p = D; p[i] = v; return v; }
EOF
for f in a b1 b2 b3 b4 c1 c2 c3; do
  for g in "-g2" "-g0"; do
    printf '%-4s %-4s ' "$f" "$g"
    "$EE" -c -O2 $g $f.c -o t.o 2>/dev/null && \
      mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' \
        | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
    echo
  done
done
echo "ORIGINAL 0128D0 : lui v0(hi) | sll a0,a0,2 | addiu v0,%lo | addu a0,a0,v0 | jr | lw v0,0(a0)"
echo "ORIGINAL 0128E8 : lui v0(hi) | sll a0,a0,2 | addiu v0,%lo | addu a0,a0,v0 | daddu v0,a1,zero | jr | sw a1,0(a0)"
echo "ORIGINAL 014C30 : lui v1,0x1000 | ori v1,0xE060 | lw v0,0(v1) | jr | sw a0,0(v1)"
