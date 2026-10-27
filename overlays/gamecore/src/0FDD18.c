/* GAMECORE.XFF @ 0x0FDD18 (8 B) - _getExecBaseMoveWork
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int _getExecBaseMoveWork(unsigned char *p) {
    return *(int *)(p + 0x4);
}
