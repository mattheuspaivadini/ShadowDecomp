/* GAMECORE.XFF @ 0x10A670 (8 B) - setWallStopHorseCtrlWork
 * Evidence: `jr $ra` with `ac850038` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setWallStopHorseCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x38) = value;
}
