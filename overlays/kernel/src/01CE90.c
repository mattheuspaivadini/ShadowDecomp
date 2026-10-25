/* KERNEL.XFF @ 0x01CE90 (28 B) - InitSubThread
 * Evidence: sibling isysInitGroup(&.data+0xA18). UNCONFIRMED: object name.
 */
extern char D_kernel_data_0A18[];
void isysInitGroup(void *group);

void InitSubThread(void) {
    isysInitGroup(D_kernel_data_0A18);
}
