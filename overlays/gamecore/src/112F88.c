/* GAMECORE.XFF @ 0x112F88 (8 B) - getBuryingWormCtrlWork
 * Evidence: `jr $ra` with `8c8200e8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getBuryingWormCtrlWork(unsigned char *p) {
    return *(int *)(p + 0xe8);
}
