/* MANAGER.XFF @ 0x0E6CA8 (8 B) - get_boot_obj_camera_lws_animation
 * Evidence: `jr $ra` with `8c8200ac` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int get_boot_obj_camera_lws_animation(unsigned char *p) {
    return *(int *)(p + 0xac);
}
