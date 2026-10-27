/* GAMECORE.XFF @ 0x0F22A0 (8 B) - get_cur_base_mode_condition_game_camera_param_manager
 * Evidence: `jr $ra` with `8c82130c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_cur_base_mode_condition_game_camera_param_manager(unsigned char *p) {
    return *(int *)(p + 0x130c);
}
