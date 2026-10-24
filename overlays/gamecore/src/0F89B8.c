/* GAMECORE.XFF @ 0x0F89B8 (8 B) - getNowPassageAreaIdx
 * Evidence: `jr $ra` with `8c820430` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getNowPassageAreaIdx(unsigned char *p) {
    return *(int *)(p + 0x430);
}
