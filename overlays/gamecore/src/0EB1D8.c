/* GAMECORE.XFF @ 0x0EB1D8 (12 B) - begin_object_interest_game_camera
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void begin_object_interest_game_camera(char *p) {
    F(p, int, 0x3114) = 1;
}
