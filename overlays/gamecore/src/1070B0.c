/* GAMECORE.XFF @ 0x1070B0 (8 B) - setBackFastLegCtrlWork
 * Evidence: `jr $ra` with `ac850038` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setBackFastLegCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0x38) = value;
}
