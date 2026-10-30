/* GAMECORE.XFF @ 0x010930 (40 B) - ResetCamFinalizer
 * Evidence: `jal get_main_cameraman`, `jal get_game_camera` with its result,
 * then a sibling `j` to `reset_game_camera_standby_flag` with that result.
 * UNCONFIRMED: the callee prototypes (all called with one forwarded pointer).
 
 */
void *get_main_cameraman(void);
void *get_game_camera(void *cameraman);
void reset_game_camera_standby_flag(void *camera);

void ResetCamFinalizer(void) {
    reset_game_camera_standby_flag(get_game_camera(get_main_cameraman()));
}
