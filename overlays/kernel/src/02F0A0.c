/* KERNEL.XFF @ 0x02F0A0 (132 B) - func_02F0A0 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing]
 * Evidence: ch < 4 guard (sltiu/beqz to the shared jr ra); record = .bss+0x9BFD8 + ch*0x1D4;
 * loads +0x1AC, +0x1B0, +0x1B4, +0x1C0 (index into a u16 table, lhu, hi/lo bytes);
 * +0x1B8 = a*b*hi/127, +0x1BC = a*c*lo/127. The single hoisted break-7 zero check on a
 * register holding 127 plus a dead second `li 127` prove the divisor arrives through an
 * inlined helper's parameter (two inline expansions, second check CSE'd away).
 * Lever: static inline v*m/d helper; statement order l, p, r.
 * UNCONFIRMED: helper name, struct field names/meanings, pan_tbl name and element type.
 */

struct PcmInput {
    char pad000[0x1AC];
    int a1ac;
    int b1b0;
    int c1b4;
    int outL;
    int outR;
    int panIdx;
    char pad1C4[0x10];
};
extern struct PcmInput D_kernel_bss_9BFD8[4];
extern unsigned short pan_tbl[];

/* UNCONFIRMED: inline helper, not present in the image */
static inline int muldiv(int v, int m, int d) { return v * m / d; }

void func_02F0A0(unsigned int ch) {
    struct PcmInput *in;
    int a, l, r;
    unsigned int p;
    if (ch < 4) {
        in = &D_kernel_bss_9BFD8[ch];
        a = in->a1ac;
        l = a * in->b1b0;
        p = pan_tbl[in->panIdx];
        r = a * in->c1b4;
        in->outL = muldiv(l, p >> 8, 127);
        in->outR = muldiv(r, p & 0xFF, 127);
    }
}
