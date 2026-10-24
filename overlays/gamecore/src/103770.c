/* GAMECORE.XFF @ 0x103770 (8 B) - setFlapWingBirdCtrlWork
 * Evidence: `jr $ra` with `ac850034` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFlapWingBirdCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x34) = value;
}
