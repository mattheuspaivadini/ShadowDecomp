#!/bin/bash
# Targeted sweep: which extra flag makes 009268 / 0148B8 / 014918 match?
cd /mnt/c/Users/Matheus/Documents/ShadowDecomp
EE=tools/cc/eegcc.sh
W=/root/shadowdecomp-work
mkdir -p $W/obj/sweep
for f in \
  "-O2 -g2 -fno-strength-reduce" \
  "-O2 -g2 -fomit-frame-pointer" \
  "-O2 -g2 -fno-rerun-cse-after-loop" \
  "-O2 -g2 -fno-expensive-optimizations" \
  "-O2 -g2 -fno-thread-jumps" \
  "-O2 -g2 -fno-caller-saves" \
  "-O2 -g2 -fno-function-cse" \
  "-O2 -g2 -fno-schedule-insns" \
  "-O2 -g2 -fno-peephole" \
  "-O2 -g2 -fno-defer-pop" \
  "-O2 -g2 -fno-omit-frame-pointer" \
  "-O2 -g2 -mno-split-addresses" \
  "-O2 -g2 -mips3" \
  "-O2 -g2 -fno-optimize-sibling-calls" \
  ; do
  ok=0; res=""
  for c in 009268 0148B8 014918; do
    if "$EE" -c $f $W/src/cod/$c.c -o $W/obj/sweep/$c.o 2>/dev/null; then
      if python3 tools/matchcheck.py --obj $W/obj/sweep/$c.o --case $c >/dev/null 2>&1; then
        ok=$((ok+1)); res="$res +$c"
      fi
    fi
  done
  echo "$ok/3 $res   <- $f"
done
