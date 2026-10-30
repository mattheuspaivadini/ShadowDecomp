/* GAMECORE.XFF @ 0x11F7E8 (32 B) - SCRConditionLWSCameraPlay
 * Evidence: ops ld sd; calls get_main_cameraman, j is_playing_lws_movie_now_game_camera; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int get_main_cameraman(void);
int is_playing_lws_movie_now_game_camera(int c);
int SCRConditionLWSCameraPlay(void) {
    return is_playing_lws_movie_now_game_camera(get_main_cameraman());
}
