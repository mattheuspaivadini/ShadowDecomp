/* KERNEL.XFF @ 0x012950 (28 B) - iosSetRootDC
 * Evidence: sibling iosDlChainTailCurrent(.data+0x554). UNCONFIRMED: object name.
 */
extern void *D_kernel_data_0554;
void iosDlChainTailCurrent(void *dc);

void iosSetRootDC(void) {
    iosDlChainTailCurrent(D_kernel_data_0554);
}
