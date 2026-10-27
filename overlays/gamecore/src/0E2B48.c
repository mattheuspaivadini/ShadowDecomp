/* GAMECORE.XFF @ 0x0E2B48 (8 B) - get_view_angle_camera_view_angle_cntrl
 * Evidence: `jr $ra` with `c480001c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_view_angle_camera_view_angle_cntrl(unsigned char *p) {
    return *(float *)(p + 0x1c);
}
