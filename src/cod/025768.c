/* asm/cod/025768.s -> func_00125768 @ 0x00125768 (0x4C bytes, 19 insns)
 *
 * Double comparison helper of the func_00127xxx float library: the two 64-bit
 * arguments are decomposed by func_001271B0 (a pointer to the value in, a
 * pointer to the part block out) and the two part blocks are then compared by
 * func_00127270, whose result is returned.
 *
 * Both arguments are 8 bytes each and are spilled with `sd` because their
 * address is taken. The frame is exactly 0x60: block A at 0x00, block B at
 * 0x20 (so each part block is 0x20 bytes), the two argument homes at 0x40/0x48,
 * $s0 at 0x50 and $ra at 0x58 - note the `sd $s0` around the 0x20 block word
 * (the address is kept across the calls).
 * The part block layout follows func_001271B0: type 0x00, sign 0x04, exponent
 * 0x08, and a 64-bit mantissa at 0x10 (the 0x18 word is padding nobody reads).
 * UNCONFIRMED: `double` vs `long long` for the two arguments (both are 8-byte
 * single-register values here and the callee only reads the bits).
 * MATCH GUESS: cc=29
 */
struct D25768 {
    int type;                       /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    unsigned long long mant;        /* 0x10 */
    unsigned long long pad18;       /* 0x18 */
};

int __unpack_d(long long *in, struct D25768 *out);
int __fpcmp_parts_d(struct D25768 *a, struct D25768 *b);

int dpcmp(long long a0, long long a1) {
    struct D25768 pa;
    struct D25768 pb;

    __unpack_d(&a0, &pa);
    __unpack_d(&a1, &pb);
    return __fpcmp_parts_d(&pa, &pb);
}
