/* GAMECORE.XFF @ 0x04E1F8 (32 B) - getWeakPointEffectIntensity
 * Evidence: lwc1 bss+0x6EA4 + a0*120
 * UNCONFIRMED: none
 */
extern char D_kernel_bss_6EA4[];

float getWeakPointEffectIntensity(int n) {
    return *(float *)(D_kernel_bss_6EA4 + n * 120);
}
