/* KERNEL.XFF @ 0x00D8A8 (40 B) - iosSWToMmColMvec
 * Evidence: the 16-byte source is copied to an aligned stack union with two
 * `ld`/`sd` pairs (so its C type is 8-byte aligned, not a 16-byte-aligned
 * quad), reloaded with `lq` as the operand of one MMI instruction in an asm,
 * and the result goes out through the compiler's `sq`. UNCONFIRMED: the vector
 * type (written as two longs) and parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec v; u_long128 q; } MvecU;
void iosSWToMmColMvec(u_long128 *d, Mvec *s) {
    MvecU u;
    u_long128 r;
    u.v = *s;
    __asm__("psllw %0, %1, 23" : "=r"(r) : "r"(u.q));
    *d = r;
}
