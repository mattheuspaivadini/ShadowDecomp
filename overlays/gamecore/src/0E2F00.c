/* GAMECORE.XFF @ 0x0E2F00 (8 B) - get_camera_obj
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_camera_obj(unsigned char *p) {
    return *(int *)(p + 0x0);
}
