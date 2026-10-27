/* GAMECORE.XFF @ 0x099C00 (8 B) - AI_SetAnimalWorkParam
 * Evidence: `jr $ra` with `ac850010` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void AI_SetAnimalWorkParam(unsigned char *p, int value) {
    *(int *)(p + 0x10) = value;
}
