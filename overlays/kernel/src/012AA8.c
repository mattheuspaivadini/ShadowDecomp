/* KERNEL.XFF @ 0x012AA8 (92 B) - iosSetDCWithClear
 * Evidence: like iosSetDC, the +0xD0 clear chain is linked only when bit 0 of word +0x170 is set and the second argument is non-zero (beql + beqz).
 */
struct DC {
    char pad[0xD0];
    char clear[0xA0];
    unsigned int flags;
};
void iosDlChainTailCurrent(void *dc);

void iosSetDCWithClear(struct DC *dc, int clear) {
    iosDlChainTailCurrent(dc);
    if ((dc->flags & 1) && clear) {
        iosDlChainTailCurrent(dc->clear);
    }
}
