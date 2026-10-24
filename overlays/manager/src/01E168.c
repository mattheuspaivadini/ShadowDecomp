/* MANAGER.XFF @ 0x01E168 (8 B) - modelNameByHeader
 * Evidence: `jr $ra` with `8c820070` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int modelNameByHeader(unsigned char *p) {
    return *(int *)(p + 0x70);
}
