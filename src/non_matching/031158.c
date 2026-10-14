/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=296, default].
 * func_00112088 variant.
 * The original .s stays in the build (asm/cod/031158.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/031158.s -> func_00131158 @ 0x00131158 (0x5C bytes, 23 insns)
 *
 * Clear the device status word D_0013A18C, run func_00112088(a1, a2) and, when
 * it reports -1 (nothing was done), hand the status word to the caller's output
 * pointer $a0 if it became non-zero:
 *
 *   *p = 0;                        ; sw $zero,0x0($s1) - in the jal delay slot
 *   r = func_00112088(a1, a2);     ; a0 = a1, a1 = a2, result copied to $v1
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 *                                  ; bnel $v1,$a0 + bnel $v1,$zero with the
 *                                  ; store `sw $v1,0x0($s0)` in its delay slot
 *
 * The output pointer is materialised into a local *first* so the callee-saved
 * roles come out as the image's ($s0 = the output pointer, $s1 = &status): the
 * pseudo created first gets $s0. No return statement ($v0 is left as the
 * callee's result).
 * MATCH GUESS: cc=296 ($s0/$s1/$ra 8 bytes apart - the 296 slot layout) */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
int func_00112088(int a0, int a1);

void func_00131158(int a0, int a1, int a2) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_00112088(a1, a2);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
}
