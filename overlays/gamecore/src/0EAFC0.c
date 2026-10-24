/* GAMECORE.XFF @ 0x0EAFC0 (8 B) - get_game_camera_cur_mode
 * Evidence: `jr $ra` with `8c821360` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_game_camera_cur_mode(unsigned char *p) {
    return *(int *)(p + 0x1360);
}
