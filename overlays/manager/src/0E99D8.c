/* MANAGER.XFF @ 0x0E99D8 (8 B) - get_screen_matrix256
 * Evidence: `jr $ra` with `24820190` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_screen_matrix256(char *p) {
    return p + 0x190;
}
