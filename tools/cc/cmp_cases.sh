#!/bin/bash
# Compare the compiled .text of one case across flag-set object directories.
# Usage: cmp_cases.sh 004E78 O2 O2g O2g2 O2g3 O2g0 O1 O3 Os
set -e
W=/root/shadowdecomp-work/obj
case="$1"; shift
for tag in "$@"; do
  f="$W/$tag/$case.o"
  if [ ! -f "$f" ]; then echo "== $tag: (no object)"; continue; fi
  echo "== $tag"
  mips-linux-gnu-objcopy -O binary --only-section=.text "$f" /tmp/"$tag".bin
  mips-linux-gnu-objdump -d "$f" | sed -n '/^00000000/,$p' | sed 's/^[ ]*[0-9a-f]*://' | sed 's/<.*//'
done
echo "== pairwise byte comparison"
prev=""
for tag in "$@"; do
  f="/tmp/$tag.bin"
  [ -f "$f" ] || continue
  if [ -n "$prev" ]; then
    if cmp -s "$prev" "$f"; then echo "  identical: $(basename $prev .bin) == $tag"; else echo "  DIFFERENT: $(basename $prev .bin) != $tag"; fi
  fi
  prev="$f"
done
