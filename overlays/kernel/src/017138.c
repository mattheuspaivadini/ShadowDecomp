/* KERNEL.XFF @ 0x017138 (492 B) - gsRegEnd
 * Evidence: closes the GIF register packet of the path-1 packet context
 * (`.data+0x664`, reloaded through the symbol between stores because a store
 * through the context pointer may alias the slot). The `.data` base is
 * `lui t7,%hi` + two independent `addiu ...,%lo` (one for the short-lived
 * pre-call base in t6, one for the callee-saved base in s0), i.e. the source
 * never keeps a single `&ctx` value alive. With error == 0: n =
 * (cur - reg) >> 4 stored at +0x14, nloop = n - 1 at +0x18; when nloop > 0 the
 * two qwords at `reg` are zeroed (`por`/`sq`) and the GIF tag is patched -
 * FLG cleared (0xF3FF...), PRE cleared (0xFFFFBFFF...), EOP set (0x8000),
 * NREG = 1 (0x1000000000000000), REGS nibble0 = 0xE, NLOOP = nloop & 0x7FFF -
 * plus `*(u32*)(reg-4) = n | 0x50000000` and `*(u32*)(reg-8) = 0x10000000`;
 * otherwise cur = tag. Then: error -> cur = 0 and return; count =
 * ((cur - top) >> 4) - 1 at +0x10; the packet is emitted only when
 * count >= 2 (`top` tag = count | 0x60000000, iosSetPacketPtrPath1(cur),
 * iosDlChainTailCurrent(top)); finally cur = 0 on every path.
 * The `if (count >= 2) {...} else cur = 0` duplication is what makes both
 * early exits compile to `bnel ... ; sw zero,0xC(ctx)` (a single
 * `if (count < 2) { cur = 0; return; }` inverts the second branch and costs
 * two extra words). Build: -G0 -fno-strict-aliasing (also -g0 identical).
 * UNCONFIRMED: field names, the meaning of 0x10000000 / 0x50000000 / 0x60000000.
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

void gsRegEnd(void) {
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
