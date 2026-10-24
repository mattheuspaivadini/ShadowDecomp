/* MANAGER.XFF @ 0x0AE360 (8 B) - MakeGeometryPointerGlobalInfo
 * Evidence: `jr $ra` with `ac800030` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void MakeGeometryPointerGlobalInfo(unsigned char *p) {
    *(int *)(p + 0x30) = 0;
}
