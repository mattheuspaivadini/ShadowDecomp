/* KERNEL.XFF @ 0x00BC38 (48 B) - CompareString16
 * Evidence: two `lq` of the 16-byte strings, `pxor`, `sq` to a stack quad, then
 * the two halves are ORed and sign-extended to int (0 = equal). The lq/pxor/sq
 * are MMI so they are an inline asm block; the reduction is compiled C.
 * UNCONFIRMED: the parameter types.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
int CompareString16(u_long128 *a, u_long128 *b) {
    unsigned long d[2];
    __asm__ __volatile__(
        "lq $8, 0(%1)\n"
        "lq $9, 0(%2)\n"
        "pxor $10, $8, $9\n"
        "sq $10, 0(%0)\n" : : "r"(d), "r"(a), "r"(b) : "$8", "$9", "$10", "memory");
    return d[0] | d[1];
}
