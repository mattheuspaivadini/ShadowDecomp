/* GAMECORE.XFF @ 0x00D4F8 (8 B) - set_pitch_parameter_effective_ratio_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `e48c013c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_pitch_parameter_effective_ratio_nico_yaw_pitch_cntrl(unsigned char *p, float value) {
    *(float *)(p + 0x13c) = value;
}
