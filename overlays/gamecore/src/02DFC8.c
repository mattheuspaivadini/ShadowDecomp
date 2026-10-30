/* GAMECORE.XFF @ 0x02DFC8 (12 B) - time_attack_get_best_time
 * Evidence: lwc1 .data+0x1078
 * UNCONFIRMED: none
 */
extern float D_kernel_data_1078[];

float time_attack_get_best_time(void) {
    return D_kernel_data_1078[0];
}
