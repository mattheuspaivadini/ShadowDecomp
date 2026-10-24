/* GAMECORE.XFF @ 0x0D0FE8 (8 B) - getSprLogStatusSize
 * Evidence: `jr $ra` with `2402000c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
int getSprLogStatusSize(void) {
    return 0xc;
}
