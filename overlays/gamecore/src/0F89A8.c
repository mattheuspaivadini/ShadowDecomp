/* GAMECORE.XFF @ 0x0F89A8 (8 B) - getLastPassageAreaIdx
 * Evidence: `jr $ra` with `8c820428` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getLastPassageAreaIdx(unsigned char *p) {
    return *(int *)(p + 0x428);
}
