/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 5 [cc=296, default].
 * func_00111FC8 stub variant.
 * The original .s stays in the build (asm/cod/0311B8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/0311B8.s -> func_001311B8 @ 0x001311B8 (0x60 bytes, 24 insns)
 *
 * Same body as the 028970/031158 siblings, with func_00111FC8 (the always-"-1"
 * stub, src/cod/011FC8.c) called with three forwarded arguments and with the
 * call result copied to $a0 (free here, since $a0 was saved into $s0 first):
 *
 *   *p = 0;                        ; sw $zero,0x0($s1) - in the jal delay slot
 *   r = func_00111FC8(a1, a2, a3); ; daddu $a0,$v0 ; addiu $v1,$zero,-1
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 *                                  ; bnel $a0,$v1 + bnel $v1,$zero with the
 *                                  ; store `sw $v1,0x0($s0)` in its delay slot
 *
 * The output pointer is materialised into a local *first* so that the
 * callee-saved roles match ($s0 = the output pointer, $s1 = &status). No return
 * statement ($v0 is left as the callee's result). The callee is declared without
 * a prototype (its matched definition is `int func_00111FC8(void)`) so the three
 * forwarded arguments pass through unchanged.
 * MATCH GUESS: cc=296 ($s0/$s1/$ra 8 bytes apart - the 296 slot layout) */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
int func_00111FC8();

void func_001311B8(int a0, int a1, int a2, int a3) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_00111FC8(a1, a2, a3);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
}
