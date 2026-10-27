/* GAMECORE.XFF @ 0x00D9C0 (8 B) - get_offset_yaw_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `c4800040` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_offset_yaw_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(float *)(p + 0x40);
}
