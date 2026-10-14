/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 12 [cc=296, default].
 * NaN predicate; same idiom caveat as 02F9B8.
 * The original .s stays in the build (asm/cod/02FA00.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/02FA00.s -> func_0012FA00 @ 0x0012FA00 (0x3C bytes, 15 insns)
 * Predicate on the raw 64-bit bit pattern in $a0 (a double's bits, passed as a
 * 64-bit integer - the caller in 0x00129xxx does `ld $a0, ...` right before):
 *   lo = (int)x;  hi = (int)(x >> 32);
 *   v  = (hi & 0x7FFFFFFF) | (((unsigned)lo | -(unsigned)lo) >> 31);
 *   return (int)(0x7FF00000 - v) < 0;      (v > 0x7FF00000  <=> NaN)
 * The two `negu`/`or`/`srl 31` chains are the "is this word non-zero, as an
 * unsigned 0/1" bit trick (NOT a plain `x != 0`, which emits `sltu` in this
 * codebase - see the matched func_0012E6D0); the `negu` + `srl` mean the
 * operands are unsigned.  Trailing `subu`+`srl 31` = the sign of the
 * 0x7FF00000 gap.
 * MATCH GUESS: cc=296 (0x12F8xx/0x12FBxx stdio family is 2.96) */
int func_0012FA00(long long x) {
    int lo;
    int hi;
    unsigned int v;

    lo = (int)x;
    hi = (int)(x >> 32);
    v = (hi & 0x7FFFFFFF) | (((unsigned int)lo | -(unsigned int)lo) >> 31);
    return (int)(0x7FF00000 - v) < 0;
}
