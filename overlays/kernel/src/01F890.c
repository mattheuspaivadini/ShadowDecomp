/* KERNEL.XFF @ 0x01F890 (20 B) - Sg2CtrlSetTickMode
 * Evidence: returns the old .bss+0x7F5C4 and stores the new mode (store in the jr slot). UNCONFIRMED: name.
 */
extern int D_kernel_bss_7F5C4;

int Sg2CtrlSetTickMode(int mode) {
    int old = D_kernel_bss_7F5C4;

    D_kernel_bss_7F5C4 = mode;
    return old;
}
