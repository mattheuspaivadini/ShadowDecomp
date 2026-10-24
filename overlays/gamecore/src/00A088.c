/* GAMECORE.XFF @ 0x00A088 (8 B) - GAMEUTIL_set_enable_side_change_angle_look_at_vs_offset
 * Evidence: `jr $ra` with `e48c0050` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_set_enable_side_change_angle_look_at_vs_offset(unsigned char *p, float value) {
    *(float *)(p + 0x50) = value;
}
