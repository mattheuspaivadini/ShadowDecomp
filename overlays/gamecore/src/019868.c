/* GAMECORE.XFF @ 0x019868 (8 B) - gStatSetGObjAdrs
 * Evidence: `jr $ra` with `ac85000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void gStatSetGObjAdrs(unsigned char *p, int value) {
    *(int *)(p + 0xc) = value;
}
