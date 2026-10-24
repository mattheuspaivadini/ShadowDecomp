/* MANAGER.XFF @ 0x0E69B8 (8 B) - get_camera_lws_animation_param
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_camera_lws_animation_param(unsigned char *p) {
    return *(int *)(p + 0x0);
}
