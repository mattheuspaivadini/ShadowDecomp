/* GAMECORE.XFF @ 0x0F2530 (28 B) - is_already_set_game_camera_param_update_data_manager
 * Evidence: ops lw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int is_already_set_game_camera_param_update_data_manager(char *p, int i) {
    return F(F(p, char *, 4) + i * 0x65C, int, 4) != 0;
}
