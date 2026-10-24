/* GAMECORE.XFF @ 0x10A668 (8 B) - setDashHorseCtrlWork
 * Evidence: `jr $ra` with `ac850034` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setDashHorseCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x34) = value;
}
