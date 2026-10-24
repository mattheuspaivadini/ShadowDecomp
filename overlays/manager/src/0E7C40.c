/* MANAGER.XFF @ 0x0E7C40 (8 B) - get_camera_obj_layout_class
 * Evidence: `jr $ra` with `24820020` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_camera_obj_layout_class(char *p) {
    return p + 0x20;
}
