/* GAMECORE.XFF @ 0x0E0950 (8 B) - CAM_get_target_obj
 * Evidence: `jr $ra` with `8c820000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CAM_get_target_obj(unsigned char *p) {
    return *(int *)(p + 0x0);
}
