/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 10 [cc=296, default].
 * inf predicate; the negu/or/srl idiom is not the plain x!=0 shape.
 * The original .s stays in the build (asm/cod/02F9B8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/02F9B8.s -> func_0012F9B8 @ 0x0012F9B8 (0x48 bytes, 18 insns)
 * Companion of func_0012FA00 on the same 64-bit bit pattern ($a0 = a double's
 * bits as a 64-bit integer):
 *   lo = (int)x;  hi = (int)(x >> 32);
 *   v  = (hi & 0x7FFFFFFF) | (((unsigned)lo | -(unsigned)lo) >> 31);
 *   d  = 0x7FF00000 - v;
 *   return 1 - (((d | -d) >> 31));         (d == 0  <=> +-Infinity)
 * Both `negu`/`or`/`srl 31` chains are the unsigned "non-zero -> 1" bit trick
 * (a plain `!= 0` would emit `sltu` - cf. matched func_0012E6D0), and the
 * literal `1 - x` explains the `addiu $v0,$zero,1` + `subu`.
 * MATCH GUESS: cc=296 (0x12F8xx/0x12FBxx stdio family is 2.96) */
int func_0012F9B8(long long x) {
    int lo;
    int hi;
    unsigned int v;
    unsigned int d;

    lo = (int)x;
    hi = (int)(x >> 32);
    v = (hi & 0x7FFFFFFF) | (((unsigned int)lo | -(unsigned int)lo) >> 31);
    d = 0x7FF00000 - v;
    return 1 - (int)((d | -d) >> 31);
}
