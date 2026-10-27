/* GAMECORE.XFF @ 0x107A78 (8 B) - setNextDistGazeCtrlWork
 * Evidence: `jr $ra` with `e48c0008` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setNextDistGazeCtrlWork(unsigned char *p, float value) {
    *(float *)(p + 0x8) = value;
}
