/* GAMECORE.XFF @ 0x01E930 (28 B) - getAttackPowerRatio
 * Evidence: bss+0x4AE8 * 0.01f (0x3C23D70A)
 * UNCONFIRMED: none
 */
extern float D_kernel_bss_4AE8[];

float getAttackPowerRatio(void) {
    return D_kernel_bss_4AE8[0] * 0.01f;
}
