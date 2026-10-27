/* GAMECORE.XFF @ 0x0D94E0 (8 B) - get_manage_obj_camera_place_status
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_manage_obj_camera_place_status(unsigned char *p) {
    return *(int *)(p + 0x4);
}
