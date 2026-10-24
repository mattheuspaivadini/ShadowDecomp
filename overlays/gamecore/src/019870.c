/* GAMECORE.XFF @ 0x019870 (8 B) - gStatGetGObjAdrs
 * Evidence: `jr $ra` with `8c82000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int gStatGetGObjAdrs(unsigned char *p) {
    return *(int *)(p + 0xc);
}
