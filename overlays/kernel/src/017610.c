/* KERNEL.XFF @ 0x017610 (612 B) - gsReglistEnd
 * Evidence: same path-1 packet context (`.data+0x664`) as gsRegEnd, with the
 * `.data` base again split into `lui t9,%hi` + two `addiu ...,%lo` (t8 for the
 * short-lived base, s0 for the callee-saved one). `daddu a2,a0,zero` in the
 * error-branch delay slot keeps the single int argument, which ends up as
 * `(arg & 0x7FF) << 47` in the PRIM field. With error == 0: n =
 * (cur - reg) >> 4 at +0x14, nloop = (n - 1) / 3 at +0x18 (a real `div` with
 * `li 3` + the zero-divisor guard `beql a0,zero ; break 7`). When nloop > 0:
 * zero both tag qwords (`por`/`sq`), then FLG cleared (0xF3FF...),
 * 0x400000000000 ORed, EOP 0x8000 ORed, NREG = 3 (0x3000000000000000 after
 * masking 0x0FFF...), REGS nibbles 2/1/1 on the second qword
 * (masks ~0xF, ~0xF0, ~0xF00), NLOOP = (nloop * 3) & 0x7FFF, and finally
 * 0xFC007FFFFFFFFFFF masked plus the PRIM field; else cur = tag. Tail is the
 * gsRegEnd one: error -> cur = 0 (fresh `lw v0,0x664(t9)`), count at +0x10,
 * count >= 2 gate, top tag = count | 0x60000000, iosSetPacketPtrPath1 /
 * iosDlChainTailCurrent, cur = 0 on every path.
 * Build: -G0 -fno-strict-aliasing.
 * UNCONFIRMED: field names, the argument name `prim`, and the exact GIF field
 * names behind 0x400000000000 / 0x8000 / 0x3000000000000000 / 0xFC00... .
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct GsPacketCtx {
    unsigned long *top;
    unsigned long *tag;
    unsigned long *reg;
    unsigned long *cur;
    int count;
    int n;
    int nloop;
    int error;
};

extern struct GsPacketCtx *D_kernel_data_0664;
void iosSetPacketPtrPath1(unsigned long *p);
void iosDlChainTailCurrent(unsigned long *p);

void gsReglistEnd(int prim) {
    if (D_kernel_data_0664->error == 0) {
        D_kernel_data_0664->n =
            ((unsigned int)D_kernel_data_0664->cur - (unsigned int)D_kernel_data_0664->reg) >> 4;
        D_kernel_data_0664->nloop = (D_kernel_data_0664->n - 1) / 3;
        if (D_kernel_data_0664->nloop > 0) {
            *(u_long128 *)D_kernel_data_0664->reg = 0;
            D_kernel_data_0664->reg[0] &= 0xF3FFFFFFFFFFFFFFUL;
            D_kernel_data_0664->reg[0] |= 0x400000000000UL;
            D_kernel_data_0664->reg[0] |= 0x8000;
            D_kernel_data_0664->reg[0] =
                (D_kernel_data_0664->reg[0] & 0x0FFFFFFFFFFFFFFFUL) | 0x3000000000000000UL;
            D_kernel_data_0664->reg[1] = (D_kernel_data_0664->reg[1] & ~0xF) | 0x2;
            D_kernel_data_0664->reg[1] = (D_kernel_data_0664->reg[1] & ~0xF0) | 0x10;
            D_kernel_data_0664->reg[1] = (D_kernel_data_0664->reg[1] & ~0xF00) | 0x400;
            D_kernel_data_0664->reg[0] = (D_kernel_data_0664->reg[0] & 0xFFFFFFFFFFFF8000UL) |
                                         ((D_kernel_data_0664->nloop * 3) & 0x7FFF);
            D_kernel_data_0664->reg[0] = (D_kernel_data_0664->reg[0] & 0xFC007FFFFFFFFFFFUL) |
                                         (((unsigned long)(prim & 0x7FF)) << 47);
        } else {
            D_kernel_data_0664->cur = D_kernel_data_0664->tag;
        }
    }
    if (D_kernel_data_0664->error != 0) {
        D_kernel_data_0664->cur = 0;
        return;
    }
    D_kernel_data_0664->count =
        (((unsigned int)D_kernel_data_0664->cur - (unsigned int)D_kernel_data_0664->top) >> 4) - 1;
    if (D_kernel_data_0664->count >= 2) {
        *(unsigned long *)D_kernel_data_0664->top = D_kernel_data_0664->count | 0x60000000;
        iosSetPacketPtrPath1(D_kernel_data_0664->cur);
        iosDlChainTailCurrent(D_kernel_data_0664->top);
        D_kernel_data_0664->cur = 0;
    }
    else
        D_kernel_data_0664->cur = 0;
}
