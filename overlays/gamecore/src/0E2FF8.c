/* GAMECORE.XFF @ 0x0E2FF8 (8 B) - get_cur_camera_target
 * Evidence: `jr $ra` with `8c82001c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_cur_camera_target(unsigned char *p) {
    return *(int *)(p + 0x1c);
}
