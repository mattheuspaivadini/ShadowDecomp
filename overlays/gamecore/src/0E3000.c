/* GAMECORE.XFF @ 0x0E3000 (8 B) - get_game_camera_WV_matrix
 * Evidence: `jr $ra` with `248237d0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
char *get_game_camera_WV_matrix(char *p) {
    return p + 0x37d0;
}
