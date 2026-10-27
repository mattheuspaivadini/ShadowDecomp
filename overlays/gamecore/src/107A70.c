/* GAMECORE.XFF @ 0x107A70 (8 B) - setViewJudgeGazeCtrlWork
 * Evidence: `jr $ra` with `ac850004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setViewJudgeGazeCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x4) = value;
}
