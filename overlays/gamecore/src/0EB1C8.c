/* GAMECORE.XFF @ 0x0EB1C8 (8 B) - set_object_interest_mode_target_game_camera
 * Evidence: `jr $ra` with `ac853110` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_object_interest_mode_target_game_camera(unsigned char *p, int value) {
    *(int *)(p + 0x3110) = value;
}
