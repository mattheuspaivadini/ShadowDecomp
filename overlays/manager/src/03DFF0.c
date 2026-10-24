/* MANAGER.XFF @ 0x03DFF0 (8 B) - doit_motion_ik_base
 * Evidence: `jr $ra` with `ac850000` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void doit_motion_ik_base(unsigned char *p, int value) {
    *(int *)(p + 0x0) = value;
}
