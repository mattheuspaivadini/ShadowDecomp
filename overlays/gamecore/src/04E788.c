/* GAMECORE.XFF @ 0x04E788 (12 B) - effectClearDamageWork
 * Evidence: sw zero -> bss+0x6E48
 * UNCONFIRMED: none
 */
extern int D_kernel_bss_6E48[];

void effectClearDamageWork(void) {
    D_kernel_bss_6E48[0] = 0;
}
