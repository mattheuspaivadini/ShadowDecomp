/* KERNEL.XFF @ 0x000C90 (44 B) - iosResetCpuRapCounter
 * Evidence: stores the argument to .data+0x94, then `mode | 0x80` to 0x10000810
 * (T0_MODE) and 0 to 0x10000800 (T0_COUNT); the trailing nop delay slot is
 * the volatile store. UNCONFIRMED: the .data object name.
 */
extern int D_kernel_data_0094;

void iosResetCpuRapCounter(int mode) {
    D_kernel_data_0094 = mode;
    *(volatile int *)0x10000810 = mode | 0x80;
    *(volatile int *)0x10000800 = 0;
}
