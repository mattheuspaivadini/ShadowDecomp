/* MANAGER.XFF @ 0x0CC900 (8 B) - GetTwoWayLinkData
 * Evidence: `jr $ra` with `8c820008` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int GetTwoWayLinkData(unsigned char *p) {
    return *(int *)(p + 0x8);
}
