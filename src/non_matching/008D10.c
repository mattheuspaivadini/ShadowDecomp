/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 17 [cc=29, default].
 * byte-emit callback.
 * The original .s stays in the build (asm/cod/008D10.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/008D10.s -> func_00108D10 @ 0x00108D10 (0x58 bytes, 22 insns)
 *
 * Output callback registered by func_00108E08 / func_00108E40 through
 * func_00107FF8(cb, &buf, ...): write ONE byte at the cursor held in *a0 while
 * decrementing the counter at *a1.
 *
 *   n = *a1; if (n == 0) return 1;
 *   p = *q;                       (q = a0, the copied variable)
 *   if (a2 >= 0x100) { *p = 0; return 0; }   (value does not fit a byte)
 *   if (n == 1) a2 = 0;           (`xori 0x1` + `movz` - terminator slot)
 *   *p = a2; p++; *q = p; *a1 = *a1 - 1; return 1;
 *
 * Shape notes: `daddu a3, a0, zero` is the extra copy the original keeps (the
 * same idiom as the matched 008D68/008D90 `a = c;`), the `beql` delay slot
 * reloads the cursor for the fail path, and the counter is RELOADED after the
 * byte store (`lw v1, 0x0(a1)`), which only happens if the source writes
 * `a1[0] = a1[0] - 1` rather than reusing the earlier value.
 * MATCH GUESS: cc=29
 */
int func_00108D10(int *a0, int *a1, int a2) {
    int *q;
    char *p;

    q = a0;
    if (a1[0] == 0)
        return 1;
    p = (char *)q[0];
    if (a2 >= 0x100) {
        p[0] = 0;
        return 0;
    }
    if (a1[0] == 1)
        a2 = 0;
    p[0] = a2;
    q[0] = (int)(p + 1);
    a1[0] = a1[0] - 1;
    return 1;
}
