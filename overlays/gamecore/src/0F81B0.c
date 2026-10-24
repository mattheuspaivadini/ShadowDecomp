/* GAMECORE.XFF @ 0x0F81B0 (8 B) - setUserPathMode
 * Evidence: `jr $ra` with `ac8503a0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setUserPathMode(unsigned char *p, int value) {
    *(int *)(p + 0x3a0) = value;
}
