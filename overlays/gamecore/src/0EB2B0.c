/* GAMECORE.XFF @ 0x0EB2B0 (24 B) - get_cur_using_camera_mode_manager_param_game_camera
 * Evidence: ops ld sd; calls j get_cur_base_mode_manager_game_camera_param_manager; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int get_cur_base_mode_manager_game_camera_param_manager(char *p);
int get_cur_using_camera_mode_manager_param_game_camera(char *p) {
    return get_cur_base_mode_manager_game_camera_param_manager(p + 0x50);
}
