/* GAMECORE.XFF @ 0x0EB6B0 (44 B) - is_view_angle_zoom_game_camera
 * Evidence: stores $ra, 0x0($sp); loads $a1, 0x1E88($v0), $ra, 0x0($sp); relocs <.data>, <.data>+0x1E88; calls GAMEUTIL_is_push_or_down_1p_button; frame
 
 */
/* UNCONFIRMED: the pad id word at .data+0x1E88 is the zoom button binding. */
extern int D_kernel_data_1E88;

int GAMEUTIL_is_push_or_down_1p_button(int pad, int button);

int is_view_angle_zoom_game_camera(void) {
    return GAMEUTIL_is_push_or_down_1p_button(0, D_kernel_data_1E88) == 1;
}
