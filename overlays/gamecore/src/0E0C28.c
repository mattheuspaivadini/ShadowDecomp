/* GAMECORE.XFF @ 0x0E0C28 (8 B) - CAM_is_return_cam_posi_target_visibility
 * Evidence: `jr $ra` with `8c820130` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CAM_is_return_cam_posi_target_visibility(unsigned char *p) {
    return *(int *)(p + 0x130);
}
