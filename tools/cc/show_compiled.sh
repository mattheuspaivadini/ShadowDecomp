#!/bin/bash
# Compile stems with their pinned flags (via tools/verify_c.py) and disassemble
# the resulting object, for the Phase-6 loop.
#
# Usage (WSL2): bash tools/cc/show_compiled.sh 009B80 0262B8
set -e
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO"
python3 tools/verify_c.py "$@" >/dev/null 2>&1 || true
OBJDIR="${SOT_WORK:-$HOME/shadowdecomp-work}/obj/verify"
for stem in "$@"; do
    echo "== $stem (compiled)"
    mips-linux-gnu-objdump -d "$OBJDIR/$stem.o" \
        | sed -n '/<func/,/^$/p' | grep -E '^\s+[0-9a-f]+:'
done
