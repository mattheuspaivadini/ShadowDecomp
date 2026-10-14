/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 8 [cc=29, default].
 * bounded memcpy-in; scheduling differs.
 * The original .s stays in the build (asm/cod/018438.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/018438.s -> func_00118438 @ 0x00118438 (0x54 bytes, 21 insns)
 *
 * Bounded copy *into* the record buffer (p->field30 is its size in bytes):
 *
 *   if (a3 == 0) return 0;                    ; null source ( $a1 <- $a3 )
 *   lim = p->field30 - (a2 << 2);             ; lw 0x30($a0) ; sll $a0,$a2,2
 *   if (a4 < 0 || lim < a4) return -0x21F;    ; bltz + slt ; addiu $v0,-0x21F
 *   func_0012821C((a2 << 2) + a1, a3, a4);    ; memcpy(dst,src,n)
 *   return 0;
 *
 * Register roles at the call: $a0 = (a2<<2)+a1 (delay slot `addu $a0,$a0,$v1`),
 * $a1 = a3 (the reassignment at 0x18444), $a2 = a4 - so the callee is
 * func_0012821C(dst, src, n) (3 arguments, as in its own asm/cod/02821C.s:
 * a0=dst, a1=src, a2=n, returns dst).
 *
 * The callee's result is discarded and *both* `return 0` sites share the
 * `.L0011847C: daddu $v0,$zero,$zero` block - the `beqz` on a3 targets it and
 * the `jal` falls straight into it, which is why the result cannot be returned
 * (`return func_0012821C(...)` would leave $v0 untouched after the jal).
 * MATCH GUESS: cc=296 (delay slots filled)
 */
int func_0012821C(int dst, int src, int n);

int func_00118438(int *p, int a1, int a2, int a3, int a4) {
    int lim;

    if (a3 == 0)
        return 0;
    lim = p[12] - (a2 << 2);
    if (a4 < 0 || lim < a4)
        return -0x21F;
    func_0012821C((a2 << 2) + a1, a3, a4);
    return 0;
}
