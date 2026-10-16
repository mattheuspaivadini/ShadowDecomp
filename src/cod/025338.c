/* asm/cod/025338.s -> func_00125338 @ 0x00125338 (0x64 bytes, 25 insns)
 *
 * Float-library "subtract": the two 64-bit arguments are decomposed by
 * func_001271B0 (a pointer to the value in, a pointer to the 0x20-byte part
 * block out), the sign word (offset 0x04) of the *second* block is flipped,
 * the blocks are combined by func_00125080 into a third block and that block is
 * converted back by func_001270D8.
 *
 *   sd $a0,0x60(sp); sd $a1,0x68(sp)     ; the two argument homes
 *   func_001271B0(&a0, &pa);             ; pa = sp+0x00, pb = sp+0x20
 *   func_001271B0(&a1, &pb);
 *   pb.sign = pb.sign ^ 1;               ; lw/xori/sw at 0x24 in the jal delay
 *   return func_001270D8(func_00125080(&pa, &pb, &pc));
 *
 * Frame 0x80: pa 0x00, pb 0x20, pc 0x40, argument homes 0x60/0x68, $s0 0x70,
 * $ra 0x78 - identical layout to the matched func_001252E0 (cc=296), and the
 * final call is a framed `jal` + epilogue, exactly as in 0252E0.
 * MATCH GUESS: cc=296 */
struct D25768 {
    int type;                       /* 0x00 */
    int sign;                       /* 0x04 */
    int exp;                        /* 0x08 */
    int pad0C;                      /* 0x0C */
    unsigned long long mant;        /* 0x10 */
    unsigned long long pad18;       /* 0x18 */
};

int __unpack_d(long long *in, struct D25768 *out);
struct D25768 *func_00125080(struct D25768 *a, struct D25768 *b,
                             struct D25768 *c);
int __pack_d(void *buf);

int dpsub(long long a0, long long a1) {
    struct D25768 pa;
    struct D25768 pb;
    struct D25768 pc;

    __unpack_d(&a0, &pa);
    __unpack_d(&a1, &pb);
    pb.sign ^= 1;
    return __pack_d(func_00125080(&pa, &pb, &pc));
}
