/* MANAGER.XFF @ 0x0E99A8 (8 B) - get_clip_matrix
 * Evidence: `jr $ra` with `24820010` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_clip_matrix(char *p) {
    return p + 0x10;
}
