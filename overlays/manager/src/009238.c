/* MANAGER.XFF @ 0x009238 (8 B) - GAMEUTIL_get_interp_value_interp_value_cntrl
 * Evidence: `jr $ra` with `c4800004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_interp_value_interp_value_cntrl(unsigned char *p) {
    return *(float *)(p + 0x4);
}
