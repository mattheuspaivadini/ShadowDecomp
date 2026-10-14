/* asm/cod/0252E0.s -> func_001252E0 @ 0x001252E0 (0x58 bytes, 22 insns)
 *
 * Double "add" helper of the func_00127xxx float library. Both 64-bit
 * arguments are decomposed by func_001271B0 (pointer to the value in, pointer
 * to the 0x20-byte part block out), the two part blocks are combined by
 * func_00125080 into a third block (its result pointer is returned in $v0), and
 * that block is converted back by func_001270D8.
 *
 * Frame 0x80: pa (0x00) + pb (0x20) + pc (0x40) + the two argument homes
 * (0x60/0x68, `sd $a0`/`sd $a1`) + $s0 (0x70) + $ra (0x78). The two sub-blocks
 * are 0x20 apart and the two saves are 8 apart - the 8-byte-packed stack-slot
 * layout of the cc=296 generation (the matched sibling 025768 is cc=296 and has
 * the identical prologue/store order).
 * MATCH GUESS: cc=296 */
struct D25768 {
    int type;                       /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    unsigned long long mant;        /* 0x10 */
    unsigned long long pad18;       /* 0x18 */
};

int func_001271B0(long long *in, struct D25768 *out);
struct D25768 *func_00125080(struct D25768 *a, struct D25768 *b,
                             struct D25768 *c);
int func_001270D8(void *buf);

int func_001252E0(long long a0, long long a1) {
    struct D25768 pa;
    struct D25768 pb;
    struct D25768 pc;

    func_001271B0(&a0, &pa);
    func_001271B0(&a1, &pb);
    return func_001270D8(func_00125080(&pa, &pb, &pc));
}
