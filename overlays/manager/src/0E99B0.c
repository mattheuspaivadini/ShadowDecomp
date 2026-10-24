/* MANAGER.XFF @ 0x0E99B0 (8 B) - get_clip_matrix128
 * Evidence: `jr $ra` with `24820050` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_clip_matrix128(char *p) {
    return p + 0x50;
}
