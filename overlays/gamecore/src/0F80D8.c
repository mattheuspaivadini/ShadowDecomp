/* GAMECORE.XFF @ 0x0F80D8 (8 B) - setAngleStabilizeYPathWork
 * Evidence: `jr $ra` with `ac8500ec` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setAngleStabilizeYPathWork(unsigned char *p, int value) {
    *(int *)(p + 0xec) = value;
}
