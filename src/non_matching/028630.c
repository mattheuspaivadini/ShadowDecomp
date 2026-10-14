/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=296, default].
 * D_0013A180+0xC clear + gated copy.
 * The original .s stays in the build (asm/cod/028630.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/028630.s -> func_00128630 @ 0x00128630 (0x58 bytes, 22 insns)
 *
 * Clear the device status word D_0013A18C, run func_00111FD0(a1) (the pending
 * operation) and, when it reports -1 (nothing done), hand the status word to
 * the caller's output pointer if it became non-zero:
 *   *p = 0;                       (sw $zero, 0x0($s1), in the jal delay slot)
 *   r = func_00111FD0(a1);        (return value moved to $a0 -> the variable)
 *   if (r == -1) { v = *p; if (v != 0) *out = v; }
 * `bnel $a0,$v1` + `bnel $v1,$zero` (the store of v sits in the branch-likely
 * delay slot) is the shape ee-gcc emits for this nested single-statement if.
 * The function returns nothing ($v0 is never set on the epilogue path).
 *
 * The address D_0013A180 + 0xC is built as lui + addiu %lo (a non-small char/
 * int array base with a 0xC addend); the three saves are 8 bytes apart
 * ($s0, $s1, $ra) - the cc=296 slot layout.
 * MATCH GUESS: cc=296 */
extern int D_0013A180[];   /* 0x0013A18C = D_0013A180 + 0xC: lui/%lo */
extern int func_00111FD0(int a0);

void func_00128630(int a0, int a1) {
    int *p = &D_0013A180[3];
    int r;

    *p = 0;
    r = func_00111FD0(a1);
    if (r == -1) {
        int v = *p;

        if (v != 0)
            *(int *)a0 = v;
    }
}
