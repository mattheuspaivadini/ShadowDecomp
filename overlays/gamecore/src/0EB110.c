/* GAMECORE.XFF @ 0x0EB110 (12 B) - jack_game_camera
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void jack_game_camera(char *p) {
    F(p, int, 0) = 1;
}
