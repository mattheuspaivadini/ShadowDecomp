/* GAMECORE.XFF @ 0x00D9F0 (8 B) - set_base_yaw_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `e48c005c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_base_yaw_nico_yaw_pitch_cntrl(unsigned char *p, float value) {
    *(float *)(p + 0x5c) = value;
}
