/* GAMECORE.XFF @ 0x112ED0 (8 B) - setChkKeepHitWormCtrlWork
 * Evidence: `jr $ra` with `ac8500d0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setChkKeepHitWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xd0) = value;
}
