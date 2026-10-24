/* GAMECORE.XFF @ 0x0F89A0 (8 B) - getLastPassagePointIdx
 * Evidence: `jr $ra` with `8c820424` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getLastPassagePointIdx(unsigned char *p) {
    return *(int *)(p + 0x424);
}
