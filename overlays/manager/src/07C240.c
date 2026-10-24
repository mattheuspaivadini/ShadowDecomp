/* MANAGER.XFF @ 0x07C240 (8 B) - SetGameLightAvailable
 * Evidence: `jr $ra` with `a0850039` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void SetGameLightAvailable(unsigned char *p, char value) {
    *(char *)(p + 0x39) = value;
}
