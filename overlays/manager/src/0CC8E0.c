/* MANAGER.XFF @ 0x0CC8E0 (8 B) - GetTwoWayLinkNext
 * Evidence: `jr $ra` with `8c820004` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
int GetTwoWayLinkNext(unsigned char *p) {
    return *(int *)(p + 0x4);
}
