/* GAMECORE.XFF @ 0x099C30 (8 B) - AI_SetSurprisedArea
 * Evidence: `jr $ra` with `e48c0004` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
void AI_SetSurprisedArea(unsigned char *p, float value) {
    *(float *)(p + 0x4) = value;
}
