/* KERNEL.XFF @ 0x012850 (72 B) - iosSetDC
 * Evidence: iosDlChainTailCurrent(dc), then, when bit 0 of word +0x170 is set (the clear-enable bit iosSetDCClearParam writes), a sibling iosDlChainTailCurrent(dc + 0xD0). UNCONFIRMED: layout names.
 */
struct DC {
    char pad[0xD0];
    char clear[0xA0];
    unsigned int flags;
};
void iosDlChainTailCurrent(void *dc);

void iosSetDC(struct DC *dc) {
    iosDlChainTailCurrent(dc);
    if ((dc->flags & 1)) {
        iosDlChainTailCurrent(dc->clear);
    }
}
