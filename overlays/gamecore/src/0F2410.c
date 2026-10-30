/* GAMECORE.XFF @ 0x0F2410 (12 B) - constructor_game_camera_param_update_data_manager
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void constructor_game_camera_param_update_data_manager(char *p) {
    F(p, int, 0) = 0;
    F(p, int, 4) = 0;
}
