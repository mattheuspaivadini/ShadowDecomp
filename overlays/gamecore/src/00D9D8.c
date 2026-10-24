/* GAMECORE.XFF @ 0x00D9D8 (8 B) - is_enable_base_pitch_rot_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `8c8200e8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int is_enable_base_pitch_rot_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(int *)(p + 0xe8);
}
