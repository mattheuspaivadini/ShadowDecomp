/* GAMECORE.XFF @ 0x0F8248 (8 B) - setCreateTempAttain
 * Evidence: `jr $ra` with `ac850414` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setCreateTempAttain(unsigned char *p, int value) {
    *(int *)(p + 0x414) = value;
}
