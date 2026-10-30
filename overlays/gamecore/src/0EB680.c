/* GAMECORE.XFF @ 0x0EB680 (44 B) - is_mode_change_game_camera
 * Evidence: stores $ra, 0x0($sp); loads $v1, 0x1364($v0), $v0, 0x1360($v0), $ra, 0x0($sp); calls get_game_camera; frame
 
 */
/* UNCONFIRMED: 0x1360 is the requested mode, 0x1364 the mode of the previous frame. */
void *get_game_camera(void);

int is_mode_change_game_camera(void) {
    char *p = get_game_camera();
    return *(int *)(p + 0x1360) != *(int *)(p + 0x1364);
}
