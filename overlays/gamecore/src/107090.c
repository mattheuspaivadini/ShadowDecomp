/* GAMECORE.XFF @ 0x107090 (8 B) - setFinalAttainWalkFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850030` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setFinalAttainWalkFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x30) = value;
}
