/* KERNEL.XFF @ 0x02AAD8 (20 B) - Sg2SlotSetVolShiftDownParam
 * Evidence: returns the old .bss+0x97E2C and stores the new parameter. UNCONFIRMED: name.
 */
extern int D_kernel_bss_97E2C;

int Sg2SlotSetVolShiftDownParam(int param) {
    int old = D_kernel_bss_97E2C;

    D_kernel_bss_97E2C = param;
    return old;
}
