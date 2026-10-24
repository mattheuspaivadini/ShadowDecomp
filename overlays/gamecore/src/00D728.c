/* GAMECORE.XFF @ 0x00D728 (8 B) - is_doing_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `8c82002c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int is_doing_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(int *)(p + 0x2c);
}
