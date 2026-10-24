/* GAMECORE.XFF @ 0x00D9E0 (8 B) - get_base_yaw_move_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `c4800058` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_base_yaw_move_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(float *)(p + 0x58);
}
