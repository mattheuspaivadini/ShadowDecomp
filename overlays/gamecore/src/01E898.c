/* GAMECORE.XFF @ 0x01E898 (12 B) - getPlayerO2
 * Evidence: lwc1 .data+0x0A54
 * UNCONFIRMED: none
 */
extern float D_kernel_data_0A54[];

float getPlayerO2(void) {
    return D_kernel_data_0A54[0];
}
