/* MANAGER.XFF @ 0x0E9A10 (8 B) - get_VCS_matrix
 * Evidence: `jr $ra` with `24820100` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_VCS_matrix(char *p) {
    return p + 0x100;
}
