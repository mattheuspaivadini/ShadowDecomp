/* GAMECORE.XFF @ 0x0F89B0 (8 B) - getNowPassagePointIdx
 * Evidence: `jr $ra` with `8c82042c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getNowPassagePointIdx(unsigned char *p) {
    return *(int *)(p + 0x42c);
}
