/* GAMECORE.XFF @ 0x0F22A8 (8 B) - get_cur_base_mode_manager_game_camera_param_manager
 * Evidence: `jr $ra` with `8c820664` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_cur_base_mode_manager_game_camera_param_manager(unsigned char *p) {
    return *(int *)(p + 0x664);
}
