/* GAMECORE.XFF @ 0x0EB100 (12 B) - get_look_at_position_game_camera
 * Evidence: ops lq sq
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
typedef unsigned int u_long128 __attribute__((mode(TI)));

void get_look_at_position_game_camera(u_long128 *out, char *p) {
    *out = F(p, u_long128, 0x13E0);
}
