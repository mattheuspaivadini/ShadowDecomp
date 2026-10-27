/* GAMECORE.XFF @ 0x00A080 (8 B) - GAMEUTIL_set_need_dir_ratio_flag_look_at_vs_offset
 * Evidence: `jr $ra` with `ac850018` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_set_need_dir_ratio_flag_look_at_vs_offset(unsigned char *p, int value) {
    *(int *)(p + 0x18) = value;
}
