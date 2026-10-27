/* GAMECORE.XFF @ 0x112EF8 (8 B) - setTypeWormCtrlWork
 * Evidence: `jr $ra` with `ac8500ec` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setTypeWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xec) = value;
}
