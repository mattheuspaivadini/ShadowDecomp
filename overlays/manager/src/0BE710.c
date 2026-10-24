/* MANAGER.XFF @ 0x0BE710 (8 B) - SetClothSingleFixedChainLeafFixNodeOffset
 * Evidence: `jr $ra` with `a0850071` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetClothSingleFixedChainLeafFixNodeOffset(unsigned char *p, char value) {
    *(char *)(p + 0x71) = value;
}
