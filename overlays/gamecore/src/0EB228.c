/* GAMECORE.XFF @ 0x0EB228 (28 B) - is_hit_leave_plane_game_camera
 * Evidence: ops ld sd; calls j is_pass_camera_etc_condition; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int is_pass_camera_etc_condition(int k, char *p);
int is_hit_leave_plane_game_camera(char *p) {
    return is_pass_camera_etc_condition(3, p + 0x10);
}
