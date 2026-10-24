/* GAMECORE.XFF @ 0x0E2FD8 (8 B) - get_camera_visible_collision_group
 * Evidence: `jr $ra` with `8c820010` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_camera_visible_collision_group(unsigned char *p) {
    return *(int *)(p + 0x10);
}
