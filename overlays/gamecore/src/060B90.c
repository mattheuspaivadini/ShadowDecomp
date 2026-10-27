/* GAMECORE.XFF @ 0x060B90 (8 B) - ColCont2_EventAttrReset
 * Evidence: `jr $ra` with `fc800008` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void ColCont2_EventAttrReset(unsigned char *p) {
    *(unsigned long *)(p + 0x8) = 0;
}
