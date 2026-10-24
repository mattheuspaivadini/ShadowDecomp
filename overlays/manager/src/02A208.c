/* MANAGER.XFF @ 0x02A208 (8 B) - spriteSetFade
 * Evidence: `jr $ra` with `e48c0008` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void spriteSetFade(unsigned char *p, float value) {
    *(float *)(p + 0x8) = value;
}
