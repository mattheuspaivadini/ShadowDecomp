/* KERNEL.XFF @ 0x00C780 (44 B) - iosInitPushPosVuSema
 * Evidence: `iosCreateSema(1, 1, 0)` stored to .bss+0xE2B0.
 * UNCONFIRMED: the object name and iosCreateSema's third parameter (it only
 * reads $a0/$a1, see 000A60).
 */
int iosCreateSema(int init, int max, int attr);
extern int D_kernel_bss_E2B0;

void iosInitPushPosVuSema(void) {
    D_kernel_bss_E2B0 = iosCreateSema(1, 1, 0);
}
