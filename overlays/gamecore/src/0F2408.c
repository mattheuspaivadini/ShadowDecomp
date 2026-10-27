/* GAMECORE.XFF @ 0x0F2408 (8 B) - drop_camera_cutout_flag_game_camera_param_manager
 * Evidence: `jr $ra` with `ac800008` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void drop_camera_cutout_flag_game_camera_param_manager(unsigned char *p) {
    *(int *)(p + 0x8) = 0;
}
