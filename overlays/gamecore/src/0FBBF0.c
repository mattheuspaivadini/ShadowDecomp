/* GAMECORE.XFF @ 0x0FBBF0 (8 B) - setForceInitPathEx
 * Evidence: `jr $ra` with `ac853c7c` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setForceInitPathEx(unsigned char *p, int value) {
    *(int *)(p + 0x3c7c) = value;
}
