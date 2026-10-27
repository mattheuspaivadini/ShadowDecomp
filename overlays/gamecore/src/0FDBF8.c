/* GAMECORE.XFF @ 0x0FDBF8 (8 B) - _setExecBaseMoveWork
 * Evidence: `jr $ra` with `ac850004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void _setExecBaseMoveWork(unsigned char *p, int value) {
    *(int *)(p + 0x4) = value;
}
