/* GAMECORE.XFF @ 0x0EB1C0 (8 B) - reset_game_camera_standby_flag
 * Evidence: `jr $ra` with `ac800004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void reset_game_camera_standby_flag(unsigned char *p) {
    *(int *)(p + 0x4) = 0;
}
