/* GAMECORE.XFF @ 0x0D7610 (8 B) - get_stretch_phase_ratio_camera_dist_to_look_at
 * Evidence: `jr $ra` with `c480007c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_stretch_phase_ratio_camera_dist_to_look_at(unsigned char *p) {
    return *(float *)(p + 0x7c);
}
