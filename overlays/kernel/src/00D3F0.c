/* KERNEL.XFF @ 0x00D3F0 (12 B) - iosMvecAllOnes
 * Evidence: MMI `pceqw $v0,$0,$0` (all ones) as an asm output, then the compiler's
 * 128-bit `sq` in the delay slot.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosMvecAllOnes(u_long128 *v) {
    u_long128 t;
    __asm__("pceqw %0, $0, $0" : "=r"(t));
    *v = t;
}
