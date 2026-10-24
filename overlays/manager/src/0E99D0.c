/* MANAGER.XFF @ 0x0E99D0 (8 B) - get_screen_matrix128
 * Evidence: `jr $ra` with `24820150` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_screen_matrix128(char *p) {
    return p + 0x150;
}
