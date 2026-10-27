/* KERNEL.XFF @ 0x00D400 (16 B) - iosMvecAllOne
 * Evidence: MMI `pceqw` (all ones) then `psrlw 31` (1 per word) in one asm with
 * a 128-bit output; the compiler's `sq` fills the delay slot.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosMvecAllOne(u_long128 *v) {
    u_long128 t;
    __asm__("pceqw %0, $0, $0\n"
            "psrlw %0, %0, 31" : "=r"(t));
    *v = t;
}
