/* KERNEL.XFF @ 0x012A68 (28 B) - iosInitDC
 * Evidence: sibling isysInitGroup(&.bss+0x1EAC8). UNCONFIRMED: object name.
 */
extern char D_kernel_bss_1EAC8[];
void isysInitGroup(void *group);

void iosInitDC(void) {
    isysInitGroup(D_kernel_bss_1EAC8);
}
