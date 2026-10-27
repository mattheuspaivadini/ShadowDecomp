/* GAMECORE.XFF @ 0x00D9C8 (8 B) - get_offset_pitch_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `c4800050` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_offset_pitch_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(float *)(p + 0x50);
}
