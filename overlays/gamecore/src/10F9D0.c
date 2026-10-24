/* GAMECORE.XFF @ 0x10F9D0 (8 B) - setGuardModeSlowLegCtrlWork
 * Evidence: `jr $ra` with `ac85009c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGuardModeSlowLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x9c) = value;
}
