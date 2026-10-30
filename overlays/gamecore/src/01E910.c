/* GAMECORE.XFF @ 0x01E910 (12 B) - initPowerWork
 * Evidence: sw zero -> bss+0x4AE8
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_4AE8[];

void initPowerWork(void) {
    D_kernel_bss_4AE8[0] = 0;
}
