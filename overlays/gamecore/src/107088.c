/* GAMECORE.XFF @ 0x107088 (8 B) - setDashFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850034` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setDashFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x34) = value;
}
