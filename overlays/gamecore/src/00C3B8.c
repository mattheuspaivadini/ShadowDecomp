/* GAMECORE.XFF @ 0x00C3B8 (12 B) - setFadeValue
 * Evidence: swc1 f12 -> .data+0x660
 * UNCONFIRMED: none
 */
extern float D_kernel_data_0660[];

void setFadeValue(float v) {
    D_kernel_data_0660[0] = v;
}
