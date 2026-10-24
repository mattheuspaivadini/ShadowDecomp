/* GAMECORE.XFF @ 0x1070C0 (8 B) - setRunStopTurnFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850040` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRunStopTurnFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x40) = value;
}
