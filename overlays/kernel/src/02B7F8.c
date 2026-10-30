/* KERNEL.XFF @ 0x02B7F8 (188 B) - func_02B7F8 (static, no symbol in the shipped .symtab)
 * Evidence: SySex-style parser over the byte buffer at ctx+0x60. Four big-endian
 * fields are assembled byte by byte (lbu/sll/or): w = bytes 4..7, a = bytes 8..9,
 * b = bytes A..B, c = bytes C..D. w must be 6, a must be 0, b must be 1;
 * otherwise -1 is returned (the -1 is materialised once and all failure paths
 * share the epilogue). On success litodp(c) is stored as a dp at +0x38 and the
 * read pointer is advanced by 0xE (bytes 0..3 are the 4-byte header + length),
 * and 0 is returned. The dp store is written *before* the pointer store in the
 * source: the scheduler then emits the pointer store first and the `addiu` that
 * forms it only after the litodp call, which is why the buffer pointer lives in
 * a callee-saved register.
 * UNCONFIRMED: field/parameter semantics (the 6/0/1 magic values and the 0xE
 * advance are read from the instruction stream only).
 */
struct Ctx {
    char pad0[0x38];
    long long dp;
    char pad40[0x60 - 0x40];
    unsigned int msg;
};
long long litodp(int v);

int func_02B7F8(struct Ctx *p) {
    unsigned char *m = (unsigned char *)p->msg;
    int w = (m[4] << 24) | (m[5] << 16) | (m[6] << 8) | m[7];
    int a = (m[8] << 8) | m[9];
    int b = (m[0xA] << 8) | m[0xB];
    int c = (m[0xC] << 8) | m[0xD];
    int ret = -1;

    if (w != 6)
        return ret;
    if (a != 0)
        return ret;
    if (b != 1)
        return ret;
    p->dp = litodp(c);
    p->msg = (unsigned int)(m + 0xE);
    return 0;
}
