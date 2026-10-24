/* GAMECORE.XFF @ 0x0F80D0 (8 B) - setStabilizeYPathWork
 * Evidence: `jr $ra` with `ac8500e8` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setStabilizeYPathWork(unsigned char *p, int value) {
    *(int *)(p + 0xe8) = value;
}
