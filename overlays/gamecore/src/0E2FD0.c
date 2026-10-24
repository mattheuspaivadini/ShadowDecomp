/* GAMECORE.XFF @ 0x0E2FD0 (8 B) - get_camera_move_collision_group
 * Evidence: `jr $ra` with `8c82000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_camera_move_collision_group(unsigned char *p) {
    return *(int *)(p + 0xc);
}
