/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 10 [cc=29, default].
 * bounded memcpy-out (018438 mirror).
 * The original .s stays in the build (asm/cod/018490.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/018490.s -> func_00118490 @ 0x00118490 (0x54 bytes, 21 insns)
 *
 * Mirror of func_00118438: bounded copy *out of* the record buffer
 * (p->field30 = its size in bytes):
 *
 *   if (a1 == 0) return 0;                    ; $a0 <- $a1, beqz $a0
 *   lim = p->field30 - (a3 << 2);             ; sll $a3,$a3,2 ; subu
 *   if (a4 < 0 || lim < a4) return -0x21F;    ; bltz + slt ; addiu $v0,-0x21F
 *   func_0012821C(a1, (a3 << 2) + a2, a4);    ; memcpy(dst,src,n)
 *   return 0;
 *
 * Register roles at the call: $a0 = a1 (set at 0x184A8), $a1 = (a3<<2)+a2 (delay
 * slot `addu $a1,$a3,$v1` with $v1 = a2), $a2 = a4 (set at 0x184A0). As in
 * func_00118438 the callee's result is dropped and both `return 0` sites share
 * the `.L001184D4` `daddu $v0,$zero,$zero` block, so the call is a void
 * statement.
 * MATCH GUESS: cc=296 (delay slots filled)
 */
int func_0012821C(int dst, int src, int n);

int func_00118490(int *p, int a1, int a2, int a3, int a4) {
    int lim;

    if (a1 == 0)
        return 0;
    lim = p[12] - (a3 << 2);
    if (a4 < 0 || lim < a4)
        return -0x21F;
    func_0012821C(a1, (a3 << 2) + a2, a4);
    return 0;
}
