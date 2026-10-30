/* GAMECORE.XFF @ 0x0EB6E0 (32 B) - is_view_angle_exist_lws_anime_mode_base
 * Evidence: ops lwc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_view_angle_exist_lws_anime_mode_base(char *p) {
    return 0.0f < F(p, float, 0x224);
}
