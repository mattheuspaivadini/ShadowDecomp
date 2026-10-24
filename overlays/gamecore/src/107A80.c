/* GAMECORE.XFF @ 0x107A80 (8 B) - setValidPosGazeCtrlWork
 * Evidence: `jr $ra` with `ac850014` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setValidPosGazeCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x14) = value;
}
