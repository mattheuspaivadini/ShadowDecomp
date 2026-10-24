/* MANAGER.XFF @ 0x03EE70 (8 B) - is_doing_motion_ik_interest
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int is_doing_motion_ik_interest(unsigned char *p) {
    return *(int *)(p + 0x4);
}
