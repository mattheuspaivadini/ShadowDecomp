/* GAMECORE.XFF @ 0x00A7B8 (8 B) - GAMEUTIL_reset_status_continue_time_status_manager
 * Evidence: `jr $ra` with `ac80000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_reset_status_continue_time_status_manager(unsigned char *p) {
    *(int *)(p + 0xc) = 0;
}
