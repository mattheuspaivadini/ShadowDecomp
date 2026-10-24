/* MANAGER.XFF @ 0x0E99C0 (8 B) - get_clip_matrix_fovignore
 * Evidence: `jr $ra` with `248200d0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_clip_matrix_fovignore(char *p) {
    return p + 0xd0;
}
