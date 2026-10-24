/* MANAGER.XFF @ 0x0E6CA0 (8 B) - get_animation_class_camera_lws_animation
 * Evidence: `jr $ra` with `24820004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 * Returns the argument advanced by a constant offset.
 */
char *get_animation_class_camera_lws_animation(char *p) {
    return p + 0x4;
}
