/* GAMECORE.XFF @ 0x0FDD20 (8 B) - _setAttainFlagBaseMoveWork
 * Evidence: `jr $ra` with `ac850000` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void _setAttainFlagBaseMoveWork(unsigned char *p, int value) {
    *(int *)(p + 0x0) = value;
}
