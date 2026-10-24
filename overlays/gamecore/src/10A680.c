/* GAMECORE.XFF @ 0x10A680 (8 B) - setFinalAttainWalkHorseCtrlWork
 * Evidence: `jr $ra` with `ac850030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFinalAttainWalkHorseCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x30) = value;
}
