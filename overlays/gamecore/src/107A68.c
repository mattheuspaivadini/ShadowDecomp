/* GAMECORE.XFF @ 0x107A68 (8 B) - setExecGazeCtrlWork
 * Evidence: `jr $ra` with `ac850000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setExecGazeCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x0) = value;
}
