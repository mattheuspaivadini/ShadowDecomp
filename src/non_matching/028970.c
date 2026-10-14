/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=296, default].
 * D_0013A18C clear + func_001120A8.
 * The original .s stays in the build (asm/cod/028970.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/028970.s -> func_00128970 @ 0x00128970 (0x5C bytes, 23 insns)
 *
 * Clear the device status word D_0013A18C, run func_001120A8(a1, a2) (the
 * pending operation) and, when it reports -1 (nothing was done), hand the status
 * word to the caller's output pointer $a0 if it became non-zero:
 *
 *   *p = 0;                        ; sw $zero,0x0($s1) - in the jal delay slot
 *   r = func_001120A8(a1, a2);     ; jal delay: a0 = a1 (a1 = a2 set before)
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 *                                  ; bnel $v1,$a0 + bnel $v1,$zero with the
 *                                  ; store `sw $v1,0x0($s0)` in its delay slot
 *
 * The output pointer is materialised into a local *first*: that is what makes
 * the image's callee-saved roles ($s0 = $a0 the output pointer, $s1 = &status)
 * come out in this order - the pseudo created first gets $s0. The function
 * returns nothing ($v0 is left as the callee's result; there is no copy in the
 * epilogue).
 * MATCH GUESS: cc=296 (the $s0/$s1/$ra saves are 8 bytes apart - the 296 slot
 * layout; the worker call is not in tail position, so the `jal` shape holds) */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
int func_001120A8(int a0, int a1);

void func_00128970(int a0, int a1, int a2) {
    int *out = (int *)a0;
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_001120A8(a1, a2);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *out = v;
    }
}
