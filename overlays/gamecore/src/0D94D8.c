/* GAMECORE.XFF @ 0x0D94D8 (8 B) - get_place_status_camera_place_status
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_place_status_camera_place_status(unsigned char *p) {
    return *(int *)(p + 0x0);
}
