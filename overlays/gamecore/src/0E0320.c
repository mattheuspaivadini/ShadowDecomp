/* GAMECORE.XFF @ 0x0E0320 (8 B) - CAM_set_yaw_shortest_rot_flag_aim_rot_common
 * Evidence: `jr $ra` with `ac850010` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void CAM_set_yaw_shortest_rot_flag_aim_rot_common(unsigned char *p, int value) {
    *(int *)(p + 0x10) = value;
}
