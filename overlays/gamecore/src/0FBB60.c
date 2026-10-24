/* GAMECORE.XFF @ 0x0FBB60 (8 B) - setUserPathExMode
 * Evidence: `jr $ra` with `ac853c60` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setUserPathExMode(unsigned char *p, int value) {
    *(int *)(p + 0x3c60) = value;
}
