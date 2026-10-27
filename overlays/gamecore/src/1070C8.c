/* GAMECORE.XFF @ 0x1070C8 (8 B) - setWalkStopTurnFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850044` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setWalkStopTurnFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x44) = value;
}
