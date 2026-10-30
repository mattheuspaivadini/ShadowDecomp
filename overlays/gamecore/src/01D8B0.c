/* GAMECORE.XFF @ 0x01D8B0 (64 B) - opflowCompareOptionData
 * Evidence: 0x20 frame, out slot at sp+0, `jal getOptionDataAdrsAndSize` with
 * `$a0 = $sp`; then `lw .data+0xA2C` non-zero returns 1 (via `bnez` with
 * `$v0 = 1` in the delay slot); otherwise `memcmp(*(.bss+0x4ADC), adrs, size)`
 * with the size loaded from sp+0.
 * UNCONFIRMED: the option block pointers and whether the callee takes more
 * than the out pointer.
 
 */
int getOptionDataAdrsAndSize(void *out);
int memcmp(const void *a, const void *b, unsigned int n);
extern char D_kernel_data_0000[];
extern char D_kernel_bss_0000[];

int opflowCompareOptionData(void) {
    int size;
    void *adrs = getOptionDataAdrsAndSize(&size);

    if (*(int *)(D_kernel_data_0000 + 0xA2C) != 0)
        return 1;
    return memcmp(*(void **)(D_kernel_bss_0000 + 0x4ADC), adrs, size);
}
