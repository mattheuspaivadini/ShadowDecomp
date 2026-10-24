/* MANAGER.XFF @ 0x0E9A18 (8 B) - get_WVCS_matrix
 * Evidence: `jr $ra` with `248201c0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_WVCS_matrix(char *p) {
    return p + 0x1c0;
}
