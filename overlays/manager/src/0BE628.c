/* MANAGER.XFF @ 0x0BE628 (8 B) - CheckClothChainExist
 * Evidence: `jr $ra` with `80820006` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int CheckClothChainExist(unsigned char *p) {
    return *(signed char *)(p + 0x6);
}
