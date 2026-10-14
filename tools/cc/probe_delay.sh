#!/bin/bash
# Probe: what makes ee-gcc2.96 fill/not fill the delay slot?
EE=/mnt/c/Users/Matheus/Documents/ShadowDecomp/tools/cc/eegcc.sh
cd /tmp && rm -rf dbprobe && mkdir dbprobe && cd dbprobe
cat > t.c <<'EOF'
extern char D_0013D840[];
char *f(int x) { return &D_0013D840[x * 320]; }
EOF
for flags in "-O2 -g0" "-O2 -g2" "-O2 -g0 -fno-delayed-branch" "-O2 -g2 -fdelayed-branch" \
             "-O2 -g3" "-O2 -g0 -fno-schedule-insns2" "-O2 -g2 -fno-schedule-insns2"; do
  echo "== $flags"
  if "$EE" -c $flags t.c -o t.o 2>/tmp/dbprobe/err; then
    mips-linux-gnu-objdump -d t.o | sed -n '/^00000000/,$p' | sed 's/^[ ]*[0-9a-f]*://;s/<.*//' | tr '\n' '|'
    echo
  else
    head -2 /tmp/dbprobe/err
  fi
done
