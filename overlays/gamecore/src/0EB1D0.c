/* GAMECORE.XFF @ 0x0EB1D0 (8 B) - get_object_interest_mode_target_game_camera
 * Evidence: `jr $ra` with `8c823110` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_object_interest_mode_target_game_camera(unsigned char *p) {
    return *(int *)(p + 0x3110);
}
