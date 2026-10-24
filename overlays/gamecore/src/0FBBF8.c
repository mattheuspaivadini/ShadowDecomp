/* GAMECORE.XFF @ 0x0FBBF8 (8 B) - setGpReferencePathEx
 * Evidence: `jr $ra` with `ac853c80` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGpReferencePathEx(unsigned char *p, int value) {
    *(int *)(p + 0x3c80) = value;
}
