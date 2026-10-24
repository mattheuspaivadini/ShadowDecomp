/* GAMECORE.XFF @ 0x0FDC00 (8 B) - _setStopCtrlModeBaseMoveWork
 * Evidence: `jr $ra` with `ac850020` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void _setStopCtrlModeBaseMoveWork(unsigned char *p, int value) {
    *(int *)(p + 0x20) = value;
}
