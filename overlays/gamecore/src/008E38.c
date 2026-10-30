/* GAMECORE.XFF @ 0x008E38 (16 B) - GAMEUTIL_get_game_camera_free_mode_reverse_cntrlUD_bool
 * Evidence: lw .data+0x0230, sltu v0,zero,v0
 * UNCONFIRMED: none
 */
extern int D_kernel_data_0230[];

int GAMEUTIL_get_game_camera_free_mode_reverse_cntrlUD_bool(void) {
    return D_kernel_data_0230[0] != 0;
}
