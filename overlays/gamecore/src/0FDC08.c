/* GAMECORE.XFF @ 0x0FDC08 (8 B) - _getStopCtrlModeBaseMoveWork
 * Evidence: `jr $ra` with `8c820020` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int _getStopCtrlModeBaseMoveWork(unsigned char *p) {
    return *(int *)(p + 0x20);
}
