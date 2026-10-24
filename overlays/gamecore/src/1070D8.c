/* GAMECORE.XFF @ 0x1070D8 (8 B) - getChkColWidth
 * Evidence: `jr $ra` with `c48000cc` in the delay slot.
 * Name is authoritative (GAMECORE.XFF .symtab, STT_FUNC).
 */
float getChkColWidth(unsigned char *p) {
    return *(float *)(p + 0xcc);
}
