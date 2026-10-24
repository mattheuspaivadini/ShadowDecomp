/* GAMECORE.XFF @ 0x0E0388 (8 B) - CAM_is_inside_of_stop_region_aim_rot_common
 * Evidence: `jr $ra` with `8c820008` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CAM_is_inside_of_stop_region_aim_rot_common(unsigned char *p) {
    return *(int *)(p + 0x8);
}
