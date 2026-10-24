/* GAMECORE.XFF @ 0x103778 (8 B) - setHoveringBirdCtrlWork
 * Evidence: `jr $ra` with `ac850038` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setHoveringBirdCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x38) = value;
}
