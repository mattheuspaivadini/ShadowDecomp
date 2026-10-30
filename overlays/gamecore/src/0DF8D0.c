/* GAMECORE.XFF @ 0x0DF8D0 (64 B) - CAM_shuffle_lws_base_space_target_boss_interest_axis_X
 * Evidence: `jal iosGetRandom`, `lui/ori 0x3F000000` (0.5f), `c.lt.s $f0,$f1` + `bc1f`, then
 * `sw 1` / `sw $zero` to `.data+0x1DD0`.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
extern int D_kernel_data_1DD0;

float iosGetRandom(void);

void CAM_shuffle_lws_base_space_target_boss_interest_axis_X(void) {
    if (iosGetRandom() < 0.5f)
        D_kernel_data_1DD0 = 1;
    else
        D_kernel_data_1DD0 = 0;
}
