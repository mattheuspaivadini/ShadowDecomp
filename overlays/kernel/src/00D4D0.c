/* KERNEL.XFF @ 0x00D4D0 (60 B) - iosSubMvec
 * Evidence: same stack-union + `lq` operands as iosAddMvec, with MMI `psubw`
 * (per-word subtract) in a volatile asm and `sq` of the result.
 * UNCONFIRMED: parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosSubMvec(u_long128 *d, MV *a, MV *b) {
    MV x = *a;
    MV y = *b;
    u_long128 r;

    __asm__ __volatile__("psubw %0, %1, %2" : "=r"(r) : "r"(x.q), "r"(y.q));
    *d = r;
}
