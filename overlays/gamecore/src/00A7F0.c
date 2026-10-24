/* GAMECORE.XFF @ 0x00A7F0 (8 B) - GAMEUTIL_get_pre_status_status_manager
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int GAMEUTIL_get_pre_status_status_manager(unsigned char *p) {
    return *(int *)(p + 0x4);
}
