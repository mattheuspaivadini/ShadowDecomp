/* GAMECORE.XFF @ 0x00A640 (8 B) - GAMEUTIL_reset_record_info
 * Evidence: `jr $ra` with `ac80000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void GAMEUTIL_reset_record_info(unsigned char *p) {
    *(int *)(p + 0xc) = 0;
}
