/* GAMECORE.XFF @ 0x0EB8F0 (44 B) - is_lws_movie_mode_game_camera
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $ra, 0x8($sp), $s0, 0x0($sp); calls get_main_type_camera_lws_animation, j <.text>; frame
 
 */
/* UNCONFIRMED: same shared LWS mode test as is_lws_fixed_point_mode. */
int get_main_type_camera_lws_animation(void);
int func_0EB898(char *p, int type);

int is_lws_movie_mode_game_camera(char *p) {
    return func_0EB898(p, get_main_type_camera_lws_animation());
}
