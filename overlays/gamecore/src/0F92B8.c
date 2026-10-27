/* GAMECORE.XFF @ 0x0F92B8 (8 B) - resetPassageWork
 * Evidence: `jr $ra` with `ac800380` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void resetPassageWork(unsigned char *p) {
    *(int *)(p + 0x380) = 0;
}
