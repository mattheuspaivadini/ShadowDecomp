/* GAMECORE.XFF @ 0x0F8998 (8 B) - getLastAttainUpdate
 * Evidence: `jr $ra` with `8c820090` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getLastAttainUpdate(unsigned char *p) {
    return *(int *)(p + 0x90);
}
