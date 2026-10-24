/* MANAGER.XFF @ 0x0AE838 (8 B) - FlushCollisionEdgeLinkDBVWallFinder
 * Evidence: `jr $ra` with `ac800020` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void FlushCollisionEdgeLinkDBVWallFinder(unsigned char *p) {
    *(int *)(p + 0x20) = 0;
}
