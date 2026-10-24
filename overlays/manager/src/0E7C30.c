/* MANAGER.XFF @ 0x0E7C30 (8 B) - get_camera_direction
 * Evidence: `jr $ra` with `248201f0` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_camera_direction(char *p) {
    return p + 0x1f0;
}
