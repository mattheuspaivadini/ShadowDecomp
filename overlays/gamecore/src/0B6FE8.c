/* GAMECORE.XFF @ 0x0B6FE8 (8 B) - setSObjNodeLock
 * Evidence: `jr $ra` with `ac850054` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setSObjNodeLock(unsigned char *p, int value) {
    *(int *)(p + 0x54) = value;
}
