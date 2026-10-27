/* GAMECORE.XFF @ 0x0EB480 (8 B) - end_stream_lws_movie_playing_game_camera
 * Evidence: `jr $ra` with `ac803574` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void end_stream_lws_movie_playing_game_camera(unsigned char *p) {
    *(int *)(p + 0x3574) = 0;
}
