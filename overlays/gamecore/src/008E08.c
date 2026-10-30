/* GAMECORE.XFF @ 0x008E08 (16 B) - GAMEUTIL_get_game_camera_free_mode_reverse_cntrlLR_bool
 * Evidence: lw .data+0x022C, sltu v0,zero,v0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_022C[];

int GAMEUTIL_get_game_camera_free_mode_reverse_cntrlLR_bool(void) {
    return D_kernel_data_022C[0] != 0;
}
