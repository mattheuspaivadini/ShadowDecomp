/* KERNEL.XFF @ 0x0129A0 (200 B) - iosResetDC   [MATCH: -G0 -fno-strict-aliasing]
 * Evidence: .data+0x554 = dc; .data+0x558 = 0; iosDlPushLayer(0) with the zero
 * store in its delay slot; s1 = &.data+0x558 held across the calls.  Bit 0 of
 * dc+0x170 selects between two copies of { D_bss_1E6C8[k] = dc; k = k + 1;
 * iosDlChainTailCurrent(dc); }, the taken one additionally retesting dc+0x170
 * before chaining dc+0xD0.  Tail: .data+0x550 = dc; `j iosDlPopLayer`.
 * Lever (g11 #2, reused): `do { ... } while (0);` around the final store with
 * the `return` outside.  Without it sched2 sinks `ld $s1` above the store and
 * restores s1,ra,s0; with the block boundary the epilogue is the image's
 * `sw`, `ld s0`, `ld s1`, `ld ra` (save order) exactly.  -g0, -O1/-O3,
 * -fno-schedule-insns(2), volatile stores and a memory-clobber asm all fail.
 * UNCONFIRMED: parameter/return types, DC field 0x170.
 */
extern int D_kernel_data_550;
extern int D_kernel_data_554;
extern int D_kernel_data_558;
extern void *D_kernel_bss_1E6C8[];

extern void iosDlPushLayer(int layer);
extern void iosDlChainTailCurrent(void *dc);
extern int iosDlPopLayer(void);

int iosResetDC(void *dc)
{
    D_kernel_data_554 = dc;
    D_kernel_data_558 = 0;
    iosDlPushLayer(0);

    if (((int *)dc)[0x5C] & 1) {
        D_kernel_bss_1E6C8[D_kernel_data_558] = dc;
        D_kernel_data_558 = D_kernel_data_558 + 1;
        iosDlChainTailCurrent(dc);
        if (((int *)dc)[0x5C] & 1)
            iosDlChainTailCurrent((char *)dc + 0xD0);
    } else {
        D_kernel_bss_1E6C8[D_kernel_data_558] = dc;
        D_kernel_data_558 = D_kernel_data_558 + 1;
        iosDlChainTailCurrent(dc);
    }
    do {
        D_kernel_data_550 = dc;
    } while (0);
    return iosDlPopLayer();
}
