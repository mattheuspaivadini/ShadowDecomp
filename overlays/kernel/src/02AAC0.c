/* KERNEL.XFF @ 0x02AAC0 (20 B) - Sg2SlotSetOutputMode
 * Evidence: returns the old .bss+0x97E28 and stores the new mode. UNCONFIRMED: name.
 */
extern int D_kernel_bss_97E28;

int Sg2SlotSetOutputMode(int mode) {
    int old = D_kernel_bss_97E28;

    D_kernel_bss_97E28 = mode;
    return old;
}
