/* GAMECORE.XFF @ 0x0EAFB0 (12 B) - reset_game_camera
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void reset_game_camera(char *p) {
    F(p, int, 0x2C40) = 5;
}
