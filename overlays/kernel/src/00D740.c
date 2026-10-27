/* KERNEL.XFF @ 0x00D740 (48 B) - iosSwClip255Mvec
 * Evidence: one asm block: builds 0x7FFFFF00-style bounds in $t0..$t3 with
 * pceqw/psrlw/psubsw/paddw and clamps the vector by saturating add/sub pairs;
 * the operand is read-modify-write in $v0 without being loaded first (an
 * uninitialised "+r" variable in the original), then the compiler's `sq`
 * stores it. UNCONFIRMED: the intended input (none is passed).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void iosSwClip255Mvec(u_long128 *d) {
    u_long128 r;
    __asm__(
        "pceqw $8, $0, $0\n"
        "psrlw $9, $8, 23\n"
        "psrlw $11, $8, 1\n"
        "psubsw $9, $11, $9\n"
        "paddsw %0, %0, $9\n"
        "psrlw $10, $8, 31\n"
        "psubsw %0, %0, $9\n"
        "paddw $10, $11, $10\n"
        "paddsw %0, %0, $10\n"
        "psubsw %0, %0, $10\n"
        : "+r"(r) : : "$8", "$9", "$10", "$11");
    *d = r;
}
