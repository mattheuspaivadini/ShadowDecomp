/* MANAGER.XFF @ 0x077EF0 (8 B) - SetLayoutClassCollisionWorkAdr
 * Evidence: `jr $ra` with `ac850174` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetLayoutClassCollisionWorkAdr(unsigned char *p, int value) {
    *(int *)(p + 0x174) = value;
}
