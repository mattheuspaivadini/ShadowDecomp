/* MANAGER.XFF @ 0x009020 (8 B) - GAMEUTIL_get_interp_ratio_interp_ratio_cntrl
 * Evidence: `jr $ra` with `c4800010` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(unsigned char *p) {
    return *(float *)(p + 0x10);
}
