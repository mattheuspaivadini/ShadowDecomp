/* GAMECORE.XFF @ 0x0E2FC8 (8 B) - get_camera_target_group
 * Evidence: `jr $ra` with `8c820008` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int get_camera_target_group(unsigned char *p) {
    return *(int *)(p + 0x8);
}
