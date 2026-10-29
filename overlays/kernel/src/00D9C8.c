/* KERNEL.XFF @ 0x00D9C8 (124 B) - iosSwClipMvec
 * Evidence: three 128-bit vectors copied through a 0x30-byte stack union (ld/sd pairs, then lq), then MMI saturating word arithmetic: ones = pceqw(0,0), hi = ones >> 1 (0x7FFFFFFF), lo = hi + (ones >> 31) (0x80000000), r = ((((a - b) +s hi) -s hi) +s b -s c +s lo -s lo) +s c, stored with sq. The add/sub pairs with the same bound clamp a-b into [lo, hi]. Same operand idiom as iosClampSW_AddMvec.
 * Lever: ONE volatile asm block with the three lq operands as inputs (+r on the first) and $8-$10 clobbered; separate asm statements interleave the lq loads and miss the image order. UNCONFIRMED: parameter names.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
typedef union { long long l[2]; u_long128 q; } MV;

void iosSwClipMvec(u_long128 *d, MV *a, MV *b, MV *c) {
    MV x = *a;
    MV y = *b;
    MV z = *c;
    u_long128 r = x.q;

    __asm__ __volatile__(
        "pceqw $8, $0, $0
"
        "psrlw $9, $8, 1
"
        "psrlw $10, $8, 31
"
        "paddw $10, $9, $10
"
        "psubsw %0, %0, %1
"
        "paddsw %0, %0, $9
"
        "psubsw %0, %0, $9
"
        "paddsw %0, %0, %1
"
        "psubsw %0, %0, %2
"
        "paddsw %0, %0, $10
"
        "psubsw %0, %0, $10
"
        "paddsw %0, %0, %2
"
        : "+r"(r) : "r"(y.q), "r"(z.q) : "$8", "$9", "$10");
    *d = r;
}
