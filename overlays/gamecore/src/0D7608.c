/* GAMECORE.XFF @ 0x0D7608 (8 B) - set_stretch_phase_ratio_camera_dist_to_look_at
 * Evidence: `jr $ra` with `e48c007c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_stretch_phase_ratio_camera_dist_to_look_at(unsigned char *p, float value) {
    *(float *)(p + 0x7c) = value;
}
