/* MANAGER.XFF @ 0x062B50 (8 B) - charrootdyn_resetEdgeUpperPlaneInfoFlag
 * Evidence: `jr $ra` with `ac800020` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void charrootdyn_resetEdgeUpperPlaneInfoFlag(unsigned char *p) {
    *(int *)(p + 0x20) = 0;
}
