/* GAMECORE.XFF @ 0x10F9B0 (8 B) - setStabilizeYSlowLegCtrlWork
 * Evidence: `jr $ra` with `ac85003c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setStabilizeYSlowLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x3c) = value;
}
