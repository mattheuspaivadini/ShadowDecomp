/* GAMECORE.XFF @ 0x10F9A8 (8 B) - setDashSlowLegCtrlWork
 * Evidence: `jr $ra` with `ac850030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setDashSlowLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x30) = value;
}
