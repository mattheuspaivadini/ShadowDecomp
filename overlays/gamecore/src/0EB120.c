/* GAMECORE.XFF @ 0x0EB120 (24 B) - end_jack_game_camera
 * Evidence: ops ld sd sw; calls j <.text>; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void reset_game_camera(char *p);
void end_jack_game_camera(char *p) {
    F(p, int, 0) = 0;
    reset_game_camera(p);
}
