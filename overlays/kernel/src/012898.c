/* KERNEL.XFF @ 0x012898 (84 B) - iosPushDC
 * Evidence: The DC stack slot address is taken before the depth (.data+0x558) is incremented (pointer to stack[depth], depth++, *slot = dc), then iosDlChainTailCurrent(dc) and .data+0x550 = dc.
 */
extern int D_kernel_data_0558;
extern void *D_kernel_bss_1E6C8[];
extern void *D_kernel_data_0550;
void iosDlChainTailCurrent(void *dc);

void iosPushDC(void *dc) {
    void **slot = &D_kernel_bss_1E6C8[D_kernel_data_0558];

    D_kernel_data_0558++;
    *slot = dc;
    iosDlChainTailCurrent(dc);
    D_kernel_data_0550 = dc;
}
