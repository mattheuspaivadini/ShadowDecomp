/* GAMECORE.XFF @ 0x0153E0 (24 B) - getBossIndexTimeAttackBestTime
 * Evidence: lwc1 bss+0xC88[a0]
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_0C88[];

float getBossIndexTimeAttackBestTime(int i) {
    return D_kernel_bss_0C88[i];
}
