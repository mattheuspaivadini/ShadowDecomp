#!/bin/bash
# Probe addressing-form options for the array-index cases and -O levels for the
# delay-slot case.
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf vp7 && mkdir vp7 && cd vp7
cat > b.c <<'EOF'
extern int D[];
int f(int i) { return D[i]; }
EOF
cat > c.c <<'EOF'
extern int D[];
int f(int i, int v) { D[i] = v; return v; }
EOF
cat > a.c <<'EOF'
#define HWREG(x) (*(volatile unsigned int *)(x))
unsigned int f(unsigned int v) { unsigned int old = HWREG(0x1000E060); HWREG(0x1000E060) = v; return old; }
EOF
run() {
  local file="$1"; shift
  printf '%-28s ' "$*"
  "$EE" -c "$@" $file.c -o t.o 2>/dev/null && \
    mips-linux-gnu-objdump -dr t.o | sed -n '/^00000000/,$p' \
      | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr -d '\t' | tr '\n' '|'
  echo
}
for opt in "-mno-split-addresses" "-msplit-addresses" "-mno-explicit-relocs" \
           "-mno-split-addresses -mno-explicit-relocs" "-mno-split-addresses -G0"; do
  run b -O2 -g2 $opt
done
echo "b ORIGINAL: lui v0(hi D) | sll a0,a0,2 | addiu v0,v0(lo D) | addu a0,a0,v0 | jr | lw v0,0(a0)"
echo
for opt in "-mno-split-addresses" "-mno-explicit-relocs" "-mno-split-addresses -mno-explicit-relocs"; do
  run c -O2 -g2 $opt
done
echo "c ORIGINAL: lui v0(hi D) | sll a0,a0,2 | addiu v0,v0(lo D) | addu a0,a0,v0 | daddu v0,a1,zero | jr | sw a1,0(a0)"
echo
for opt in "-O1" "-Os" "-O3" "-O1 -g0" "-Os -g0" "-O0" "-O2 -g0 -fno-delayed-branch"; do
  run a -O2 $opt
done
echo "a ORIGINAL: lui v1,0x1000 | ori v1,0xe060 | lw v0,0(v1) | jr | sw a0,0(v1)"
