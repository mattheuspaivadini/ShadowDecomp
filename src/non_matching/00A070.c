/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 2 [cc=29, default].
 * drain loop; the entry `b` offset differs by one instruction (the original has an extra `nop` before the loop body) and the bnez displacement is +1.
 * The original .s stays in the build (asm/cod/00A070.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/00A070.s -> func_0010A070 @ 0x0010A070 (0x40 bytes, 16 insns)
 *
 * Drain loop over a free list, with an idle call when the list is empty:
 *
 *   sd    $s0, 0x0($sp) / sd $ra, 0x10($sp)
 *   b     .L0010A090                   ; entry jumps straight to the test
 *    daddu $s0, $a0, $zero             ; ctx = a0 (survives both calls)
 * .L0010A088:
 *   jal   func_00109E50                ; body: consume the node ...
 *    nop
 * .L0010A090:
 *   jal   func_00109E50                ; test: node = pop(ctx)
 *    daddu $a0, $s0, $zero
 *   bnez  $v0, .L0010A088              ; non-zero -> back to the body
 *    daddu $a0, $v0, $zero             ;   (arg for the body's call)
 *   jal   func_00106F00                ; empty -> idle/poll
 *    nop
 *   b     .L0010A090                   ; ... and test again
 *    nop
 *
 * The body block sits *before* the test and falls through into it (and the
 * entry jumps over it), so the source order is: `goto test;` ... `body:`;
 * a plain `for (;;) { v = pop(); if (v) use(v); else idle(); }` would emit the
 * body last with a `b` back to the test and can never give this layout.
 * Debug level is mixed evidence: the `jal`/`b` delay slots are `nop`, but the
 * entry `b` carries the `$s0 = $a0` copy in its slot - try both -g2 and -g0.
 * func_00109E50 is the matched pop helper
 * (its own draft declares `int func_00109E50(int *a0)`), func_00106F00 is the
 * hand-written syscall stub (`addiu $v1,$zero,0x32; syscall 0`).
 * MATCH GUESS: cc=296 (no cc-discriminating instruction; the stall pattern of
 * the 00A7xx/00A79x neighbours is the default revision)
 */
int *func_00109E50(int *ctx);
void func_00109EA8(int *node);
void func_00106F00(void);

void func_0010A070(int *ctx) {
    int *node;

    goto test;
body:
    func_00109EA8(node);
test:
    node = func_00109E50(ctx);
    if (node != 0)
        goto body;
    func_00106F00();
    goto test;
}
