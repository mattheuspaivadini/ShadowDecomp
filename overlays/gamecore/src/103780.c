/* GAMECORE.XFF @ 0x103780 (8 B) - setHoverAttackBirdCtrlWork
 * Evidence: `jr $ra` with `ac85003c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setHoverAttackBirdCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x3c) = value;
}
