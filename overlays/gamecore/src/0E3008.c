/* GAMECORE.XFF @ 0x0E3008 (12 B) - is_game_camera_mode_now
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_game_camera_mode_now(char *p) {
    return F(p, unsigned, 4) < 2;
}
