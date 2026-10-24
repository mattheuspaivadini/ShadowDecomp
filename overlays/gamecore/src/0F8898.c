/* GAMECORE.XFF @ 0x0F8898 (8 B) - setAttainModePathWork
 * Evidence: `jr $ra` with `ac8500e0` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setAttainModePathWork(unsigned char *p, int value) {
    *(int *)(p + 0xe0) = value;
}
