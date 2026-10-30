/* GAMECORE.XFF @ 0x03E8F0 (32 B) - SCRSetCharaMotionPlaySpeedRatio
 * Evidence: a1=a0, a0=bss+0x6B40, sibling j MotSpdCtrl_SetSpeed
 * UNCONFIRMED: none
 */
extern char D_kernel_bss_6B40[];
void MotSpdCtrl_SetSpeed(char *p, int a);

void SCRSetCharaMotionPlaySpeedRatio(int a) {
    MotSpdCtrl_SetSpeed(D_kernel_bss_6B40, a);
}
