/* GAMECORE.XFF @ 0x00D4F0 (8 B) - set_yaw_parameter_effective_ratio_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `e48c0138` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_yaw_parameter_effective_ratio_nico_yaw_pitch_cntrl(unsigned char *p, float value) {
    *(float *)(p + 0x138) = value;
}
