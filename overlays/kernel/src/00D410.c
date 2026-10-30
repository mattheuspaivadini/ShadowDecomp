/* KERNEL.XFF @ 0x00D410 (60 B) - iosAddMvec
 * Evidence: both 128-bit operands are copied to stack unions, loaded with `lq`,
 * combined by MMI `paddw` (per-word add) in a volatile asm, and the result is
 * stored with `sq`. A non-volatile asm changes the operand allocation, so the
 * volatile form is the one that reproduces the image. UNCONFIRMED: parameter
 * names (types follow the 128-bit MMI data).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosAddMvec(u_long128 *d, MV *a, MV *b) {
    MV x = *a;
    MV y = *b;
    u_long128 r;

    __asm__ __volatile__("paddw %0, %1, %2" : "=r"(r) : "r"(x.q), "r"(y.q));
    *d = r;
}
