/* MANAGER.XFF @ 0x03DFE8 (8 B) - init_motion_ik_base
 * Evidence: `jr $ra` with `ac800000` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void init_motion_ik_base(unsigned char *p) {
    *(int *)(p + 0x0) = 0;
}
