/* GAMECORE.XFF @ 0x0F22B0 (8 B) - is_base_mode_manager_update_game_camera_param_manager
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int is_base_mode_manager_update_game_camera_param_manager(unsigned char *p) {
    return *(int *)(p + 0x0);
}
