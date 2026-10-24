/* MANAGER.XFF @ 0x0E99F8 (8 B) - get_VC_matrix
 * Evidence: `jr $ra` with `24820040` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_VC_matrix(char *p) {
    return p + 0x40;
}
