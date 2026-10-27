/* GAMECORE.XFF @ 0x1070D0 (8 B) - setCurveCollisionFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850048` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setCurveCollisionFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x48) = value;
}
