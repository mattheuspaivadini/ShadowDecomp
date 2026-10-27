/* GAMECORE.XFF @ 0x10F9B8 (8 B) - setMoveModeSlowLegCtrlWork
 * Evidence: `jr $ra` with `ac850034` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setMoveModeSlowLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x34) = value;
}
