/* MANAGER.XFF @ 0x0E9A08 (8 B) - get_WVC_matrix
 * Evidence: `jr $ra` with `248200c0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_WVC_matrix(char *p) {
    return p + 0xc0;
}
