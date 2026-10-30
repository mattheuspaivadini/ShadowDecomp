/* GAMECORE.XFF @ 0x0EB180 (32 B) - request_end_pause_rise_game_camera
 * Evidence: ops ld sd; calls j request_end_camera_pause_rise; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void request_end_camera_pause_rise(char *p, char *q, int a);
void request_end_pause_rise_game_camera(char *p, int a) {
    request_end_camera_pause_rise(p + 0x3750, p, a);
}
