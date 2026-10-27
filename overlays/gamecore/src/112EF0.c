/* GAMECORE.XFF @ 0x112EF0 (8 B) - setSelfEvasionUpWormCtrlWork
 * Evidence: `jr $ra` with `ac8500e4` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setSelfEvasionUpWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xe4) = value;
}
