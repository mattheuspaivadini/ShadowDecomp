/* GAMECORE.XFF @ 0x00DA00 (8 B) - get_base_yaw_nico_yaw_pitch_cntrl
 * Evidence: `jr $ra` with `c480005c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float get_base_yaw_nico_yaw_pitch_cntrl(unsigned char *p) {
    return *(float *)(p + 0x5c);
}
