/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 9 [cc=29, default].
 * error-code unbox (01C4C8 family).
 * The original .s stays in the build (asm/cod/01C510.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/01C510.s -> func_0011C510 @ 0x0011C510 (0x64 bytes, 25 insns)
 *
 * Error post-processing of the func_0011C4C8 result (the 0x01C1xx error-code
 * family; the matched 01C4C8.c is the callee):
 *
 *   r = func_0011C4C8(a0, a1, a2);        ; `daddu $s0,$a2` first: a2 is kept
 *   if (*a2 != 0)                          ; bnez -> v0 = 0 in the delay slot
 *       return 0;
 *   if (r != 0xFFFFFFFF)                   ; bne -> $v0 = 0x7FFFFFFF already
 *       return r & 0x7FFFFFFF;             ; ori + and
 *   *a2 = 0x81010059;                      ; 0x81010059 = 0x81019002 + ... err
 *   return 0xFFFFFFFF;
 *
 * The `-1` result is materialised twice (lui/ori) and the second one is the
 * returned value; the error word is stored in the `b` shadow.
 * MATCH GUESS: cc=29
 */
int func_0011C4C8(int a0, int a1, int *a2);

int func_0011C510(int a0, int a1, int *a2) {
    int r;

    r = func_0011C4C8(a0, a1, a2);
    if (*a2 != 0)
        return 0;
    if (r == -1) {
        *a2 = 0x81010059;
        return -1;
    }
    return r & 0x7FFFFFFF;
}
