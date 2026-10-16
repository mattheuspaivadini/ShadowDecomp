/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=296, default].
 * 028630 clone with the -1 stub.
 * The original .s stays in the build (asm/cod/031100.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/031100.s -> func_00131100 @ 0x00131100 (0x58 bytes, 22 insns)
 *
 * Same body as the sibling 028630, with func_00111FB8 (the always-"-1" stub)
 * as the worker:
 *   *p = 0;                       (sw $zero, 0x0($s1), in the jal delay slot)
 *   r = func_00111FB8(a1);        (return value moved to $a0)
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 * The output pointer is the first argument; the status word lives at
 * D_0013A180 + 0xC (lui/%lo, non-small). Three 8-byte-spaced saves.
 * MATCH GUESS: cc=296 */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
extern int close(int a0);

void _close_r(int a0, int a1) {
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = close(a1);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *(int *)a0 = v;
    }
}
