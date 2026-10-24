/* GAMECORE.XFF @ 0x0E0958 (8 B) - CAM_get_target_riding_obj
 * Evidence: `jr $ra` with `8c8202c8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int CAM_get_target_riding_obj(unsigned char *p) {
    return *(int *)(p + 0x2c8);
}
