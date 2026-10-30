/* GAMECORE.XFF @ 0x0EB470 (12 B) - begin_stream_lws_movie_playing_game_camera
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void begin_stream_lws_movie_playing_game_camera(char *p) {
    F(p, int, 0x3574) = 1;
}
