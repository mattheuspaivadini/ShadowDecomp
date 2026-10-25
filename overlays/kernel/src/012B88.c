/* KERNEL.XFF @ 0x012B88 (108 B) - iosPushDCWithClear
 * Evidence: The DC stack slot address is taken before the depth (.data+0x558) is incremented (pointer to stack[depth], depth++, *slot = dc), then iosDlChainTailCurrent(dc) and .data+0x550 = dc. The clear chain (dc + 0xD0) is linked when bit 0 of word +0x170 is set.
 */
struct DC {
    char pad[0xD0];
    char clear[0xA0];
    unsigned int flags;
};
extern int D_kernel_data_0558;
extern void *D_kernel_bss_1E6C8[];
extern void *D_kernel_data_0550;
void iosDlChainTailCurrent(void *dc);

void iosPushDCWithClear(struct DC *dc) {
    void **slot = &D_kernel_bss_1E6C8[D_kernel_data_0558];

    D_kernel_data_0558++;
    *slot = dc;
    iosDlChainTailCurrent(dc);
    if (dc->flags & 1) {
        iosDlChainTailCurrent(dc->clear);
    }
    D_kernel_data_0550 = dc;
}
