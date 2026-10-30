/* GAMECORE.XFF @ 0x01D870 (32 B) - opflowSetDemoFrame
 * Evidence: div.s f12 by 30.0f (0x41F00000) -> bss+0x4AD8
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_4AD8[];

void opflowSetDemoFrame(float f) {
    D_kernel_bss_4AD8[0] = f / 30.0f;
}
