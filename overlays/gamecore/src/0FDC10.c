/* GAMECORE.XFF @ 0x0FDC10 (8 B) - _setBackVolumeBaseMoveWork
 * Evidence: `jr $ra` with `ac850024` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void _setBackVolumeBaseMoveWork(unsigned char *p, int value) {
    *(int *)(p + 0x24) = value;
}
