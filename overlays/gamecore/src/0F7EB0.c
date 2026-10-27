/* GAMECORE.XFF @ 0x0F7EB0 (8 B) - getPassageNum
 * Evidence: `jr $ra` with `8c820380` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getPassageNum(unsigned char *p) {
    return *(int *)(p + 0x380);
}
