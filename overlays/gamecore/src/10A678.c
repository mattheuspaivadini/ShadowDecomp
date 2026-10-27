/* GAMECORE.XFF @ 0x10A678 (8 B) - setLimitModeHorseCtrlWork
 * Evidence: `jr $ra` with `ac850044` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setLimitModeHorseCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x44) = value;
}
