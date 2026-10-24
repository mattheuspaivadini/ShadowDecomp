/* MANAGER.XFF @ 0x0E1CF8 (8 B) - sheetFileGetSize
 * Evidence: `jr $ra` with `8c820010` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int sheetFileGetSize(unsigned char *p) {
    return *(int *)(p + 0x10);
}
