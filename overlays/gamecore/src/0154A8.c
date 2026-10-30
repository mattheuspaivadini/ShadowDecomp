/* GAMECORE.XFF @ 0x0154A8 (16 B) - getSavedClock
 * Evidence: ld bss+0xC80; sd to a0
 * UNCONFIRMED: none
 */
extern long D_kernel_bss_0C80[];

void getSavedClock(long *p) {
    *p = D_kernel_bss_0C80[0];
}
