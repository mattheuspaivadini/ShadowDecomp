#!/bin/bash
# Probe: constant-multiply code generation (Session 4 evidence, corrected).
#
# Question: the original image uses the R5900 3-operand `mult rd,rs,rt` for
#   func_00120F18  -> i * 0x184
#   func_00122018  -> i * 0x24
# but a shift/add sequence for
#   func_00104E78  -> x * 320   (which matches with ee-gcc2.96)
#
# Findings (all reproduced by this script):
#   * ee-gcc2.96: a multiply by a *literal* constant is ALWAYS expanded into a
#     shift/add sequence, for every ISA/CPU/-O level it accepts
#     (`-mips1..4`, `-m3900`, `-m5900`, `-O0..-O3`, `-Os`, `-mmad`, ...);
#     `-m3900` alone does select MULT, but it also switches e_flags to
#     `0x814001, mips1, 3900` - not the original's `0x20924001, mips3, 5900`;
#     a multiply by a *runtime* value becomes `mult rd,rs,rt` there;
#   * ee-gcc2.9-991111[-01]: a *literal* constant stride IS compiled to
#     `mult rd,rs,rt` (section 3 below) - the original's shape.
#
# Consequence (docs/compiler.md 4.2/4.3): the `mult` shape is a *revision*
# difference, not a flag one. func_00120F18 / func_00122018 are byte-exact with
# the 2.9 revision and a plain literal stride.
#
# Usage (WSL2): bash tools/cc/probe_mult.sh
set -e
WORK="${SOT_WORK:-$HOME/shadowdecomp-work}"
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
mkdir -p "$WORK"
cd "$WORK"

cat > probe_mult.c <<'EOF'
struct S { char b[0x184]; };
extern struct S D[];
struct S *c388(int i) { return &D[i]; }
int c036(int x) { return x * 0x24; }
int c320(int x) { return x * 320; }
long long w64(long long a, long long b) { return a + b; }
EOF

echo "=== 1. flag sweep (does any flag select MULT for a literal stride?)"
for flags in "-O2 -g2 -G8" "-O0 -g2 -G8" "-O1 -g2 -G8" "-O3 -g2 -G8" "-Os -g2 -G8" \
             "-O2 -g2 -G8 -mmad" "-O2 -g2 -G8 -mips1" "-O2 -g2 -G8 -mips4" \
             "-O2 -g2 -G8 -m5900" "-O2 -g2 -G8 -mips3 -m5900" \
             "-O2 -g2 -G8 -m3900" "-O2 -g2 -G8 -mips3 -m3900"; do
    if "$REPO/tools/cc/eegcc.sh" -c $flags probe_mult.c -o probe_mult.o 2>probe_mult.err; then
        fl=$(mips-linux-gnu-readelf -h probe_mult.o | sed -n 's/.*Flags: //p')
        n=$(mips-linux-gnu-objdump -d probe_mult.o | grep -c '^\s*[0-9a-f]*:\s*[0-9a-f]*\s*mult\s' || true)
        printf '  %-32s flags=%-42s mult_insns=%s\n' "$flags" "$fl" "$n"
    else
        printf '  %-32s FAILED: %s\n' "$flags" "$(head -1 probe_mult.err)"
    fi
done

echo
echo "=== 2. source spellings (literal vs runtime stride), pinned flags"
cat > probe_mult_spelling.c <<'EOF'
struct S { char b[0x184]; };
extern struct S D[];
struct S *literal(int i)    { return &D[i * 0x184]; }
struct S *runtime(int i)    { int size = 0x184; return (struct S *)((char *)D + i * size); }
struct S *var_times_var(int i, int j) { return (struct S *)((char *)D + i * j); }
EOF
"$REPO/tools/cc/eegcc.sh" -c -O2 -g2 -G8 probe_mult_spelling.c -o probe_mult_spelling.o
for f in literal runtime var_times_var; do
    echo "  -- $f"
    mips-linux-gnu-objdump -d probe_mult_spelling.o | sed -n "/<$f>:/,/^$/p" \
        | grep -E '^\s+[0-9a-f]+:\s' | sed 's/^/       /'
done

echo
echo "=== 3. literal stride under the alternate revision (2.9-991111-01)"
EE_GCC_DIR=ee-gcc2.9-991111-01 \
    "$REPO/tools/cc/eegcc.sh" -c -O2 -g2 -G8 probe_mult_spelling.c \
    -o probe_mult_spelling_29.o
for f in literal; do
    echo "  -- $f (2.9-991111-01)"
    mips-linux-gnu-objdump -d probe_mult_spelling_29.o | sed -n "/<$f>:/,/^$/p" \
        | grep -E '^\s+[0-9a-f]+:\s' | sed 's/^/       /'
done
