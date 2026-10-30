/* GAMECORE.XFF @ 0x00C3A8 (12 B) - getFadeValue
 * Evidence: lwc1 .data+0x660
 * UNCONFIRMED: none
 */
extern float D_kernel_data_0660[];

float getFadeValue(void) {
    return D_kernel_data_0660[0];
}
