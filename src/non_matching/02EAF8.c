/* asm/cod/02EAF8.s -> func_0012EAF8 @ 0x0012EAF8 (0x80 bytes, 32 insns)
 *
 * Binary-search count-leading-zeros for a 32-bit value (returns 32 for 0):
 *   n = 0;
 *   if ((x & 0xFFFF0000) == 0) { n  = 16; x <<= 16; }
 *   if ((x & 0xFF000000) == 0) { n +=  8; x <<=  8; }
 *   if ((x & 0xF0000000) == 0) { n +=  4; x <<=  4; }
 *   if ((x & 0xC0000000) == 0) { n +=  2; x <<=  2; }
 *   if ((int)x < 0) return n;             (top bit now set)
 *   if ((x & 0x40000000) == 0) return 32; (x was zero)
 *   return n + 1;
 * The `daddu $a1,$zero,$zero` in the first bnez delay slot is the `n = 0`
 * initialisation; each later test has its next mask materialised in the delay
 * slot (0xF0000000, 0xC0000000).
 *
 * STATUS (2026-10-14, Session 4 step 3): NON_MATCHING. The first 27 of the 32
 * instructions and the whole register assignment (x=$4, n=$5) are reproduced at
 * -O2; the only difference is the final `if`: the original branches
 * (`and v1,x,0x40000000; beqz v1,L; addiu v0,0,0x20; move v0,n`), our
 * ee-gcc2.96 if-converts it into `li v0,0x20; movn v0,n,v1`. No source spelling
 * tried (separate returns, explicit result variable `v`, inverted condition)
 * or -O level suppresses the conversion, and there is no `-fno-if-conversion`
 * in this revision; ee-gcc2.9-991111-01 is worse (23 insns differ). Another
 * "revision/codegen shape" entry — see docs/compiler.md §2.2, where it is the
 * ≥30-instruction candidate and a 30-vs-5-instruction -O1/-O2 sensitivity data
 * point that still does not match at any level.
 */
int func_0012EAF8(unsigned int x) {
    int n = 0;

    if ((x & 0xFFFF0000U) == 0) { n = 0x10; x <<= 16; }
    if ((x & 0xFF000000U) == 0) { n += 0x8; x <<= 8; }
    if ((x & 0xF0000000U) == 0) { n += 0x4; x <<= 4; }
    if ((x & 0xC0000000U) == 0) { n += 0x2; x <<= 2; }
    if ((int)x < 0)
        return n;
    n += 1;
    if ((x & 0x40000000U) != 0)
        return n;
    return 0x20;
}
