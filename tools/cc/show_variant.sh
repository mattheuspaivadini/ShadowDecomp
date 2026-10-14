#!/bin/bash
# Disassemble a permuter variant object next to the original function's asm.
# Usage: bash tools/cc/show_variant.sh <stem> <variant> <cc>
set -e
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO"
stem="$1"; variant="$2"; cc="${3:-29}"
OBJ="${SOT_WORK:-$HOME/shadowdecomp-work}/permute/$stem/obj/$cc/$variant.o"
echo "== $stem / $variant (cc=$cc) compiled"
mips-linux-gnu-objdump -d "$OBJ" | sed -n '/<func/,/^$/p' | grep -E '^\s+[0-9a-f]+:' | sed 's/^[[:space:]]*//'
echo "== $stem original"
grep -E '\*/' "asm/cod/$stem.s" | sed 's/^ *//'
