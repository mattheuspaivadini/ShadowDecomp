/* GAMECORE.XFF @ 0x00A7E0 (8 B) - GAMEUTIL_get_status_continue_time_status_manager
 * Evidence: `jr $ra` with `c480000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float GAMEUTIL_get_status_continue_time_status_manager(unsigned char *p) {
    return *(float *)(p + 0xc);
}
