/* KERNEL.XFF @ 0x016EE0 (40 B) - iStart
 * Evidence: calls the hook at .data+0x624 when non-NULL (jalr). UNCONFIRMED: name.
 */
extern void (*D_kernel_data_0624)(void);
void iStart(void) {
    if (D_kernel_data_0624 != 0) {
        D_kernel_data_0624();
    }
}
