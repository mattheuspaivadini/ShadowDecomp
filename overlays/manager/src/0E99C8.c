/* MANAGER.XFF @ 0x0E99C8 (8 B) - get_screen_matrix
 * Evidence: `jr $ra` with `24820110` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_screen_matrix(char *p) {
    return p + 0x110;
}
