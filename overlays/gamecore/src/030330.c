/* GAMECORE.XFF @ 0x030330 (32 B) - bgmScriptSendSoundSignal
 * Evidence: bss+0x4DC0 |= 1<<a0
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_bss_4DC0[];

void bgmScriptSendSoundSignal(int n) {
    D_kernel_bss_4DC0[0] |= 1 << n;
}
