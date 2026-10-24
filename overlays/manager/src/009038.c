/* MANAGER.XFF @ 0x009038 (8 B) - GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl
 * Evidence: `jr $ra` with `ac850004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(unsigned char *p, int value) {
    *(int *)(p + 0x4) = value;
}
