/* GAMECORE.XFF @ 0x112EE0 (8 B) - setMiddleTargetWormCtrlWork
 * Evidence: `jr $ra` with `ac8500dc` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setMiddleTargetWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xdc) = value;
}
