/* GAMECORE.XFF @ 0x0EAFC8 (32 B) - is_reset_or_lws_movie_game_camera
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_reset_or_lws_movie_game_camera(char *p) {
    int m = F(p, int, 0x1360);
    if (m == 0 || m == 8)
        return 1;
    return 0;
}
