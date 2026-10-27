/* GAMECORE.XFF @ 0x10A6A8 (8 B) - setFreezeHorseCtrlWork
 * Evidence: `jr $ra` with `ac85003c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFreezeHorseCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x3c) = value;
}
