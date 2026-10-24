/* MANAGER.XFF @ 0x0E7C38 (8 B) - get_camera_up_direction
 * Evidence: `jr $ra` with `24820200` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_camera_up_direction(char *p) {
    return p + 0x200;
}
