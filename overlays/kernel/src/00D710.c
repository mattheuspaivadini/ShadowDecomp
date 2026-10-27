/* KERNEL.XFF @ 0x00D710 (44 B) - iosIColAddVec
 * Evidence: both ints are stored to separate 16-byte stack unions, reloaded with
 * `lq`, combined by MMI `paddub` (per-byte unsigned saturating add) in an asm,
 * and the low word of the result is stored to *d. UNCONFIRMED: parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { int i; u_long128 q; } ColU;
void iosIColAddVec(int *d, int a, int b) {
    ColU ua, ub, ur;
    ua.i = a;
    ub.i = b;
    __asm__("paddub %0, %1, %2" : "=r"(ur.q) : "r"(ua.q), "r"(ub.q));
    *d = ur.i;
}
