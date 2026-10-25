/* KERNEL.XFF @ 0x006068 (24 B) - iosSrpWaitDMA
 * Evidence: frame, a `sync` with nothing else, then sibling `j iosWaitDMA`.
 */
void iosWaitDMA(void);
void iosSrpWaitDMA(void) {
    __asm__ volatile ("sync");
    iosWaitDMA();
}
