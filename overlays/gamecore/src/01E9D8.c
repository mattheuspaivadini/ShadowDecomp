/* GAMECORE.XFF @ 0x01E9D8 (20 B) - setFullPower
 * Evidence: 100.0f (0x42C80000) -> bss+0x4AE8
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_4AE8[];

void setFullPower(void) {
    D_kernel_bss_4AE8[0] = 100.0f;
}
