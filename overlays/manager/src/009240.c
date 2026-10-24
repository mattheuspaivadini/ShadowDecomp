/* MANAGER.XFF @ 0x009240 (8 B) - GAMEUTIL_get_hope_value_interp_value_cntrl
 * Evidence: `jr $ra` with `c4800008` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_hope_value_interp_value_cntrl(unsigned char *p) {
    return *(float *)(p + 0x8);
}
