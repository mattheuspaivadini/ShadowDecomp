/* KERNEL.XFF @ 0x00D490 (60 B) - iosClampUW_AddMvec
 * Evidence: same stack-union + `lq` operands as iosAddMvec, with MMI `padduw`
 * (unsigned saturating per-word add) in a volatile asm and `sq` of the result.
 * UNCONFIRMED: parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosClampUW_AddMvec(u_long128 *d, MV *a, MV *b) {
    MV x = *a;
    MV y = *b;
    u_long128 r;

    __asm__ __volatile__("padduw %0, %1, %2" : "=r"(r) : "r"(x.q), "r"(y.q));
    *d = r;
}
