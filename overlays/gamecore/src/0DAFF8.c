/* GAMECORE.XFF @ 0x0DAFF8 (8 B) - get_attr_camera_target_lost_angle
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_attr_camera_target_lost_angle(unsigned char *p) {
    return *(int *)(p + 0x0);
}
