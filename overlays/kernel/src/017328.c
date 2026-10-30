/* KERNEL.XFF @ 0x017328 (508 B) - gsRegEndWithPtr
 * Evidence: byte-identical body and prologue to gsRegEnd (0x017138): the same
 * `lui t9/t7 + 2x addiu` split base, n = (cur - reg) >> 4 at +0x14,
 * nloop = n - 1 at +0x18, the FIFO tag patch (FLG/PRE cleared, EOP 0x8000,
 * NREG = 1, REGS nibble0 = 0xE, NLOOP), *(u32*)(reg-4) = n | 0x50000000 and
 * *(u32*)(reg-8) = 0x10000000, the cur = tag reset when nloop <= 0, and the
 * count = ((cur - top) >> 4) - 1 / count >= 2 gate with count | 0x60000000 on
 * `top`. Difference is only the result: the success path returns the packet
 * top (`lw v1,0(s0) ; b epilogue ; lw v0,0(v1)`) and both early exits return 0
 * (`daddu v0,zero,zero`); the fail branch still stores cur = 0 in its delay
 * slot. Build: -G0 -fno-strict-aliasing.
 * UNCONFIRMED: field names and the 0x10000000/0x50000000/0x60000000 meanings;
 * the return value is only evidenced as ctx->top.
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

unsigned long *gsRegEndWithPtr(void) {
    if (D_kernel_data_0664->error == 0) {
        D_kernel_data_0664->n =
            ((unsigned int)D_kernel_data_0664->cur - (unsigned int)D_kernel_data_0664->reg) >> 4;
        D_kernel_data_0664->nloop = D_kernel_data_0664->n - 1;
        if (D_kernel_data_0664->nloop > 0) {
            *(u_long128 *)D_kernel_data_0664->reg = 0;
            D_kernel_data_0664->reg[0] &= 0xF3FFFFFFFFFFFFFFUL;
            D_kernel_data_0664->reg[0] &= 0xFFFFBFFFFFFFFFFFUL;
            D_kernel_data_0664->reg[0] |= 0x8000;
            D_kernel_data_0664->reg[0] =
                (D_kernel_data_0664->reg[0] & 0x0FFFFFFFFFFFFFFFUL) | 0x1000000000000000UL;
            D_kernel_data_0664->reg[1] = (D_kernel_data_0664->reg[1] & ~0xF) | 0xE;
            D_kernel_data_0664->reg[0] = (D_kernel_data_0664->reg[0] & 0xFFFFFFFFFFFF8000UL) |
                                         (D_kernel_data_0664->nloop & 0x7FFF);
            *(unsigned int *)((char *)D_kernel_data_0664->reg - 4) =
                D_kernel_data_0664->n | 0x50000000;
            *(unsigned int *)((char *)D_kernel_data_0664->reg - 8) = 0x10000000;
        } else {
            D_kernel_data_0664->cur = D_kernel_data_0664->tag;
        }
    }
    if (D_kernel_data_0664->error != 0) {
        D_kernel_data_0664->cur = 0;
        return 0;
    }
    D_kernel_data_0664->count =
        (((unsigned int)D_kernel_data_0664->cur - (unsigned int)D_kernel_data_0664->top) >> 4) - 1;
    if (D_kernel_data_0664->count >= 2) {
        *(unsigned long *)D_kernel_data_0664->top = D_kernel_data_0664->count | 0x60000000;
        iosSetPacketPtrPath1(D_kernel_data_0664->cur);
        iosDlChainTailCurrent(D_kernel_data_0664->top);
        D_kernel_data_0664->cur = 0;
        return D_kernel_data_0664->top;
    }
    else {
        D_kernel_data_0664->cur = 0;
        return 0;
    }
}
