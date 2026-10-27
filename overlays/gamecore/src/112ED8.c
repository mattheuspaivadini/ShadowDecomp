/* GAMECORE.XFF @ 0x112ED8 (8 B) - setRotColCheckWormCtrlWork
 * Evidence: `jr $ra` with `ac8500d8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setRotColCheckWormCtrlWork(unsigned char *p, int value) {
    *(int *)(p + 0xd8) = value;
}
