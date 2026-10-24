/* GAMECORE.XFF @ 0x0E07B8 (8 B) - CAM_is_motion_kind_change_target
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CAM_is_motion_kind_change_target(unsigned char *p) {
    return *(int *)(p + 0x4);
}
