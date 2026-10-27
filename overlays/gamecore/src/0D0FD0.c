/* GAMECORE.XFF @ 0x0D0FD0 (8 B) - getSprLogWorkSize
 * Evidence: `jr $ra` with `24022d00` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getSprLogWorkSize(void) {
    return 0x2d00;
}
