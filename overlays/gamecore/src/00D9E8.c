/* GAMECORE.XFF @ 0x00D9E8 (8 B) - get_base_pitch_move_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `c4800064` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_base_pitch_move_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(float *)(p + 0x64);
}
