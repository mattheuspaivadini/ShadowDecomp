/* GAMECORE.XFF @ 0x0C8260 (12 B) - GetTimeAttackTimer
 * Evidence: ops lwc1; data <.data>+0x1958
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern float D_kernel_data_1958;

float GetTimeAttackTimer(void) {
    return D_kernel_data_1958;
}
