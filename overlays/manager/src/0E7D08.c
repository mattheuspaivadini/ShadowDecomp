/* MANAGER.XFF @ 0x0E7D08 (8 B) - get_view_matrix
 * Evidence: `jr $ra` with `24820210` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_view_matrix(char *p) {
    return p + 0x210;
}
