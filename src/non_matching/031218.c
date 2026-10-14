/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=296, default].
 * 030FE8 twin with func_00111F18.
 * The original .s stays in the build (asm/cod/031218.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/031218.s -> func_00131218 @ 0x00131218 (0x60 bytes, 24 insns)
 *
 * Exact twin of 030FE8 (same nine-instruction shape, other worker): the status
 * word D_0013A18C is cleared, func_00111F18(a1, a2, a3) is run, and on a -1
 * report the status word goes to the output pointer $a0 when non-zero; the
 * worker's value is returned:
 *
 *   *p = 0;                        ; sw $zero,0x0($s1) - in the jal delay slot
 *   r = func_00111F18(a1, a2, a3); ; a0 = a1, a1 = a2, a2 = a3
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 *                                  ; bnel $v1,$zero with `sw $v1,0x0($s0)` in
 *                                  ; its delay slot
 *   return r;                      ; daddu $v1,$v0 ; bne, daddu $v0,$v1 in slot
 *
 * The output pointer is materialised into a local *first* so the callee-saved
 * roles come out as the image's ($s0 = the output pointer, $s1 = &status).
 * MATCH GUESS: cc=296 ($s0/$s1/$ra 8 bytes apart - the 296 slot layout) */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
int func_00111F18(int a0, int a1, int a2);

int func_00131218(int a0, int a1, int a2, int a3) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_00111F18(a1, a2, a3);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
    return r;
}
