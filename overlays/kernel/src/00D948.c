/* KERNEL.XFF @ 0x00D948 (64 B) - iosFvecToMmColMvec
 * Evidence: `iosFTOI15Vector(d, s)` with d kept in $s0, then d is copied to a
 * stack union (ld/sd), shifted with MMI `psllw 8` in a volatile asm (the
 * epilogue `ld $ra` stays after the `sq`), and stored back to d.
 * UNCONFIRMED: vector types.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef struct { long lo, hi; } Mvec;
typedef union { Mvec v; u_long128 q; } MvecU;

void iosFTOI15Vector(u_long128 *d, void *s);
void iosFvecToMmColMvec(u_long128 *d, void *s) {
    MvecU u;
    u_long128 r;
    iosFTOI15Vector(d, s);
    u.v = *(Mvec *)d;
    __asm__ __volatile__("psllw %0, %1, 8" : "=r"(r) : "r"(u.q));
    *d = r;
}
