/* GAMECORE.XFF @ 0x0153F8 (24 B) - setBossIndexTimeAttackBestTime
 * Evidence: swc1 f12 -> bss+0xC88[a0]
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_0C88[];

void setBossIndexTimeAttackBestTime(int i, float v) {
    D_kernel_bss_0C88[i] = v;
}
