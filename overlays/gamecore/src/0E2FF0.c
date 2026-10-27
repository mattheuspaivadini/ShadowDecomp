/* GAMECORE.XFF @ 0x0E2FF0 (8 B) - get_game_camera
 * Evidence: `jr $ra` with `24820020` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
char *get_game_camera(char *p) {
    return p + 0x20;
}
