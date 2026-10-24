/* MANAGER.XFF @ 0x072258 (8 B) - SetFogColAvailableFlag
 * Evidence: `jr $ra` with `ac850080` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetFogColAvailableFlag(unsigned char *p, int value) {
    *(int *)(p + 0x80) = value;
}
