/* KERNEL.XFF @ 0x01F8B8 (20 B) - Sg2CtrlSetTickTime
 * Evidence: returns the old .bss+0x7F5C0 and stores the new tick time (store in the jr slot). UNCONFIRMED: name.
 */
extern int D_kernel_bss_7F5C0;

int Sg2CtrlSetTickTime(int t) {
    int old = D_kernel_bss_7F5C0;

    D_kernel_bss_7F5C0 = t;
    return old;
}
