/* GAMECORE.XFF @ 0x0DBA50 (8 B) - is_exist_camera_target_visible_angle
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int is_exist_camera_target_visible_angle(unsigned char *p) {
    return *(int *)(p + 0x0);
}
