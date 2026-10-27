/* GAMECORE.XFF @ 0x1070B8 (8 B) - setNotFastTurnFastLegCtrlWork
 * Evidence: `jr $ra` with `ac85003c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setNotFastTurnFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x3c) = value;
}
