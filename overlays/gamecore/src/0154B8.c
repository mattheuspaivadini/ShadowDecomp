/* GAMECORE.XFF @ 0x0154B8 (16 B) - setSavedClock
 * Evidence: ld a0; sd to bss+0xC80
 * UNCONFIRMED: none
 */
extern long D_kernel_bss_0C80[];

void setSavedClock(long *p) {
    D_kernel_bss_0C80[0] = *p;
}
