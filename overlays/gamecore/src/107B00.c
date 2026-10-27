/* GAMECORE.XFF @ 0x107B00 (8 B) - setBirdModeGazeCtrlWork
 * Evidence: `jr $ra` with `ac85000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setBirdModeGazeCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xc) = value;
}
