/* GAMECORE.XFF @ 0x0EB1A0 (24 B) - is_end_pause_rise_game_camera
 * Evidence: ops ld sd; calls j is_end_camera_pause_rise; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int is_end_camera_pause_rise(char *p);
int is_end_pause_rise_game_camera(char *p) {
    return is_end_camera_pause_rise(p + 0x3750);
}
