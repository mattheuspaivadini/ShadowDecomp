/* GAMECORE.XFF @ 0x0FDC18 (8 B) - _setSlideVolumeBaseMoveWork
 * Evidence: `jr $ra` with `ac850028` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void _setSlideVolumeBaseMoveWork(unsigned char *p, int value) {
    *(int *)(p + 0x28) = value;
}
