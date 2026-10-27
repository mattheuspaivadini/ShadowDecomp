/* GAMECORE.XFF @ 0x00D730 (8 B) - set_temp_stop_base_rot_flag_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `ac850030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void set_temp_stop_base_rot_flag_nico_yaw_pitch_cntrl(unsigned char *p, int value) {
    *(int *)(p + 0x30) = value;
}
