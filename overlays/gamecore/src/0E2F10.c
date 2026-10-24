/* GAMECORE.XFF @ 0x0E2F10 (8 B) - get_cur_camera_mode
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_cur_camera_mode(unsigned char *p) {
    return *(int *)(p + 0x4);
}
