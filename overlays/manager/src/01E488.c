/* MANAGER.XFF @ 0x01E488 (8 B) - modelGetName
 * Evidence: `jr $ra` with `8c820070` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int modelGetName(unsigned char *p) {
    return *(int *)(p + 0x70);
}
