/* KERNEL.XFF @ 0x00D770 (116 B) - iosIColAddVecXYZ
 * Evidence: the shipped code builds the packed colour with read-modify-write
 * masks (~0xFF / ~0xFF00 / ~0xFF0000 then |= 0xFF000000) on a value that is
 * read before it is written, which is what `col &= mask; col |= field;` pairs
 * produce; the two 32-bit colours go into 16-byte stack unions and are added
 * with MMI paddub in a volatile asm (iosIColAddVec pattern), the low word
 * going to *d. UNCONFIRMED: the uninitialised `col` (the shipped code relies
 * on the same undefined read) and the parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { int i; u_long128 q; } ColU;

void iosIColAddVecXYZ(int *d, int c, int x, int y, int z) {
    ColU ua, ub, ur;
    int col;

    col &= ~0xFF;
    col |= x & 0xFF;
    col &= ~0xFF00;
    col |= (y & 0xFF) << 8;
    col &= ~0xFF0000;
    col |= (z & 0xFF) << 16;
    col |= 0xFF000000;
    ua.i = c;
    ub.i = col;
    __asm__("paddub %0, %1, %2" : "=r"(ur.q) : "r"(ua.q), "r"(ub.q));
    *d = ur.i;
}
