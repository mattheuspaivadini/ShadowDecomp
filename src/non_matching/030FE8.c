/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 4 [cc=296, default].
 * D_0013A18C clear + func_00111E98 + return r.
 * The original .s stays in the build (asm/cod/030FE8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/030FE8.s -> func_00130FE8 @ 0x00130FE8 (0x60 bytes, 24 insns)
 *
 * Same family as the 028970/031158/0311B8 wrappers, but the worker's result is
 * also returned: the copy `daddu $v0,$v1,$zero` sits in the delay slot of the
 * `bne $v1,$a0,-1` and the epilogue leaves $v0 = r:
 *
 *   *out = (a0 copy first: it is what makes $s0 the output pointer and $s1 the
 *           status pointer)
 *   *p = 0;                        ; sw $zero,0x0($s1) - in the jal delay slot
 *   r = func_00111E98(a1, a2, a3); ; a0 = a1, a1 = a2, a2 = a3
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 *                                  ; bnel $v1,$zero with `sw $v1,0x0($s0)` in
 *                                  ; its delay slot
 *   return r;                      ; daddu $v1,$v0 ; bne + daddu $v0,$v1
 *
 * The output pointer is materialised into a local *first* so the callee-saved
 * roles come out as the image's (the pseudo created first gets $s0).
 * MATCH GUESS: cc=296 ($s0/$s1/$ra 8 bytes apart - the 296 slot layout) */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
int func_00111E98(int a0, int a1, int a2);

int func_00130FE8(int a0, int a1, int a2, int a3) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_00111E98(a1, a2, a3);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
    return r;
}
