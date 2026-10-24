/* GAMECORE.XFF @ 0x0FBBE8 (8 B) - setGPSelectMode
 * Evidence: `jr $ra` with `ac853c78` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void setGPSelectMode(unsigned char *p, int value) {
    *(int *)(p + 0x3c78) = value;
}
