/* MANAGER.XFF @ 0x009030 (8 B) - GAMEUTIL_set_act_interp_flag_interp_ratio_cntrl
 * Evidence: `jr $ra` with `ac850000` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_set_act_interp_flag_interp_ratio_cntrl(unsigned char *p, int value) {
    *(int *)(p + 0x0) = value;
}
