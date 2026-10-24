/* MANAGER.XFF @ 0x009028 (8 B) - GAMEUTIL_get_interp_timer_interp_ratio_cntrl
 * Evidence: `jr $ra` with `c480000c` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_interp_timer_interp_ratio_cntrl(unsigned char *p) {
    return *(float *)(p + 0xc);
}
