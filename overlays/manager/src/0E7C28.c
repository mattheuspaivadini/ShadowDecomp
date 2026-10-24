/* MANAGER.XFF @ 0x0E7C28 (8 B) - get_camera_position
 * Evidence: `jr $ra` with `248201e0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_camera_position(char *p) {
    return p + 0x1e0;
}
