/* KERNEL.XFF @ 0x012980 (28 B) - iosSetCurrentDC
 * Evidence: sibling iosDlChainTailCurrent(.data+0x550). UNCONFIRMED: object name.
 */
extern void *D_kernel_data_0550;
void iosDlChainTailCurrent(void *dc);

void iosSetCurrentDC(void) {
    iosDlChainTailCurrent(D_kernel_data_0550);
}
