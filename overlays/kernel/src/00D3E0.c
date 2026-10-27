/* KERNEL.XFF @ 0x00D3E0 (12 B) - iosMvecZero
 * Evidence: `daddu $v0,$0,$0` (GAS `move`) and the 128-bit `sq $v0,0($a0)` in the
 * delay slot. A plain TImode zero compiles to `por`, so the zero comes from an
 * asm `move` producing a 128-bit value that the compiler stores.
 * UNCONFIRMED: the exact asm text (any form assembling to this daddu matches).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosMvecZero(u_long128 *v) {
    u_long128 t;
    __asm__("move %0, $0" : "=r"(t));
    *v = t;
}
