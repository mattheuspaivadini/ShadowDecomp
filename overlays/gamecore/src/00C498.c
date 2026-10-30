/* GAMECORE.XFF @ 0x00C498 (24 B) - getDemoBarFade
 * Evidence: 1.0f - .data+0x678
 * UNCONFIRMED: none
 */
extern float D_kernel_data_0678[];

float getDemoBarFade(void) {
    return 1.0f - D_kernel_data_0678[0];
}
