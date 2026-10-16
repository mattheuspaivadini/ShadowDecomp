/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 12 [cc=296].
 * R1 wave3e: two 64-bit literals as ori+dsll32; loop rotation
 * The original .s stays in the build (asm/cod/02F790.s); this C
 * draft (Session 8) is kept for the record. */
extern long long __mprec_tens[];   /* lui/%lo 0x00139B60: 8-byte entries */
extern long long dpmul(long long a0);

long long _mprec_log10(int a0) {
    long long r;

    r = 0xFFC0LL << 46;
    if (a0 < 0x18)
        return __mprec_tens[a0];
    while (a0 > 0) {
        r = dpmul(0x8048LL << 47);
        a0--;
    }
    return r;
}
/* func_0012F790 */
