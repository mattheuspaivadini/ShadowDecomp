/* GAMECORE.XFF @ 0x0EB1B8 (8 B) - is_game_camera_standby_ok
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int is_game_camera_standby_ok(unsigned char *p) {
    return *(int *)(p + 0x4);
}
