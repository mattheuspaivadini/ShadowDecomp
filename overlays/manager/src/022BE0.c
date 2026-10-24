/* MANAGER.XFF @ 0x022BE0 (8 B) - GetShadowLength
 * Evidence: `jr $ra` with `c4800018` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
float GetShadowLength(unsigned char *p) {
    return *(float *)(p + 0x18);
}
