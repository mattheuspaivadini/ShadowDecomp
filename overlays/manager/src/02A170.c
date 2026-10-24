/* MANAGER.XFF @ 0x02A170 (8 B) - spriteSetRotation
 * Evidence: `jr $ra` with `e48c0048` in the delay slot.
 * Name is authoritative (MANAGER.XFF .symtab, STT_FUNC).
 */
void spriteSetRotation(unsigned char *p, float value) {
    *(float *)(p + 0x48) = value;
}
