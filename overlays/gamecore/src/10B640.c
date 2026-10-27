/* GAMECORE.XFF @ 0x10B640 (8 B) - setDashHumanCtrlWork
 * Evidence: `jr $ra` with `ac850030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setDashHumanCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x30) = value;
}
