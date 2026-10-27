/* KERNEL.XFF @ 0x0128F0 (80 B) - iosPopDC
 * Evidence: --depth (.data+0x558), then current = stack[depth - 1] from the .bss+0x1E6C8 array (iosPushDC stores at stack[depth++]); iosDlChainTailCurrent(current) and .data+0x550 = current. UNCONFIRMED: names.
 */
extern int D_kernel_data_0558;
extern void *D_kernel_bss_1E6C8[];
extern void *D_kernel_data_0550;
void iosDlChainTailCurrent(void *dc);

void iosPopDC(void) {
    void *dc;

    D_kernel_data_0558--;
    dc = D_kernel_bss_1E6C8[D_kernel_data_0558 - 1];
    iosDlChainTailCurrent(dc);
    D_kernel_data_0550 = dc;
}
